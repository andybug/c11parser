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
	CPP_TOKEN_NONE = 0,

	/* generic */
	CPP_TOKEN_HEADER_NAME,
	CPP_TOKEN_IDENTIFIER,
	CPP_TOKEN_PP_NUMBER,
	CPP_TOKEN_CHAR_CONST,
	CPP_TOKEN_STRING_LITERAL,
	CPP_TOKEN_PUNCTUATOR,

	CPP_TOKEN_NEWLINE
};

struct lex_token {
	size_t begin;
	size_t end;
	enum token_type type;

	struct lex_token *next;
	struct lex_token *prev;
};

#define LEX_HANDLE_BEGIN		0x1
#define LEX_HANDLE_CONT			0x2
#define LEX_HANDLE_END			0x4

struct lex_context {
	/* token list */
	struct lex_token *head;
	struct lex_token *tail;
	
	/* the current token being processed */
	struct lex_token token;
	int (*handler)(struct lex_context *lex, int mode, int c);

	/* index into cpp_context line of the current char being processed */
	size_t index;

	/* flags */
	bool octal;
	bool hex;
	bool decimal;
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

#define LEX_TOKEN_SUCCESS	1
#define LEX_TOKEN_ENDLINE	2
#define LEX_TOKEN_ENDFILE	3
#define LEX_TOKEN_ERROR		4

int lex_token(struct cpp_context *ctx);

/* --------------------- program options ----------------------------------- */

struct cpp_options {
	bool dummy;
};

extern struct cpp_options options;

#endif
