#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>

typedef struct login{
	char uname[25], pw[25];
	int role;
}creds;

creds *details;

void admin();
void client();

void main()
{
	system("cls");
	FILE *fptr;//file pointer for user database
	FILE *activeUser;//file pointer for activeUser.txt
	creds auth;
	int no=1, readLoop=0, newSize=1; //variable for reading data from database
	int loggedin=0; //checks if loggedin
	int choice, index; 
	
	
	details=(creds *)calloc(no,sizeof(creds));
	fptr=fopen("user.txt","ab+");
	activeUser=fopen("activeUser.txt","wb");//saves the data of the active user
	
	if(loggedin==0)
	{
		err:
		printf("Menu:\n");
		printf("1. Log In\n2. Sign Up\n3. Check Data\n4. Exit");
		printf("\n1/2/3/4?: ");
		scanf("%d",&choice);
		fflush(stdin);
		switch(choice)
		{
			case 1:
				system("cls");
				printf("Enter Log In Details:\n");
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
						fwrite(&auth,sizeof(creds),1,activeUser);//saves the data of the active user
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
				break;
				
			default:
				goto err;
				break;	
		}	
	}
	if(loggedin==1)
	{
		if(auth.role==0)
		{
			fclose(fptr);
			fclose(activeUser);
			admin();
		}
	}
	
	else
	{
		printf("Login Error\n");
		char ent;
		printf("Press Enter");
		scanf("%c",&ent);
		system("cls");
		goto err;
	}
	
	
	getch();
	fclose(fptr);	
	free(details);
}

void admin()
{
	system("admin");
}