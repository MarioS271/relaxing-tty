/**
 * @file helpers.c
 * @authors MarioS271
 *
 * SPDX-FileCopyrightText: (C) MarioS271 2026
 * SPDX-License-Identifier: GPL-3.0-only
 */

#include "defs.h"
#include "funcs.h"
#include "globals.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

int rand_range(const int min, const int max) {
    return min + rand() % (max - min + 1);
}

static bool prog_exists(const char* name) {
    static const char* search_paths[] = { "/usr/bin", "/usr/local/bin", "/usr/games", NULL };
    char buf[128];
    for (int i = 0; search_paths[i]; ++i) {
        snprintf(buf, sizeof(buf), "%s/%s", search_paths[i], name);
        if (access(buf, X_OK) == 0) return true;
    }
    return false;
}

void validate_progs() {
    int num_of_needed_progs = sizeof(NEEDED_PROGS) / sizeof(NEEDED_PROGS[0]);
    bool error = false;

    for (int i = 0; i < num_of_needed_progs; ++i) {
        if (!prog_exists(NEEDED_PROGS[i])) {
            error = true;
            printf("Missing: %s\n", NEEDED_PROGS[i]);
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

void spawn_piped(char* const argv[], volatile pid_t* pid_proc, volatile pid_t* pid_lolcat) {
    int _pipe[2];
    pipe(_pipe);

    pid_t pid = fork();
    if (pid == 0) {
        dup2(_pipe[1], STDOUT_FILENO);
        close(_pipe[0]);
        close(_pipe[1]);

        execvp(argv[0], argv);
        _exit(1);
    }
    *pid_proc = pid;

    pid = fork();
    if (pid == 0) {
        dup2(_pipe[0], STDIN_FILENO);
        close(_pipe[0]);
        close(_pipe[1]);

        execvp(LOLCAT_ARGS[0], LOLCAT_ARGS);
        _exit(1);
    }
    *pid_lolcat = pid;

    close(_pipe[0]);
    close(_pipe[1]);
}

void set_title() {
    write(STDOUT_FILENO, "\033]0;relaxing-tty\007", 18);
}

void cleanup() {
    system("clear");
    set_title();
    child_pid = 0;
    lolcat_pid = 0;
}

void run_timed(char* const argv[], const bool lolcat_mode, const int seconds) {
    if (lolcat_mode) {
        spawn_piped(argv, &child_pid, &lolcat_pid);
    } else {
        child_pid = spawn(argv);
    }

    if (child_pid < 0)
        return;

    sleep(seconds);
    kill(child_pid, SIGTERM);

    if (lolcat_pid > 0) {
        kill(lolcat_pid, SIGTERM);
        waitpid(lolcat_pid, nullptr, 0);
    }

    waitpid(child_pid, nullptr, 0);
    cleanup();
}

void run_until_exit(char* const argv[], const bool lolcat_mode) {
    if (lolcat_mode) {
        spawn_piped(argv, &child_pid, &lolcat_pid);
    } else {
        child_pid = spawn(argv);
    }

    if (child_pid < 0)
        return;

    waitpid(child_pid, nullptr, 0);

    if (lolcat_pid > 0)
        waitpid(lolcat_pid, nullptr, 0);

    cleanup();
}