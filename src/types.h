/**
 * @file types.h
 * @authors MarioS271
 * 
 * SPDX-FileCopyrightText: (C) MarioS271 2026
 * SPDX-License-Identifier: GPL-3.0-only
 */

#pragma once

typedef enum {
    MODE_CLOCK,
    MODE_FUN
} display_mode_t;

typedef struct {
    char* const* argv;
    bool timed;
} fun_def_t;