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
	bool deleteNewsGroup(int groupID);
	std::vector<Article> listArticles(int groupID);
	bool createArticle(int groupID,std::string title,std::string author, std::string text);
	int deleteArticle(int groupID, int articleID);
	Article* getArticle(int groupID, int articleID);

private:
	std::multimap<std::string,Article> db;
	std::vector<std::string> groupIDs;
};

#endif
