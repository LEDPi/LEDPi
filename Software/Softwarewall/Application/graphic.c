#include "graphic.h"

///////////////////////////////////////////////////////////////////////////////
//Globale private Variables graphic.c
///////////////////////////////////////////////////////////////////////////////
GLfloat Vertices[NUM_VALUES]; 
GLfloat Colors[NUM_VALUES];

int CurrentWidth = 800;
int CurrentHeight = 600;
int WindowHandle = 0;
unsigned FrameCount = 0;

static pthread_t graphic_thread;


GLuint
	VertexShaderId,
	FragmentShaderId,
	ProgramId,
	VaoId,
	VboId,
	ColorBufferId;

const GLchar* VertexShader =
{
	"#version 400\n"\

	"layout(location=0) in vec4 in_Position;\n"\
	"layout(location=1) in vec4 in_Color;\n"\
	"out vec4 ex_Color;\n"\

	"void main(void)\n"\
	"{\n"\
	"	gl_Position = in_Position;\n"\
	"	ex_Color = in_Color;\n"\
	"}\n"
};

const GLchar* FragmentShader =
{
	"#version 400\n"\

	"in vec4 ex_Color;\n"\
	"out vec4 out_Color;\n"\

	"void main(void)\n"\
	"{\n"\
	"	out_Color = ex_Color;\n"\
	"}\n"
};

///////////////////////////////////////////////////////////////////////////////
//Private Function Declarartions
///////////////////////////////////////////////////////////////////////////////

//Initial Functions
void InitWindow();
void CreateVBO(void);
void CreateShaders(void);
void InitializeQuads();

//Callback Functions
void ResizeFunction(int, int);
void RenderFunction(void);
void IdleFunction(void);
void TimerFunction(int);
void UpdateFunction(int);
void KeyboardFunction(unsigned char Key, int X, int Y);
void Cleanup(void);

//Deinit Functions
void DestroyVBO(void);
void DestroyShaders(void);

//Helper Functions
void *graphic_run_thread(void*);
float randomFloat();
void setNewRandomColors();

///////////////////////////////////////////////////////////////////////////////
//Public Function Implementation
///////////////////////////////////////////////////////////////////////////////
bool graphic_run()
{
	if(pthread_create(&graphic_thread, NULL, graphic_run_thread, NULL) != 0)
	{
		fprintf(stdout,"ERROR: Unable to create the graphic thread\n");
		return;
	}
	
}

void InitializeWindow()
{
	GLenum GlewInitResult;

	InitWindow();
	
	glewExperimental = GL_TRUE;
	GlewInitResult = glewInit();

	if (GLEW_OK != GlewInitResult) {
		fprintf(
			stderr,
			"ERROR: %s\n",
			glewGetErrorString(GlewInitResult)
		);
		exit(EXIT_FAILURE);
	}
	
	fprintf(
		stdout,
		"INFO: OpenGL Version: %s\n",
		glGetString(GL_VERSION)
	);

	InitializeQuads();
	CreateShaders();
	CreateVBO();

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glutMainLoop();
	
	exit(EXIT_SUCCESS);
}



///////////////////////////////////////////////////////////////////////////////
//Private Function Implementation
///////////////////////////////////////////////////////////////////////////////

void InitWindow()
{
	int i = 1;
	glutInit(&i, NULL);
	
	glutInitContextVersion(4, 0);
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
	glutInitContextProfile(GLUT_CORE_PROFILE);

	glutSetOption(
		GLUT_ACTION_ON_WINDOW_CLOSE,
		GLUT_ACTION_GLUTMAINLOOP_RETURNS
	);
	
	glutInitWindowSize(CurrentWidth, CurrentHeight);

	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

	WindowHandle = glutCreateWindow(WINDOW_TITLE_PREFIX);

	if(WindowHandle < 1) {
		fprintf(
			stderr,
			"ERROR: Could not create a new rendering window.\n"
		);
		exit(EXIT_FAILURE);
	}
	
	//Register Callback
	glutReshapeFunc(ResizeFunction);
	glutDisplayFunc(RenderFunction);
	glutIdleFunc(IdleFunction);
	glutTimerFunc(0, TimerFunction, 0);
	glutTimerFunc(0, UpdateFunction, 0);
	glutKeyboardFunc(KeyboardFunction);
	glutCloseFunc(Cleanup);
}

void CreateVBO(void)
{
	GLenum ErrorCheckValue = glGetError();
	
	glGenVertexArrays(1, &VaoId);
	glBindVertexArray(VaoId);

	glGenBuffers(1, &VboId);
	glBindBuffer(GL_ARRAY_BUFFER, VboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	
	glGenBuffers(1, &ColorBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, ColorBufferId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Colors), Colors, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	ErrorCheckValue = glGetError();
	if (ErrorCheckValue != GL_NO_ERROR)
	{
		fprintf(
			stderr,
			"ERROR: Could not create a VBO: %s \n",
			gluErrorString(ErrorCheckValue)
		);

		exit(-1);
	}
}

void CreateShaders(void)
{
	GLenum ErrorCheckValue = glGetError();
	
	VertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(VertexShaderId, 1, &VertexShader, NULL);
	glCompileShader(VertexShaderId);

	FragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(FragmentShaderId, 1, &FragmentShader, NULL);
	glCompileShader(FragmentShaderId);

	ProgramId = glCreateProgram();
		glAttachShader(ProgramId, VertexShaderId);
		glAttachShader(ProgramId, FragmentShaderId);
	glLinkProgram(ProgramId);
	glUseProgram(ProgramId);

	ErrorCheckValue = glGetError();
	if (ErrorCheckValue != GL_NO_ERROR)
	{
		fprintf(
			stderr,
			"ERROR: Could not create the shaders: %s \n",
			gluErrorString(ErrorCheckValue)
		);

		exit(-1);
	}
}


void InitializeQuads()
{
	int row = NUM_ROWS;	
	int column = NUM_COLUMNS;
	
	float elWidth  =  2.0/((float)column);
	float elHeigth =  2.0/((float)row);
	int i,j,k;

	for(i=0; i<row; i++)
	{
		for(j=0; j<column; j++)
		{
			float xOffset = ((float)j)*elWidth;
			
			float yOffset = ((float)i)*elHeigth;

			Vertices[24*column*i+24*j+0] = -1.0f+xOffset;
			Vertices[24*column*i+24*j+1] = -1.0f+yOffset+elHeigth;
			Vertices[24*column*i+24*j+2] =  0.0f;
			Vertices[24*column*i+24*j+3] =  1.0f;

			Vertices[24*column*i+24*j+4] = -1.0f+xOffset;
			Vertices[24*column*i+24*j+5] = -1.0f+yOffset;
			Vertices[24*column*i+24*j+6] =  0.0f;
			Vertices[24*column*i+24*j+7] =  1.0f;
	
			Vertices[24*column*i+24*j+8] = -1.0f+xOffset+elWidth;
			Vertices[24*column*i+24*j+9] = -1.0f+yOffset;
			Vertices[24*column*i+24*j+10] = 0.0f;
			Vertices[24*column*i+24*j+11] = 1.0f;

			Vertices[24*column*i+24*j+12] = -1.0f+xOffset;
			Vertices[24*column*i+24*j+13] = -1.0f+yOffset+elHeigth;
			Vertices[24*column*i+24*j+14] =  0.0f;
			Vertices[24*column*i+24*j+15] =  1.0f;

			Vertices[24*column*i+24*j+16] = -1.0f+xOffset+elWidth;
			Vertices[24*column*i+24*j+17] = -1.0f+yOffset+elHeigth;
			Vertices[24*column*i+24*j+18] =  0.0f;
			Vertices[24*column*i+24*j+19] =  1.0f;

			Vertices[24*column*i+24*j+20] = -1.0f+xOffset+elWidth;
			Vertices[24*column*i+24*j+21] = -1.0f+yOffset;
			Vertices[24*column*i+24*j+22] =  0.0f;
			Vertices[24*column*i+24*j+23] =  1.0f;	
		}
	}
	
	setNewRandomColors();	
}


void ResizeFunction(int Width, int Height)
{
	CurrentWidth = Width;
	CurrentHeight = Height;
	glViewport(0, 0, CurrentWidth, CurrentHeight);
}

void RenderFunction(void)
{
	++FrameCount;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glDrawArrays(GL_TRIANGLES, 0, NUM_VERTICES);

	glutSwapBuffers();
	glutPostRedisplay();
}

void IdleFunction(void)
{
	glutPostRedisplay();
}

void TimerFunction(int Value)
{
	if (1 == Value) {
		char* TempString = (char*)
			malloc(512 + strlen(WINDOW_TITLE_PREFIX));

		sprintf(
			TempString,
			"%s: %d Frames Per Second @ %d x %d",
			WINDOW_TITLE_PREFIX,
			FrameCount * 4,
			CurrentWidth,
			CurrentHeight
		);

		glutSetWindowTitle(TempString);
		free(TempString);
	}
	
	FrameCount = 0;
	glutTimerFunc(250, TimerFunction, 1);
}

void UpdateFunction(int Value)
{
	if(Value ==2)
	{
	  //printf("Update\n");
	  setNewRandomColors();
	  glBufferData(GL_ARRAY_BUFFER, sizeof(Colors), Colors, GL_STATIC_DRAW);
		
	}
	glutTimerFunc(1000,UpdateFunction,2);

}

void KeyboardFunction (unsigned char Key, int X, int Y)
{
	int i = 0; 
	float ch2_red,ch2_green,ch2_blue;
	switch (Key) 
	{
	 	case 'r':
			glBufferData(GL_ARRAY_BUFFER, sizeof(Colors), Colors, GL_STATIC_DRAW);	
	 		break;

	 	case 'g':
			
			glBufferData(GL_ARRAY_BUFFER, sizeof(Colors), Colors, GL_STATIC_DRAW);
			break;

	 	case 'b':
			glBufferData(GL_ARRAY_BUFFER, sizeof(Colors), Colors, GL_STATIC_DRAW);
		 	break;

		case 'n':

			setNewRandomColors();
			glBufferData(GL_ARRAY_BUFFER, sizeof(Colors), Colors, GL_STATIC_DRAW);
		
		 	break;
	}
	
 }

void Cleanup(void)
{
	DestroyShaders();
	DestroyVBO();
}

void DestroyVBO(void)
{
	GLenum ErrorCheckValue = glGetError();

	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glDeleteBuffers(1, &ColorBufferId);
	glDeleteBuffers(1, &VboId);

	glBindVertexArray(0);
	glDeleteVertexArrays(1, &VaoId);

	ErrorCheckValue = glGetError();
	if (ErrorCheckValue != GL_NO_ERROR)
	{
		fprintf(
			stderr,
			"ERROR: Could not destroy the VBO: %s \n",
			gluErrorString(ErrorCheckValue)
		);

		exit(-1);
	}
}

void DestroyShaders(void)
{
	GLenum ErrorCheckValue = glGetError();

	glUseProgram(0);

	glDetachShader(ProgramId, VertexShaderId);
	glDetachShader(ProgramId, FragmentShaderId);

	glDeleteShader(FragmentShaderId);
	glDeleteShader(VertexShaderId);

	glDeleteProgram(ProgramId);

	ErrorCheckValue = glGetError();
	if (ErrorCheckValue != GL_NO_ERROR)
	{
		fprintf(
			stderr,
			"ERROR: Could not destroy the shaders: %s \n",
			gluErrorString(ErrorCheckValue)
		);

		exit(-1);
	}
}

void *graphic_run_thread(void *unused)
{
	printf("Now we start the thread\n");
	InitializeWindow();
}


float randomFloat()
{
	float x = ((float)rand()/(float)(RAND_MAX))*1;
}

void setNewRandomColors()
{
	int i,j,k;
	int row = NUM_ROWS;
	int column = NUM_COLUMNS;
	
	for(i=0; i<row; i++)
	{
		for(j=0; j<column; j++)
		{
			float CLred = randomFloat();
			float CLgreen = randomFloat();
			float CLblue = randomFloat();

			for(k=0; k<6; k++)
			{
				Colors[6*4*column*i+6*4*j+4*k+0]=CLred;
				Colors[6*4*column*i+6*4*j+4*k+1]=CLgreen;
				Colors[6*4*column*i+6*4*j+4*k+2]=CLblue;
				Colors[6*4*column*i+6*4*j+4*k+3]=1.0f;
			}
		}
	}
}
