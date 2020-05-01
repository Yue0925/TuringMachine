#include "../include/argparse.h"

int main(int argc, char ** argv)
{
	OutputOptions options = {false, false, false};

	parsing(argc, argv, options);

	TuringMachine tm;
	tm.setOutputOptions(options);
	tm.setInput(argv[optind+1]);

	Reader myReader(argv[optind]);

	myReader.Read(tm);

	//tm.affichage();
	tm.execute();
	tm.output();
	
	exportDot(tm, argv[optind]);
	exit(EXIT_SUCCESS);
}