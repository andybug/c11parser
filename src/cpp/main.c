
#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include "cpp.h"

struct cpp_options options;

static void print_usage(void)
{
	puts("Usage: c11-cpp [options] file");
	puts("Options:");
	puts("  -v\t\t\tDisplay version information and exit");
	puts("  -o <file>\t\tPlace the output into file");
	puts("  -I <directory>\tAdd directory to the search path");
}

static void read_args(int argc, char *argv[], const char **filename)
{
	int ch;

	while ((ch = getopt(argc, argv, "vo:I:")) != -1) {
		switch (ch) {
		case 'v':
			/* print version information */
			puts("C11 Preprocessor ALPHA");
			puts("Andrew Fields (2013)");
			exit(EXIT_SUCCESS);

		case 'o':
			/* set output file name */
			fprintf(stderr, "Ignoring option 'o'\n");
			break;

		case 'I':
			/* add an include directory */
			fprintf(stderr, "Ignoring option 'I'\n");
			break;

		default:
			/* unknown option */
			fprintf(stderr, "Unknown option '%c'\n\n", ch);
			print_usage();
			exit(EXIT_FAILURE);
		}
	}

	/* handle the filename */
	if (optind < argc) {
		*filename = argv[optind];
	} else {
		fprintf(stderr, "File name required\n\n");
		print_usage();
		exit(EXIT_FAILURE);
	}
}

int main(int argc, char *argv[])
{
	const char *filename;
	
	read_args(argc, argv, &filename);
	return 0;
}
