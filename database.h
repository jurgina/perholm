/*
 * Interface NameServerInterface -- all name server implementations must
 * implement this interface.
 */
#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include "article.h"
class DataBase {
public:
	virtual ~DataBase()=0;
	virtual   std::vector<pair<string,int>> listNewsGroups() = 0;
	virtual bool createNewsGroup(std::string name) = 0;
	virtual bool deleteNewsGroup(std::string groupID) = 0;
	virtual std::vector<Article> listArticles(std::string groupID) = 0;
	virtual bool createArticle(std::string groupID,std::string title,std::string author, std::string text) = 0;
	virtual bool deleteArticle(std::string groupID,std::string articleID) = 0;
	virtual Article getArticle(std::string groupID,std::string articleID) = 0;
};

#endif
