#include "magic.h"

void magic_executeScript(char* tmpDirectory, char* mountPoint, char* scriptPath) {
	printf("Ejecutando operaciones...\n");

	char command[MAX_PATH];
	sprintf(command, "sh %s", scriptPath);

	chdir(tmpDirectory);
	system(command);
	chdir(mountPoint);
	system(command);
}

void magic_generateTree(char* path, char* pathToDump) {
	char command[MAX_PATH];
	chdir(path);
	sprintf(command, "tree . > %s", pathToDump);
	system(command);
}

void magic_generateMd5Log(char* path, char* pathToDump) {
	t_list* entries = files_getEntriesOfDirectory(path);
	list_sort(entries, (void*) strcmp);

	char command[MAX_PATH];
	sprintf(command, "touch %s", pathToDump);
	system(command);
	void _printMd5(char* fileName) {
		chdir(path);
		if (files_directoryExists(fileName)) {
			char* fullPath = files_getFullPath(fileName);
			magic_generateMd5Log(fullPath, pathToDump);
			free(fullPath);
		} else {
			sprintf(command, "md5sum %s >> %s", fileName, pathToDump);
			system(command);
		}
	}
	system(command);
	list_iterate(entries, (void*) _printMd5);

	list_destroy_and_destroy_elements(entries, free);
}
