/*
 * server.C
 *
 *  Created on: 11.09.2019
 *      Author: aml
 */
#include <iostream>
#include <cstdio> // standard input and output library
#include <cstdlib> // this includes functions regarding memory allocation
#include <cstring> // contains string functions
#include <cerrno> //It defines macros for reporting and retrieving error conditions through error codes
#include <ctime> //contains various functions for manipulating date and time

#include <unistd.h> //contains various constants
#include <sys/types.h> //contains a number of basic derived types that should be used whenever appropriate
#include <arpa/inet.h> // defines in_addr structure
#include <sys/socket.h> // for socket creation
#include <netinet/in.h> //contains constants and structures needed for internet domain addresses

#include "SIMPLESOCKET.H"
#include "TASK1.H"

using namespace std;

class PasswortServer : public TCPserver{
public:
    PasswortServer(int port, int bufferSize);    //int maxDataSizeRecv geht auch anstatt bufferSize
    string myResponse(string input);

protected:                                       //private aufgrund von Komplikationen entfernt

    TASK1::BlackBoxSafe *bb = nullptr;

};

int main(){


	srand(time(nullptr));
    PasswortServer srv(2022,25);
	srv.run();
}



string PasswortServer::myResponse(string input){

    int pwdL, alphabetL;

    if(input.compare(0,7,"GENPWD[") == 0){
        sscanf(input.c_str(),"GENPWD[%i,%i]",&pwdL,&alphabetL);

        if(bb != nullptr){
            delete bb;
            bb = nullptr;
        }
        bb = new TASK1::BlackBoxSafe(pwdL,alphabetL);
        return string("DONE");
    }

    if(input.compare(0,4,"PWD[") == 0 ){
        int posStart;
        int posEnd;
        posStart = input.find("[");
        posEnd = input.find ("]");
        string pwdGuess;
        pwdGuess = (input.substr(4,posEnd - posStart - 1));

        cout << "#" << pwdGuess << "#\n";
        return (bb->input(pwdGuess));
    }

{
            return string("ERROR");
            }


    return string("ERROR");
}


PasswortServer::PasswortServer(int port,int bufferSize) : TCPserver(port,bufferSize){
    bb = new TASK1::BlackBoxSafe(4,4);
}
