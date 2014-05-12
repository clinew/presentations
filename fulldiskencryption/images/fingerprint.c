#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define STEP_COUNT 128

int main(int argc, char* argv[]) {
	char command[100000]; // Overkill, but whatever.
	char* compare;
	char* empty;
	int file;
	int i;
	struct stat stat;
	off_t step;

	// Open file.
	if ((file = open("./fingerprint", O_RDONLY)) == -1) {
		fprintf(stderr, "Unable to open file: %s.", strerror(errno));
		goto out;
	}

	// Get filesize.
	if (fstat(file, &stat) == -1) {
		fprintf(stderr, "Unable to get file stats: %s.", strerror(errno));
		goto out;
	}

	// Begin command.
	strcpy(command, "convert -size 257x513 xc:white");

	// Get step size.
	step = stat.st_size / STEP_COUNT;

	// Initialize empty and compare memory sections.
	empty = (char*)malloc(sizeof(char) * step);
	memset(empty, 0, sizeof(char) * step);
	compare = (char*)malloc(sizeof(char) * step);

	// Read in and compare chunks.
	lseek(file, 0, SEEK_SET);
	for (i = 0; i < STEP_COUNT; i++) {
		char extra[1024];

		// Read.
		if (read(file, compare, sizeof(char) * step) == -1) {
			fprintf(stderr, "Error reading file: %s.", strerror(errno));
			goto out;
		}

		// Compare.
		if (memcmp(empty, compare, sizeof(char) * step)) {
			sprintf(extra, " -fill red -stroke black -draw \"rectangle 0,%i 256,%i\"",
				i * 4, i * 4 + 4);
		} else {
			sprintf(extra, " -fill white -stroke black -draw \"rectangle 0,%i 256,%i\"",
				i * 4, i * 4 + 4);
		}
		strcat(command, extra);
	}

	// Run command.
	strcat(command, " fingerprint.gif");
	if (system(command) == -1) {
		fprintf(stderr, "Error executing command: %s.", strerror(errno));
		goto out;
	}

	exit(EXIT_SUCCESS);
out:
	exit(EXIT_FAILURE);
}
