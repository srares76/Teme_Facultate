#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LINE_SIZE 300
#define TRUE 1
#define ROOT_NAME 5

struct Dir;
struct File;

typedef struct Dir {
	char *name;
	struct Dir *parent;
	struct File *head_children_files;
	struct Dir *head_children_dirs;
	struct Dir *next;
} Dir;

typedef struct File {
	char *name;
	struct Dir *parent;
	struct File *next;
} File;

// TOUCH ------------------------------------------------------------------------
void touch (Dir *parent, char *name) {
	/* Creates the new file node */
	File *new_file = malloc(sizeof(File));
	if (!new_file) {
		return;
	}
	new_file->name = malloc(strlen(name) + 1);
	if (!new_file->name) {
		free(new_file);
		return;
	}
	strcpy(new_file->name, name);
	new_file->next = NULL;

	/* If the list is empty, places the new node as the head */
	if (!parent->head_children_files) {
		parent->head_children_files = new_file;
		return;
	}
	
	/* If the head's name is the given name frees the created node */
	File *curr = parent->head_children_files;
	if (!strcmp(curr->name, name)) {
		printf("File already exists\n");
		free(new_file->name);
		free(new_file);
		return;
	}

	/*
	Traverses the list and if there a file with the given name already exists,
	frees the created node. If not, places the node at the end
	*/
	while (curr->next) {
		if (!strcmp(curr->name, name)) {
			printf("File already exists\n");
			free(new_file->name);
			free(new_file);
			return;
		}
		curr = curr->next;
	}
	curr->next = new_file;
}

// MKDIR ------------------------------------------------------------------------
void mkdir (Dir *parent, char *name) {
	/* Creates the new directory node */
	Dir *new_dir = malloc(sizeof(Dir));
	if (!new_dir) {
		return;
	}
	new_dir->name = malloc(strlen(name) + 1);
	if (!new_dir->name) {
		free(new_dir);
		return;
	}
	strcpy(new_dir->name, name);
	new_dir->parent = parent;
	new_dir->head_children_files = NULL;
	new_dir->head_children_dirs = NULL;
	new_dir->next = NULL;

	/* If the list is empty, places the node as the head */
	if (!parent->head_children_dirs) {
		parent->head_children_dirs = new_dir;
		return;
	}

	/* If the head's name is the given name, removes the created node */
	Dir *curr = parent->head_children_dirs;
	if (!strcmp(curr->name, name)) {
		printf("Directory already exists\n");
		free(new_dir->name);
		free(new_dir);
		return;
	}

	/*
	Traverses the list and if there a file with the given name already exists
	free the created node. If not, place the node at the end
	*/
	while (curr->next) {
		if (!strcmp(curr->name, name)) {
			printf("Directory already exists\n");
			free(new_dir->name);
			free(new_dir);
			return;
		}
		curr = curr->next;
	}
	curr->next = new_dir;	
}

// LS ------------------------------------------------------------------------
void ls (Dir *parent) {
	Dir *curr_dir = parent->head_children_dirs;
	File *curr_file = parent->head_children_files;

	/* Prints all directories' name */
	while (curr_dir) {
		printf("%s\n", curr_dir->name);
		curr_dir = curr_dir->next;
	}

	/* Prints all files' name */
	while (curr_file) {
		printf("%s\n", curr_file->name);
		curr_file = curr_file->next;
	}
}

// RM ------------------------------------------------------------------------
void rm (Dir *parent, char *name) {
	File *curr = parent->head_children_files, *to_delete;

	if (!curr) {
		printf("Could not find the file\n");
		return;
	}

	/* If the head has the given name, removes it */
	if (!strcmp(parent->head_children_files->name, name)) {
		to_delete = curr;
		parent->head_children_files = curr->next;
		free(to_delete->name);
		free(to_delete);
		return;
	}
	
	/* Traverses the list and remove the node when found */
	while (curr->next) {
		if (!strcmp(curr->next->name, name)) {
			to_delete = curr->next;
			curr->next = curr->next->next;
			free(to_delete->name);
			free(to_delete);
			return;
		}
		curr = curr->next;
	}
	printf("Could not find the file\n");
}

/*
A helper function for emptying directories
Works kind of lile the "-r" part in "rm -r"
*/
void free_mem(Dir *target) {
	File *to_delete_file;
	Dir *to_delete_dir;

	while (target->head_children_files) {
		to_delete_file = target->head_children_files;
		target->head_children_files = target->head_children_files->next;
		free(to_delete_file->name);
		free(to_delete_file);
	}

	while (target->head_children_dirs) {
		free_mem(target->head_children_dirs);
		to_delete_dir = target->head_children_dirs;
		target->head_children_dirs = target->head_children_dirs->next;
		free(to_delete_dir->name);
		free(to_delete_dir);
	}
}

// RMDIR ------------------------------------------------------------------------
void rmdir (Dir *parent, char *name) {
	Dir *to_delete;

	if (!parent->head_children_dirs) {
		printf("Could not find the dir\n");
		return;
	}

	/* Treats the head case */
	if (!strcmp(parent->head_children_dirs->name, name)) {
		free_mem(parent->head_children_dirs);
		to_delete = parent->head_children_dirs;
		parent->head_children_dirs = parent->head_children_dirs->next;
		free(to_delete->name);
		free(to_delete);
		return;
	}

	for (Dir *curr_dir = parent->head_children_dirs; curr_dir->next; curr_dir = curr_dir->next) {
		if (!strcmp(curr_dir->next->name, name)) {
			to_delete = curr_dir->next;
			curr_dir->next = curr_dir->next->next;
			free_mem(to_delete);
			free(to_delete->name);
			free(to_delete);
			return;
		}
	}
	printf("Could not find the dir\n");
}

// CD ------------------------------------------------------------------------
void cd (Dir **target, char *name) {
	/* Go back functionality */
	if (!strcmp(name, "..")) {
		if ((*target)->parent) {
			*target = (*target)->parent;
		}
		return;
	}

	/* Changes the current directory to the specified one */
	Dir *curr = (*target)->head_children_dirs;
	while (curr) {
		if (!strcmp(curr->name, name)) {
			*target = curr;
			return;
		}
		curr = curr->next;
	}
	printf("No directories found!\n");
}

// PWD ------------------------------------------------------------------------
char *pwd (Dir *target) {
	char *path = calloc(MAX_INPUT_LINE_SIZE, sizeof(char));
	if (!path) {
		return NULL;
	}
	char *current = calloc(MAX_INPUT_LINE_SIZE, sizeof(char));
	if (!current) {
		free(path);
		return NULL;
	}
	char *aux = calloc(MAX_INPUT_LINE_SIZE, sizeof(char));
	if (!aux) {
		free(path);
		free(current);
		return NULL;
	}
	/* Builds a string and returns it to main */
	Dir *curr = target;
	while (curr->parent) {
		sprintf(current, "/%s", curr->name);
		strcpy(aux, path);
		sprintf(path, "%s%s", current, aux);
		curr = curr->parent;
	}
	strcpy(aux, path);
	sprintf(path, "/home%s", aux);
	
	free(aux);
	free(current);
	return path;
}

// STOP ------------------------------------------------------------------------
void stop (Dir *target) {
	strcpy(target->name, "stop");
}

// TREE ------------------------------------------------------------------------
void tree (Dir *target, int level) {
	if (!target) {
		return;
	}

	char *format = calloc(MAX_INPUT_LINE_SIZE, sizeof(char));
	if (!format) {
		return;
	}

	/*
	Constructs the format for sprintf based on the level of recursion
	(aka the indentation of the output lines)
	*/
	for (int i = 0; i < level; i++) {
		strcat(format, "    ");
	}
	strcat(format, "%s\n");

	/* Recursive printing */
	for (Dir *curr_dir = target->head_children_dirs; curr_dir; curr_dir = curr_dir->next) {
		printf(format, curr_dir->name);
		tree(curr_dir, level + 1);
	}
	for (File *curr_file = target->head_children_files; curr_file; curr_file = curr_file->next) {
		printf(format, curr_file->name);
	}
	free(format);
}

// MV ------------------------------------------------------------------------
void mv(Dir* parent, char* oldname, char* newname) {
	int found = 0;
	Dir *aux_dir = NULL;
	File *aux_file = NULL;

	for (Dir *curr_dir = parent->head_children_dirs; curr_dir; curr_dir = curr_dir->next) {
		if (!strcmp(curr_dir->name, oldname)) {
			found = 1;  // 1 daca lucrez cu directoare
			aux_dir = curr_dir;
			break;
		}
	}
	if (!found) {
		for (File *curr_file = parent->head_children_files; curr_file; curr_file = curr_file->next) {
			if (!strcmp(curr_file->name, oldname)) {
				aux_file = curr_file;
				found = 2;  // 2 daca lucrez cu fisiere
				break;
			}
		}
	}
	if (!found) {
		printf("File/Director not found\n");
		return;
	}
	// Daca nu am old, s-a terminat 

	// Caut new
	for (Dir *curr_dir = parent->head_children_dirs; curr_dir; curr_dir = curr_dir->next) {
		if (!strcmp(curr_dir->name, newname)) {
			printf("File/Director already exists\n");
			return;
		}
	}
	for (File *curr_file = parent->head_children_files; curr_file; curr_file = curr_file->next) {
		if (!strcmp(curr_file->name, newname)) {
			printf("File/Director already exists\n");
			return;
		}
	}
	// Daca am ajuns aici am gasit si oldname si newname
	if (found == 1) {
		strcpy(aux_dir->name, newname);
		Dir *curr_dir = NULL;

		if (!strcmp(parent->head_children_dirs->name, newname)) {
			if (!parent->head_children_dirs->next) {
				return;
			}
			parent->head_children_dirs = parent->head_children_dirs->next;
			curr_dir = parent->head_children_dirs;
			while (curr_dir->next) {
				curr_dir = curr_dir->next;
			}
			curr_dir->next = aux_dir;
			aux_dir->next = NULL;
			return;
		}

		curr_dir = parent->head_children_dirs;
		while (curr_dir->next) {
			if (!strcmp(curr_dir->next->name, newname)) {
				curr_dir->next = curr_dir->next->next;
			}
			curr_dir = curr_dir->next;
		}
		curr_dir->next = aux_dir;
		aux_dir->next = NULL;
	} else if (found == 2) {
		strcpy(aux_file->name, newname);
		File *curr_file = NULL;

		if (!strcmp(parent->head_children_files->name, newname)) {
			if (!parent->head_children_files->next) {
				return;
			}
			parent->head_children_files = parent->head_children_files->next;
			curr_file = parent->head_children_files;
			while (curr_file->next) {
				curr_file = curr_file->next;
			}
			curr_file->next = aux_file;
			aux_file->next = NULL;
			return;
		}

		curr_file = parent->head_children_files;
		while (curr_file->next) {
			if (!strcmp(curr_file->next->name, newname)) {
				curr_file->next = curr_file->next->next;
			}
			curr_file = curr_file->next;
		}
		curr_file->next = aux_file;
		aux_file->next = NULL;
	}

}

int main () {
	Dir *root = malloc(sizeof(Dir));
	if (!root) {
		return 0;
	}

	root->parent = NULL;
	root->head_children_files = NULL;
	root->head_children_dirs = NULL;
	root->next = NULL;
	root->name = malloc(ROOT_NAME * sizeof(char));
	if (!root->name) {
		free(root);
		return 0;
	}

	strcpy(root->name, "home");

	Dir *current = root;
	Dir *keep_root = root;

	char *command = malloc(MAX_INPUT_LINE_SIZE * sizeof(char));
	if (!command) {
		free(root);
		return 0;
	}

	do {
		scanf("%s", command);
		if (!strcmp(command, "touch")) {
			scanf("%s", command);
			touch(current, command);
		} else if (!strcmp(command, "mkdir")) {
			scanf("%s", command);
			mkdir(current, command);
		} else if (!strcmp(command, "ls")) {
			ls(current);
		} else if (!strcmp(command, "rm")) {
			scanf("%s", command);
			rm(current, command);
		} else if (!strcmp(command, "rmdir")) {
			scanf("%s", command);
			rmdir(current, command);
		} else if (!strcmp(command, "cd")) {
			scanf("%s", command);
			cd (&current, command);
		} else if (!strcmp(command, "pwd")) {
			char *path = pwd(current);
			printf("%s\n", path);
			free(path);
		} else if (!strcmp(command, "stop")) {
			stop(root);
		} else if (!strcmp(command, "parent")) {
			if (current->parent)
				printf("%s", current->parent->name);
		} else if (!strcmp(command, "tree")) {
			int level = 0;
			tree(current, level);
		} else if(!strcmp(command, "free")) {
			free_mem(keep_root);
		} else if (!strcmp(command, "mv")) {
			char *aux = calloc(MAX_INPUT_LINE_SIZE, sizeof(char));
			scanf("%s%s", command, aux);
			mv(current, command, aux);
			free(aux);
		}
	} while (strcmp(root->name, "stop"));

	free_mem(keep_root);

	free(command);
	free(root->name);
	free(root);
	return 0;
}
