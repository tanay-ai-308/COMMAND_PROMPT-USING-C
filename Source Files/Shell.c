#include<stdio.h>
#include<string.h>
#include<windows.h>

#include"Shell.h"
#include"Commands.h"

void ShellInit(void)
{
	printf("\n#==========================================================\n#\n# - WELLCOME TO Command Prompt [created by Tanay] v %s\n# - Date of Creation - 09/06/2026.\n# - NOTE :- To see list of all commands, give command 'help'.\n#\n#==========================================================\n\n",VERSION);
}

void StartShell(void)
{
	char *p = NULL;
	char buffer[256];
	char *command = NULL;

	while(1)
	{
		GetCurrentDirectory(sizeof(buffer),buffer);
		printf("\n%s> ",buffer);

		memset(buffer,0,sizeof(buffer));
		gets(buffer);

		command = strtok(buffer," ");
		
		if(!strcmp(command," "))
			continue;
		else if(!strcmp(command,"print"))
			{
				p = &buffer[6];
				printf(">>Entered String is :\n\t|%s\n",p);
			}
		else if(!strcmp(command,"date"))
			{
				Date ();
			}
		else if(!strcmp(command,"time"))
			{
				Time ();
			}
		else if(!strcmp(command,"--version"))
			{
				Version ();
			}
		else if(!strcmp(command,"dir"))
			{
				Dir ();
			}
		else if(!strcmp(command,"help"))
			{
				Help ();
			}
		else if(!strcmp(command,"exit"))
			return ;
		else
			printf("\"%s\" : Command not found.\n",buffer);	
	}
}