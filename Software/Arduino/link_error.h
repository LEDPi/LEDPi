#ifndef _H_LINK_ERROR_
#define _H_LINK_ERROR_

#ifdef __cplusplus
extern "C" {
#endif

/* only one prcess support, as this is OS dependant */
#define __MYPID 1

int _exit (int);

int _kill (int pid, int sig)
{
	if(pid == __MYPID)
		_exit(sig);
	
	return 0;
}

/*
* getpid -- only one process, so just return 1.
*/
int	_getpid ()
{
	return __MYPID;
}

#ifdef __cplusplus
}
#endif

#endif