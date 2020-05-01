#ifndef _Reader_H
#define _Reader_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <sstream>
#include <vector>
#include <stdio.h>
#include <string.h>

#include "TuringMachine.h"
using namespace std;

class Reader
{
private:
	string path;

	void BuildInit(string line, TuringMachine & tm);
	void BuildOrtherStates(string line, TuringMachine & tm);
	void BuildBlanks(string line, TuringMachine & tm);
	void BuildSymbols(string line, TuringMachine & tm);
	void BuildTransitions(string line, TuringMachine & tm);

public:
	Reader(string p);
	//~reader();
	void Read(TuringMachine & tm);	
	
};

#endif  //_Reader_H