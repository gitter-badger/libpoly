/*
 * statistics_internal.h
 *
 *  Created on: Dec 4, 2013
 *      Author: dejan
 */

#pragma once

#include <statistics.h>

#include <sys/time.h>

// names and output
#define STAT_NAME(module, name) __stat_ ## module ## _ ## name
#define STAT_INIT_NAME(module, name) __stat_ ## module ## _ ## name ## __init
#define STAT_OUT(module, name) #module "::" #name

/**
 * Use to declare a statistic of the given type with the variable name
 * c_name and the output string string_name. The statistic will be registered
 * at library load_time. This should only be used at global scope in the .c
 * files.
 */
#define STAT_DECLARE(type, module, name)      \
  type* STAT_NAME(module, name);              \
                                              \
  __attribute__ (( __constructor__ (102) ))   \
  void STAT_INIT_NAME(module, name) (void) {  \
    STAT_NAME(module, name) = statistics_ops.register_ ## type(STAT_OUT(module, name)); \
  }

/**
 * Use to reference the (previously declared) statistic.
 */
#define STAT(module, name) (*STAT_NAME(module, name))
