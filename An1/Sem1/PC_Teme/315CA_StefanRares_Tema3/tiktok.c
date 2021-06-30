#include "functions.h"
// Stefan Rares Constantin - 315CA

int main(void)
{
	char *command = alloc_string(COM_LEN);
	fgets(command, COM_LEN, stdin);
	command[strlen(command) - 1] = 0;
	char *copy = alloc_string(COM_LEN);
	char *nexter = alloc_string(COM_LEN);
	strcpy(nexter, "vreau sa intru in examen");
	strcpy(copy, command);

	while (strcmp(copy, "EXIT")) { //se asteapta EXIT ca sa se incheie
		char *type = strtok(copy, " ");
		if (!strcmp(type, "LOAD")) {
			load(command, &nexter);
		} else if (!strcmp(type, "ROTATE") || !strcmp(type, "SELECT") ||
				   !strcmp(type, "CROP") || !strcmp(type, "SEPIA") ||
				   !strcmp(type, "GRAYSCALE") || !strcmp(type, "SAVE")) {
			printf("No image loaded\n");
		}
		//daca nexter e "vreau sa..." inseamna ca a esuat LOAD-ul precedent
		if (!strcmp(nexter, "vreau sa intru in examen")) {
			fgets(command, COM_LEN, stdin); //citesc o noua comanda
			if (command[strlen(command) - 1] == '\n')
				command[strlen(command) - 1] = 0;
			if (!strcmp(command, "EXIT")) {
				printf("No image loaded\n");
				break;
			}
			strcpy(copy, command);
		} else if (strcmp(nexter, "\0")) {
			strcpy(command, "LOAD ");
			strcat(command, nexter);
		} else {
			break;
		}
	}
	free(command);
	free(copy);
	free(nexter);
	return 0;
}
