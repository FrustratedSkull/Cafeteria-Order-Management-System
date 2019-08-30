/*
 ============================================================================
 Name        : Cafeteria.c
 Author      : Ranjana
 Version     :
 Description : C programming Assigment (WASE)
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ROW 40
#define COL 30
// Structure Declaration
/*
 * Dataset will hold all the item details for the cafe
 */
typedef struct Dataset{
	char category[40];
	char item[20];
	int  price;
	struct Dataset *next;
}Dataset;
/*
 * Order will hold the details for the ordered items for customer
 */
// Order Details
typedef struct Order{
	char category[40];
	char item[20];
	int price;
	int orderNumber;
	int quantity;
	struct Order *next;
}Order;
// Global Variables
	FILE *file;
	char dataset[1000];
	Dataset *Head = NULL;			// Root node for Data set
	Order *orderHead = NULL;		// Root node for Order
// Function Declaration
void fileOpen();					// To open the data source file i.e. data.txt
void initialization();				// To initialize all the global node and variables
void createNode(char[ROW][COL]);	// To store the data into structure after reading from file
void showNode();					// Display the data as a Menu
void takeOrder();					// To take user input to book the order
void fileClose();					// To close the open file
int main(void) {
	fileOpen();
	if(file != NULL){
		initialization();
		showNode();
		takeOrder();
	}
	else {
		printf("\n\t !! Warning !! \n\t Data Source file data.txt is missing");
		fflush(stdin);
		getchar();
	}
	fileClose();
	return EXIT_SUCCESS;
}
/* Function Definition
 * It will open the source file i.e. data.txt in read mode
 */
void fileOpen(){
	file = fopen("data.txt","r");
}
/*Initialization function
 *It will fill the data set variable.
 *Data is captured from data.txt source file
*/
void initialization(){			// To initialize all the global node and variables
	char data[ROW][COL] = {};
	int j = 0;
	orderHead = (Order*)malloc(sizeof(Order));
	orderHead->next = NULL;
	Head = (Dataset*)malloc(sizeof(Dataset));
	Head->next = NULL;
	while(fgets(dataset, 50, file) != NULL){
		strcpy(data[j],dataset);
		j++;
	}
	createNode(data);

}
void createNode(char data[ROW][COL]){		// To store the data into structure after reading from file
	Dataset *temp = (Dataset*)malloc(sizeof(Dataset));
	int i = 0;
	while(i < 32){
		if(Head->next == NULL){
			Dataset *dataset = (Dataset*)malloc(sizeof(Dataset));
			strcpy(dataset->category,data[i]);
			i++;
			strcpy(dataset->item,data[i]);
			i++;
			sscanf(data[i], "%d", &dataset->price);
			i++;
			dataset->next = NULL;
			Head->next = dataset;
		}
		else{
			Dataset *dataset = (Dataset*)malloc(sizeof(Dataset));
			strcpy(dataset->category,data[i]);
			i++;
			strcpy(dataset->item,data[i]);
			i++;
			sscanf(data[i], "%d", &dataset->price);
			i++;
			dataset->next = NULL;
			temp = Head->next;
			while(temp->next != NULL){
				temp = temp->next;
			}
			temp->next = dataset;
		}
	}

}
void showNode(){				// Display the data as a Menu
	system("cls");
	Dataset *temp = (Dataset*)malloc(sizeof(Dataset));
	temp = Head->next;
	int flag = 0;
	while(temp != NULL){
		switch(temp->category[0]){
		case 'H':
			if(flag == 0){
				printf("\n %s", temp->category);
				flag = 1;
			} break;
		case 'C':
			if(flag == 1){
				printf("\n %s", temp->category);
				flag = 2;
			} break;
		case 'S':
			if(flag == 2){
				printf("\n %s", temp->category);
				flag = 3;
			} break;
		}
		printf("\n\t\t %s \t\t\t\t\t %d", temp->item, temp->price);
		temp = temp->next;
	}
}
void takeOrder(){			// To take user input to book the order
	Dataset *temp = (Dataset*)malloc(sizeof(Dataset));
	Order *orderTemp = (Order*)malloc(sizeof(Order));
	int i = 0, quantity = 0, randNumber, totalPrice = 0;
	char choose = 'Y';
	char itemName[20];
	randNumber = rand();
	while(choose != 'N'){
		// Start of taking user input
		fflush(stdin);
		printf("\n\n\t What would you like to Order: ");
		fflush(stdin);
		fgets(itemName, 20,stdin);		// Item
		printf("\n\t Quantity: ");
		scanf("%d",&quantity);		// Quantity
		// Taking copy of head nodes for both struture
		orderTemp = orderHead;
		temp = Head->next;
		while(temp != NULL){
			// Validating user input by comparing item name
			if(strcmp(itemName, temp->item) == 0){
				Order *newOrder = (Order*)malloc(sizeof(Order));
				// After condition match, copying item details to order details
				strcpy(newOrder->category, temp->category);
				strcpy(newOrder->item, temp->item);
				newOrder->price = 0;
				for(i = 0; i < quantity; i++){		// Adding price according to quantity
					newOrder->price = newOrder->price + temp->price;
				}
				newOrder->quantity = quantity;
				newOrder->orderNumber = 40000 + randNumber;
				newOrder->next = NULL;
				orderTemp = orderHead->next;
				// Below condition is to put the current order to the last node
				if(orderHead->next == NULL){	// This condition will work if there is no first order
					orderHead->next = newOrder;
				}
				else{
					while(orderTemp != NULL){
						if(orderTemp->next == NULL){
							break;
						}
						orderTemp = orderTemp->next;
					}
					orderTemp->next = newOrder;
				}
			}
			temp = temp->next;

		}
		// Asking whether user want to order more 'Y' for Yes 'N' for No
		printf("\n\t Do you want to Order more? (Y/N): ");
		fflush(stdin);
		scanf("%c",&choose);
	}

/*								Output Order details
 *
*/
	system("cls");
	orderTemp = orderHead->next;
	if(orderTemp == NULL){
		printf("\n\t Sorry, Order can't be booked");
	}
	else{
		printf("\n\t Details for Order: %d", orderTemp->orderNumber);
		printf("\n\n\n\t Category \t Item \t\t\t Quantity \t\t Sub-Total\n");
		printf("\t________________________________________________________________________");
		while(orderTemp != NULL){
			totalPrice = totalPrice + orderTemp->price;
			printf("\n\n\t %s \t\t\t %s \t\t\t\t\t\t %d \t\t\t %d ",orderTemp->category, orderTemp->item,
													orderTemp->quantity, orderTemp->price);
			orderTemp = orderTemp->next;
		}
	}
	printf("\n\n\n\t\t\t\t\t\t Total :\t\t %d", totalPrice);
	fflush(stdin);
	printf("\n\n\n\n\t Press enter to go back to main menu");
	getchar();
	main();
}

void fileClose(){		// To close the open file
	fclose(file);
}
