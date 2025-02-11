/*
 * client.C
 *
 *  Created on: 11.09.2019
 *      Author: aml
 */

#include <string>
#include <iostream>
#include <unistd.h> //contains various constants
#include <cstdlib>
#include <ctime>
#include "SHA256.H"
#include "TASK1.H"
#include "SIMPLESOCKET.H"


using namespace std;

//Kindklasse von TCPClient
class PasswordClient : public TCPclient{
public:
    PasswordClient() : TCPclient(){};
    string randompwd (int pwdL, int alphabetL); //Funktion erzeugt ein zufälliges Passwort mit einer definierten Passwort- und Alphabetlänge

};


//Überschreiben der Funktion randompwd aus der Elternklasse
string PasswordClient::randompwd (int pwdL, int alphabetL) {
    string pwd;
    for (int i = 0; i < pwdL; i++){
        int randomNumb = rand() %alphabetL;
        pwd += TASK1::SYMBOLS[randomNumb];
    }

    pwd = "PWD[" + pwd + "]";

    return pwd; //Rückgabe eines zufälligen Passworts in der Form: PWD[Passwort]
}




int main() {
	srand(time(NULL));
	PasswordClient c;
	string host = "localhost";
	string msg;
	//Variablen
    int pwdL = 4; //definiert die Passwortlänge
    int alphabetL = 2; //definiert die Alphabetlänge
    int loop = 10; //definiert die Anzahl der Durchläufe

	//connect to host
	c.conn(host , 2023);

    cout<<"Password length: " << pwdL <<endl;
    cout<<"Alphabet length: " << alphabetL <<endl;
    cout<<"Alphabet: " << TASK1::SYMBOLS.substr(0,(alphabetL)) <<endl;
	int i=0;
	bool goOn=1;

	while(goOn){ // send and receive data



        for (int i = 0; i < loop; i++){
            int counter = 0; //Variable zur Erfassung der Anzahl der Versuche
            msg = "GenPWD[" + to_string(pwdL) + "," + to_string(alphabetL) + "]";
            cout <<"client sends: " <<msg <<endl;
            c.sendData(msg);
            msg = c.receive(32);
            cout <<"got response: " <<msg <<endl;

            if (msg == "done"){

                while (msg != "ACCESS ACCEPTED"){

                    msg = string(c.randompwd(pwdL,alphabetL));
                    cout <<"client sends: " <<msg <<endl;
                    c.sendData(msg);
                    msg = c.receive(32);
                    cout <<"got response: " <<msg <<endl;

                    if (msg == "Error"){
                        cout <<"Error occured" <<endl;
                        break;

                    }
                counter++;
                }
                cout <<"attempts: " <<counter <<endl;

            }




        }
        msg = string("BYEBYE");
        cout <<"client sends: " <<msg <<endl;
        c.sendData(msg);
        c.receive(32);
        cout <<"got response: " <<msg <<endl;
        goOn = 0;

	}
}


