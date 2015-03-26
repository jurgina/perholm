/* myclient.cc: sample client program */
#include "connection.h"
#include "connectionclosedexception.h"
#include "encoding.h"
#include "HInterpreter.h"
#include "protocol.h"
#include <iostream>
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
		//port = stoi(argv[2]);
		port = 1234;
	} catch (exception& e) {
		cerr << "Wrong port number. " << e.what() << endl;
		exit(1);
	}
	
	shared_ptr<Connection> c(new Connection(argv[1], 1234));
	if (!c->isConnected()) {
		cerr << "Connection attempt failed" << endl;
		exit(1);
	}
	
	cout << "Write a command";
	int nbr=0;
	HInterpreter inter;
	while (nbr!=1) {
		try {
			string input;
			getline(cin,input);
			string msg=inter.interpret(input);
			writeString(msg,c);
			cout << " " << msg << " is ...";
			string reply = readString(c);
			//add server interpeter
			++nbr;
		} catch (ConnectionClosedException&) {
			cout << " no reply from server. Exiting." << endl;
			exit(1);
		}
	}
}

