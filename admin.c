#include<stdio.h>
#include<stdlib.h>

typedef struct login{
	char uname[25], pw[25];
	int role;
}creds;

int main()
{
	int choice;
	creds details;
	FILE *fptr;
	printf("Admin\n");
	fptr=fopen("activeUser.txt","rb");
	rewind(fptr);
	fread(&details,sizeof(creds),1,fptr);
	
	err:
	printf("Menu:\n");
	printf("1. Statement\n");
	printf("2. Add Purchase\n");
	printf("3. Add Sales\n");
	printf("4. Check Credit\n");
	printf("5. Check Inventory\n");
	printf("6. Logout\n");
	printf("1/2/3/4/5/6? ");
	scanf("%d",&choice);
	
	switch(choice)
	{
		case 1:
			system("statement");
			break;
		
		case 2:
			system("addPurchase");
			break;
			
		case 3:
			
	}
	
}