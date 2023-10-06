#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "func.h"
#include "struct.h"

#define first 100
#define max 1000

int nextPosition = 0, nextPID = 0;

Process processes[max];

void create();
void delete();
void deleteAll();
void generate();
void read();
void readAll();
void solve();
void update();

int main()
{
	int option;
	while (1)
	{
		clear();
		printf("\n Ready Queue");
		printf("\n ----------------------------------");
		printf("\n  1 - Generate - Create multiple fake processes.");
		printf("\n  2 - Create - Create a new single process.");
		printf("\n  3 - Read - Read a single process.");
		printf("\n  4 - Update - Update a sinlge process.");
		printf("\n  5 - Delete - Delete a single process.");
		printf("\n  6 - List - Show all processes.");
		printf("\n  7 - Delete All - Delete all processes.");
		printf("\n  8 - Executar o Gerenciador de Processos.");
		printf("\n  9 - Sair do Programa.");
		printf("\n ----------------------------------");
		printf("\n Choose an option: ");
		scanf("%i", &option);
		fflush(stdin);

		if (option < 1 || option > 9)
		{
			printf("\n Invalid option. Please choose a valid option.");
			pause("\n\n Press any key to continue...");
			continue;
		}

		clear();
		switch (option)
		{
		case 1:
			generate();
			break;
		case 2:
			create();
			break;
		case 3:
			read();
			break;
		case 4:
			update();
			break;
		case 5:
			delete ();
			break;
		case 6:
			readAll();
			break;
		case 7:
			deleteAll();
			break;
		case 8:
			solve();
			break;
		case 9:
			printf("\n Exiting program...");
			exit(0);
		}

		pause("\n\n Press any key to continue...");
	}

	return 0;
}

void create()
{
	char name[5], type[2];
	int pid = nextPID + first;
	int cpu = 0, io = 0;

	printf("\n PID: %d\n", pid);
	processes[nextPosition].pid = pid;
name:
	printf(" NOME: ");
	scanf("%s", name);
	for (int i = 0; i < nextPosition; i++)
	{
		if (strcmp(processes[i].name, name) == 0)
		{
			printf("\r This name already exists, try again\n");
			goto name;
		}
	}
	strcpy(processes[nextPosition].name, name);
	fflush(stdin);
tipo:
	printf(" TIPO: ");
	scanf("%s", type);
	if (strcmp(type, "SO") != 0 && strcmp(type, "IN") != 0 && strcmp(type, "NI") != 0)
	{
		printf("\r This type does not exist, are available: SO, IN, NI\n");
		goto tipo;
	}
	strcpy(processes[nextPosition].type, type);
	fflush(stdin);
cpu:
	printf(" CPU: ");
	scanf("%d", &cpu);
	if (cpu < 0)
	{
		printf("\r Negative values are not allowed, try again\n");
		goto cpu;
	}
	processes[nextPosition].cpu = cpu;
	fflush(stdin);
io:
	printf(" I/O: ");
	scanf("%d", &io);
	if (io < 0)
	{
		printf("\r Negative values are not allowed, try again\n");
		goto io;
	}
	processes[nextPosition].io = io;
	fflush(stdin);

	processes[nextPosition].status = 0;
	nextPosition++;
	nextPID++;
}

void generate()
{
	printf("\n Complete the list of processes with fake processes.");
	printf("\n ------------------------------------------------");
	if (!(nextPosition < max))
	{
		printf("\n Full list.");
		return;
	}

	int generated = 0;
	for (int i = nextPosition; i < max; i++)
	{
		int type = rand() % 100;

		if (type < 10) // 10% of chance to be SO
		{
			strcpy(processes[nextPosition].type, "SO");
		}
		else if (type < 30) // 20% of chance to be IN
		{
			strcpy(processes[nextPosition].type, "IN");
		}
		else // 70% of chance to be NI
		{
			strcpy(processes[nextPosition].type, "NI");
		}
		sprintf(processes[nextPosition].name, "%d", i + 1);

		processes[nextPosition].status = 0;
		processes[nextPosition].pid = nextPID + first;
		processes[nextPosition].cpu = rand() % 100;
		processes[nextPosition].io = rand() % 100;
		nextPosition++;
		nextPID++;

		generated++;
	}
	printf("\n %d fake processes were generated!", generated);
}

void delete()
{
	int pid;
	printf("\n Digite o PID: ");
	scanf("%d", &pid);
	fflush(stdin);

	for (int i = 0; i < nextPosition; i++)
	{
		if (processes[i].pid == pid)
		{
			nextPosition--;
			for (int ind = i; ind < nextPosition; ind++)
			{
				processes[ind].pid = processes[ind + 1].pid;
				strcpy(processes[ind].name, processes[ind + 1].name);
				strcpy(processes[ind].type, processes[ind + 1].type);
				processes[ind].cpu = processes[ind + 1].cpu;
				processes[ind].io = processes[ind + 1].io;
				processes[ind].status = processes[ind + 1].status;
			}
			printf("\n Processo Deletado!");
			return;
		}
	}
}

void deleteAll()
{
	printf("\n Delete All");
	printf("\n ------------------------------------------------");
	if (nextPosition == 0)
	{
		printf("\n Empty list.");
		return;
	}

	Process emptyList[10];

	memcpy(processes, emptyList, sizeof(emptyList));
	nextPosition = 0;
	printf("\n All processes are deleted!");
}

void read()
{
	printf("\n Read a single process");
	printf("\n ------------------------------------------------");
	if (nextPosition == 0)
	{
		printf("\n Empty list.");
	}

	int pid = 0;
	printf("\n\n Digite o PID: ");
	scanf("%d", &pid);
	fflush(stdin);

	printf("\n PID\tNOME\tTIPO\tCPU\tI/O");
	printf("\n ------------------------------------------------");
	for (int i = 0; i < nextPosition; i++)
	{
		if (processes[i].pid == pid)
		{
			printf("\n %d\t%s\t%s\t%d\t%d", processes[i].pid, processes[i].name, processes[i].type, processes[i].cpu, processes[i].io);
		}
	}
	printf("\n ------------------------------------------------");
	printf("\n All processes are listed!");
}

void readAll()
{
	printf("\n Read all processes");
	printf("\n ------------------------------------------------");
	if (nextPosition == 0)
	{
		printf("\n Empty list.");
		return;
	}

	printf("\n PID\tNOME\tTIPO\tCPU\tI/O");
	for (int i = 0; i < nextPosition; i++)
	{
		printf("\n %d\t%s\t%s\t%d\t%d", processes[i].pid, processes[i].name, processes[i].type, processes[i].cpu, processes[i].io);
	}
	printf("\n ------------------------------------------------");
	printf("\n All processes are listed!");
}

void solve()
{
	printf("\n Solve all processes");
	printf("\n ------------------------------------------------");
	if (nextPosition == 0)
	{
		printf("\n Empty list.");
		return;
	}

	Process endedProcess[max], orderlyProcess[max];
	int bloqueado = 0;

	int ordaindedID = 0;
	int maxSO = 0, maxIN = 0, maxNI = 0;

	int loops = 0;
	int endedID = 0;

	printf("\n PID\tNOME\tTIPO\tCPU\tI/O\tENCERRADO");
	printf("\n ------------------------------------------------");
	for (int i = 0; i < 3; i++)
	{
		for (int x = 0; x < nextPosition; x++)
		{
			if (strcmp(processes[x].type, "SO") == 0 && i == 0)
			{
				orderlyProcess[ordaindedID].io = processes[x].io;
				orderlyProcess[ordaindedID].cpu = processes[x].cpu;
				orderlyProcess[ordaindedID].pid = processes[x].pid;
				orderlyProcess[ordaindedID].status = processes[x].status;
				strcpy(orderlyProcess[ordaindedID].type, processes[x].type);
				strcpy(orderlyProcess[ordaindedID].name, processes[x].name);
				ordaindedID++;
				maxSO++;
			}
			else if (strcmp(processes[x].type, "IN") == 0 && i == 1)
			{
				orderlyProcess[ordaindedID].io = processes[x].io;
				orderlyProcess[ordaindedID].cpu = processes[x].cpu;
				orderlyProcess[ordaindedID].pid = processes[x].pid;
				orderlyProcess[ordaindedID].status = processes[x].status;
				strcpy(orderlyProcess[ordaindedID].type, processes[x].type);
				strcpy(orderlyProcess[ordaindedID].name, processes[x].name);
				ordaindedID++;
				maxIN++;
			}
			else if (strcmp(processes[x].type, "NI") == 0 && i == 2)
			{
				orderlyProcess[ordaindedID].io = processes[x].io;
				orderlyProcess[ordaindedID].cpu = processes[x].cpu;
				orderlyProcess[ordaindedID].pid = processes[x].pid;
				orderlyProcess[ordaindedID].status = processes[x].status;
				strcpy(orderlyProcess[ordaindedID].type, processes[x].type);
				strcpy(orderlyProcess[ordaindedID].name, processes[x].name);
				ordaindedID++;
				maxNI++;
			}
		}
	}

	for (int z = 0; z < nextPosition; z++)
	{
		for (int i = 0; i < maxSO; i++)
		{
			if (strcmp(orderlyProcess[i].type, "SO") == 0)
			{
				if (orderlyProcess[i].cpu > 0)
				{
					orderlyProcess[i].cpu--;
				}
				if (orderlyProcess[i].io > 0)
				{
					if (bloqueado == 0)
					{
						bloqueado = orderlyProcess[i].pid;
						orderlyProcess[i].io--;
					}
				}
				if (orderlyProcess[((i + 1) > maxSO - 1) ? 0 : (i + 1)].io > 0)
				{
					bloqueado = 0;
				}
				if (orderlyProcess[i].cpu == 0 && orderlyProcess[i].io == 0 && orderlyProcess[i].status == 0)
				{
					orderlyProcess[i].status = 1;
					endedProcess[endedID].io = orderlyProcess[i].io;
					endedProcess[endedID].cpu = orderlyProcess[i].cpu;
					endedProcess[endedID].pid = orderlyProcess[i].pid;
					endedProcess[endedID].status = orderlyProcess[i].status;
					strcpy(endedProcess[endedID].name, orderlyProcess[i].name);
					strcpy(endedProcess[endedID].type, orderlyProcess[i].type);
					endedID++;
				}
			}
			loops++;
		}
	}

	for (int z = 0; z < nextPosition; z++)
	{
		for (int i = maxSO; i < maxSO + maxIN; i++)
		{
			if (strcmp(orderlyProcess[i].type, "IN") == 0)
			{
				if (orderlyProcess[i].cpu > 0)
				{
					orderlyProcess[i].cpu--;
				}
				if (orderlyProcess[i].io > 0)
				{
					if (bloqueado == 0)
					{
						bloqueado = orderlyProcess[i].pid;
						orderlyProcess[i].io--;
					}
				}
				if (orderlyProcess[((i + 1) > maxSO + maxIN - 1) ? maxSO : (i + 1)].io > 0)
				{
					bloqueado = 0;
				}
				if (orderlyProcess[i].cpu == 0 && orderlyProcess[i].io == 0 && orderlyProcess[i].status == 0)
				{
					orderlyProcess[i].status = 1;
					endedProcess[endedID].io = orderlyProcess[i].io;
					endedProcess[endedID].cpu = orderlyProcess[i].cpu;
					endedProcess[endedID].pid = orderlyProcess[i].pid;
					endedProcess[endedID].status = orderlyProcess[i].status;
					strcpy(endedProcess[endedID].name, orderlyProcess[i].name);
					strcpy(endedProcess[endedID].type, orderlyProcess[i].type);
					endedID++;
				}
			}
			loops++;
		}
	}

	for (int z = 0; z < nextPosition; z++)
	{
		for (int i = maxIN; i < maxSO + maxIN + maxNI; i++)
		{
			if (strcmp(orderlyProcess[i].type, "NI") == 0)
			{
				if (orderlyProcess[i].cpu > 0)
				{
					orderlyProcess[i].cpu--;
				}
				if (orderlyProcess[i].io > 0)
				{
					if (bloqueado == 0)
					{
						bloqueado = orderlyProcess[i].pid;
						orderlyProcess[i].io--;
					}
				}
				if (orderlyProcess[((i + 1) > maxSO + maxIN + maxNI - 1) ? maxSO + maxIN : (i + 1)].io > 0)
				{
					bloqueado = 0;
				}
				if (orderlyProcess[i].cpu == 0 && orderlyProcess[i].io == 0 && orderlyProcess[i].status == 0)
				{
					orderlyProcess[i].status = 1;
					endedProcess[endedID].io = orderlyProcess[i].io;
					endedProcess[endedID].cpu = orderlyProcess[i].cpu;
					endedProcess[endedID].pid = orderlyProcess[i].pid;
					endedProcess[endedID].status = orderlyProcess[i].status;
					strcpy(endedProcess[endedID].name, orderlyProcess[i].name);
					strcpy(endedProcess[endedID].type, orderlyProcess[i].type);
					endedID++;
				}
			}
			loops++;
		}
	}

	for (int i = 0; i < nextPosition; i++)
	{
		printf("\n %d\t%s\t%s\t%d\t%d\t%dth", endedProcess[i].pid, endedProcess[i].name, endedProcess[i].type, endedProcess[i].cpu, endedProcess[i].io, i + 1);
	}
	printf("\n ------------------------------------------------");
	printf("\n All processes are solved! %d loops", loops);
}

void update()
{
	int pid = 0;
	printf("\n\n Digite o PID: ");
	scanf("%d", &pid);
	fflush(stdin);

	for (int i = 0; i < nextPosition; i++)
	{
		if (processes[i].pid == pid)
		{
			char name[5], type[2];
			int cpu = 0, io = 0;

			printf("\n PID: %d", pid);
		name:
			printf(" NOME: ");
			scanf("%s", name);
			for (int i = 0; i < nextPosition; i++)
			{
				if (strcmp(processes[i].name, name) == 0)
				{
					printf("\r Esse Nome ja Existe, Tente Novamente\n");
					goto name;
				}
			}
			strcpy(processes[nextPosition].name, name);
			fflush(stdin);
		tipo:
			printf(" TIPO: ");
			scanf("%s", type);
			if (strcmp(type, "SO") != 0 && strcmp(type, "IN") != 0 && strcmp(type, "NI") != 0)
			{
				printf("\r Esse Tipo nao Existe, Tente Novamente\n");
				goto tipo;
			}
			strcpy(processes[nextPosition].type, type);
			fflush(stdin);
		cpu:
			printf(" CPU: ");
			scanf("%d", &cpu);
			if (cpu < 0)
			{
				printf("\r Esse Valor e invalido, Tente Novamente\n");
				goto cpu;
			}
			processes[nextPosition].cpu = cpu;
			fflush(stdin);
		io:
			printf(" I/O: ");
			scanf("%d", &io);
			if (io < 0)
			{
				printf("\r Esse Valor e invalido, Tente Novamente\n");
				goto io;
			}
			processes[nextPosition].io = io;
			fflush(stdin);
		}
	}
}