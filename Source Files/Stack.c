#include<stdio.h>
#include<malloc.h>

struct Node
{
	struct Node *pPrev;
	char * pPath;
	struct Node *pNext;
};

static struct Node * pStack = NULL;

void Push_Path(char *pPath)
{
	struct Node *pNewNode = NULL;

	pNewNode = (struct Node *)malloc(sizeof(struct Node));

	if(NULL == pNewNode)
	{
		printf("memory allocation faild.");
		return ;
	}

	pNewNode->pPath = malloc(strlen(pPath) + 1);

    if (pNewNode->pPath == NULL)
    {
        free(pNewNode);
        return;
    }

    strcpy(pNewNode->pPath, pPath);
	pNewNode->pNext = NULL;
	pNewNode->pPrev = pStack;

	if(pStack != NULL)
		pStack->pNext = pNewNode;
	
	pStack = pNewNode;
}

char * Pop_Path()
{	
	char *pPath = NULL;

	if(NULL == pStack)
		return NULL;

	if(NULL == pStack->pPrev)
	{
		pPath = pStack->pPath;
		free(pStack);
		pStack = NULL;
	}
	else
	{
		pStack = pStack->pPrev;
		pStack->pNext->pPrev = NULL;

		pPath = pStack->pNext->pPath;

		pStack->pNext->pPath = NULL;
		free(pStack->pNext);

		pStack->pNext = NULL;
	}

	return(pPath);
}
