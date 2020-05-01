#include <sstream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <bits/stdc++.h>
#include "TuringMachine.h"

using namespace std;

void getBaseName(string path, string & baseName);

void exportDot(TuringMachine & tm, string path);

string eraseSpace(string s);

void createPdf(string dotFile);
