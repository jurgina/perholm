/* myserver.cc: sample server program */
#include "server.h"
#include "connection.h"
#include "database.h"
#include "interpreter.h"
#include "memoryDB.h"
#include "driveDB.h"
#include "article.h"
#include "connectionclosedexception.h"

#include <memory>
#include <iostream>
#include <string>
#include <stdexcept>
#include <cstdlib>

using namespace std;


int main(int argc, char* argv[]){
	if (argc <3) {
		cerr << "Usage: myserver port-number" << endl;
		exit(1);
	}
	
	int port = -1;
	try {
		port = 1235;
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
	DataBase* db;
	string ar=argv[2];
	if(ar=="drive"){
		string path=argv[3];
		
		db=new driveDB(path);
		cout<<"Running drive DB"<<endl;
	}else{
		db=new memoryDB();
		cout<<"Running memory DB"<<endl;
	}
	
	InterPreter inter(*db);
	while (true) {
		auto conn = server.waitForActivity();
		if (conn != nullptr) {
			try {
				cout<<"Reading"<<endl;
				string msg=readString(conn);
				string out=inter.interpret(msg);
				writeString(out,conn);
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
