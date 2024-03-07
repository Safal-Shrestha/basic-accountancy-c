#include<stdio.h>
#include<stdlib.h>

typedef struct login{
	char uname[25], pw[25];
}creds;

creds *details;

int main()
{
	FILE *fptr;
	creds auth;
	int no=1, readLoop=0, newSize=1;
	
	details=(creds *)calloc(no,sizeof(creds));	
	
	fptr=fopen("user.txt","ab+");
	
	rewind(fptr);
	
	while(fread((details+readLoop), sizeof(creds),1,fptr)==1)
	{
		newSize++;
		details=(creds *)realloc(details, (newSize)*sizeof(creds));
		readLoop++;
	}
	
	for(int i=0; i<newSize-1;i++)
	{
		printf("%s\n%s\n\n",details[i].uname,details[i].pw);
	}

	
	fflush(fptr);
	fclose(fptr);	
	free(details);
}