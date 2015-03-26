#ifndef SERVERRESPONSE_H
#define SERVERRESPONSE_H


#include <string>
#include <iostream>
#include <sstream>
#include "database.h"
#include "protocol.h"
#include "encoding.h"

class ServerResponse {
public:
	std::string interpret(const std::string&);

private:
	/* Returns the message from the list newsgroup command */
	std::string messageListNewsGroups(std::istringstream& message);

	/* Returns the message from the create newsgroup command */
	std::string messageCreateNewsGroup(std::istringstream& message);

	/* Returns the message from the delete newsgroup command */
	std::string messageDeleteNewsGroup(std::istringstream& message);

	/* Returns the message from the list articles command */
	std::string messageListArticles(std::istringstream& message);

	/* Returns the message from the create article command */
	std::string messageCreateArticle(std::istringstream& message);

	/* Returns the message from the delete article command */
	std::string messageDeleteArticle(std::istringstream& message);

	/* Returns the message from the get article command */
	std::string messageGetArticle(std::istringstream& message);
};

#endif