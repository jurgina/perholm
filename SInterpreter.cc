#include <string>
#include <iostream>
#include <sstream>
#include "protocol.h"
#include "encoding.h"
#include "article.h"
#include "SInterpreter.h"

using namespace std;


/* Returns the message from the list newsgroup command */
string SInterpreter::messageListNewsGroups(){
	string response;
	
	response += Protocol::COM_LIST_NG;
	response +=  Protocol::COM_END;
	return response;
}

/* Returns the message from the create newsgroup command */
string SInterpreter::messageCreateNewsGroup(istringstream& message){
	string response;
	
	response += Protocol::COM_CREATE_NG;
	response +=' ';
	string name;
	message>>name;
	response +=convertStringToStringP(name);
	response +=' ';
	response +=  Protocol::COM_END;
	
	return response;
}

/* Returns the message from the delete newsgroup command */
string SInterpreter::messageDeleteNewsGroup(istringstream& message){
string response;
	
	response += Protocol::COM_DELETE_NG;
	response +=' ';
	int id;
	message>>id;
	response +=convertNumberToNumP(id);
	response +=' ';
	response +=  Protocol::COM_END;
	
	return response;
}

/* Returns the message from the list articles command */
string SInterpreter::messageListArticles(istringstream& message){
	string response;
	response += Protocol::COM_LIST_ART;
	response +=' ';
	int id;
	message>>id;
	response +=convertNumberToNumP(id);
	response +=' ';
	response +=  Protocol::COM_END;
	
	return response;
}

/* Returns the message from the create article command */
string SInterpreter::messageCreateArticle(istringstream& message){
	string response;
	response += Protocol::COM_CREATE_ART;
	response +=' ';
	int id;
	message>>id;
	response +=convertNumberToNumP(id);
	response +=' ';
	string p;
	message>>p;
	response+=convertStringToStringP(p);
	response +=' ';
	string p2;
	message>>p2;
	response+=convertStringToStringP(p2);
	response +=' ';
	string p3;
	message>>p3;
	response+=convertStringToStringP(p3);
	
	response +=' ';
	response +=  Protocol::COM_END;
	
	return response;
}

/* Returns the message from the delete article command */
string SInterpreter::messageDeleteArticle(istringstream& message){
	string response;
	response += Protocol::COM_DELETE_ART;
	response +=' ';
	int id;
	message>>id;
	response +=convertNumberToNumP(id);
	response +=' ';
	int idA;
	message>>idA;
	response+=convertNumberToNumP(idA);
	
	response +=' ';
	response +=  Protocol::COM_END;
	
	return response;
}

/* Returns the message from the get article command */
string SInterpreter::messageGetArticle(istringstream& message){
	string response;
	response += Protocol::COM_GET_ART;
	response +=' ';
	int id;
	message>>id;
	response +=convertNumberToNumP(id);
	response +=' ';
	int idA;
	message>>idA;
	response+=convertNumberToNumP(idA);
	
	response +=' ';
	response +=  Protocol::COM_END;
	
	return response;
}

string SInterpreter::interpret(const std::string& message){
	istringstream input(message);
	char command;
	input >> command;
	switch(command){
		case Protocol::ANS_LIST_NG: 
			return messageListNewsGroups();
		case Protocol::ANS_CREATE_NG: 
			return messageCreateNewsGroup(input);
		case Protocol::ANS_DELETE_NG: 
			return messageDeleteNewsGroup(input);
		case Protocol::ANS_LIST_ART: 
			return messageListArticles(input);
		case Protocol::ANS_CREATE_ART: 
			return messageCreateArticle(input);
		case Protocol::ANS_DELETE_ART: 
			return messageDeleteArticle(input);
		case Protocol::ANS_GET_ART: 
			return messageGetArticle(input);
		default: cout << "Something is wrong in interpret server side, wrong command code" << endl;
			break; 
	}
	return ":-( interpret\n";
}
