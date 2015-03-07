#ifndef MEMORYDB_H
#define MEMORYDB_H
#include "article.h" 
#include "database.h"
#include <map>
#include <string>

class memoryDB: public DataBase {
	
public:
	memoryDB();
	 ~memoryDB();
	  std::vector<std::pair<std::string,int>> listNewsGroups();
	 bool createNewsGroup(std::string name);
	 bool deleteNewsGroup(std::string groupID);
	 std::vector<Article> listArticles(std::string groupID) ;
	 bool createArticle(std::string groupID,std::string title,std::string author, std::string text);
	 bool deleteArticle(std::string groupID,std::string articleID);
	 Article getArticle(std::string groupID,std::string articleID) ;

private:
	std::multimap<std::string,Article> db;
	std::vector<std::string> groupIDs;
};

#endif
