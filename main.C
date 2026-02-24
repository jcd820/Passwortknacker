//============================================================================
// Name        : Passwortknacker.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C, Ansi-style
//============================================================================

#include <string>
#include <iostream>
#include <sstream>

#include <cstdio>      /* printf, NULL */
#include <cstdlib>     /* srand, rand */
#include <ctime>       /* time */

#include <unistd.h>

#include "SHA256.H"
#include "TASK1.H"


using namespace std;


int main(){
	srand(time(nullptr));
	stringstream sout;
	string output;
	int a;
	a=13;
	int b;
	b=14;
	cout << "COORD [" <<a <<"," <<b << "]" <<endl;
    sout << "COORD [" <<a <<"," <<b << "]";
    output = sout.str();
    cout <<"#" <<output <<"#" <<endl;
    return 0;
}





