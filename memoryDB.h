#ifndef MEMORYDB_H
#define MEMORYDB_H
#include "article.h" 
#include "database.h"
#include <map>
#include <string>
#include <vector>

class memoryDB: public DataBase {
public:
	memoryDB(){
	nbr=1;
}
	std::vector<std::pair<int,std::string>> listNewsGroups();
	bool createNewsGroup(std::string name);
	bool deleteNewsGroup(int groupID);
	std::vector<Article> listArticles(int groupID);
	bool createArticle(int groupID,std::string title,std::string author, std::string text);
	int deleteArticle(int groupID, int articleID);
	Article getArticle(int groupID, int articleID);

private:
	struct newsGroup{
		int id;
		std::string name;
		std::vector<Article> arts;	
		char c;
	};

	int nbr;
	std::vector<newsGroup> ng;

};

#endif
