#include "main.h"
void main(int argc, char**argv) { 
    
	//InitializeWindow();
	if(graphic_run())
	{
		printf("The shit is runnging \n");
	}

	char tmp;
	while(true)
	{	
		printf("Please enter something \n");
		scanf("%c", &tmp);
		if(tmp == 'e') exit(0);
	}
	
}
