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
#define SIZE 40
// Structure Declaration
typedef struct Dataset{
	char category[40];
	char item[20];
	int  price;
	struct Dataset *next;
}Dataset;

// Global Variables
	FILE *file;
	char dataset[1000];
	Dataset *Head = NULL;
// Function Declaration
void fileOpen();
void initialization();
void createNode(char[SIZE][SIZE]);
void showNode();
void fileClose();
int main(void) {
	fileOpen();
	if(file != NULL){
		initialization();
		showNode();
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
	char category[SIZE][SIZE] = {};
	int j = 0;
	Head = (Dataset*)malloc(sizeof(Dataset));
	Head->next = NULL;
	while(fgets(dataset, 50, file) != NULL){
		strcpy(category[j],dataset);
		j++;
	}
	createNode(category);

}
void createNode(char data[SIZE][SIZE]){
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
	fflush(stdin);
	getchar();
}
void fileClose(){
	fclose(file);
}
