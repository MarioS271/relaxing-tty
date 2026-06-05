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

int main(void) {
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
            // float max_weight = 0;
            //
            // for (int i = 0; i < FUN_COUNT; ++i) {
            //     if (weights[i] > max_weight)
            //         max_weight = weights[i];
            // }
            //
            // fun_mode_t allowed_modes[FUN_COUNT];
            // int num_allowed_modes = 0;
            //
            // for (int i = 0; i < FUN_COUNT; ++i) {
            //     if (weights[i] >= max_weight)
            //         allowed_modes[num_allowed_modes++] = (fun_mode_t)i;
            // }
            //
            // if (num_allowed_modes == 0) {
            //     printf("Error: allowed_modes array contains 0 entries (illegal state), exiting");
            //     exit(1);
            // }
            //
            // int random_index = rand() % num_allowed_modes;
            // fun_mode_t chosen_mode = allowed_modes[random_index];

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
