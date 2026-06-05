/**
 * @file defs.h
 * @authors MarioS271
 *
 * SPDX-FileCopyrightText: (C) MarioS271 2026
 * SPDX-License-Identifier: GPL-3.0-only
 */

#pragma once

#include "types.h"

static char* CLOCK_ARGS[] = { "tty-clock", "-c", "-C", "4", "-s", nullptr };
static char* CMATRIX_ARGS[] = { "cmatrix", nullptr };
static char* SL_ARGS[] = { "sl", nullptr };
static char* PIPES_ARGS[] = { "pipes", nullptr };

static const char* NEEDED_PROGS[] = {
    "tty-clock",
    "cmatrix",
    "sl",
    "pipes"
};

typedef enum {
    FUN_CMATRIX,
    FUN_SL,
    FUN_PIPES,
    FUN_COUNT
} fun_mode_t;

// i know its shit code but oh well
static fun_def_t fun_defs[FUN_COUNT] = {
    [FUN_CMATRIX] = {CMATRIX_ARGS, true},
    [FUN_SL] = { SL_ARGS, false },
    [FUN_PIPES] = { PIPES_ARGS, true },
};