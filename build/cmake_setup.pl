#!/usr/bin/perl

use Cwd 'abs_path';

# get user's choice
print "Please enter desired build mode:\n";
print "\t1. Debug\n";
print "\t2. Optimized\n";
print "\t3. Quit\n";
print "\nSelection: ";
$mode = <>;
chomp $mode;

# convert mode into string, or quit if invalid selection
$mode_map{'1'} = 'debug';
$mode_map{'2'} = 'opt';
$mode_map{'3'} = 'quit';
$mode = $mode_map{ $mode };

if ($mode eq 'quit') {
	exit 0;
}
elsif ($mode eq '') {
	print 'Error: Invalid selection' . "\n";
	exit 1;
}

# find the path to the project's build directory
$build = abs_path($0);
$build =~ s/build\/.*\.pl$/build/;

# move into the build directory
chdir $build;

# emit cmake command with debug arguments
if ($mode eq 'debug') {
	@output = `cmake -DCMAKE_BUILD_TYPE=Debug .. 2>&1`;
	print @output;
}

# emit cmake command with optimized arguments
elsif ($mode eq 'opt') {
	@output = `cmake ..`;
	print @output;
}

exit 0;
