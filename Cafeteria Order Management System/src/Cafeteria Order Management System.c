/*
 ============================================================================
 Name        : Cafeteria.c
 Author      : Ranjana
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ROW 40
#define COL 30
// Structure Declaration
typedef struct Dataset{
	char category[40];
	char item[20];
	int  price;
	struct Dataset *next;
}Dataset;
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
	Dataset *Head = NULL;
	Order *orderHead = NULL;
	char userChoice[ROW][COL];
// Function Declaration
void fileOpen();
void initialization();
void createNode(char[ROW][COL]);
void showNode();
void takeOrder();
void orderSuccessful();
void fileClose();
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
void initialization(){
	char category[ROW][COL] = {};
	int j = 0;
	orderHead = (Order*)malloc(sizeof(Order));
	orderHead->next = NULL;
	Head = (Dataset*)malloc(sizeof(Dataset));
	Head->next = NULL;
	while(fgets(dataset, 50, file) != NULL){
		strcpy(category[j],dataset);
		j++;
	}
	createNode(category);

}
void createNode(char data[ROW][COL]){
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
void showNode(){
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
void takeOrder(){
	Dataset *temp = (Dataset*)malloc(sizeof(Dataset));
	Order *orderTemp = (Order*)malloc(sizeof(Order));
	int i = 0;
	int randNum, currentOrder;
	randNum = rand();
	char choose = 'Y';
	while(choose != 'N'){			// Only storing item and quantity, later on price will be calculated
		Order *order = (Order*)malloc(sizeof(Order));
		printf("\n\t What would you like to Order: ");
		fflush(stdin);
		fgets(order->item, 20,stdin);		// Item
		printf("\n\t Quantity: ");
		scanf("%d",&order->quantity);		// Quantity
		printf("\n\t Do you want to Order more? (Y/N): ");
		fflush(stdin);
		scanf("%c",&choose);
		if(orderHead->next == NULL){
			orderHead->next = order;
			order->next = NULL;
		}
		else{
			orderTemp = orderHead->next;
			while(orderTemp != NULL){
				if(orderTemp->next == NULL) break;
				orderTemp = orderTemp->next;
			}
			orderTemp->next = order;
			order->next = NULL;
		}

	}											// End of taking input

	i = 0;
	temp = Head->next;							// Price will be calculated

	orderTemp = orderHead->next;
	while(orderTemp != NULL){
		while(temp != NULL){
			//printf("\n %s and %s",orderTemp->item, temp->item);
			i = 0;
			while(orderTemp->item[i] != '\n'){
				if(orderTemp->item[i] == temp->item[i]){
					//printf("\n Match found");
					strcpy(orderTemp->category, temp->category);	// Setting the category
					orderTemp->price = 0;			// Initializing price to 0
					for(i = 0; i < orderTemp->quantity; i++){
						orderTemp->price = orderTemp->price + temp->price;
						printf("\n %d",temp->price);
					}
					orderTemp->orderNumber = 400000 + randNum;
					currentOrder = orderTemp->orderNumber;
					printf("\n Success");

				}
				if(orderTemp->item[i] == '\n') break;
				i++;

			//if(strcmp(orderTemp->item, temp->item) == 0){


			}
			temp = temp->next;
		}
		orderTemp = orderTemp->next;
	}

fflush(stdin);
getchar();
/*								Prompt Order details
 *
*/
	system("cls");
	printf("\n\t Details for Order: %d",currentOrder);
	orderTemp = orderHead->next;
	if(orderTemp == NULL){
		printf("\n\t Sorry, Order can't be booked");
	}
	else{
		printf("\n\n\t Category \t Item \t Quantity \t Total Price\n");
		while(orderTemp != NULL){
			printf("\n\t %s \t\t\t %s \t\t\t\t %d \t\t\t %d ",orderTemp->category, orderTemp->item,
													orderTemp->quantity, orderTemp->price);
			orderTemp = orderTemp->next;
		}
	}
	fflush(stdin);
	getchar();
}

void orderSuccessful(){

}
void fileClose(){
	fclose(file);
}
