#include<stdio.h>
#include<time.h>
#include<string.h>
#include<windows.h>

#include"Commands.h"

void Date (void)
{
	time_t tTime;
	struct tm* ptr = NULL;

	tTime = time(NULL);
	ptr = localtime(&tTime);
	printf(">> %d-%d-%d\n",ptr->tm_mday,(ptr->tm_mon)+1,1900+(ptr->tm_year));
}

void Time (void)
{
	time_t tTime;
	struct tm* ptr = NULL;

	tTime = time(NULL);
	ptr = localtime(&tTime);
	printf(">> %d:%d:%d\n",ptr->tm_hour,ptr->tm_min,ptr->tm_sec);
}

void Version (void)
{
	printf("%s\n",VERSION);
}

void Dir (void)
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

void Help (void)
{
	printf("- print.\n- date.\n- time.\n- --version.\n- dir.\n- help.\n- exit.\n");
}