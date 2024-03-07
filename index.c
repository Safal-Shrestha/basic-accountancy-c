#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct login{
	char uname[25], pw[25];
}creds;

creds *details;

void authentication(creds,int);

int main()
{
	FILE *fptr;
	creds auth;
	int no=1, readLoop=0, newSize=1, choice, loggedin=0;
	
	details=(creds *)calloc(no,sizeof(creds));
	
	if(loggedin==0)
	{
		printf("%d\n",loggedin);
		err:
		printf("Menu:\n");
		printf("1. Log In\n2. Sign Up\n3.Check Data\n4. Exit");
		printf("\n1/2/3/4?: ");
		scanf("%d",&choice);
		fflush(stdin);
		switch(choice)
		{
			case 1:
				printf("Username: ");
				gets(auth.uname);	
				printf("Password: ");
				gets(auth.pw);	
				
				fptr=fopen("user.txt","ab+");
				
				rewind(fptr);
				while(fread((details+readLoop), sizeof(creds),1,fptr)==1)
				{
					newSize++;
					details=(creds *)realloc(details, (newSize)*sizeof(creds));
					readLoop++;
				}
				
				for(int i=0;i<newSize;i++)
				{
					if(strcmp(auth.uname,details[i].uname)==0&&strcmp(auth.pw,details[i].pw)==0)
					{
						loggedin=1;
					}
				}
				break;
				
			case 2:
				system("signup");
				loggedin=1;
				break;
				
			case 3:
				system("checkData");
				break;
				
			case 4:
				exit(0);
				
			default:
				goto err;	
		}
		
	}
	
		
	fclose(fptr);	
	free(details);
}