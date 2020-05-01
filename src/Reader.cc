#include "../include/Reader.h"

Reader::Reader(string p): path(p){
	if(p.substr(p.length() - 3, p.length()).compare(".tm") !=0 ){
		cerr << "Your description file doesn't end with suffix .tm!"<<endl;
		exit(EXIT_FAILURE);
	}
}

void Reader::BuildInit(string line, TuringMachine & tm){
	size_t pos = 0;
	string name;

	pos = line.find('(');
	name = line.substr(0, pos);
	if(name.compare("initial") != 0){
		cerr << "ERROR : first line is not a initial state!" << endl;
		exit(EXIT_FAILURE);}
	line.erase(0, pos + 1);
	pos = line.find(')');
	name = line.substr(0, pos);
	tm.addState({name, true, false});
}

void Reader::BuildOrtherStates(string line, TuringMachine & tm){
	size_t pos = 0;
	string isFinal;
	string name;

	pos = line.find('(');
	line.erase(0, pos + 1);
	pos = line.find(',');
	name = line.substr(0, pos);
	line.erase(0, pos + 1);
	pos = line.find(')');
	isFinal = line.substr(0, pos);

	if(isFinal.compare("T") == 0)
		tm.addState({name, false, true});
	else if(isFinal.compare("F") == 0)
		tm.addState({name, false, false});
	else{
		cerr << "Unknow indication! Expected T or F"<<endl;
		exit(EXIT_FAILURE);
	}
}

void Reader::BuildSymbols(string line, TuringMachine & tm){
	size_t pos = 0;
	string isInput;
	string symbol;

	pos = line.find('(');
	line.erase(0, pos + 1);
	pos = line.find(',');
	symbol = line.substr(0, pos);
	line.erase(0, pos + 1);
	pos = line.find(')');
	isInput = line.substr(0, pos);

	if (symbol.size()>1)
	{
		cerr << "ERROR symbol longer than 1!"<<endl;
		exit(EXIT_FAILURE);
	}

	if(isInput.compare("T") == 0)
		tm.addSymbol({symbol, true});
	else if(isInput.compare("F") == 0)
		tm.addSymbol({symbol, false});
	else{
		cerr << "Unknow indication! Expected T or F"<<endl;
		exit(EXIT_FAILURE);
	}
}

void Reader::BuildTransitions(string line, TuringMachine & tm){
	size_t pos = 0;
	string state1;
	string symbol1;
	string state2;
	string symbol2;
	string move;

	pos = line.find('(');
	line.erase(0, pos + 1);
	pos = line.find(',');
	state1 = line.substr(0, pos);
	line.erase(0, pos + 1);
	pos = line.find(',');
	symbol1 = line.substr(0, pos);
	line.erase(0, pos + 1);
	pos = line.find(',');
	state2 = line.substr(0, pos);
	line.erase(0, pos + 1);
	pos = line.find(',');
	symbol2 = line.substr(0, pos);
	line.erase(0, pos + 1);
	pos = line.find(')');
	move = line.substr(0, pos);

	tm.addTransition({state1, symbol1, state2, symbol2, move});
}

void Reader::BuildBlanks(string line, TuringMachine & tm){
	size_t pos = 0;
	string symbol;

	pos = line.find('(');
	line.erase(0, pos + 1);
	pos = line.find(')');
	symbol = line.substr(0, pos);

	if (symbol.size()>1)
	{
		cerr << "ERROR blank symbol longer than 1!"<<endl;
		exit(EXIT_FAILURE);
	}
	tm.setBlank(symbol);
}

void Reader::Read(TuringMachine & tm){
	ifstream fichierIn (path);

	if (!fichierIn.is_open())
	{
		cerr << "ERROR : No such file: "<<path<< endl;
		exit(EXIT_FAILURE);
	}

	string line;
	getline(fichierIn, line); 
	BuildInit(line, tm);

	while(!fichierIn.eof()){
		getline(fichierIn, line); 
		string w;
		for(auto x : line){
			if(x == '('){
				if(w.compare("state") == 0){//read orther states
					BuildOrtherStates(line, tm);
				}else if (w.compare("blank") == 0){
					BuildBlanks(line, tm);
				}else if (w.compare("symbol") == 0){
					BuildSymbols(line, tm);
				}else if (w.compare("transition") == 0){
					BuildTransitions(line, tm);
				}else{
					cerr<<"ERROR : file not regular!"<<endl;
					exit(EXIT_FAILURE);
				}
			}else
				w += x;
		}
	}
	fichierIn.close();
}
