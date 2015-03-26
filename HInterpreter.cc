#include <string>
#include <iostream>
#include <sstream>
#include "protocol.h"
#include "encoding.h"
#include "article.h"
#include "HInterpreter.h"

using namespace std;


/* Returns the message from the list newsgroup command */
string HInterpreter::messageListNewsGroups(){
	string response;
	
	response += Protocol::COM_LIST_NG;
	response +=  Protocol::COM_END;
	return response;
}

/* Returns the message from the create newsgroup command */
string HInterpreter::messageCreateNewsGroup(istringstream& message){
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
string HInterpreter::messageDeleteNewsGroup(istringstream& message){
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
string HInterpreter::messageListArticles(istringstream& message){
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
string HInterpreter::messageCreateArticle(istringstream& message){
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
string HInterpreter::messageDeleteArticle(istringstream& message){
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
string HInterpreter::messageGetArticle(istringstream& message){
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

string HInterpreter::interpret(const std::string& message){
	istringstream input(message);
	string command;
	input >> command;
	if(command=="list_ng"){
		return messageListNewsGroups();
	}else if(command=="create_ng"){
		return messageCreateNewsGroup(input);
	}else if(command=="delete_ng"){
		return messageDeleteNewsGroup(input);
	}else if(command=="list_a"){
		return messageListArticles(input);
	}else if(command=="create_a"){
		return messageCreateArticle(input);
	}else if(command=="delete_a"){
		return messageDeleteArticle(input);
	}else if(command=="get_a"){
		return messageGetArticle(input);
	}
	
	cout << "Unvalid command" << endl;
	return ":-( interpret\n";
}
