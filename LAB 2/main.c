#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct patient Patient;
struct patient
{
	int arrival;
	char color[10];
	Patient *next;
};

FILE *open(char *filepath);
Patient *insertPatient(Patient *head, Patient *p);
Patient *createPatient(int arrival, char *color);
Patient *removePatient(Patient *head, int arrival);
void showPatients(Patient *head);
void freePatients(Patient **head);

int main(void)
{
	FILE *file = open("arquivo.txt");
	int tempInt;
	char tempStr[10];
	char opType;
	Patient *head = NULL;
	while (fscanf(file, " %c %d %[^\n]", &opType, &tempInt, tempStr) == 3)
	{
		if (opType == 'E')
		{
			Patient *p = createPatient(tempInt, tempStr);
			head = insertPatient(head, p);
			printf("Inserindo paciente '%s de chegada %d' na lista\n", p->color, p->arrival);
		}
		else if (opType == 'S')
		{
			head = removePatient(head, tempInt);
			printf("Removendo paciente de chegada %d da lista\n", tempInt);
		}
		showPatients(head);
		printf("-----------------\n");
	}
	freePatients(&head);
	printf("Esvaziando lista de pacientes\n");
	// showPatients(head);
	return 0;
}

// Gera um ponteiro para uma estrutura Paciente
Patient *createPatient(int arrival, char *color)
{
	Patient *newPatient = (Patient *)malloc(sizeof(Patient));
	if (newPatient == NULL)
		return NULL;
	newPatient->arrival = arrival;
	strcpy(newPatient->color, color);
	newPatient->next = NULL;
	return newPatient;
}

// Função para retornar o ponteiro para o arquivo. Em caso de erro, o programa é encerrado
FILE *open(char *filepath)
{
	FILE *p = fopen(filepath, "r");
	if (p == NULL)
	{
		exit(1);
		return NULL;
	}
	return p;
}

// Função para a exibição de todos os nós Pacientes da lista
void showPatients(Patient *head)
{
	int red = 0;
	int yellow = 0;
	int green = 0;

	for (Patient *i = head; i != NULL; i = i->next)
	{
		printf("%d %s\n", i->arrival, i->color);

		if (i->color[0] == 'r')
			red++;
		else if (i->color[0] == 'y')
			yellow++;
		else if (i->color[0] == 'g')
			green++;
	}

	printf("\nPacientes de prioridade vermelha: %d\nPacientes de prioridade amarela: %d\nPacientes de prioridade verde: %d\n", red, yellow, green);
}

// Função para a remoção de um paciente específico da lista
Patient *removePatient(Patient *head, int arrival)
{
	Patient *prev = NULL;
	Patient *cur = head;

	for (; cur != NULL; cur = cur->next)
	{
		if (cur->arrival == arrival)
			break;
		prev = cur;
	}
	if (cur)
	{
		if (prev)
		{
			prev->next = cur->next;
		}
		else
		{
			head = cur->next;
		}
		free(cur);
	}

	return head;
}

// Inserção de um paciente na lista de forma ordenada.
Patient *insertPatient(Patient *head, Patient *p)
{
	Patient *cur = head;
	Patient *prev = NULL;

	for (cur; cur != NULL; cur = cur->next)
	{
		// Se a cor do paciente for vermelha, ele deve ser inserido antes de qualquer paciente amarelo ou verde.
		if (p->color[0] == 'r' && (cur->color[0] == 'y' || cur->color[0] == 'g'))
		{
			break;
		}
		// Se a cor do paciente for amarela, ele deve ser inserido antes de qualquer paciente verde.
		else if (p->color[0] == 'y' && cur->color[0] == 'g')
		{
			break;
		}
		prev = cur;
	}

	p->next = cur;

	if (prev)
	{
		prev->next = p;
	}
	else
	{
		head = p;
	}

	return head;
}

// Libera por completo a lista de pacientes
void freePatients(Patient **head)
{
	while (*head)
	{
		Patient *temp = (*head);
		*head = (*head)->next;
		free(temp);
	}
	*head = NULL;
}