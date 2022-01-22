#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
	int pid;

	printf("Starting program; process has pid %d\n", getpid());

	FILE* file = fopen("fork-output.txt", "w+");
	fprintf(file, "BEFORE FORK\n");
	fflush(file);

	int pipefd[2];
	pipe(pipefd);
	FILE* file2;

	if ((pid = fork()) < 0) {
		fprintf(stderr, "Could not fork()");
		exit(1);
	}

	/* BEGIN SECTION A */

	printf("Section A;  pid %d\n", getpid());
	fprintf(file, "SECTION A\n");
	fflush(file);
	// sleep(30);

	/* END SECTION A */
	if (pid == 0) { // Ran only by child
		/* BEGIN SECTION B */

		close(pipefd[0]);
		file2 = fdopen(pipefd[1], "w");
		fputs("Hello from Section B", file2);

		printf("Section B\n");
		fprintf(file, "SECTION B\n");
		fflush(file);
		// sleep(30);
		// sleep(30);
		// printf("Section B done sleeping\n");

		/* FROM EXEC.C */
		char *newenviron[] = { NULL };

		printf("Program \"%s\" has pid %d. Sleeping.\n", argv[0], getpid());
		//sleep(30);

		if (argc <= 1) {
			printf("No program to exec.  Exiting...\n");
			exit(0);
		}

		printf("Running exec of \"%s\"\n", argv[1]);
		dup2(fileno(file2), STDOUT_FILENO);
		execve(argv[1], &argv[1], newenviron);
		printf("End of program \"%s\".\n", argv[0]);
		/* END EXEC.C */
		exit(0);

		/* END SECTION B */
	} else { // Ran only by parent
		/* BEGIN SECTION C */ 

		close(pipefd[1]);
		file2 = fdopen(pipefd[0], "r");
		char contents[100];
		fgets(contents, 100, file2);
		printf("%s\n", contents);

		printf("Section C\n");
		fprintf(file, "SECTION C\n");
		fflush(file);
		wait(NULL);
		// sleep(30);

		// printf("Section C done sleeping\n");

		exit(0);

		/* END SECTION C */
	}
	/* BEGIN SECTION D */

	printf("Section D\n");
	fprintf(file, "SECTION D\n");
	fflush(file);
	// sleep(30);

	/* END SECTION D */
}
