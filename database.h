/*
 * Interface NameServerInterface -- all name server implementations must
 * implement this interface.
 */
#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <utility> 
#include <vector>
#include "article.h"
class DataBase {
public:
	virtual std::vector<std::string> listNewsGroups() = 0;
	virtual bool createNewsGroup(std::string name) = 0;
	virtual bool deleteNewsGroup(char groupID) = 0;
	virtual std::vector<Article> listArticles(char groupID) = 0;
	virtual bool createArticle(char groupID,std::string title,std::string author, std::string text) = 0;
	virtual int deleteArticle(char groupID,char articleID) = 0;
	virtual Article* getArticle(char groupID,char articleID) = 0;
};

#endif
