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
	virtual std::vector<std::pair<int,std::string>> listNewsGroups() = 0;
	virtual bool createNewsGroup(std::string name) = 0;
	virtual bool deleteNewsGroup(int groupID) = 0;
	virtual std::vector<Article> listArticles(int groupID) = 0;
	virtual bool createArticle(int groupID,std::string title,std::string author, std::string text) = 0;
	virtual int deleteArticle(int groupID, int articleID) = 0;
	virtual Article* getArticle(int groupID, int articleID) = 0;
};

#endif
