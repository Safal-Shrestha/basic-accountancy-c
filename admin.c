#include<stdio.h>
#include<stdlib.h>

typedef struct login{
	char uname[25], pw[25];
	int role;
}creds;

typedef struct {
	int id,qnty,rate,total;
	char name[40],dealer[40],message[100],mode,type;
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
	int choice;
	FILE *fptr;
	fptr=fopen("activeUser.txt","rb");
	rewind(fptr);	
	
	err:
	system("cls");
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
			exit(0);
			break;
			
		default:
			system("cls");
			goto err;
			
	}
	goto err;
}

void stmt()
{
	system("cls");
	FILE *stmt;
	statement *read;
	int newSize=1,readLoop=0,stmt_total=0;
	
	stmt=fopen("statement.txt","rb");
	
	read=(statement *)calloc(1,sizeof(statement));
	
	while(fread((read+readLoop),sizeof(statement),1,stmt)==1)
	{
		newSize++;
		read=(statement *)realloc(read,newSize*sizeof(statement));
		readLoop++;
	}
	
	printf("Statement\n");
	printf("S.No.\tParticulars\t\tDebit\t\tCredit\n");
	for(int i=0;i<newSize-1;i++)
	{
		if(read[i].type=='p')
		{
			printf("%d\tFrom %s A/c Dr.\t%d\t\n",i+1,read[i].name,read[i].total);
			printf("\tTo %s A/c\t\t\t\t%d\n",read[i].dealer,read[i].total);
			printf("\t(%s)\n\n",read[i].message);
			stmt_total=stmt_total+read[i].total;
		}
		
		if(read[i].type=='s')
		{
			printf("%d\tFrom %s A/c Cr.\t\t\t%d\n",i+1,read[i].name,read[i].total);
			printf("\tTo %s A/c\t\t%d\n",read[i].dealer,read[i].total);
			printf("\t(%s)\n\n",read[i].message);
			stmt_total=stmt_total+read[i].total;
		}
	}
	printf("-------------------------------------------------------\n");
	printf("\t\t\t\t\%d\t\t%d\n\n",stmt_total,stmt_total);
	printf("\n*Press Enter to continue to Home*");
	scanf("%c");
}

void addPurchase()
{
	system("cls");
	printf("Add Purchase Information\n");
	FILE *purch;
	FILE *stmt;
	FILE *cred;
	purchase *info;
	int no;
	
	purch=fopen("expenditure.txt","ab");
	stmt=fopen("statement.txt","ab");
	cred=fopen("credit.txt","ab");
		
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
		fflush(stdin);
		printf("Enter Narration: ");
		gets(info[i].p_message);
		info[i].type='p';
		fwrite((info+i),sizeof(purchase),1,purch);
		fwrite((info+i),sizeof(purchase),1,stmt);
		if(info[i].p_mode=='C'||info[i].p_mode=='c')
		{
			fwrite((info+i),sizeof(purchase),1,cred);
		}
	}
	fclose(purch);
	fclose(stmt);
	free(info);
	
}

void addSales()
{
	system("cls");
	printf("Add Sales Information\n");
	FILE *sale;
	FILE *stmt;
	FILE *cred;
	sales *info;
	int no;
	
	sale=fopen("sales.txt","ab");
	stmt=fopen("statement.txt","ab");
	cred=fopen("credit.txt","ab");
	
	printf("Enter Number of Products: ");
	scanf("%d",&no);
	
	info=(sales *)calloc(no,sizeof(sales));
	
	for(int i=0;i<no;i++)
	{
		printf("Product Id: ");
		scanf("%d",&info[i].s_id);
		fflush(stdin);
		printf("Product Name: ");
		gets(info[i].s_name);
		printf("Quantity: ");
		scanf("%d",&info[i].s_qnty);
		printf("Rate: ");
		scanf("%d",&info[i].s_rate);
		info[i].s_total=info[i].s_qnty*info[i].s_rate;
		fflush(stdin);
		printf("Buyer Name: ");
		gets(info[i].s_cust);
		printf("Cash/Credit(M/C): ");
		scanf("%c",&info[i].s_mode);
		fflush(stdin);
		printf("Enter Narration: ");
		gets(info[i].s_message);
		info[i].type='s';
		fwrite((info+i),sizeof(sales),1,sale);
		fwrite((info+i),sizeof(sales),1,stmt);
		if(info[i].s_mode=='c'||info[i].s_mode=='C')
		{
			fwrite((info+i),sizeof(sales),1,cred);
		}
	}
	fclose(sale);
	fclose(stmt);
	free(info);
}

void checkCredit()
{
	system("cls");
	FILE *credit;
	statement *read;
	int newSize=1,readLoop=0;
	int cred=0,debit=0;
	
	read=(statement *)calloc(1,sizeof(statement));
	credit=fopen("credit.txt","rb");
	
	while(fread((read+readLoop),sizeof(statement),1,credit)==1)
	{
		newSize++;
		read=(statement *)realloc(read,newSize*sizeof(statement));
		readLoop++;
	}	
	
	printf("Remaining Credits\n");
	printf("S.No.\tParticulars\t\tCreditor\tDebtor\n");
	for(int i=0;i<newSize-1;i++)
	{
		if(read[i].type=='p')
		{
			printf("%d\tFrom %s A/c Dr.\t%d\t\n",i+1,read[i].name,read[i].total);
			printf("\t(%s)\n\n",read[i].message);
			cred=cred+read[i].total;
		}
		
		if(read[i].type=='s')
		{
			printf("%d\tFrom %s A/c Cr.\t\t\t%d\n",i+1,read[i].name,read[i].total);
			printf("\t(%s)\n\n",read[i].message);
			debit=debit+read[i].total;
		}
	}
	printf("-------------------------------------------------------\n");
	printf("\t\t\t\t\%d\t\t%d\n\n",cred,debit);
	printf("\nPress Enter to continue to Home");
	scanf("%c");
}

void checkInventory()
{
	system("cls");
	printf("Inventory Details\n");
	FILE *inv;
}
