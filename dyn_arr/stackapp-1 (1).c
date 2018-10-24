/*	stack.c: Stack application. */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "dynArray.h"


/* ***************************************************************
Using stack to check for unbalanced parentheses.
***************************************************************** */

/* Returns the next character of the string, once reaches end return '0' (zero)
	param: 	s pointer to a string 	
	pre: s is not null		
*/
char nextChar(char* s)
{
	static int i = -1;	
	char c;
	++i;	
	c = *(s+i);			
	if ( c == '\0' )
		return '\0';	
	else 
		return c;
}

/* Checks whether the (), {}, and [] are balanced or not
	param: 	s pointer to a string 	
	pre: s is not null	
	post:	
*/
int isBalanced(char* s)
{
	/* FIXME: You will write this function */	
	assert(s != NULL);
	struct DynArr *balanceStack = newDynArr(10);
	
	char checkNext;


	while ((checkNext = nextChar(s)) != '\0') 
	{
		if (checkNext == '{')
		{
			pushDynArr(balanceStack, '}');
		} else if ( checkNext == '(') 
		{
			pushDynArr(balanceStack, ')');
		} else if (checkNext == '[') 
		{
			pushDynArr(balanceStack, ']');
		} else if ((checkNext == ']') || (checkNext == '}') || (checkNext == ')'))
		{
			if ((isEmptyDynArr(balanceStack)) || (checkNext != topDynArr(balanceStack)))
			{
				deleteDynArr(balanceStack);
				return 0;
			}
			popDynArr(balanceStack);
		}
		/*
		else if (checkNext == topDynArr(balanceStack))
		{
			popDynArr(balanceStack);
		} 
		*/
			
	}

	if (!isEmptyDynArr(balanceStack)) 
	{
		deleteDynArr(balanceStack);
		return 0;
	} else {
		deleteDynArr(balanceStack);
		return 1;
	}	
	return 0;
}

int main(int argc, char* argv[]){
	
	//char* s=argv[1];	
	char s[] = "({abcd)}";


	int res;


	printf("Assignment 2\n");

	res = isBalanced(s);


	if (res)
		printf("The string %s is balanced\n",s);
	else 
		printf("The string %s is not balanced\n",s);
	
	return 0;	
}

