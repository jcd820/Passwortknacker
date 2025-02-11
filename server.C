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
#include <sstream>
#include <cstdio>
#include "TASK1.H"
using namespace std;

//Kindklasse von TCPserver
class PasswortServer : public TCPserver{

public:
    ~PasswortServer();
    PasswortServer(int port, int buffersize);
    string myResponse(string input);

private:



protected:

    TASK1::BlackBoxSafe  *bb = nullptr;

};




int main(){
	srand(time(nullptr));
	PasswortServer srv(2023,25);
	srv.run();
}


//Überschreiben der beiden Konstruktoren aus der Elternklasse
PasswortServer::PasswortServer(int port, int buffersize) : TCPserver(port, buffersize){
    bb = new TASK1::BlackBoxSafe(4,4);
}

PasswortServer::~PasswortServer(){

}



//Überschreiben der Funktion myResponse aus der Elternklasse
string PasswortServer::myResponse(string input){
    stringstream o;
    int pwdL, alphabetL;

    //Antwort auf GenPWD
    if(input.compare(0,7,"GenPWD[") == 0){
        sscanf(input.c_str(),"GenPWD[%i,%i]",&pwdL,&alphabetL);
        if (bb != nullptr){
            delete bb;
            bb = nullptr;
        }
        bb = new TASK1::BlackBoxSafe(pwdL,alphabetL);
        std::cout <<"Password chiffre: " <<bb->pwd_ <<endl;
        return string("done"); //Rückgabe eines neuen zufälligen Passworts in der gewünschten Passwort- und Alphabetlänge
    }
    //Antwort auf PWD
    if (input.compare(0,4,"PWD[") == 0){
        int posStart;
        int posEnd;
        posStart = input.find("[");
        posEnd = input.find("]");
        string pwdGuess;
        pwdGuess = input.substr(4,(posEnd-1) - posStart);
        std::cout << "#" <<pwdGuess <<"# \n";
        return (bb->input(pwdGuess)); //Rückgabe von ACCESS DENIED oder ACCESS ACCEPTED (siehe Task1.C Funktion BlackBoxUnsafe::input(string strPwd)

    }


    return string("Error"); //Anwort bei allen sonstigen Nachrichten

}
