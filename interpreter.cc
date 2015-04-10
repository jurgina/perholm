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
string InterPreter::messageListNewsGroups(){
	vector<pair<int,string>> newsgroups = db.listNewsGroups();
	string response;
	response += Protocol::ANS_LIST_NG;
	if(newsgroups.size() != 0){
		response += convertNumberToNumP(newsgroups.size());
		
		// response += ' ';
		for(auto p: newsgroups){
			int i=p.first;
			response += convertNumberToNumP(p.first);
			// response += ' ';
			response += convertStringToStringP(p.second);
			// response += ' ';	
		}
	}else{
		response += convertNumberToNumP(0);
		// response += ' ';				

	}
	response += Protocol::ANS_END;
	return response;
}

/* Returns the message from the create newsgroup command */
string InterPreter::messageCreateNewsGroup(istringstream& message){
	string title = convertStringPToString(message);
	cout << title;
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
	string response;
	response += Protocol::ANS_LIST_ART;
	try {			// If the newsgroup exists
		vector<Article> articles = db.listArticles(c);
		response += Protocol::ANS_ACK;
			  
		response += convertNumberToNumP(articles.size());
			  
		for (size_t i = 0; i < articles.size();++i){
			response += convertNumberToNumP(articles[i].getID());
		      
		    response += convertStringToStringP(articles[i].getTitle());
		}
		
	} catch (exception e) {						// If the newsgroup doesn't exist
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
	  cout<<groupID<<endl;
	cout<<articleID<<endl;
	try{
		Article article = db.getArticle(groupID,articleID);
		response += Protocol::ANS_ACK;
		response += convertStringToStringP(article.getTitle());
		response += convertStringToStringP(article.getAuthor());
		response += convertStringToStringP(article.getText());
	}catch(int e){
		cout<<e<<endl;
		response += Protocol::ANS_NAK;
	}
	
	response += Protocol::ANS_END;
	cout << response << endl;
	return response;
}

string InterPreter::interpret(const std::string& message){
	istringstream input(message);
	char command;
	input >> command;
	switch(command){
		case Protocol::COM_LIST_NG:
			return messageListNewsGroups();
		case Protocol::COM_CREATE_NG: 
			return messageCreateNewsGroup(input);
		case Protocol::COM_DELETE_NG: 
			return messageDeleteNewsGroup(input);
		case Protocol::COM_LIST_ART: 
			return messageListArticles(input);
		case Protocol::COM_CREATE_ART: 
			return messageCreateArticle(input);
		case Protocol::COM_DELETE_ART: 
			return messageDeleteArticle(input);
		case Protocol::COM_GET_ART: 
			return messageGetArticle(input);
		default: cout << "Something is wrong in interpret server side, wrong command code" << endl;
			break; 
	}
	return ":-( interpret\n";
}
