#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>

void daemonize() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(1);
    }

    if (pid > 0) {
        exit(0); // Exit the parent process
    }

    // Create a new session and become the session leader
    if (setsid() < 0) {
        perror("setsid");
        exit(1);
    }

    // Fork again to ensure the daemon cannot acquire a controlling terminal
    pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(1);
    }

    if (pid > 0) {
        exit(0); // Exit the first child process
    }

    // Change the working directory to root
    if (chdir("/") < 0) {
        perror("chdir");
        exit(1);
    }

    // Set the file mode creation mask to 0
    umask(0);

    // Redirect standard file descriptors to /dev/null
    int dev_null = open("/dev/null", O_RDWR);
    if (dev_null == -1) {
        perror("open");
        exit(1);
    }

    dup2(dev_null, STDIN_FILENO);
    dup2(dev_null, STDOUT_FILENO);
    dup2(dev_null, STDERR_FILENO);

    close(dev_null);
}

void write_log() {
    FILE *logfile = fopen("/tmp/daemon_example.log", "a");
    if (logfile == NULL) {
        perror("fopen");
        exit(1);
    }

    while (1) {
        time_t now = time(NULL);
        struct tm *tm_info = localtime(&now);

        fprintf(logfile, "%04d-%02d-%02d %02d:%02d:%02d - Daemon is running.\n",
                tm_info->tm_year + 1900, tm_info->tm_mon + 1, tm_info->tm_mday,
                tm_info->tm_hour, tm_info->tm_min, tm_info->tm_sec);

        fflush(logfile);
        sleep(5);
    }

    fclose(logfile);
}

int main() {
    daemonize(); // Turn this process into a daemon
    write_log(); // Daemon function that logs data

    return 0;
}
