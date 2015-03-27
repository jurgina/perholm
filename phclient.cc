/* myclient.cc: sample client program */
#include "connection.h"
#include "connectionclosedexception.h"
#include "encoding.h"
#include "HInterpreter.h"
#include "serverresponse.h"
#include "protocol.h"
#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <cstdlib>

using namespace std;


int main(int argc, char* argv[]) {
	if (argc != 3) {
		cerr << "Usage: myclient host-name port-number" << endl;
		exit(1);
	}
	
	int port = -1;
	try {
		port = stoi(argv[2]);
	} catch (exception& e) {
		cerr << "Wrong port number. " << e.what() << endl;
		exit(1);
	}
	
	shared_ptr<Connection> c(new Connection(argv[1], 1234));
	if (!c->isConnected()) {
		cerr << "Connection attempt failed" << endl;
		exit(1);
	}
	
	cout << "Write a command\nThe commands are:\n"<< HInterpreter::listCommands() << endl;
	int nbr=0;
	HInterpreter inter;
	ServerResponse response;
	while (c->isConnected()) {
		try {
			string input;
			getline(cin,input);
			if(input=="quit"){
				exit(1);
			}
			string msg=inter.interpret(input);
			string msg1;
			if(msg.size()>6){
				msg1=msg.substr(0,6);
			}
			if(msg== "Unvalid command"){
				cout << "The command you have entered is unvalid. Please enter a new command."<<endl;
				cout << HInterpreter::listCommands() << endl;
			}else if(msg1=="Unvalid" || msg1=="Help  "){
				cout<<msg<<endl;

			}else{
				writeString(msg,c);
				string serverResponse;
				serverResponse = readString(c);
				cout << "response from server is: " << response.interpret(serverResponse) <<endl;
			}
		} catch (ConnectionClosedException&) {
			cout << " no reply from server. Exiting." << endl;
			exit(1);
		}
	}
}

