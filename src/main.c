/**
 * @file main.c
 * @authors MarioS271
 *
 * SPDX-FileCopyrightText: (C) MarioS271 2026
 * SPDX-License-Identifier: GPL-3.0-only
 */

#include "defs.h"
#include "types.h"
#include "funcs.h"
#include "globals.h"
#include "constants.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

volatile pid_t child_pid = 0;
float weights[FUN_COUNT] = {};

static void on_kill_signal(int sig) {
    if (child_pid > 0)
        kill(child_pid, SIGTERM);

    _exit(0);
}

int main(int argc, char* argv[]) {
    FILE* log_file = nullptr;

    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "-d") == 0) {
            log_file = fopen(LOG_FILE_NAME, "w");
            break;
        }
    }
    system("clear");
    set_title();

    srand(time(nullptr));

    signal(SIGTERM, on_kill_signal);
    signal(SIGINT, on_kill_signal);

    for (int i = 0; i < FUN_COUNT; ++i) {
        weights[i] = 1.0f;
    }

    validate_progs();

    display_mode_t mode = MODE_CLOCK;

    while (true) {
        if (mode == MODE_CLOCK) {
            run_timed(CLOCK_ARGS, rand_range(CLOCK_MIN_SECS, CLOCK_MAX_SECS));
            mode = MODE_FUN;
        } else {
            fun_mode_t chosen_mode = -1;

            float sum = 0;
            for (int i = 0; i < FUN_COUNT; ++i) {
                sum += weights[i];
            }

            float random = (rand() / (float)RAND_MAX) * sum;
            for (int i = 0; i < FUN_COUNT; ++i) {
                random -= weights[i];

                if (random <= 0) {
                    chosen_mode = (fun_mode_t)i;
                    break;
                }
            }

            if (log_file) {
                fprintf(log_file, "chosen: %d | weights before:", chosen_mode);
                for (int i = 0; i < FUN_COUNT; ++i)
                    fprintf(log_file, " [%d]=%.3f", i, weights[i]);
                fprintf(log_file, "\n");
            }

            if (chosen_mode < 0 || chosen_mode >= FUN_COUNT) {
                printf("Error: chosen_mode is invalid");
                exit(1);
            }

            if (weights[chosen_mode] - WEIGHT_DROP >= WEIGHT_MIN)
                weights[chosen_mode] -= WEIGHT_DROP;

            for (int i = 0; i < FUN_COUNT; ++i) {
                if (chosen_mode == i)
                    continue;

                if (weights[i] + WEIGHT_RISE <= WEIGHT_MAX)
                    weights[i] += WEIGHT_RISE;
            }

            if (log_file) {
                fprintf(log_file, "         | weights after: ");
                for (int i = 0; i < FUN_COUNT; ++i)
                    fprintf(log_file, " [%d]=%.3f", i, weights[i]);
                fprintf(log_file, "\n");
                fflush(log_file);
            }

            if (fun_defs[chosen_mode].timed) {
                run_timed(fun_defs[chosen_mode].argv, rand_range(FUN_MIN_SECS, FUN_MAX_SECS));
            } else {
                run_until_exit(fun_defs[chosen_mode].argv);
            }

            mode = MODE_CLOCK;
        }
    }

    return 0;
}
