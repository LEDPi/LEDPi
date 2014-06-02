#include "LUtil.h"

GLfloat gProjectionScale = 1.f;

bool initGL()
{
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glOrtho( 0.0, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0, 1.0, -1.0 );

    //Initialize Modelview Matrix
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    //Initialize clear color
    glClearColor( 1.f, 1.f, 1.f, 1.f );

    //Check for error
    GLenum error = glGetError();
    if( error != GL_NO_ERROR )
    {
        printf( "Error initializing OpenGL! %s\n", gluErrorString( error ) );
        return false;
    }

    return true;
}

void render()
{
    //Clear color buffer
    glClear( GL_COLOR_BUFFER_BIT );

    //Reset modelview matrix
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    //Move to center of the screen
    // glTranslatef( SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f, 0.f );

         //RYGB Mix
        glBegin( GL_QUADS );

            for(int i=0 ; i< SCREEN_WIDTH-55 ; i+=55)
            {
                for(int j=0 ; j<SCREEN_HEIGHT-55 ; j+=55)
                {
                    glColor3f( ((double) rand() / (RAND_MAX)), ((double) rand() / (RAND_MAX)), ((double) rand() / (RAND_MAX)) ); glVertex2f(    i,   j );
                    glColor3f( ((double) rand() / (RAND_MAX)), ((double) rand() / (RAND_MAX)), ((double) rand() / (RAND_MAX)) ); glVertex2f( i+50,   j );
                    glColor3f( ((double) rand() / (RAND_MAX)), ((double) rand() / (RAND_MAX)), ((double) rand() / (RAND_MAX)) ); glVertex2f( i+50, j+50);
                    glColor3f( ((double) rand() / (RAND_MAX)), ((double) rand() / (RAND_MAX)), ((double) rand() / (RAND_MAX)) ); glVertex2f(    i, j+50 );
                }
            }

        glEnd();

    glutSwapBuffers();
}
