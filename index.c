#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct login{
	char uname[25], pw[25];
	int role;
}creds;

creds *details;

void admin();
void client();

int main()
{
	FILE *fptr;
	creds auth;
	int no=1, readLoop=0, newSize=1; //variable for reading data from database
	int loggedin=0; //checks if loggedin
	int choice, index; 
	
	
	details=(creds *)calloc(no,sizeof(creds));
	fptr=fopen("user.txt","ab+");
	
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
						auth.role=details[i].role;
						loggedin=1;
					}
				}
				break;
				
			case 2:
				fclose(fptr);
				system("signup");
				fptr=fopen("user.txt","ab+");
				loggedin=1;
				break;
				
			case 3:
				system("checkData");
				goto err;
				break;
				
			case 4:
				exit(0);
				
			default:
				goto err;	
		}	
	}
	
	if(auth.role==0)
		admin();
	else
		client();	
		
	fclose(fptr);	
	free(details);
}

void admin()
{
	printf("Admin");
}

void client()
{
	printf("Client");
}