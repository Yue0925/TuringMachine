#include "Reader.h"
#include "TuringMachine.h"
#include "drawer.h"
#include <stdlib.h>
#include <cstdlib>
#include <unistd.h>
#include <getopt.h>

void display_help();

void parse_args(int argc, char ** argv, OutputOptions & options);

void parsing(int argc, char ** argv, OutputOptions & options);