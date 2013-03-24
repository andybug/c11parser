
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <assert.h>

#include "cpp.h"

/* --------------------- character identification -------------------------- */

static bool is_whitespace(int c)
{
	if (c == ' ' || c == '\t')
		return true;

	return false;
}

static bool is_identifier_terminal(int c)
{
	if (!isalnum(c) || c != '_')
		return true;

	return false;
}

static bool is_identifier_leader(int c)
{
	if (isalpha(c) || c == '_')
		return true;

	return false;
}

static bool is_identifier(int c)
{
	if (isalnum(c) || c == '_')
		return true;

	return false;
}

static bool is_string_prefix1(int c)
{
	int lower;

	lower = tolower(c);

	if (lower == 'l' || lower == 'u')
		return true;

	return false;
}

static bool is_number_leader(int c)
{
	return isnumeric(c);
}

#if 0
static int is_string_prefix2(const char *prefix, size_t len)
{
	bool unsigned_ = false;
	bool long_ = false;
	bool longlong_ =false;
	bool upper_ = false;

	if (*prefix == 'u') {


	while (len) {
		if (*prefix == 'u' || *prefix == 'U') {
			if (unsigned_) {
				/* error */
			}

			unsigned_ = true;
		} else if (*prefix == 'l') {


}
#endif

/* --------------------- token list functions ------------------------------ */

static void toklist_add(struct lex_context *lex, struct lex_token *t)
{
	struct lex_token *token;

	token = malloc(sizeof(struct lex_token));
	memcpy(token, t, sizeof(struct lex_token));

	if (lex->head) {
		assert(lex->tail != NULL);
		assert(lex->head->prev == NULL);
		assert(lex->tail->next == NULL);

		token->next = NULL;
		token->prev = lex->tail;
		lex->tail->next = token;
		lex->tail = token;
	} else {
		assert(lex->head == NULL);
		assert(lex->tail == NULL);

		token->next = NULL;
		token->prev = NULL;
		lex->head = token;
		lex->tail = token;
	}
}

/* --------------------- helper functions for lexing ----------------------- */

/* --------------------- lexing handlers ----------------------------------- */

static int lex_handle_identifier(struct lex_context *lex, int mode, int c)
{
	if (mode & LEX_HANDLE_BEGIN) {
		lex->token.begin = lex->index;
		lex->token.type = CPP_TOKEN_IDENTIFIER;
		lex->handler = lex_handle_identifier;
	} else if (mode & LEX_HANDLE_CONT) {
		if (!is_identifier(c)) {
			lex->token.end = lex->index;
			toklist_add(lex, &lex->token);
			return 1;
		}
	} else {
	}

	return 0;
}

int lex_token(struct cpp_context *ctx)
{
	size_t *index = &ctx->lex.index;
	char c;
	int retval = 0;

	memset(&ctx->lex.token, 0, sizeof(struct lex_token));

	for (; *index < ctx->line_len; *index = *index + 1) {
		c = ctx->line[*index];
		if (ctx->lex.token.type != CPP_TOKEN_NONE) {
			retval = ctx->lex.handler(
					&ctx->lex,
					LEX_HANDLE_CONT,
					c);
			if (retval != 0)
				break;
		} else if (is_identifier(c)) {
			lex_handle_identifier(
					&ctx->lex,
					LEX_HANDLE_BEGIN,
					c);
		} else if (is_whitespace(c)) {
		} else if (c == '\n') {
			ctx->lex.token.type = CPP_TOKEN_NEWLINE;
			break;
		}
	}

	return retval;
}
