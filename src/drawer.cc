#include "../include/drawer.h"

void getBaseName(string path, string & baseName){
	size_t pos = 0;

	while((pos = path.find('/')) != std::string::npos){
		path.erase(0, pos + 1);
	}

	baseName = "./visual/" + path.substr(0, path.length() - 3) + ".dot";
}

string eraseSpace(string s){
	string name = s;
	size_t pos = 0;
	while((pos = name.find(' ')) != std::string::npos){
		name.replace(pos, 1, "");
	}
	return name;
}

void createPdf(string dotFile){
	string command = "dot -Tpdf " + dotFile + " -o " + dotFile.substr(0, dotFile.length()-3) + "pdf";
	const char * c = command.c_str();
	if(system(c) < 0)
		cerr<<"Error: executation of dot command failed!"<<endl;
}

void exportDot(TuringMachine & tm, string path){
	string baseName;
	getBaseName(path, baseName);

	ofstream fichierOut (baseName);
	if (!fichierOut.is_open())
	{
		cerr <<"Error: cannot open and write dot file!"<<endl;
		exit(EXIT_FAILURE);
	}
	fichierOut << "digraph TuringMachine {"<<endl<<"\trankdir=LR;"<<endl/*<<"\tsize=\"8,5\""<<endl*/;

	for(State s : tm.getAllStates()){
		fichierOut << "\tnode [shape =";
		if(s.isFinal)
			fichierOut << " doublecircle, ";
		else
			fichierOut << " circle, ";
		fichierOut <<"label=\""<<s.name<<"\", fontsize=12] "<<eraseSpace(s.name)<<";"<<endl;
	}

	fichierOut <<"\tnode [shape = point ]; start"<<endl<<"\tstart -> "<<eraseSpace(tm.getInitialState())<<";"<<endl;

	for(Transition t : tm.getAllTransitions()){
		fichierOut<<"\t"<<eraseSpace(t.state1)<<" -> "<<eraseSpace(t.state2)<<" [ label = \""<<t.symbol1<<"/"<<t.symbol2<<"/"<<t.move<<"\" ];"<<endl;
	}
	fichierOut<<"}"<<endl;
	fichierOut.close();
	createPdf(baseName);
}
//dot -Tpdf mult2.dot -o mult2.pdf
//sudo apt-get install graphviz