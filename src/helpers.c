/**
 * @file helpers.c
 * @authors MarioS271
 *
 * SPDX-FileCopyrightText: (C) MarioS271 2026
 * SPDX-License-Identifier: GPL-3.0-only
 */

#include "defs.h"
#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

int rand_range(const int min, const int max) {
    return min + rand() % (max - min + 1);
}

void validate_progs() {
    int num_of_needed_progs = sizeof(needed_progs) / sizeof(needed_progs[0]);

    char buffer[32];
    bool error = false;

    for (int i = 0; i < num_of_needed_progs; ++i) {
        snprintf(buffer, sizeof(buffer), "which %s > /dev/null", needed_progs[i]);
        const int result = system(buffer);

        if (WEXITSTATUS(result) != EXIT_SUCCESS) {
            error = true;
            printf("Missing: %s\n", needed_progs[i]);
        }
    }

    if (error) {
        printf("Aborting because of missing dependencies\n");
        exit(1);
    }
}

pid_t spawn(char* const argv[]) {
    pid_t pid = fork();

    if (pid == 0) {
        execvp(argv[0], argv);
        _exit(1);
    }

    return pid;
}

void cleanup() {
    system("clear");
    child_pid = 0;
}

void run_timed(char* const argv[], const int seconds) {
    child_pid = spawn(argv);

    if (child_pid < 0)
        return;

    sleep(seconds);
    kill(child_pid, SIGTERM);

    waitpid(child_pid, nullptr, 0);
    cleanup();
}

void run_until_exit(char* const argv[]) {
    child_pid = spawn(argv);

    if (child_pid < 0)
        return;

    waitpid(child_pid, nullptr, 0);
    cleanup();
}