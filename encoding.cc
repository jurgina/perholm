#include <string>
#include <memory>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>
#include "encoding.h"
#include "connection.h"
#include "protocol.h"
#include <stdio.h>

using namespace std;

void writeString(const string& s, const shared_ptr<Connection>& conn){
	for (char c : s) {
		conn->write(c);
	}
}

string readString(const shared_ptr<Connection>& conn){
	string message;
	char c = conn->read();
	
	while(c != Protocol::COM_END&&c != Protocol::ANS_END){
		message += c;

		c = conn->read();
	}
	
	return message;
}

string convertStringToStringP(const string& s){
	string message;
	message += Protocol::PAR_STRING;
	// message += ' ';
	vector<unsigned char> v = intToBytes(s.size());
	for_each(v.begin(), v.end(), [&] (char c) {message += c;});
	for (char c: s){
		// message += ' ';
		message += c;
	}
	return message;
}

string convertNumberToNumP(int num){
	string message;
	message += Protocol::PAR_NUM;
	vector<unsigned char> v = intToBytes(num);
	for_each(v.begin(), v.end(), [&] (char c) {/*message += ' ';*/ message += c;});
	return message;
}

string convertStringPToString(istringstream& message){
	string s;
	char c;
	message >> c;
	vector<unsigned char> v;
	
	message.get(c);
	v.push_back(c); 
	
	message.get(c);
	v.push_back(c); 
	
	message.get(c);
	v.push_back(c); 
	
	message.get(c);
	v.push_back(c); 

	// message >> v[1];
	// message >> v[2];
	// message >> v[3];
	int N = bytesToInt(v);
	cout << "N " << N << endl;
	for (int i = 0; i != N; ++i) {
		message.get(c);
		s += c;
	}
	return s;
}

int convertNumPToNum(istringstream& message) {
	char c;
	message >> c;
	vector<unsigned char> v(4);
	message >> v[0];
	message >> v[1];
	message >> v[2];
	message >> v[3];
	int N = bytesToInt(v);
	return N;
}

vector<unsigned char> intToBytes(int num) {
	vector<unsigned char> v(4);
	for (int i = 0; i != 4; ++i) {
		v[3 - i] = (num >> (i*8));
	}
	return v;
}

int bytesToInt(vector<unsigned char>& v) {
	unsigned int a0 = v[0];
	unsigned int a1 = v[1];
	unsigned int a2 = v[2];
	unsigned int a3 = v[3];
	int num = (a0 << 24) | (a1 << 16) | (a2 << 8) | a3;
	printf("%u %u %u %u\n", v[0], v[1], v[2], v[3]);
	return num;
}