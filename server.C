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

using namespace std;

class PasswortServer : public TCPserver{

public:
    //~PasswortServer();
    PasswortServer(int port, int buffersize);
    string myResponse(string input);

private:



protected:

};




int main(){
	srand(time(nullptr));
	PasswortServer srv(2023,25);
	srv.run();
}



PasswortServer::PasswortServer(int port, int buffersize) : TCPserver(port, buffersize){

}






string PasswortServer::myResponse(string input){
    stringstream o;
    int x,y,e;

    if(input.compare(0,6,"COORD[")){
        sscanf(input.c_str(),"COORD[%i,%i]",&x,&y);
        if (e != 2){
            return string("COULD NOT READ COORDINATES!");
        }
        o << "SUMME[" << (x+y) << "]";
        return (o.str());

    }

    return string("UNKNOWN_COMMAND");

}
