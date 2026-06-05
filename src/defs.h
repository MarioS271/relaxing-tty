/**
 * @file defs.h
 * @authors MarioS271
 *
 * SPDX-FileCopyrightText: (C) MarioS271 2026
 * SPDX-License-Identifier: GPL-3.0-only
 */

#pragma once

#include <stdlib.h>

static const char* needed_progs[] = {
    "tty-clock",
    "cmatrix",
    "cacafire",
    "sl"
};

typedef enum {
    MODE_CLOCK,
    MODE_FUN
} display_mode_t;

typedef enum {
    FUN_CMATRIX,
    FUN_CACAFIRE,
    FUN_SL,
    FUN_COUNT
} fun_t;

extern volatile pid_t child_pid;

int rand_range(int min, int max);
void validate_progs();
pid_t spawn(char* const argv[]);
void cleanup();
void run_timed(char* const argv[], int seconds);
void run_until_exit(char* const argv[]);