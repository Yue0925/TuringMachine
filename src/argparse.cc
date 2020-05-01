#include "../include/argparse.h"

void display_help() {
	cout<<"Usage: myTuring" <<"[OPTION]... [FILE]...[INPUT]..."<<endl;
	cout<<"  -a, --state or -state    the program will print the final state of the machine."<<endl;
	cout<<"  -s, --steps or -steps    the program will print all the steps of the machine execution."<<endl;
	cout<<"  -h, --help  or -help     print this help."<<endl;
	cout<<"  -t, --tape  or -tape     the program will print the content of the tape at the end of the execution."<<endl;
	cout <<"After command options, the program needs a description file *.tm and a input word."<<endl;
}

void parse_args(int argc, char ** argv, OutputOptions & options) {
	struct option longopts[] = {
		{"steps", 0, NULL, 's'}, //no_argument, 
		{"state", 0, NULL, 'a'},
		{"help", 0, NULL, 'h'},
		{"tape", 0, NULL, 't'},
		{0, 0, 0, 0},
	};

	int longindex;
	int opt;
	bool noOpt = true;
	bool first = true;
	
	while ((opt = getopt_long_only(argc, argv, "asht", longopts, &longindex)) != -1) {
		if(first){
			first = false;
			if( optind > 2){
				cerr <<"Error: param must begin with command options."<<first<<endl;
				exit(EXIT_FAILURE);}
		}
		switch(opt) {
		case 'a':
			options.outputState = true;
			noOpt = false;
			break;
		case 's':
			options.outputSteps = true;
			noOpt = false;
			break;
		case 'h':
			display_help();
			break;
		case 't':
			options.outputTape = true;
			noOpt = false;
			break;
		default:
		    cerr<<"Error: option impossible."<<endl;
			exit(EXIT_FAILURE);
		}
	}
	if(noOpt){
		cerr <<"Error : no output options for turing machine!"<<endl;
		exit(EXIT_FAILURE);
	}
}

void parsing(int argc, char ** argv, OutputOptions & options){
	parse_args(argc, argv, options);

	if(argc < 4){
		cerr << "ERROR: the number of params must be greater than or equal to 3!"<<endl;
		exit(EXIT_FAILURE);
	}
	if (argc < optind+2)
	{
		cerr<<"Error: you missed .tm file or you missed input words!"<<endl;
		exit(EXIT_FAILURE);
	}
	if (argc > optind+2)
	{
		for (int i = optind+2; i < argc; ++i)
			cerr<<"Error: unknown param "<<argv[i]<<endl;
		exit(EXIT_FAILURE);
	}
}