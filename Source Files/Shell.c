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
	char buffer[256];
	char *arg = NULL;
	char *command = NULL;

	while(1)
	{
		GetCurrentDirectory(sizeof(buffer),buffer);
		printf("\n%s> ",buffer);

		memset(buffer,0,sizeof(buffer));
		gets(buffer);

		command = strtok(buffer," ");
		arg = strtok(NULL,"");
		
		if(!strcmp(command," "))
			continue;
		else if(!strcmp(command,"print"))
			{
				printf(">>Entered String is :\n\t|%s\n",arg);
				arg = NULL;
			}
		else if(!strcmp(command,"date"))
			{
				Show_Date ();
			}
		else if(!strcmp(command,"time"))
			{
				Show_Time ();
			}
		else if(!strcmp(command,"--version"))
			{
				Show_Version ();
			}
		else if(!strcmp(command,"dir"))
			{
				Show_List_Of_Files ();
			}
		else if(!strcmp(command,"cls"))
			{
				Clear_Console ();
			}
		else if(!strcmp(command,"cd"))
			{
				if(arg)
				{
					if(!strcmp(arg,".."))
						Go_To_Parent_Directory ();
					else
						Change_Directory (arg);
				}
				arg = NULL;
			}
		else if(!strcmp(command,"pushd"))
			{
				if(arg)
				{
					Push_Directory(arg);
				}
			}
		else if(!strcmp(command,"help"))
			{
				Help ();
			}
		else if(!strcmp(command,"exit"))
			return ;
		else
			printf("\"%s\" : No such internal or extrenal command.\n",buffer);	
	}
}