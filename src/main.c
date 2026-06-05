/**
 * @file main.c
 * @authors MarioS271
 *
 * SPDX-FileCopyrightText: (C) MarioS271 2026
 * SPDX-License-Identifier: GPL-3.0-only
 */

#include "config.h"
#include "defs.h"

#include <unistd.h>
#include <signal.h>
#include <time.h>

volatile pid_t child_pid = 0;

static void on_kill_signal(int sig) {
    if (child_pid > 0)
        kill(child_pid, SIGKILL);

    _exit(0);
}

int main(void) {
    system("clear");
    set_title();

    srand(time(nullptr));

    signal(SIGTERM, on_kill_signal);
    signal(SIGINT, on_kill_signal);

    validate_progs();

    display_mode_t mode = MODE_CLOCK;

    while (true) {
        if (mode == MODE_CLOCK) {
            char* argv[] = { CLOCK_ARGS };
            run_timed(argv, rand_range(CLOCK_MIN_SECS, CLOCK_MAX_SECS));
            mode = MODE_FUN;
        } else {
            const auto fun = (fun_t)(rand() % FUN_COUNT);

            switch (fun) {
                case FUN_CMATRIX: {
                    char* argv[] = { CMATRIX_ARGS };
                    run_timed(argv, rand_range(FUN_MIN_SECS, FUN_MAX_SECS));
                    break;
                }

                case FUN_CACAFIRE: {
                    char* argv[] = { CACAFIRE_ARGS };
                    run_timed(argv, rand_range(FUN_MIN_SECS, FUN_MAX_SECS));
                    break;
                }

                case FUN_SL: {
                    char* argv[] = { SL_ARGS };
                    run_until_exit(argv);
                    break;
                }

                case FUN_PIPES: {
                    char* argv[] = { PIPES_ARGS };
                    run_until_exit(argv);
                    break;
                }

                default:
                    break;
            }
            mode = MODE_CLOCK;
        }
    }

    return 0;
}
