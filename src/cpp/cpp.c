
#include <stdio.h>
#include "cpp.h"

int cpp_preprocess(const char *filename, int options, FILE *outstream)
{
	FILE *instream;
	char buf[256];

	instream = fopen(filename, "r");
	if (!instream)
		return -1;

	while (fgets(buf, 256, instream)) {
		fputs(buf, outstream);
	}

	fclose(instream);

	return 0;
}
