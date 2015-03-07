#ifndef INTERPRETER_H
#define INTERPRETER_H


#include <string>
#include <iostream>
#include <istream>
#include "database.h"
#include "protocol.h"
#include "encoding.h"

class InterPreter {
public:
	InterPreter(Database& data): db(data) {}
	/* Gets an message from the client, interprets it and does stuff with it and sends back the r
		the results */
	std::string interpret(const std::string& message);


private:
	Database& db;

	/* Returns the message from the list newsgroup command */
	std::string messageListNewsGroups(const std::istream& message);

	/* Returns the message from the create newsgroup command */
	std::string messageCreateNewsGroup(const std::istream& message);

	/* Returns the message from the delete newsgroup command */
	std::string messageDeleteNewsGroups(const std::istream& message);

	/* Returns the message from the list articles command */
	std::string messageListArticles(const std::istream& message);

	/* Returns the message from the create article command */
	std::string messageCreateArticle(const std::istream& message);

	/* Returns the message from the delete article command */
	std::string messageDeleteArticle(const std::istream& message);

};

#endif
