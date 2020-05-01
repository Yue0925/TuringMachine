#include <string>
using namespace std;

struct State
{
	string name;
	bool isInit;
	bool isFinal;
};

struct Symbol
{
	string symbol;
	bool isInput;
};

struct Transition
{
	string state1;
	string symbol1;
	string state2;
	string symbol2;
	string move;
};

struct OutputOptions
{
	bool outputSteps;
	bool outputState;
	bool outputTape;
};