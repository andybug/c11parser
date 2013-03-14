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

/* --------------------- external defs (move later) ------------------------ */

int cpp_preprocess(const char *filename, int options, FILE *outstream);

/* --------------------- token definitions --------------------------------- */

enum token_type {
	CPP_TOKEN_UNDEF = 0,

	/* generic */
	CPP_TOKEN_HEADER_NAME,
	CPP_TOKEN_IDENTIFIER,
	CPP_TOKEN_PP_NUMBER,
	CPP_TOKEN_CHAR_CONST,
	CPP_TOKEN_STRING_LITERAL,
	CPP_TOKEN_PUNCTUATOR,

	/* specific */
	CPP_TOKEN_POUND
};

#define CPP_EXPECT_WHITESPACE		0x1
#define CPP_EXPECT_POUND		0x2
#define CPP_EXPECT_DIRECTIVE		0x4

struct lex_context {
	/* tokens */
	size_t token_begin;
	size_t token_end;
	enum token_type token_type;

	/* line context */
	unsigned long expected;
	bool ignore_whitespace;
};

/* --------------------- parsing context ----------------------------------- */

#define CPP_LINE_MAX	1024

struct cpp_context {
	/* line buffer */
	char line[CPP_LINE_MAX];
	size_t line_len;
	int logical_line_num;
	int real_line_num;
	bool line_read;

	/* lexing */
	struct lex_context lex;
};

/* --------------------- lexing -------------------------------------------- */

int lex_next_token(struct cpp_context *ctx);

/* --------------------- program options ----------------------------------- */

struct cpp_options {
	bool dummy;
};

extern struct cpp_options options;

#endif
