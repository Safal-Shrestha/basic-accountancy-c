#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct login{
	char uname[25], pw[25];
	int role;
}creds;

typedef struct {
	int id,qnty,rate,total;
	char name[40],dealer[40],message[100],mode,type;
}product_detail;

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
			goto err;
		
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
	product_detail *read;
	int newSize=1,readLoop=0,stmt_total=0;
	
	stmt=fopen("statement.txt","rb");
	
	read=(product_detail *)calloc(1,sizeof(product_detail));
	
	while(fread((read+readLoop),sizeof(product_detail),1,stmt)==1)
	{
		newSize++;
		read=(product_detail *)realloc(read,newSize*sizeof(product_detail));
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
	product_detail *info;
	int no;
	
	purch=fopen("expenditure.txt","ab");
	stmt=fopen("statement.txt","ab");
	cred=fopen("credit.txt","ab");
		
	printf("Enter Number of Products: ");
	scanf("%d",&no);
	
	info=(product_detail *)calloc(no,sizeof(product_detail));
	
	for(int i=0;i<no;i++)
	{
		printf("Product Id: ");
		scanf("%d",&info[i].id);
		fflush(stdin);
		printf("Product Name: ");
		gets(info[i].name);
		printf("Quantity: ");
		scanf("%d",&info[i].qnty);
		printf("Rate: ");
		scanf("%d",&info[i].rate);
		info[i].total=info[i].qnty*info[i].rate;
		fflush(stdin);
		printf("Supplier Name: ");
		gets(info[i].dealer);
		printf("Cash/Credit(M/C): ");
		scanf("%c",&info[i].mode);
		fflush(stdin);
		printf("Enter Narration: ");
		gets(info[i].message);
		info[i].type='p';
		fwrite((info+i),sizeof(product_detail),1,purch);
		fwrite((info+i),sizeof(product_detail),1,stmt);
		if(info[i].mode=='C'||info[i].mode=='c')
		{
			fwrite((info+i),sizeof(product_detail),1,cred);
		}
	}
	fclose(purch);
	fclose(stmt);
	fclose(cred);
	free(info);
	
}

void addSales()
{
	system("cls");
	printf("Add Sales Information\n");
	FILE *sale;
	FILE *stmt;
	FILE *cred;
	product_detail *info;
	int no;
	
	sale=fopen("sales.txt","ab");
	stmt=fopen("statement.txt","ab");
	cred=fopen("credit.txt","ab");
	
	printf("Enter Number of Products: ");
	scanf("%d",&no);
	
	info=(product_detail *)calloc(no,sizeof(product_detail));
	
	for(int i=0;i<no;i++)
	{
		printf("Product Id: ");
		scanf("%d",&info[i].id);
		fflush(stdin);
		printf("Product Name: ");
		gets(info[i].name);
		printf("Quantity: ");
		scanf("%d",&info[i].qnty);
		printf("Rate: ");
		scanf("%d",&info[i].rate);
		info[i].total=info[i].qnty*info[i].rate;
		fflush(stdin);
		printf("Buyer Name: ");
		gets(info[i].dealer);
		printf("Cash/Credit(M/C): ");
		scanf("%c",&info[i].mode);
		fflush(stdin);
		printf("Enter Narration: ");
		gets(info[i].message);
		info[i].type='s';
		fwrite((info+i),sizeof(product_detail),1,sale);
		fwrite((info+i),sizeof(product_detail),1,stmt);
		if(info[i].mode=='c'||info[i].mode=='C')
		{
			fwrite((info+i),sizeof(product_detail),1,cred);
		}
	}
	fclose(sale);
	fclose(stmt);
	fclose(cred);
	free(info);
}

void checkCredit()
{
	system("cls");
	FILE *credit;
	product_detail *read;
	int newSize=1,readLoop=0;
	int cred=0,debit=0;
	
	read=(product_detail *)calloc(1,sizeof(product_detail));
	credit=fopen("credit.txt","rb");
	
	while(fread((read+readLoop),sizeof(product_detail),1,credit)==1)
	{
		newSize++;
		read=(product_detail *)realloc(read,newSize*sizeof(product_detail));
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
	FILE *stmt;
	product_detail *readStatement, *inventory;
	int newSize=1,readLoop=0,uniqueProduct=0,uniqueProductPointer[uniqueProduct],uniqueProductId=0;
	
	stmt=fopen("statement.txt","rb");
	readStatement=(product_detail *)calloc(1,sizeof(product_detail));
	inventory=(product_detail *)calloc(1,sizeof(product_detail));
	
	while(fread((readStatement+readLoop),sizeof(product_detail),1,stmt)==1)
	{
		newSize++;
		readStatement=(product_detail *)realloc(readStatement,newSize*sizeof(product_detail));
		readLoop++;
	}
	
	for(int i=0; i<newSize-1; i++)
	{
		int flag=0,prodCount=0;
		
		if(readStatement[i].type=='p')
		{
			prodCount=readStatement[i].qnty;
		}
		else
		{
			prodCount=-readStatement[i].qnty;
		}
		
		for(int j=i-1; j>=0; j--)
		{
			if(readStatement[i].id==readStatement[j].id && strcmp(readStatement[i].name,readStatement[j].name)==0)
			{
				if(readStatement[j].type=='p')
				{
					prodCount=prodCount+readStatement[j].qnty;
				}
				else
				{
					prodCount=prodCount-readStatement[j].qnty;
				}
				flag=1;
			}
		}
		if(flag==1)
		{          
			continue;
		}
		readStatement[i].qnty=prodCount;
		uniqueProductPointer[uniqueProductId]=i;
		uniqueProductId++;
		uniqueProduct++;
	}
	printf("%d\t%d",uniqueProduct,uniqueProductId);
	inventory=(product_detail *)realloc(inventory,uniqueProduct*sizeof(product_detail));
	
	
	printf("Inventory Details\n");
	printf("S.No.\tParticulars\t\tQuantity\n");
	for(int i=0;i<uniqueProduct;i++)
	{
		inventory[i]=readStatement[uniqueProductPointer[i]];	
		printf("%d\t%s\t\t\t%d\n",i+1,inventory[i].name,inventory[i].qnty);
	}
	printf("\nPress Enter to continue to Home");
	scanf("%c");
}
