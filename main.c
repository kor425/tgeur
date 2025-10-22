#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 500

//argv RATE
int main(int argc, char *argv[]) {

	if(argc != 2) {
		printf("INFO: Invialid argument! Please try again.\n");
		return 0;
	}

	char link[MAX];
	char path[MAX];
	char command[MAX];
	FILE *links_f = fopen("links", "r");


	while(fgets(link, sizeof(link), links_f) && fgets(path, sizeof(path), links_f)) {
		link[strcspn(link, "\n")] = 0;
		path[strcspn(path, "\n")] = 0;

		printf("INFO: LINK=%s\n", link);
		printf("INFO: PATH=%s\n", path);
		
		snprintf(command, sizeof(command), "yt-dlp --limit-rate %s --paths %s %s", argv[1], path, link);
		printf("INFO: Final command: %s\n\n", command);

		FILE *fp;
		char buffer[MAX];

		fp = popen(command, "r");
		
		while(fgets(buffer, sizeof(buffer), fp) != NULL) {
			printf("%s", buffer);
		}

		pclose(fp);

		//clearing the buffers
		if(strlen(link) > strlen(path)) {
			for(int k = 0; k < strlen(link); k++ ) {
				link[k] = ' ';
				path[k] = ' ';
			}
		}else {
			for(int k = 0; k < strlen(path); k++ ) {
				link[k] = ' ';
				path[k] = ' ';
			}
		}
	}

	printf("Closing file, end of program!\n");
	fclose(links_f);
	return 0;
}
