/* myclient.cc: sample client program */
#include "connection.h"
#include "connectionclosedexception.h"
#include "encoding.h"
#include "HInterpreter.h"
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
	
	cout << "Write a command"<<endl;
	int nbr=0;
	HInterpreter inter;
	while (nbr!=10) {
		try {
			string floff = convertNumberToNumP(0);
			for(char ccc:floff) {
				cout <<(int) ccc << " ";
			}
			cout << endl;

			string input;
			getline(cin,input);
			string msg=inter.interpret(input);
			//writeString(msg,c);
			for(auto cc: msg){
				cout<<(int)cc<<' ';
			}
			cout<<endl;
			cout << " " << msg << " is ..."<<endl;
			//string reply = readString(c);
			//add server interpeter
			/*
			string msg;
			msg += Protocol::COM_LIST_NG;
			msg += ' ';
			msg += Protocol::COM_END;
			writeString(msg,c);
			//cout << msg.size( << endl;
			cout << " " << msg << " is ..." << endl;
			/*writeNumber(conn, nbr);
			string reply = readString(conn);
			cout << " " << reply << endl;
			cout << "Type another number: ";*/
			++nbr;
		} catch (ConnectionClosedException&) {
			cout << " no reply from server. Exiting." << endl;
			exit(1);
		}
	}
}

