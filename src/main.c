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
    srand(time(nullptr));
    signal(SIGTERM, on_kill_signal);
    signal(SIGINT, on_kill_signal);

    system("clear");
    set_title();

    int speed_multiplier = 1;
    for (int i = 0; i < argc; ++i) {
        if (strcmp(argv[i], "--fast") == 0)
            speed_multiplier = FAST_MODE_SPEED_MULTIPLIER;
    }

    display_mode_t mode = MODE_CLOCK;
    for (int i = 0; i < FUN_COUNT; ++i) {
        weights[i] = 1.0f;
    }

    validate_progs();

    while (true) {
        if (mode == MODE_CLOCK) {
            // min color id is 1, max is 7
            clock_color[0] = (char)('0' + rand() % 7 + 1);

            run_timed(
                CLOCK_ARGS,
                rand_range(CLOCK_MIN_SECS / speed_multiplier, CLOCK_MAX_SECS / speed_multiplier)
            );
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
                run_timed(
                    fun_defs[chosen_mode].argv,
                    rand_range(FUN_MIN_SECS / speed_multiplier, FUN_MAX_SECS / speed_multiplier)
                );
            } else {
                run_until_exit(
                    fun_defs[chosen_mode].argv
                );
            }

            mode = MODE_CLOCK;
        }
    }

    return 0;
}
