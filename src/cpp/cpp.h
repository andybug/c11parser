/*
 * cpp.h
 * Internal header for libcpp. All functions, structures, etc that
 * need not be exposed through the external interface should be defined
 * in this file.
 */

#ifndef CPP_H
#define CPP_H

#include <stdio.h>
#include <stdbool.h>

/* ------------------- external defs (move later) -------------------------- */

int cpp_preprocess(const char *filename, int options, FILE *outstream);

/* --------------------- program options ----------------------------------- */

struct cpp_options {
	bool dummy;
};

extern struct cpp_options options;

#endif
