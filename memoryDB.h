#ifndef MEMORYDB_H
#define MEMORYDB_H
#include "article.h" 
#include "database.h"
#include <map>
#include <string>

class memoryDB: public DataBase {
	
public:
	memoryDB();
	 ~DataBase();
	 std::vector<std::string> listNewsGroups();
	 bool createNewsGroup(std::string name);
	 bool deleteNewsGroup(std::string groupID);
	 std::string listArticles(std::string groupID) ;
	 bool createArticle(std::string groupID,std::string title,std::string author, std::string text);
	 bool deleteArticle(std::string groupID,std::string articleID);
	 article:Article getArticle(std::string groupID,std::string articleID) ;

private:
	map::multimap<std::string,article::Article> db;
};

#endif
