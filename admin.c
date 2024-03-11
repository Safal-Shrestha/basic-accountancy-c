#include<stdio.h>
#include<stdlib.h>

typedef struct login{
	char uname[25], pw[25];
	int role;
}creds;

typedef struct {
	int id;
	char name[40],
}statement;

typedef struct{
	int p_id,p_qnty,p_rate,p_total;
	char p_name[40],p_dealer[40],p_message[100],p_mode,type;
}purchase;

typedef struct{
	int s_id,s_qnty,s_rate,s_total;
	char s_name[40],s_cust[40],s_message[100],s_mode,type;
}sales;

void stmt();
void addPurchase();
void addSales();
void checkCredit();
void checkInventory();

int main()
{
	system("cls");
	int choice;
	creds details;
	FILE *fptr;
	fptr=fopen("activeUser.txt","rb");
	rewind(fptr);
	fread(&details,sizeof(creds),1,fptr);
	if((details.uname)==NULL)
	{
		exit(0);
	}
	printf("Admin\n");
	
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
	fflush(stdin);
	
	switch(choice)
	{
		case 1:
			stmt();
			break;
		
		case 2:
			addPurchase();
			break;
			
		case 3:
			addSales();
			break;
		
		case 4:
			checkCredit();
			break;
		
		case 5:
			checkInventory();
			break;
		
		case 6:
			fclose(fptr);
			fptr=fopen("activeUser.txt","wb");
			system("index");
			break;
			
		default:
			system("cls");
			goto err;
			
		goto err;
	}
}

void stmt()
{
	system("cls");
	printf("Statement\n");
	FILE *stmt;
	
	stmt=fopen("statement.txt","rb");
	
}

void addPurchase()
{
	system("cls");
	printf("Add Purchase Information\n");
	FILE *purch;
	FILE *stmt;
	purchase *info;
	int no;
	
	purch=fopen("expenditure.txt","wb");
	stmt=fopen("statement.txt","wb");
	
	printf("Enter Number of Products: ");
	scanf("%d",&no);
	
	info=(purchase *)calloc(no,sizeof(purchase));
	
	for(int i=0;i<no;i++)
	{
		printf("Product Id: ");
		scanf("%d",&info[i].p_id);
		fflush(stdin);
		printf("Product Name: ");
		gets(info[i].p_name);
		printf("Quantity: ");
		scanf("%d",&info[i].p_qnty);
		printf("Rate: ");
		scanf("%d",&info[i].p_rate);
		info[i].p_total=info[i].p_qnty*info[i].p_rate;
		fflush(stdin);
		printf("Supplier Name: ");
		gets(info[i].p_dealer);
		printf("Cash/Credit(M/C): ");
		scanf("%c",&info[i].p_mode);
		info[i].type='p';
		fwrite((info+i),sizeof(purchase),1,purch);
		fwrite((info+i),sizeof(purchase),1,stmt);
	}
	fclose(purch);
	fclose(stmt);
	free(info);
	
}

void addSales()
{
	system("cls");
	printf("Add Sales Information\n");
	FILE *sales;
}

void checkCredit()
{
	system("cls");
	printf("Remaining Creditors\n");
	FILE *credit;
}

void checkInventory()
{
	system("cls");
	printf("Inventory Details\n");
	FILE *inv;
}
