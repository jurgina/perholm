#include <string>
#include <iostream>
#include <sstream>
#include "database.h"
#include "protocol.h"
#include "encoding.h"
#include "article.h"
#include "serverresponse.h"

using namespace std;


/* Returns the message from the list newsgroup command */
string ServerResponse::messageListNewsGroups(istringstream& message){
	string response;
	int N = convertNumPToNum(message);
	if (N != 0) {
		response += "The newsgroups are:\n"; 
		for (int i = 0; i != N; ++i) {
			int num = convertNumPToNum(message);
			response += to_string(num);
			response += ": ";
			response += convertStringPToString(message);
			response += "\n";
		}
	} else {
		response += "No newsgroups exists";
	}
	return response;
}

/* Returns the message from the create newsgroup command */
string ServerResponse::messageCreateNewsGroup(istringstream& message){
	string response;
	char ack;
	message >> ack;
	if(ack ==  Protocol::ANS_ACK){
		response += "Newsgroup successfully created";
	}else{
		response += "Newsgroup already exist";
	}
	return response;
}


/* Returns the message from the delete newsgroup command */
string ServerResponse::messageDeleteNewsGroup(istringstream& message){
	string response;
	char ack;
	message >> ack;
	if(ack ==  Protocol::ANS_ACK){
		response += "Newsgroup successfully deleted";
	}else{
		response += "Newsgroup does not exist";
	}
	return response;
}

/* Returns the message from the list articles command */
string ServerResponse::messageListArticles(istringstream& message){
	string response;
	char ack;
	message >> ack;
	if(ack ==  Protocol::ANS_ACK){
		int nbrArticles = convertNumPToNum(message);
		if (nbrArticles != 0) {
		response += "The articles are:\n"; 
			for (int i = 0; i != nbrArticles; ++i) {
				int num = convertNumPToNum(message);
				response += to_string(num);
				response += ": ";
				response += convertStringPToString(message);
				response += "\n";
			}
		} else {
		response += "No articles exists";
		}
	}else{
		response += "Newsgroup does not exist";
	}
	return response;
}

/* Returns the message from the create article command */
string ServerResponse::messageCreateArticle(istringstream& message){
	string response;
	char ack;
	message >> ack;
	if(ack ==  Protocol::ANS_ACK){
		response += "Article successfully created";
	}else{
		response += "Newsgroup does not exist";
		}
	return response;
}

/* Returns the message from the delete article command */
string ServerResponse::messageDeleteArticle(istringstream& message){
	string response;
	char ack;
	message >> ack;
	if(ack ==  Protocol::ANS_ACK){
		response += "Article successfully deleted";
	}else{
		message >> ack;
		if(ack == Protocol::ERR_NG_DOES_NOT_EXIST){
		response += "Newsgroup does not exist";
		}else{
		response += "Article does not exist";
			}
		}
	return response;
}

/* Returns the message from the get article command */
string ServerResponse::messageGetArticle(istringstream& message){
	string response;
	char ack;
	message >> ack;
	if(ack ==  Protocol::ANS_ACK){
		response += "Title: ";
		response += convertStringPToString(message);
		response += "\nAuthor: ";
		response += convertStringPToString(message);
		response += "\n";
		response += convertStringPToString(message);
	}else{
		message >> ack;
		if(ack == Protocol::ERR_NG_DOES_NOT_EXIST){
			response += "Newsgroup does not exist";
		}else{
			response += "Article does not exist";
			}
		}
	return response;
}

string ServerResponse::interpret(const std::string& message){
	istringstream input(message);
	char command;
	input >> command;
	switch(command){
		case Protocol::ANS_LIST_NG:
			return messageListNewsGroups(input);
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
		default: cout << "Something is wrong in interpret client-serverresponse side, wrong command code" << endl;
			break; 
	}
	return ":-( interpret\n";
}
