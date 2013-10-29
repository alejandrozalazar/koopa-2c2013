#include "headers.h"

#define TEMP_DIRECTORY_NAME "/.koopa_tmp"
#define LINUX_LOG_NAME "linux_dump.txt"
#define GRASA_LOG_NAME "grasa_dump.txt"

void main_setPaths(char** argv);
void main_cleanPaths();
void main_generateDumps();
void main_goToAnimation();

static char* workingDirectory;
static char* mountPoint;
static char* script;
static char* tmpDirectory;

int main(int argc, char **argv) {
	validate_terminalSize();

	if (argc == 3) {
		validate_paths(argv);

		main_setPaths(argv);

		files_resetDirectory(tmpDirectory);

		magic_executeScript(tmpDirectory, mountPoint, script);

		main_generateDumps();

		//validar y setear win

		chdir(workingDirectory);
		main_cleanPaths();
	} else {
		printf("Uso: ./koopa puntoMontaje script.sh\n");
	}

	//showAnimation();

	return EXIT_SUCCESS;
}

void main_setPaths(char** argv) {
	char cwd[MAX_PATH];
	getcwd(cwd, sizeof(cwd));
	workingDirectory = files_getFullPath(cwd);
	mountPoint = files_getFullPath(argv[1]);
	script = files_getFullPath(argv[2]);
	tmpDirectory = string_duplicate(workingDirectory);
	string_append(&tmpDirectory, TEMP_DIRECTORY_NAME);
}

void main_cleanPaths() {
	free(workingDirectory); free(mountPoint);
	free(script); free(tmpDirectory);
}

void main_generateDumps() {
	char linuxLogName[MAX_PATH];
	sprintf(linuxLogName, "%s/%s", tmpDirectory, LINUX_LOG_NAME);
	magic_generateTree(tmpDirectory, linuxLogName);
	magic_generateMd5Log(tmpDirectory, linuxLogName);

	char grasaLogName[MAX_PATH];
	sprintf(grasaLogName, "%s/%s", tmpDirectory, GRASA_LOG_NAME);
	magic_generateTree(mountPoint, grasaLogName);
	magic_generateMd5Log(mountPoint, grasaLogName);
}

void main_goToAnimation() {
	t_anim* anim = anim_create(koopa_onInit, koopa_onUpdate, 85);
	anim_play(anim);
	anim_destroy(anim);
}
