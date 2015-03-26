/* myserver.cc: sample server program */
#include "server.h"
#include "connection.h"
#include "database.h"
#include "interpreter.h"
#include "memoryDB.h"
#include "article.h"
#include "connectionclosedexception.h"

#include <memory>
#include <iostream>
#include <string>
#include <stdexcept>
#include <cstdlib>

using namespace std;


int main(int argc, char* argv[]){
	if (argc != 2) {
		cerr << "Usage: myserver port-number" << endl;
		exit(1);
	}
	
	int port = -1;
	try {
		port = 1234;
		//port = stoi(argv[1]);
	} catch (exception& e) {
		cerr << "Wrong port number. " << e.what() << endl;
		exit(1);
	}
	
	Server server(port);
	if (!server.isReady()) {
		cerr << "Server initialization error." << endl;
		exit(1);
	}
	DataBase* db=new memoryDB();
	InterPreter inter(*db);
	while (true) {
		auto conn = server.waitForActivity();
		if (conn != nullptr) {
			try {
				//char c=conn->read();
				cout<<"reading"<<endl;
				string msg=readString(conn);
				//cout<<c<<endl;
				cout<<msg<<endl;
			} catch (ConnectionClosedException&) {
				server.deregisterConnection(conn);
				cout << "Client closed connection" << endl;
			}
		} else {
			conn = make_shared<Connection>();
			server.registerConnection(conn);
			cout << "New client connects" << endl;
		}
	}
}
