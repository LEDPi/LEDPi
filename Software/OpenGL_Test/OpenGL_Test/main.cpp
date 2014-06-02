#include "LUtil.h"

void runMainLoop( int val );

int main( int argc, char* args[] )
{
    //Initialize FreeGLUT
    glutInit( &argc, args );

    //Create OpenGL 2.1 context
    glutInitContextVersion( 2, 1 );

    //Create Double Buffered Window
    glutInitDisplayMode( GLUT_DOUBLE );
    glutInitWindowSize( SCREEN_WIDTH, SCREEN_HEIGHT );
    glutCreateWindow( "OpenGL" );

    //Do post window/context creation initialization
    if( !initGL() )
    {
        printf( "Unable to initialize graphics library!\n" );
        return 1;
    }

    glutDisplayFunc( render );
    glutTimerFunc( 500, runMainLoop, 0 );

    glutMainLoop();

    return 0;
}

void runMainLoop( int val )
{
    render();

    //Run frame one more time
    glutTimerFunc( 500, runMainLoop, val );
}
