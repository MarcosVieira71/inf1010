#define _CRT_SECURE_NO_DEPRECATE
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

Patient* removePatient(Patient* head, Patient* p)
{
 	Patient* prev = NULL;
    Patient* cur = head;

    for (;cur != NULL; cur=cur->next) {
        if(cur->arrival == p->arrival) break;;
		prev = cur;
    }

    if (cur) {
        prev->next = cur->next;
        free(cur);
    }

    return head;
}

Patient* insertPatient(Patient* head, Patient* p) {
	Patient* cur = head;
	Patient* prev = NULL;

	for (cur; cur != NULL; cur = cur->next) {
		if (p->color[0] == 'r' &&(cur->color[0] == 'y' || cur->color[0] == 'g')) {
			break;
		}
		else if (p->color[0] == 'y' && cur->color[0] == 'g') {
			break;
		}
		
		prev = cur;
	}

	p->next = cur;

	if (prev) {
		prev->next = p;
	}
	else {
		head = p;
	}

	return head;
}


int main(void) {
	FILE* file = open("arquivo.txt");
	int tempInt;
	char tempStr[10];
	Patient* head = NULL;
	while (fscanf(file, " %d %[^\n]", &tempInt, tempStr) == 2) {
		Patient* p = createPatient(tempInt, tempStr);
		head = insertPatient(head, p);
		
	}
	Patient* p = createPatient(12, "red");
	head = removePatient(head, p);

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
	for (Patient* i = head; i != NULL; i = i->next) {
		if (!strcmp(i->color, color)) return 1;
	}
	return 0;
}

FILE* open(char* filepath) {
	FILE* p = fopen(filepath, "r");
	if (p == NULL) {
		exit(1);
		return NULL;
	}
	return p;
}

void showPatients(Patient* head) {
	for (Patient* i = head; i != NULL; i = i->next) {
		printf("%d %s\n", i->arrival, i->color);
	}
}