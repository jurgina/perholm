#ifndef INTERPRETER_H
#define INTERPRETER_H


#include <string>
#include <iostream>
#include <sstream>
#include "database.h"
#include "protocol.h"
#include "encoding.h"

class InterPreter {
public:
	InterPreter(DataBase& data): db(data) {}
	/* Gets an message from the client, interprets it and does stuff with it and sends back the r
		the results */
	std::string interpret(const std::string& message);


private:
	DataBase& db;

	/* Returns the message from the list newsgroup command */
	std::string messageListNewsGroups(const std::istringstream& message);

	/* Returns the message from the create newsgroup command */
	std::string messageCreateNewsGroup(const std::istringstream& message);

	/* Returns the message from the delete newsgroup command */
	std::string messageDeleteNewsGroups(const std::istringstream& message);

	/* Returns the message from the list articles command */
	std::string messageListArticles(const std::istringstream& message);

	/* Returns the message from the create article command */
	std::string messageCreateArticle(const std::istringstream& message);

	/* Returns the message from the delete article command */
	std::string messageDeleteArticle(const std::istringstream& message);

};

#endif
