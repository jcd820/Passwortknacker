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
using namespace std;

class PasswortServer : public TCPserver{
private:

public:
    //~PasswortServer();
    PasswortServer(int port, int buffersize);

protected:

    string myResponse(string input);

};




int main(){
	srand(time(nullptr));
	PasswortServer srv(2022,25);
	srv.run();
}


PasswortServer::PasswortServer(int port, int buffersize) : TCPserver(port, buffersize){

}


string PasswortServer::myResponse(string input){

    if(0 == input.compare(0,6,"COORD[")){

        return string ("OK");

    }else{

        return string ("UNKOWN_COMAND");
    }

    return string ("ERROR");
}

