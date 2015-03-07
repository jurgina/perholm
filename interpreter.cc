#include <string>
#include "database.h"
#include "protocol.h"
#include "encoding.h"

using namespace std;
/* Gets an message from the client, interprets it and does stuff with it and sends back the r
	the results */
string interpret(const std::string& message);

/* Returns the message from the list newsgroup command */
std::string messageListNewsGroups(const std::string& message);

/* Returns the message from the create newsgroup command */
std::string messageCreateNewsGroup(const std::string& message);

/* Returns the message from the delete newsgroup command */
std::string messageDeleteNewsGroups(const std::string& message);

/* Returns the message from the list articles command */
std::string messageListArticles(const std::string& message);

/* Returns the message from the create article command */
std::string messageCreateArticle(const std::string& message);

/* Returns the message from the delete article command */
std::string messageDeleteArticle(const std::string& message);
