#include <string>
#include "encoding.h"
#include "connection.h"
#include "protocol.h"

using namespace std;

void writeString(const string& s, const shared_ptr<Connection>& conn){
	for (char c : s) {
		conn->write(c);
	}
}

string readString(const shared_ptr<Connection>& conn){
	string message;
	char c = conn->read();
	while(c != Protocol.COM_END){
		message += c;
		c = conn->read();
	}
	return message;
}

string convertStringToStringP(const string& s){
	string message;
	message += Protocol.PAR_STRING;
	message += ' ';
	message += s.size();
	for (char c: s){
		message += ' ';
		message += c;
	}
	return message;
}

string convertNumberToNumP(int num){
	string message;
	message += Protocol.PAR_NUM;
	message += ' ';
	message += num;
	return message;
}