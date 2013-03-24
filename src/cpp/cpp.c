
#include <stdio.h>
#include <string.h>

#include "cpp.h"

/* --------------------- line reading -------------------------------------- */

static int read_line(struct cpp_context *ctx, FILE *stream)
{
	char *err;

	if (ctx->line_read) {		/* append another line to the buffer */
	}

	err = fgets(ctx->line, CPP_LINE_MAX, stream);
	if (err == NULL)
		return 0;

	ctx->line_len = strlen(ctx->line);
	memset(&ctx->lex, 0, sizeof(struct lex_context));

	return 1;
}

int cpp_preprocess(const char *filename, int options, FILE *outstream)
{
	FILE *instream;
	struct cpp_context ctx;
	struct lex_token *token;

	memset(&ctx, 0, sizeof(struct cpp_context));

	instream = fopen(filename, "r");
	if (!instream)
		return -1;

	while (read_line(&ctx, instream)) {
		lex_token(&ctx);
		while (ctx.lex.token.type != CPP_TOKEN_NEWLINE) {
			if (ctx.lex.token.type == CPP_TOKEN_IDENTIFIER) {
				printf("identifier: '%.*s'\n",
						ctx.lex.token.end -
						ctx.lex.token.begin,
						ctx.line + ctx.lex.token.begin);
			}
			lex_token(&ctx);

		}

	}

	fclose(instream);
	return 0;
}
