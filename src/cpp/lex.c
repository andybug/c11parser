
#include <string.h>
#include <stdlib.h>

#include "cpp.h"

/* --------------------- character identification -------------------------- */

static int is_whitespace(int c)
{
	if (c == ' ' || c == '\t')
		return 1;

	return 0;
}

static int lex_pound(struct cpp_context *ctx)
{
	ctx->lex.token_end = ctx->lex.token_begin;
	ctx->lex.token_type = CPP_TOKEN_POUND;
	ctx->lex.expected = CPP_EXPECT_DIRECTIVE;

	return 0;
}

int lex_next_token(struct cpp_context *ctx)
{
	char c;

	for (; ctx->lex.token_begin < ctx->line_len; ctx->lex.token_begin++) {
		c = ctx->line[ctx->lex.token_begin];

		if (is_whitespace(c))
			continue;

		if (c == '#')
			return lex_pound(ctx);
	}

	return 1;
}
