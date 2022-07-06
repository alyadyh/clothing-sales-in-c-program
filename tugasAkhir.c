#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct customer
{
	int hh, mm, yyyy;
	char nameCust[100];
	char category[100];
	char product[100];
	int amount;
	int price;
	long long total; 
};

struct price
{
	int num1;
	int num2;
};

struct mostSold
{
	char pro[100];
	int total;
	long long income;
};


/*--------------------Case 2------------------*/
void dateSort (struct customer data[], int n, int i, int j, int flag)
{
    struct customer temp;
    
    if(i < n - 1)
	{
    	if (flag)
    	{
    		j = i + 1;
		}
		if (j < n)
		{
			if (data[i].yyyy > data[j].yyyy)
			{
				temp = data[i];
                data[i] = data[j];
            	data[j] = temp;
			}
            else if (data[i].yyyy == data[j].yyyy && data[i].mm > data[j].mm)
            {
				temp = data[i];
                data[i] = data[j];
                data[j] = temp;
			}
			else if (data[i].yyyy == data[j].yyyy && data[i].mm == data[j].mm && data[i].hh > data[j].hh)
			{
				temp = data[i];
                data[i] = data[j];
                data[j] = temp;
			}
			dateSort(data, n, i, j + 1, 0);
		}
		dateSort(data, n, i + 1, 0, 1);
	}
}

void displayData(struct customer data[], int n)
{
	int i;
	dateSort(data, n, 0, 0, 1);
	
	printf("\n======================================================\n");
	printf("	Sales Report based on Transaction Date\n");
	printf("======================================================\n\n");
	printf("==================================================================================\n");
	printf("    DATE   ||  NAME  ||   CATEGORY  :  PRODUCT  || AMOUNT || PRICE || TOTAL PRICE\n");
	printf("==================================================================================\n");
	for(i = 0; i < n; i++){
		printf("%02d-%02d-%d || %s || %s : %s\t||   %d   || Rp%d || Rp%lld\n", data[i].hh, data[i].mm, data[i].yyyy, 
		data[i].nameCust, data[i].category, data[i].product, data[i].amount, data[i].price, data[i].total);
	}
}

void dateReport()
{	
	struct customer data[100];
	int n = 0, i;
	FILE *f;
	f = fopen("sales.txt", "r");
	if(f==NULL){
		printf("File sales.txt can't be opened.\n");
		exit(1);
	} else {
		while(fscanf(f,"%d-%d-%d || %[^|]|| %[^:]:%[^(] ( %d )\t|| Rp%lld || Rp%d\n", 
		&data[n].hh, &data[n].mm, &data[n].yyyy, data[n].nameCust, data[n].category, 
		data[n].product, &data[n].amount, &data[n].price, &data[n].total) != EOF)
		{
			n++;
		}
		
		displayData(data, n);
		
		printf("\nReading data successful.\n");
	}
	fclose(f);
}


/*--------------------Case 3------------------*/
void productSort (struct mostSold data[])
{
    struct mostSold temp;
    
    for (int i = 0; i < 9; i++)
    {
        for (int j = i + 1; j < 10; j++)
        {
            if (data[i].total < data[j].total)
            {
				temp = data[i];
                data[i] = data[j];
            	data[j] = temp;
			}
		}
	}
}

void productDisplay(struct mostSold count[])
{
	int i;
	
	//For neat display
	strcpy(count[0].pro, "Long-sleeve");
	strcpy(count[1].pro, "Short-sleeve");
	strcpy(count[2].pro, "Flared skirt");
	strcpy(count[3].pro, "Straight skirt");
	strcpy(count[4].pro, "Trousers");
	strcpy(count[5].pro, "Shorts  ");
	strcpy(count[6].pro, "Long dress");
	strcpy(count[7].pro, "Short dress");
	strcpy(count[8].pro, "Jacket  ");
	strcpy(count[9].pro, "Coat    ");
	
	productSort(count);
	
	printf("\n=============================================================\n");
	printf("	Sales Report based on The Most Sold Products\n");
	printf("=============================================================\n\n");
	
	printf("================================================\n");
	printf("   PRODUCT  \t  || AMOUNT || TOTAL INCOME\n");
	printf("================================================\n");
	for(i = 0; i < 10; i++)
	{
		printf(" %s\t       %d\t%lld\n", count[i].pro, count[i].total, count[i].income);
	}
}

void productReport()
{
	struct customer data;
	struct mostSold count[10];
	int i;
	
	count[0].total = 0, count[1].total = 0, count[2].total = 0, count[3].total = 0;
	count[4].total = 0, count[5].total = 0, count[6].total = 0, count[7].total = 0;
	count[8].total = 0, count[9].total = 0;
	
	FILE *f;
	f = fopen("sales.txt", "r");
	if(f==NULL){
		printf("File sales.txt can't be opened.\n");
		exit(1);
	} else {
		//For comparing strings
		strcpy(count[0].pro, " Long-sleeve ");
		strcpy(count[1].pro, " Short-sleeve ");
		strcpy(count[2].pro, " Flared skirt ");
		strcpy(count[3].pro, " Straight skirt ");
		strcpy(count[4].pro, " Trousers ");
		strcpy(count[5].pro, " Shorts ");
		strcpy(count[6].pro, " Long dress ");
		strcpy(count[7].pro, " Short dress ");
		strcpy(count[8].pro, " Jacket ");
		strcpy(count[9].pro, " Coat ");
		
		while(fscanf(f,"%d-%d-%d || %[^|]|| %[^:]:%[^(] ( %d )\t|| Rp%d || Rp%lld\n", 
		&data.hh, &data.mm, &data.yyyy, data.nameCust, data.category, 
		data.product, &data.amount, &data.price, &data.total) != EOF)
		{
			//Count amount of products sold
			if(strcmp(data.product, count[0].pro) == 0){
				count[0].total += data.amount;
			} else if(strcmp(data.product, count[1].pro) == 0){
				count[1].total += data.amount;
			} else if(strcmp(data.product, count[2].pro) == 0){
				count[2].total += data.amount;
			} else if(strcmp(data.product, count[3].pro) == 0){
				count[3].total += data.amount;
			} else if(strcmp(data.product, count[4].pro) == 0){
				count[4].total += data.amount;
			} else if(strcmp(data.product, count[5].pro) == 0){
				count[5].total += data.amount;
			} else if(strcmp(data.product, count[6].pro) == 0){
				count[6].total += data.amount;
			} else if(strcmp(data.product, count[7].pro) == 0){
				count[7].total += data.amount;
			} else if(strcmp(data.product, count[8].pro) == 0){
				count[8].total += data.amount;
			} else if(strcmp(data.product, count[9].pro) == 0){
				count[9].total += data.amount;
			}
		}
		
		//Count total income per product
		for(i = 0; i < 10; i++)
		{
			if(i % 2 == 0)
			{
				count[i].income = count[i].total * 150000;
			} else {
				count[i].income = count[i].total * 100000;
			}
		}
		
		productDisplay(count);
		
		printf("\nReading data successful.\n");
	}
	fclose(f);
}


/*-----------------Case 1 (Input Data to File)------------------*/
void salesData()
{
	struct customer data[100];
	struct price set = {.num1 = 150000, .num2 = 100000};
	
	int x, b, i, j;
	
	FILE *fp;
	fp = fopen("sales.txt","a");
	if(fp==NULL)
	{
		printf("File sales.txt can't be open.\n");
		exit(1);
	} else {
		//display products
		printf("\n---------------------------------------------------------\n");
		printf("Products in YaPao Clothing :\n\n");
		printf("Category: Top\n");
		printf("1. Long-sleeve		Rp150.000\n");
		printf("2. Short-sleeve		Rp100.000\n");
		printf("Category: Skirt\n");
		printf("3. Flared Skirt		Rp150.000\n");
		printf("4. Straight Skirt	Rp100.000\n");
		printf("Category: Breeches\n");
		printf("5. Trousers		Rp150.000\n");
		printf("6. Shorts		Rp100.000\n");
		printf("Category: Dress\n");
		printf("7. Long Dress		Rp150.000\n");
		printf("8. Short Dress		Rp100.000\n");
		printf("Category: Outerwear\n");
		printf("9. Jacket		Rp150.000\n");
		printf("10. Coat		Rp100.000\n");
		printf("\n---------------------------------------------------------\n");
		
		printf("How many customer data you want to input : ");
		scanf("%d", &x);
		printf("\n");
		
		printf("==========================================\n");
		printf("            	Sales Data             \n");
		printf("==========================================\n\n");
		
		for(i=0; i<x; i++)
		{
			printf("Enter customer name : ");
			scanf("%\n");
			scanf("%[^\n]", &data[i].nameCust);
			printf("Enter transaction date : ");
			scanf("%d-%d-%d", &data[i].hh, &data[i].mm, &data[i].yyyy);

			choose:
			printf("Enter product number based on the list above : ");
			scanf("%d", &b);
			
			while (b < 1 || b > 10)
			{
				printf("Input invalid. Enter number between 1 to 10\n");
				goto choose;
			}
			
			switch (b)
			{
				case 1:
					strcpy(data[i].category, "Top");
					strcpy(data[i].product, "Long-sleeve");
					printf("Enter amount of product : ");
					scanf("%d", &data[i].amount);
					data[i].price = set.num1;
					data[i].total = data[i].amount * data[i].price;
					break;
					
				case 2:
					strcpy(data[i].category, "Top");
					strcpy(data[i].product, "Short-sleeve");
					printf("Enter amount of product : ");
					scanf("%d", &data[i].amount);
					data[i].price = set.num2;
					data[i].total = data[i].amount * data[i].price;
					break;
				
				case 3:
					strcpy(data[i].category, "Skirt");
					strcpy(data[i].product, "Flared skirt");
					printf("Enter amount of product : ");
					scanf("%d", &data[i].amount);
					data[i].price = set.num1;
					data[i].total = data[i].amount * data[i].price;
					break;
				
				case 4:
					strcpy(data[i].category, "Skirt");
					strcpy(data[i].product, "Straight skirt");
					printf("Enter amount of product : ");
					scanf("%d", &data[i].amount);
					data[i].price = set.num2;
					data[i].total = data[i].amount * data[i].price;
					break;
					
				case 5:
					strcpy(data[i].category, "Breeches");
					strcpy(data[i].product, "Trousers");
					printf("Enter amount of product : ");
					scanf("%d", &data[i].amount);
					data[i].price = set.num1;
					data[i].total = data[i].amount * data[i].price;
					break;
				
				case 6:
					strcpy(data[i].category, "Breeches");
					strcpy(data[i].product, "Shorts");
					printf("Enter amount of product : ");
					scanf("%d", &data[i].amount);
					data[i].price = set.num2;
					data[i].total = data[i].amount * data[i].price;
					break;
					
				case 7:
					strcpy(data[i].category, "Dress");
					strcpy(data[i].product, "Long dress");
					printf("Enter amount of product : ");
					scanf("%d", &data[i].amount);
					data[i].price = set.num1;
					data[i].total = data[i].amount * data[i].price;
					break;
				
				case 8:
					strcpy(data[i].category, "Dress");
					strcpy(data[i].product, "Short dress");
					printf("Enter amount of product : ");
					scanf("%d", &data[i].amount);
					data[i].price = set.num2;
					data[i].total = data[i].amount * data[i].price;
					break;
					
				case 9:
					strcpy(data[i].category, "Outerwear");
					strcpy(data[i].product, "Jacket");
					printf("Enter amount of product : ");
					scanf("%d", &data[i].amount);
					data[i].price = set.num1;
					data[i].total = data[i].amount * data[i].price;
					break;
					
				case 10:
					strcpy(data[i].category, "Outerwear");
					strcpy(data[i].product, "Coat");
					printf("Enter amount of product : ");
					scanf("%d", &data[i].amount);
					data[i].price = set.num2;
					data[i].total = data[i].amount * data[i].price;
					break;
			}
			
			//input data to file sales.txt
			fprintf(fp,"%02d-%02d-%d || %s || %s : %s ( %d )\t|| Rp%d || Rp%lld\n",data[i].hh, data[i].mm, data[i].yyyy, 
			data[i].nameCust, data[i].category, data[i].product, data[i].amount, data[i].price, data[i].total);
			
			printf("\n");
		}
		printf("\nData has been inputted successfully.\n");
	}
	fclose(fp);
	
}

int main(){
	int n;
	printf("\n\t\t==================================================\n");
	printf("\t\t\tWelcome to YaPao Clothing Program\n");
	printf("\t\t==================================================\n\n");
	
	printf("1. Product Sales Data\n");
	printf("2. Sales Report based on Transaction Date\n");
	printf("3. Sales Report based on The Most Sold Products\n");
	start:
	printf("Input your choice : ");
	scanf("%d", &n);
	
	switch(n)
	{
		case 1:
			salesData();
			break;
		case 2:
			dateReport();
			break;
		case 3:
			productReport();
			break;
		default:
			printf("Input invalid. Enter number between 1 to 3.\n");
			goto start;
	}
	return 0;
}