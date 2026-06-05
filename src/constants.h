/**
 * @file constants.h
 * @authors MarioS271
 * 
 * SPDX-FileCopyrightText: (C) MarioS271 2026
 * SPDX-License-Identifier: GPL-3.0-only
 */

#pragma once

#define CLOCK_MIN_SECS 30
#define CLOCK_MAX_SECS 120

#define FUN_MIN_SECS 10
#define FUN_MAX_SECS 60

#define WEIGHT_DROP 0.1f
#define WEIGHT_RISE (WEIGHT_DROP / (FUN_COUNT - 1.0f))
#define WEIGHT_MIN 0.1f
#define WEIGHT_MAX 1.0f