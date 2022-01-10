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

	if (!parent->head_children_files) {
		parent->head_children_files = new_file;
		return;
	}

	File *curr = parent->head_children_files;
	if (!strcmp(curr->name, name)) {
		printf("Directory already exists\n");
		return;
	}

	while (curr->next) {
		if (!strcmp(curr->name, name)) {
			printf("Directory already exists\n");
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

	if (!parent->head_children_dirs) {
		parent->head_children_dirs = new_dir;
		return;
	}

	Dir *curr = parent->head_children_dirs;
	if (!strcmp(curr->name, name)) {
		printf("Directory already exists\n");
		return;
	}

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

	while (curr_dir) {
		printf("%s\n", curr_dir->name);
		curr_dir = curr_dir->next;
	}

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

	if (!strcmp(parent->head_children_files->name, name)) {
		to_delete = curr;
		parent->head_children_files = curr->next;
		free(to_delete->name);
		free(to_delete);
		return;
	}

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

// RMDIR_TOOL ------------------------------------------------------------------------
void rmdir_tool (Dir *parent, char *name) {
	Dir *curr = parent->head_children_dirs, *to_delete;

	if (!curr) {
		printf("Could not find the file\n");
		return;
	}

	if (!strcmp(parent->head_children_dirs->name, name)) {
		to_delete = curr;
		parent->head_children_dirs = curr->next;
		free(to_delete->name);
		free(to_delete);
		return;
	}

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
}

// FREE_MEM ------------------------------------------------------------------------
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

	if (!strcmp(parent->head_children_dirs->name, name)) { // daca e headul
		free_mem(parent->head_children_dirs); // goleste-l
		to_delete = parent->head_children_dirs; // sterge-l
		parent->head_children_dirs = parent->head_children_dirs->next;
		free(to_delete->name);
		free(to_delete);
		return;
	}

	for (Dir *curr_dir = parent->head_children_dirs; curr_dir->next; curr_dir = curr_dir->next) {
		if (!strcmp(curr_dir->name, name)) {
			free_mem(curr_dir); // l-am gasit si l-am golit
			to_delete = curr_dir;
			curr_dir->next = curr_dir->next->next;
			free(curr_dir->name);
			free(curr_dir);
			return;
		}
	}
}

// CD ------------------------------------------------------------------------
void cd (Dir **target, char *name) {
	if (!strcmp(name, "..")) {
		if ((*target)->parent) {
			*target = (*target)->parent;
		}
		return;
	}

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

	for (int i = 0; i < level; i++) {
		strcat(format, "    ");
	}
	strcat(format, "%s\n");

	for (Dir *curr_dir = target->head_children_dirs; curr_dir; curr_dir = curr_dir->next) {
		printf(format, curr_dir->name);
		tree(curr_dir, level + 1);
	}
	for (File *curr_file = target->head_children_files; curr_file; curr_file = curr_file->next) {
		printf(format, curr_file->name);
	}
	free(format);
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
		}
	} while (strcmp(root->name, "stop"));

	free_mem(keep_root);

	free(command);
	free(root->name);
	free(root);
	return 0;
}

