#ifndef MEMORYDB_H
#define MEMORYDB_H
#include "article.h" 
#include "database.h"
#include <map>
#include <string>
#include <vector>

class memoryDB: public DataBase {
public:
	std::vector<std::string> listNewsGroups();
	bool createNewsGroup(std::string name);
	bool deleteNewsGroup( char groupID);
	std::vector<Article> listArticles(char groupID);
	bool createArticle(char groupID,std::string title,std::string author, std::string text);
	int deleteArticle(char groupID,char articleID);
	Article* getArticle(char groupID, char articleID);

private:
	std::multimap<std::string,Article> db;
	std::vector<std::string> groupIDs;
};

#endif
