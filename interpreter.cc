#include <string>
#include <iostream>
#include <istream>
#include "database.h"
#include "protocol.h"
#include "encoding.h"
#include "article.h"

using namespace std;

string Interpreter::interpret(const std::string& message){
	istream input(message);
	char command;
	input >> command;
	switch(command){
		case Protocol.COM_LIST_NG: 
			return messageListNewsGroups(message);
		case Protocol.COM_CREATE_NG: 
			return messageCreateNewsGroups(message);
		case Protocol.COM_DELETE_NG: 
			return messageDeleteNewsGroups(message);
		case Protocol.COM_LIST_ART: 
			return messageListArticles(message);
		case Protocol.COM_CREATE_ART: 
			return messageCreateArticle(message);
		case Protocol.COM_DELETE_ART: 
			return messageDeleteArticle(message);
		default: cout << "Something is wrong in interpret server side, wrong command code" << endl;
			break; 
	}
	return ":-( interpret\n";
}

/* Returns the message from the list newsgroup command */
std::string Interpreter::messageListNewsGroups(const istream& message){
	//std::vector<string> newsgroups = db.listNewsGroups();
	return "Simon fixar ";
}

/* Returns the message from the create newsgroup command */
std::string Interpreter::messageCreateNewsGroup(const istream& message){
	return "";
}

/* Returns the message from the delete newsgroup command */
std::string Interpreter::messageDeleteNewsGroups(const istream& message){
	return "";
}

/* Returns the message from the list articles command */
std::string Interpreter::messageListArticles(const istream& message){
	istream input(message);
	char c;
	input.get(c); 	//c = Par_Num
	input.get(c);	//c = N
	vector<Article> articles = db.listArticles(c);
	string response;
	response += Protocol.ANS_LIST_ART;
	response += ' ';
	if (articles != nullptr) {		// If the newsgroup exists
		response += Protocol.ANS_ACK;
		response += ' ';
		response += convertNumberToNumP(articles.size());
		response += ' ';
		for (size_t i = 0; i < articles.size();++i){
			response += convertNumberToNumP(i);
		    response += ' ';
		    response += convertStringToStringP(articles[i].getTitle());
		    response += ' ';
		}
	} else {						// If the newsgroup doesn't exist
		response += Protocol.ANS_NAK;
		response += ' ';
		response += Protocol.ERR_NG_DOES_NOT_EXIST;
	}
	response += Protocol.ANS_END;
	return response;
}

/* Returns the message from the create article command */
std::string Interpreter::messageCreateArticle(const istream& message){
	string response;
	char c;
	char groupID;
	message >> c;			// Par_num
	message >> groupID;		// N

	//Collects title
	string title;
	message >> c;
	message >> c;			//N
	for (char i = 0; i != c; ++i) {
		message >> c;
		title += c;
	}
	return "";
}

/* Returns the message from the delete article command */
std::string Interpreter::messageDeleteArticle(const istream& message){
	return "";
}

