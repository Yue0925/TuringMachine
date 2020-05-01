#include "../include/TuringMachine.h"

// Constructor
TuringMachine::TuringMachine(){
	finalState<<"Final State: ";
	tape<<"Final tape: ";
}

void TuringMachine::setInput(string in){
	input = in;
}

void TuringMachine::setOutputOptions(OutputOptions opt){
	options = opt;
}

void TuringMachine::addState(State s){
	tabState.push_back(s);
}

void TuringMachine::addSymbol(Symbol s){
	tabSymbol.push_back(s);
}

void TuringMachine::addTransition(Transition t){
	tabTransition.push_back(t);
}

void TuringMachine::setBlank(string b){
	this->blank = b;
}

string TuringMachine::getBlank(){
	return blank;
}

string TuringMachine::getInitialState(){
	for(State s : tabState){
		if(s.isInit)
			return s.name;
	}
	cerr << "ERROR: no initial state!"<<endl;
	exit(EXIT_FAILURE);
}

void TuringMachine::matchTransition(string & stateCurrent, string & symbolCurrent,
 bool & isFind, int  & indice){
	for(Transition t : tabTransition){
		if(t.state1.compare(stateCurrent) == 0 && t.symbol1.compare(symbolCurrent) == 0){
			isFind = true;
			steps<<"("<<t.state2<<", "<<t.symbol2<<", ";
			if(t.symbol2.compare(blank) != 0)
				tape<<t.symbol2;
			stateCurrent = t.state2;
			if(t.move.compare("R") == 0){
				indice++;
				steps<<"RIGHT)"<<endl;
				return;
			}else{
				indice--;
				steps<<"LEFT)"<<endl;
				return;
			}
		}
	}
}

void TuringMachine::execute(){
	string  stateCurrent = getInitialState();
	int indice = 0;
	string symbolCurrent;
	const clock_t deadline = clock() + CLOCKS_PER_SEC * 15.0;

	while(clock() < deadline){
		bool isFind = false; // if we find a correspond transition
		if(indice == -1) //before the first symbol
			symbolCurrent = blank;
		else if(indice == input.length()) //after the last symbol
			symbolCurrent = blank;
		else if(indice < input.length() && indice >= 0) //in the input word table
			symbolCurrent = input.at(indice);
		else
			symbolCurrent = blank;

		steps<<"("<<stateCurrent<<", "<<symbolCurrent<<") -> ";

		matchTransition(stateCurrent, symbolCurrent, isFind, indice);
		
		if(!isFind){ // didn't find a correspond transition
			cerr<<"ERROR: input isn't accepted by ths turing machine!"<<endl;
			exit(EXIT_FAILURE);
		}
		if(isFinalState(stateCurrent))	
			break;
	}
	finalState<<stateCurrent<<endl;
	tape<<endl;
	
	if(!isFinalState(stateCurrent)){
		cerr << "ERROR: you turing machine terminates without touching the final state!"<<endl;
		cerr << "ERROR: The execution is over 15 seconds, which indicates that may be a loop infinite!"<<endl;
		exit(EXIT_FAILURE);
	}
}

bool TuringMachine::isFinalState(string s){
	for(State st : tabState){
		if(st.name.compare(s) == 0)
			return st.isFinal;
	}
	cerr<<"ERROR: unexpected state!"<<endl;
	exit(EXIT_FAILURE);
}

void TuringMachine::output(){
	if(options.outputSteps)
		cout<<steps.str();
	if(options.outputState)
		cout<<finalState.str();
	if(options.outputTape)
		cout<<tape.str();
}

void TuringMachine::affichage(){
	cout << "READER tabState :"<<endl;
	for(State s: tabState){
		cout<<"Name : "<<s.name<<" isInit : "<<s.isInit << " isFinal : "<<s.isFinal<<endl;
	}

	cout << "READER Blank: "<< getBlank()<<endl;

	cout << "READER tabSymbol :"<<endl;
	for(Symbol s: tabSymbol){
		cout<<"Symbol : "<<s.symbol<<" isInput : "<<s.isInput<<endl;
	}

	cout << "READER tabTransition :"<<endl;
	for(Transition s: tabTransition){
		cout<<"state1: "<<s.state1<<" symbol1: "<<s.symbol1<<" state2: "<< s.state2
		<<" symbol2: "<<s.symbol2<<" move: " <<s.move <<endl;
	}		
}

const vector<State> & TuringMachine::getAllStates()const{
	return tabState;
}

const vector<Transition> & TuringMachine::getAllTransitions()const{
	return tabTransition;
}