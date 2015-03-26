#include <string>
#include <iostream>
#include <sstream>
#include "database.h"
#include "protocol.h"
#include "encoding.h"
#include "article.h"
#include "interpreter.h"

using namespace std;


/* Returns the message from the list newsgroup command */
string InterPreter::messageListNewsGroups(istringstream& message){
	string response;
	int N = convertNumPToNum(message);
	if (N != 0) {
		response += "The newsgroups are:\n"; 
		for (int i = 0; i != N; ++i) {
			int num = convertNumPToNum(message);
			response += num + ": ";
			response += convertStringPToString(message);
			response += "\n";
		}
	} else {
		response += "Sorry no newsgroups exists";
	}
	return response;
}

/* Returns the message from the create newsgroup command */
string InterPreter::messageCreateNewsGroup(istringstream& message){
	string title = convertStringPToString(message);
	bool success = db.createNewsGroup(title);
	string response;
	response += Protocol::ANS_CREATE_NG;
	  
	
	if(success){
		response +=Protocol::ANS_ACK;
	}else{
		response +=Protocol::ANS_NAK;
		// response+=' ';
		response +=Protocol::ERR_NG_ALREADY_EXISTS;
	}
	// response+=' ';
	response +=Protocol::ANS_END;	

	return response;
}

/* Returns the message from the delete newsgroup command */
string InterPreter::messageDeleteNewsGroup(istringstream& message){
	int title = convertNumPToNum(message);
	bool success = db.deleteNewsGroup(title);
	string response;
	response += Protocol::ANS_DELETE_NG;
	  
	
	if(success){
		response +=Protocol::ANS_ACK;
	}else{
		response +=Protocol::ANS_NAK;
		// response+=' ';
		response +=Protocol::ERR_NG_DOES_NOT_EXIST;
	}
	// response+=' ';
	response +=Protocol::ANS_END;	
	return response;
}

/* Returns the message from the list articles command */
string InterPreter::messageListArticles(istringstream& message){
	int c = convertNumPToNum(message);
	vector<Article> articles = db.listArticles(c);
	string response;
	response += Protocol::ANS_LIST_ART;
	  
	if (articles.size() != 0) {		// If the newsgroup exists
		response += Protocol::ANS_ACK;
		  
		response += convertNumberToNumP(articles.size());
		  
		for (size_t i = 0; i < articles.size();++i){
			response += convertNumberToNumP(i);
		      
		    response += convertStringToStringP(articles[i].getTitle());
		      
		}
	} else {						// If the newsgroup doesn't exist
		response += Protocol::ANS_NAK;
		  
		response += Protocol::ERR_NG_DOES_NOT_EXIST;
	}
	response += Protocol::ANS_END;
	return response;
}

/* Returns the message from the create article command */
string InterPreter::messageCreateArticle(istringstream& message){
	string response;
	int groupID = convertNumPToNum(message);
	string title = convertStringPToString(message);
	string author = convertStringPToString(message);
	string text = convertStringPToString(message);
	bool success = db.createArticle(groupID, title, author, text);

	//write response to client
	response += Protocol::ANS_CREATE_ART;
	  
	if(success){
		response += Protocol::ANS_ACK;  
	}else{
		response += Protocol::ANS_NAK;
		response += Protocol::ERR_NG_DOES_NOT_EXIST;
	}
	response += Protocol::ANS_END;
	return response;
}

/* Returns the message from the delete article command */
string InterPreter::messageDeleteArticle(istringstream& message){
	int groupID = convertNumPToNum(message);
	int articleID = convertNumPToNum(message);
	int success = db.deleteArticle(groupID,articleID);
	string response;
	response += Protocol::ANS_DELETE_ART;
	  
	if(success == 2){
		response += Protocol::ANS_ACK;
	}else if(success == 1){
		response += Protocol::ANS_NAK;
		response += Protocol::ERR_NG_DOES_NOT_EXIST;
	}else if(success == 0){
		response += Protocol::ANS_NAK;
		response += Protocol::ERR_ART_DOES_NOT_EXIST;
	}
	  
	response += Protocol::ANS_END;
	return response;
}

/* Returns the message from the get article command */
string InterPreter::messageGetArticle(istringstream& message){
	int groupID = convertNumPToNum(message);
	int articleID = convertNumPToNum(message);	
	string response;
	response += Protocol::ANS_GET_ART;
	  

	Article* article = db.getArticle(groupID,articleID);

	if (article != nullptr) {	
		response += Protocol::ANS_ACK;
		response += convertStringToStringP(article->getTitle());
		response += convertStringToStringP(article->getAuthor());
		response += convertStringToStringP(article->getText());
	} else {
		response += Protocol::ANS_NAK;
		//fixa fall h'r!!!
	}
	
	response += Protocol::ANS_END;
	return response;
}

string InterPreter::interpret(const std::string& message){
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
