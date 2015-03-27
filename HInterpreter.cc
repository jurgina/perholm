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
	string name;
	if(message>>name){
		response +=convertStringToStringP(name);
		response +=  Protocol::COM_END;
		return response;
	}
	return "Unvalid format of name. Name of a newsgroup should be a word.";
	
}

/* Returns the message from the delete newsgroup command */
string HInterpreter::messageDeleteNewsGroup(istringstream& message){
	string response;
	response += Protocol::COM_DELETE_NG;
	int id;
	if(message>>id){
		response +=convertNumberToNumP(id);
		response +=  Protocol::COM_END;
		return response;
	}
	return "Unvalid format of id. Id of a newsgroup a should be a number.";
}

/* Returns the message from the list articles command */
string HInterpreter::messageListArticles(istringstream& message){
	string response;
	response += Protocol::COM_LIST_ART;
	int id;
	if(message>>id){
		response +=convertNumberToNumP(id);
		response +=  Protocol::COM_END;
		return response;
	}
	return "Unvalid format of id. Id of a newsgroup should be a number.";
	
}

/* Returns the message from the create article command */
string HInterpreter::messageCreateArticle(istringstream& message){
	string response;
	response += Protocol::COM_CREATE_ART;
	int id;
	if(!(message>>id)){
		return "Unvalid format of id. Id of a newsgroup should be a number.";
	}
	response +=convertNumberToNumP(id);
	string title;
	if(!(message>>title)){
		return "Unvalid format of title. Title of an article should be a word.";
	}
	response+=convertStringToStringP(title);
	
	string author;
	if(!(message>>author)){
		return "Unvalid format of author. The author of an article should be a word.";
	}
	response+=convertStringToStringP(author);
	string text;
	char ctmp;
	while(message>>ctmp){
		text+=ctmp;
	}
	response+=convertStringToStringP(text);
	response +=  Protocol::COM_END;
	return response;
}

/* Returns the message from the delete article command */
string HInterpreter::messageDeleteArticle(istringstream& message){
	string response;
	response += Protocol::COM_DELETE_ART;
	int id;
	if(!(message>>id)){
		return "Unvalid format of id. Id of a newsgroup should be a number.";
	}
	response +=convertNumberToNumP(id);
	int idA;
	if(!(message>>idA)){
		return "Unvalid format of id. Id of an article should be a number.";
	}
	response+=convertNumberToNumP(idA);
	response +=  Protocol::COM_END;
	return response;
}

/* Returns the message from the get article command */
string HInterpreter::messageGetArticle(istringstream& message){
	string response;
	response += Protocol::COM_GET_ART;
	int id;
	if(!(message>>id)){
		return "Unvalid format of id. Id of a newsgroup should be a number.";
	}
	response +=convertNumberToNumP(id);
	int idA;
	if(!(message>>idA)){
		return "Unvalid format of id. Id of an article should be a number.";
	}
	response+=convertNumberToNumP(idA);
	response +=  Protocol::COM_END;
	
	return response;
}

string HInterpreter::messageHelp(istringstream& message){
	string command;
	message >> command;
	if(command=="list_ng"){
		return "Help  \n list_ng \n No input parameters.\n Lists all news groups";
	}else if(command=="create_ng"){
		return "Help  \n create_ng ngName \n string ngName - newsgroup name.\n Creates a newsgroup with name ngName. ";
	}else if(command=="delete_ng"){
		return "Help  \n delete_ng ngID \n int ngID - newsgroup ID \n Deletes the newsgroup with newsgroup ID ngID if it exists.";
	}else if(command=="list_a"){
		return "Help  \n list_a ngID \n int ngID - newsgroup ID \n Lists all of the articles in the newsgroup with newsgroup ID ngID if it exists.";
	}else if(command=="create_a"){
		return "Help  \n create_a ngID titleA authorA textA \n int ngID - newsgroup ID \n string titleA - article title  \n string authorA - article author  \n string textA - contents of article \n Creates an article in the newsgroup with newsgroup ID ngID, title titleA author authorA and contents textA.";
	}else if(command=="delete_a"){
		return "Help  \n delete_a ngID aID \n int ngID - newsgroup ID \n int ngID - newsgroup ID \n Deletes the article with newsgroup ID ngID and article ID aID.";
	}else if(command=="get_a"){
		return "Help  \n get_a ngID aID \n int ngID - newsgroup ID \n int ngID - newsgroup ID \n Shows the article with newsgroup ID ngID and article ID aID.";
	}
	return  "Help  \n"+listCommands() ;
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
	}else if(command=="help"){
		return messageHelp(input);
	}
	return  "Unvalid command" ;
}


string HInterpreter::listCommands() {
	string s = "list_ng - List all newsgroups\n";
	s += "create_ng - Create a new newsgroup\n";
	s += "delete_ng - Deletes a newsgroup\n";
	s += "list_a - List articles in a newgroup\n";
	s += "create_a - Create article\n";
	s += "delete_a - Delete article\n";	
	s += "get_a - Displays article\n";
	s += "quit - Quit the program\n";
	return s;
}
