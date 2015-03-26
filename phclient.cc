/* myclient.cc: sample client program */
#include "connection.h"
#include "connectionclosedexception.h"
#include "encoding.h"

#include "protocol.h"
#include <iostream>
#include <string>
#include <stdexcept>
#include <cstdlib>

using namespace std;

/*
 * Send an integer to the server as four bytes.
 */
void writeNumber(const Connection& conn, int value) {
	conn.write((value >> 24) & 0xFF);
	conn.write((value >> 16) & 0xFF);
	conn.write((value >> 8)	 & 0xFF);
	conn.write(value & 0xFF);
}

/*
 * Read a string from the server.
 */
string readString(const Connection& conn) {
	string s;
	char ch;
	while ((ch = conn.read()) != '$') {
		s += ch;
	}
	return s;
}

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
	
	Connection conn(argv[1], port);
	if (!conn.isConnected()) {
		cerr << "Connection attempt failed" << endl;
		exit(1);
	}
	shared_ptr<Connection> c(new Connection(argv[1], 1234));
	cout << "Sending a string";
	int nbr=0;
	while (nbr!=1) {
		try {
			string msg=convertStringToStringP("c8");
			writeString(msg,c);
			/*cout << nbr << " is ...";
			writeNumber(conn, nbr);
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

