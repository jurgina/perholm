#include <string>
#include <iostream>
#include <sstream>
#include "database.h"
#include "protocol.h"
#include "encoding.h"
#include "article.h"

using namespace std;

string Interpreter::interpret(const std::string& message){
	istringstream input(message);
	char command;
	input >> command;
	switch(command){
		case Protocol::COM_LIST_NG: 
			return messageListNewsGroups(message);
		case Protocol::COM_CREATE_NG: 
			return messageCreateNewsGroups(message);
		case Protocol::COM_DELETE_NG: 
			return messageDeleteNewsGroups(message);
		case Protocol::COM_LIST_ART: 
			return messageListArticles(message);
		case Protocol::COM_CREATE_ART: 
			return messageCreateArticle(message);
		case Protocol::COM_DELETE_ART: 
			return messageDeleteArticle(message);
		default: cout << "Something is wrong in interpret server side, wrong command code" << endl;
			break; 
	}
	return ":-( interpret\n";
}

/* Returns the message from the list newsgroup command */
string Interpreter::messageListNewsGroups(const istringstream& message){
	vector<std::string> newsgroups = db.listNewsGroups();
	string response;
	response += Protocol::ANS_LIST_NG;
	response += ' ';
	if(newsgroups != nullptr){
		response += convertNumberToNumP(newsgroups.size());
		response += ' ';
		size_t i = 0;
		for(auto p: newsgroups){
			response += convertNumberToNumP(i);
			response += ' ';
			response += convertStringToStringP(p);
			response += ' ';	
			++i;
		}
	}else{
		response += convertNumberToNumP(0);
		response += ' ';
	}
	response += Protocol::ANS_END;
	return response;
}

/* Returns the message from the create newsgroup command */
string Interpreter::messageCreateNewsGroup(const istringstream& message){
	string title = convertStringPToString(message);
	bool success = db.createNewsGroup(title);
	string response;
	response += Protocol::ANS_CREATE_NG;
	response += ' ';
	
	if(success){
		response +=Protocol::ANS_ACK;
	}else{
		response +=Protocol::ANS_NAK;
		response+=' ';
		response +=Protocol::ERR_NG_ALREADY_EXIST;
	}
	response+=' ';
	response +=Protocol::ANS_END;	

	return response;
}

/* Returns the message from the delete newsgroup command */
string Interpreter::messageDeleteNewsGroups(const istringstream& message){
	string title = convertStringPToString(message);
	bool success = db.deleteNewsGroup(title);
	string response;
	response += Protocol::ANS_DELETE_NG;
	response += ' ';
	
	if(success){
		response +=Protocol::ANS_ACK;
	}else{
		response +=Protocol::ANS_NAK;
		response+=' ';
		response +=Protocol::ERR_NG_DOES_NOT_EXIST;
	}
	response+=' ';
	response +=Protocol::ANS_END;	
	return response;
}

/* Returns the message from the list articles command */
string Interpreter::messageListArticles(const istringstream& message){
	char c;
	input.get(c); 	//c = Par_Num
	input.get(c);	//c = N
	vector<Article> articles = db.listArticles(c);
	string response;
	response += Protocol::ANS_LIST_ART;
	response += ' ';
	if (articles != nullptr) {		// If the newsgroup exists
		response += Protocol::ANS_ACK;
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
		response += Protocol::ANS_NAK;
		response += ' ';
		response += Protocol::ERR_NG_DOES_NOT_EXIST;
	}
	response += Protocol::ANS_END;
	return response;
}

/* Returns the message from the create article command */
string Interpreter::messageCreateArticle(const istringstream& message){
	string response;
	char c;
	char groupID;
	message >> c;			// Par_num
	message >> groupID;		// N

	string title = convertStringPToString(message);
	string author = convertStringPToString(message);
	string text = convertStringPToString(message);
	bool success = db.createArticle(groupID, title, author, text);

	//write response to client
	response += Protocol::ANS_CREATE_ART;
	response += ' ';
	if(success){
		response += Protocol::ANS_ACK;
		response += ' ';
	}else{
		response += Protocol::ANS_NAK;
		response += ' ';
		response += Protocol::ERR_NG_DOES_NOT_EXIST;
		response += ' ';
	}
	response += Protocol::ANS_END;
	return response;
}

/* Returns the message from the delete article command */
string Interpreter::messageDeleteArticle(const istringstream& message){
	char c;
	char groupID;
	message >> c;			// Par_num
	message >> groupID;		// N
	char articleID;
	message >> c;
	message >> articleID;

	int success = db.deleteArticle(groupID,articleID);
	string response;
	response += Protocol::ANS_DELETE_ART;
	response += ' ';
	if(success == 2){
		response += Protocol::ANS_ACK;
	}else if(success == 1){
		response += Protocol::ANS_NAK;
		response += ' ';
		response += Protocol::ERR_NG_DOES_NOT_EXIST;
		
	}else if(success == 0){
		response += Protocol::ANS_NAK;
		response += ' ';
		response += Protocol::ERR_NG_ART_DOES_NOT_EXIST;
	}
	response += ' ';
	response += Protocol::ANS_END;
	return response;
}

