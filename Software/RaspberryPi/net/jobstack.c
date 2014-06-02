#include "net/jobstack.h"

///////////////////////////////////////////////////////////////////////////////
// module private variables

static bool jobstack_initialized = false;
static pthread_t jobstack_thread;
static bool thread_running = false;
static pthread_mutex_t thread_lock = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t thread_cond = PTHREAD_COND_INITIALIZER;
static p_ll_list_t pjobstack_list;

///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//private function declaration

///////////////////////////////////////////////////////////////////////////////
// If there are job on the job stack they will be executed by the FIFO order.
// If there is no job on the stack to execute the thread will fall asleep.
// This method has the correct syntax to be used as thread entry point
//
// PARA:
//	void * unnamed: needed to match the thread entry point method signature
//			but is not used. Passed data will be ignored.
//	return value:	is also not used, function will not return anything.
///////////////////////////////////////////////////////////////////////////////
void *jobstack_run_thread(void *);

///////////////////////////////////////////////////////////////////////////////
//Pauses the the jobstack thread
///////////////////////////////////////////////////////////////////////////////
void jobstack_pause_thread();

///////////////////////////////////////////////////////////////////////////////
//Resumes a the the paused jobstack the thread.
//Sends a condition signal.
///////////////////////////////////////////////////////////////////////////////
void jobstack_resume_thread();

///////////////////////////////////////////////////////////////////////////////
// Excute job and calls the necessary msg_handler function
//
// PARA:
//		job: the job that has to be executed
///////////////////////////////////////////////////////////////////////////////
void jobstack_executejob(pjobstackjob_t job);

///////////////////////////////////////////////////////////////////////////////
// Cleanup a job an frees used memory
//
// PARA:
//		job: the job that has to be cleaned up 
///////////////////////////////////////////////////////////////////////////////
void jobstack_cleanupjob(void *job);

///////////////////////////////////////////////////////////////////////////////
// public function implementation

bool jobstack_init()
{
	pjobstack_list = ll_create(&jobstack_cleanupjob);
	
	jobstack_initialized = true;
	return true;		
}

void jobstack_run()
{
	if(!jobstack_initialized) return;

	log_debug("Start jobstack thread");
	if(pthread_create(&jobstack_thread, NULL, jobstack_run_thread, NULL) != 0)
	{
		log_error("Unable to create the jobstack thread");
		return;
	}
}

void jobstack_pause_thread()
{
	pthread_mutex_lock(&thread_lock);
	thread_running = false;
	pthread_mutex_unlock(&thread_lock);
}

void jobstack_resume_thread()
{
	pthread_mutex_lock(&thread_lock);
	thread_running = true;
	pthread_cond_signal(&thread_cond);
	pthread_mutex_unlock(&thread_lock);
}

void jobstack_deinit()
{
	if(!jobstack_initialized) return;
	
	pthread_cancel(jobstack_thread);
	ll_delete(pjobstack_list);
}

void jobstack_addjob(netsenderinfo_t senderinfo, uint16_t fc, uint16_t len, uint8_t *data, void (*function) (void*,uint16_t, uint16_t, uint8_t*))
{
	//Proof that jobstack not become to big
	if(pjobstack_list->Size > JOBSTACK_SIZE)
	{
		log_error("Jobstack is full");
		ll_first(pjobstack_list);
		if(ll_next(pjobstack_list))
		{
			//remove oldest job
			ll_remove(pjobstack_list);
		}
	} 

	//Build new job
	pjobstackjob_t pjob = (pjobstackjob_t) malloc(sizeof(jobstackjob_t));
	pjob->senderinfo = senderinfo;
	pjob->fc = fc;
	pjob->len = len;
	pjob->data = data;
	pjob->function = function;

	//Add job to list

	ll_append(pjobstack_list,(void *)pjob);

	//Resume thread if stopped
	if(thread_running == false)
	{
		jobstack_resume_thread();
	}
}

///////////////////////////////////////////////////////////////////////////////
// private function implementation

void *jobstack_run_thread(void *)
{
	log_debug("Jobstack function is running");

	while(true)
	{
		ll_first(pjobstack_list);
		if(ll_next(pjobstack_list))
		{
			//execute a job
			jobstack_executejob((pjobstackjob_t)ll_get(pjobstack_list));
			ll_remove(pjobstack_list);
		}
		else
		{
			//pause thread
			jobstack_pause_thread();

			pthread_mutex_lock(&thread_lock);
			while(thread_running == false)
			{
				pthread_cond_wait(&thread_cond, &thread_lock);
			}
			pthread_mutex_unlock(&thread_lock);
		}		
	}
}

void jobstack_executejob(pjobstackjob_t job)
{
	(job->function)((void *) &job->senderinfo,job->fc,job->len,job->data);
}

void jobstack_cleanupjob(void  *pjob)
{
	pjobstackjob_t job = (pjobstackjob_t) pjob;
	free(job->data);
	free(job);
}
