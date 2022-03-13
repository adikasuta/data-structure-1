#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 255
#define MAX_ID 11
#define MAX_NAME 31
#define MAX_MAJOR 31
#define MAX_STUDENT 5

struct student{
  char id[MAX_ID];
  char name[MAX_NAME];
  char major[MAX_MAJOR];
} typedef Student;

struct node{
	Student value;
	struct node *next;
} typedef Node;

Node *initLinkedList(){
	Node *head = NULL;
	return head;
}

Node *addStack(Node *head, Student student){
	Node *newHead = initLinkedList();
	newHead = (Node*)malloc(sizeof(Node));
	newHead->value = student;
	newHead->next = head;
	return newHead;
}

Node* swap(Node* ptr1, Node* ptr2)
{
    Node* tmp = ptr2->next;
    ptr2->next = ptr1;
    ptr1->next = tmp;
    return ptr2;
}

void printStudent(Student input){
  printf("NIM: %s\n", input.id);
  printf("Name: %s\n", input.name);
  printf("Jurusan: %s\n", input.major);
}

void printList(Node* n){
    while (n != NULL) {
        printf("\n--------------------\n");
        printStudent(n->value);
        printf("\n--------------------");
        n = n->next;
    }
}

void sortByStudentId(Node** head, int size){
	Node** h;
    int i, j, swapped;
  
    for (i = 0; i <= size; i++) {
        h = head;
        swapped = 0;
        for (j = 0; j < size - i - 1; j++) {
            Node* p1 = *h;
            Node* p2 = p1->next;
            
            Student p1Val = p1->value;
            Student p2Val = p2->value;
            if (strcmp(p1Val.id,p2Val.id)>0) {
                *h = swap(p1, p2);
                swapped = 1;
            }
            h = &(*h)->next;
        }
        if (swapped == 0)
            break;
    }
}

void destroyList(Node** head){
	Node* current = *head;
	Node* next;
 
	while (current != NULL){
	   next = current->next;
	   free(current);
	   current = next;
	}
	*head = NULL;
}

int getSize(Node* n){
	int size=0;
    while (n != NULL) {
        size++;
        n = n->next;
    }
    return size;
}

int isReachMaxSize(Node* n){
	int size = getSize(n);
	return size >= MAX_STUDENT;
}

void readStudentField(char *target, char *field, int length){
	char temp[MAX];
	while(1){
		printf("Enter %s(%d character): \n", field, length-1);
		fgets (temp, MAX, stdin);
		temp[strcspn(temp, "\n")] = 0;
		int inputtedLength = strlen(temp);
		if(inputtedLength>length-1){//char enter termasuk dalam string
			printf("\nMax Character %d!\n", length);
		}else{
			break;
		}
	}
	strcpy(target, temp);
}

Student readStudent(){
	char temp[MAX];
	Student newStudent;
	printf("Enter new Student: \n");
	readStudentField(newStudent.id, "NIM", MAX_ID);
	readStudentField(newStudent.name, "Name", MAX_NAME);
	readStudentField(newStudent.major, "Jurusan", MAX_MAJOR);
	return newStudent;
}

int mainMenu(){
	printf("Student Database\n");
	printf("1. Add Student\n");
	printf("2. View Students\n");
	printf("3. Delete All Students\n");
	printf("4. Exit\n");
	int action;
	scanf("%d", &action);
	return action;
}

int main(void) {
	int action = 0;
	Node *students = initLinkedList();
	char _[1];
	while(action !=4){
		action = mainMenu();
		gets(_);
		switch(action){
			case 1:{
				if(isReachMaxSize(students)){
					printf("Has reached maximum of %d", MAX_STUDENT);
					break;
				}
				Student inputted = readStudent();
				students = addStack(students, inputted);
				printf("\nSuccessfully registered: \n");
				printStudent(inputted);
				break;
			}
			case 2:{
				sortByStudentId(&students, getSize(students));
				printList(students);
				break;
			}
			case 3:{
				destroyList(&students);
				break;
			}
		}
	}
	return 0;
}
