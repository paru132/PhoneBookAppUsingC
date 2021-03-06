#include <stdio.h>
#include<string.h>
#include<stdlib.h>

//a node
struct node{
	char firstName[80];                         
	char lastName[80];                          
	char phNum[20];                             
	
	struct node * next;                         
};
//Declare methods
void printList();
void insertingContact();
void getFromTextFile();
void retrievingContact();
void deletingContact();
void writeToTextFile();
struct node *head=NULL;

struct node* retrieveNode();

int main(){
	int loop=5;  //used in while loop 
	char input; // getting input from user
	printf("The PhoneBook App\n");
	printf("Contacts List is: \n");
	getFromTextFile(); //reading contacts from the file	
	while(loop){
	printf("\nWhat do you want to do?\n");
	printf("Add Contact:      Type add\n");
	printf("Retrieve Contact: Type retrieve\n");
	printf("Delete Contact:   Type delete\n");
	printf("Load Contact:     Type load\n");
	printf("Save Contact:     Type save\n");
	printf("Enter an Action: ");
	scanf("%s", &input);		
		getchar();  
		switch(input) {
			case 'add':
				insertingContact(); 
				break;
           case 'retrieve':
				retrievingContact(); 
				break;
           case 'delete':
				deletingContact(); 
				break;
          case 'load':
				getFromTextFile(); 
				break;
            case 'save':
				writeToTextFile(); 
				break;
			default:
         printf("Input is invalid!");
				break;
		}

		
	}
}

void printList(){
	
	if(head == NULL){
	printf("\n List is Empty!\n");
	}
	else{
	struct node *temp=head;
	while(temp != NULL) {
		printf("First Name: %s \nLast Name:  %s \nPhone Number: %s ",temp->firstName, temp->lastName, temp->phNum);
			temp=temp->next;
		}
	}
}

void getFromTextFile() {
	int i=0;
    head = NULL;
    FILE *fp;
	fp = fopen("Contacts.txt","a+"); 
	char firstNm[80];
    char lastNm[80];
    char number[20];
   
	while(fscanf(fp, "%s", firstNm) != EOF) { 
        fscanf(fp, "%s", lastNm);
        fscanf(fp, "%s", number);
        
        printf("%d) First Name: %s Last Name:  %s (Contact Number: %s) \n",++i,firstNm, lastNm, number );
        struct node* newNode = retrieveNode();
		                                          //add this value to link list
        strcpy(newNode->firstName, firstNm);
        strcpy(newNode->lastName, lastNm);
        strcpy(newNode->phNum, number);
        

        
		if(head == NULL) {
            head = newNode;
        } else {
            struct node *temp = head;
            while(temp->next != NULL){
                temp = temp->next;
            }
            temp->next = newNode;
        }
	}
	
	fclose(fp); //closes a file
}


void writeToTextFile(){
	
	FILE *fp;
	fp = fopen("Contacts.txt","w");
	struct node *temp=head;

	while(temp != NULL) {
        fprintf(fp,"%s\n%s\n%s\n",temp->firstName,temp->lastName,temp->phNum);
        temp=temp->next;
    }

	fclose(fp);
	printf("\nThe Contact details are saved!");
}


void insertingContact(){  	
	
	char firstNm[100];
	char lastNm[100];
	char number[15];
	
	printf("\nEnter the First Name: \n");
	gets(firstNm);
	printf("\nEnter the Last Name: \n");
	gets(lastNm);
	printf("\nEnter the contact number: \n");
	gets(number);
	
   
	struct node* newNode = retrieveNode();
	strcpy(newNode->firstName, firstNm);
	strcpy(newNode->lastName, lastNm);
	strcpy(newNode->phNum, number);
	
	if(head == NULL) {
        head = newNode;
	} else {
        struct node *temp = head;
        while(temp->next != NULL){
            temp = temp->next;
		}
		temp->next = newNode;
	}
}

struct node* retrieveNode() {  
    struct node* newNode;
	newNode = (struct node*)malloc(sizeof(struct node));
	newNode->next = NULL;
	return newNode;
}


void retrievingContact(){
	//to retrieve a contact, u need to first save it ....then process
	char firstNm[80];
	printf("\nEnter First Name You Want to See: \n");
	gets(firstNm);
	int compare;
	if(head==NULL){
        printf("\n List is Empty!\n");
	} else {
        struct node *temp=head;
        while(temp != NULL){
            compare =	strcmp(temp->firstName,firstNm);
            if(compare==0) {
printf("First Name: %s \nLast Name:  %s \nContact Number: %s  \n",temp->firstName, temp->lastName, temp->phNum);
            }
                temp=temp->next;
            }
	}
}

void deletingContact(){
	
char firstNm[100];
	printf("\nEnter the first Name To Delete: \n");
	gets(firstNm);
	int compare;  //for comparing the strings
    if(head == NULL){
        printf("\n List is Empty!\n");
	}

 else {
        struct node *temp = head, *prev = NULL;
        if(strcmp(head->firstName, firstNm) == 0) { 
            head = head->next;
            return;
        }



        while(temp != NULL){
			compare = strcmp(temp->firstName,firstNm);
			if(compare == 0) {
                prev->next = temp->next; 
                free(temp);
				printf("\nA contact is deleted!!!");
			}
			
			
			prev = temp;
			temp = temp->next;
		}
			
	}
}






