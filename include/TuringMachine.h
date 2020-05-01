#ifndef _TURINGMACHINE_H
#define _TURINGMACHINE_H
#include "elements.h"
#include <vector>
#include <cstdlib>
#include <sstream>
#include <string>
#include <iostream>
#include <ctime>
#include <algorithm>
using namespace std;

class TuringMachine
{

private:
	string input;
	// memorization & stock
	vector<State> tabState; 
	string blank;
	vector<Symbol> tabSymbol;
	vector<Transition> tabTransition;
	// flux restore
	stringstream steps;
	stringstream finalState;
	stringstream tape;
	//output options with order: steps, finalState, tape 
	OutputOptions options;

	bool isFinalState(string s);
	void matchTransition(string & stateCurrent, string & symbolCurrent,
		bool & isFind, int & indice);

public:
	TuringMachine();
	//~TuringMachine();

	void affichage();

	void addState(State s);
	void addSymbol(Symbol s);
	void addTransition(Transition t);

	void setBlank(string b);
	void setInput(string in);
	void setOutputOptions(OutputOptions opt);

	string getBlank();
	string getInitialState();
	const vector<State> & getAllStates() const ;
	const vector<Transition> & getAllTransitions() const ;

	void execute();
	void output();

};

#endif  //_TURINGMACHINE_H