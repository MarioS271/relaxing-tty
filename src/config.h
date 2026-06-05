/**
 * @file config.h
 * @authors MarioS271
 *
 * SPDX-FileCopyrightText: (C) MarioS271 2026
 * SPDX-License-Identifier: GPL-3.0-only
 */

#pragma once

// Min/Max Durations for 
// #define CLOCK_MIN_SECS 60
// #define CLOCK_MAX_SECS 300
#define CLOCK_MIN_SECS 10
#define CLOCK_MAX_SECS 11

// #define FUN_MIN_SECS 30
// #define FUN_MAX_SECS 90
#define FUN_MIN_SECS 10
#define FUN_MAX_SECS 11

// Launch Args for programs
#define CLOCK_ARGS "tty-clock", "-c", "-C", "4", "-s", NULL

#define CMATRIX_ARGS "cmatrix", NULL
#define CACAFIRE_ARGS "cacafire", NULL
#define SL_ARGS "sl", NULL

// Needed programs for the application to run
static const char* needed_progs[] = {
    "tty-clock",
    "cmatrix",
    "cacafire",
    "sl"
};