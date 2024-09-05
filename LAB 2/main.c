#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct patient Patient;
struct patient {
	int arrival;
	char color[10];
	Patient* next;
};

FILE* open(char* filepath);
//void insertPatient(Patient* head, Patient* p);
Patient* createPatient(int arrival, char* color);
int searchByColor(char* color, Patient* head);
void showPatients(Patient* head);


Patient* insertPatient(Patient* head, Patient* p){
	p->next = head;
	return p;
}


int main(void){
	FILE* file = open("arquivo.txt");
	int tempInt;
	char tempStr[10];
	Patient* head = NULL;
	while (fscanf(file, " %d %[^\n]", &tempInt, tempStr) == 2) {
		Patient* p = createPatient(tempInt, tempStr);
		if(!head){
			head = insertPatient(head, p);
			printf("Cai apenas uma vez\n");
		}
		else{
			Patient* cur = head;
			while(1){
				Patient* next = cur->next;
				if(!(head->next)){
					head->next = insertPatient(head->next, p);
					break;
				}
				if(p->color[0] == 'r'){
					if(next->color[0] == 'y' || next->color[0] == 'g'){
						p->next = cur->next;
						cur->next = p;
						break;		
					}
				}
				cur = cur->next;
			}
		}
	}
	showPatients(head);
	return 0;
}


Patient* createPatient(int arrival, char* color) {
	Patient* newPatient = (Patient*)malloc(sizeof(Patient));
	if (newPatient == NULL) return NULL;
	newPatient->arrival = arrival;
	strcpy(newPatient->color, color);
	newPatient->next = NULL;
	return newPatient;
}

int searchByColor(char* color, Patient* head) {
	for (Patient* i = head; i != NULL; i=i->next) {
		if (!strcmp(i->color, color)) return 1;
	}
	return 0;
}

FILE* open(char* filepath){
	FILE* p = fopen(filepath, "r");
	if (p == NULL){
	 exit(1);
	 return NULL;
	}	
	return p;
}

void showPatients(Patient* head){
	for(Patient* i = head; i != NULL; i=i->next){
		printf("%d %s\n", i->arrival, i->color);
	}
}