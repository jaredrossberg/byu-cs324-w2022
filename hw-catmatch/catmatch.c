// Jared Rossberg

/*
1. Executable programs: 1
System calls: 2
Library calls: 3

2. section 2

3. #include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

4. sections 2, 7

5. section 7

6. 7

7. null-terminated

8. an integer greater than zero
*/

/*
"I completed the TMUX exercise from Part 2"
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {

    pid_t pid = getpid();
    fprintf(stderr, "%d\n", pid);

    if (argc < 2) {
        return 0;
    }

    char* pattern = getenv("CATMATCH_PATTERN");

    FILE* file = fopen(argv[1], "r");
    char* line = NULL;
    size_t len = 0;
    while (getline(&line, &len, file) != -1) {
        int found = 0;
        if (pattern != NULL && strstr(line, pattern) != NULL) {
            found = 1;
        }
        printf("%d %s", found, line);
    }

    fclose(file);
    return 0;
}