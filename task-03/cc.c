#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid = fork();

    if (pid > 0) {
        // Parent
        printf("Parent Process: My PID is %d, my child's PID is %d\n", getpid(), pid);
        sleep(10);  // So you have time to check `ps` or `pstree`
    } else if (pid == 0) {
        // Child
        printf("Child Process: My PID is %d, my parent's PID is %d\n", getpid(), getppid());
        sleep(10);
    } else {
        perror("fork failed");
    }

    return 0;
}
