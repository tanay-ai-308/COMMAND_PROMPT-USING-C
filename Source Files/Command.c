#include<stdio.h>
#include<time.h>
#include<string.h>
#include<windows.h>

#include"Commands.h"

#define MAX_PATH 260

void Get_Parent_Directory(char *);

void Show_Date (void)
{
	time_t tTime;
	struct tm* ptr = NULL;

	tTime = time(NULL);
	ptr = localtime(&tTime);
	printf(">> %d-%d-%d\n",ptr->tm_mday,(ptr->tm_mon)+1,1900+(ptr->tm_year));
}

void Show_Time (void)
{
	time_t tTime;
	struct tm* ptr = NULL;

	tTime = time(NULL);
	ptr = localtime(&tTime);
	printf(">> %d:%d:%d\n",ptr->tm_hour,ptr->tm_min,ptr->tm_sec );
}

void Show_Version (void)
{
	printf("%s\n",VERSION);
}

void Show_List_Of_Files (void)
{
	HANDLE hFind;
	WIN32_FIND_DATA fd;
	
	hFind = FindFirstFile("*",&fd);

	if(hFind != INVALID_HANDLE_VALUE)
	{
		do
		{
			printf("\t%-30s%-10d kb\n",fd.cFileName,fd.nFileSizeLow/1024);
		}while(FindNextFile(hFind,&fd));

		FindClose(hFind);
	}
}

void Clear_Console(void)
{
	HANDLE hConsole;
	DWORD bufferSize;
	CONSOLE_SCREEN_BUFFER_INFO BufferInfo;
	COORD dwCoord = {0,0};

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsole,&BufferInfo);

	bufferSize = (BufferInfo.dwSize.X) * (BufferInfo.dwSize.Y);
	
	FillConsoleOutputCharacter(hConsole,' ',bufferSize,dwCoord,&bufferSize);
	SetConsoleCursorPosition(hConsole,dwCoord); 
}

void Change_Directory(char *lpPath)
{
	DWORD Error;
	HANDLE hFind;
	WIN32_FIND_DATA fd;
	char * pDirectory = NULL;

	pDirectory = strtok(lpPath,"\\");

	while(pDirectory != NULL)
	{
		hFind = FindFirstFile(pDirectory,&fd);

		if(SetCurrentDirectory(fd.cFileName))
			FindClose(hFind);
		else
		{
			Error = GetLastError();
			switch(Error)
			{
				case ERROR_FILE_NOT_FOUND:
	           		printf("\"%s\" : folder not found.\n", pDirectory);
	           		break;

	   			case ERROR_PATH_NOT_FOUND:
	                printf("\"%s\" : invalid path.\n", pDirectory);
	                break;

	            default:
	                printf("\"%s\" the system cannot find the path specified.\n",pDirectory);
			}
			break;
		}
		pDirectory = strtok(NULL,"\\");
	}
}
void Go_To_Parent_Directory(void)
{
	char lpPath[MAX_PATH];

	GetCurrentDirectory(MAX_PATH,lpPath);

	Get_Parent_Directory(lpPath);
	
	SetCurrentDirectory(lpPath);
}

void Get_Parent_Directory(char *plpPath)
{
	char * pSlash = NULL;

	while(*plpPath != '\0')
	{
		plpPath++;

		if(*plpPath == '\\')
			pSlash = plpPath;
	}

	plpPath = pSlash;
	(*plpPath) = '\0';
}

void Help (void)
{
	printf("- print ----   - Print the given string.\n\n- date         - Show today's date.\n\n- time         - Show current time.\n\n- --version    - Show current Version of the shell.\n\n- dir          - Show list of files and folder present in current directory.\n\n- cls          - Clear the console.\n\n- cd           - Change Directory.\n	cd ..	 	 - To move one step backward in shell.\n	cd ----		 - Changes Directory to given directory.\n\n- help         - Show list of commands can be used on present shell.\n\n- exit         - Ends the Shell process.\n");
}