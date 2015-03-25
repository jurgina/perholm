#include "article.h" 
#include "database.h"
#include "memoryDB.h"
#include <map>
#include <string>
#include <cstddef>
#include <vector>
#include  <algorithm>

using namespace std;

vector<string> memoryDB::listNewsGroups(){
	return groupIDs;   
}

bool memoryDB::createNewsGroup(std::string name){
	auto it= find(groupIDs.begin(), groupIDs.end(),name);
	if(it==groupIDs.end()){
		groupIDs.push_back(name);
		return true;
	}
	return false;
}

bool memoryDB::deleteNewsGroup(char groupID){
	db.erase(groupIDs[groupID]);
	return true;
}

std::vector<Article> memoryDB::listArticles(char groupID) {
	string gname=groupIDs[groupID];
	auto itpair = db.equal_range(gname);
	vector<pair<string,Article>> tmp(itpair.first, itpair.second);
	vector<Article> art;
	for(auto itr=tmp.begin();itr!=tmp.end();++itr){
		art.push_back((*itr).second);
	}
	return art;
}

bool memoryDB::createArticle(char groupID, string title,string author, string text){
	string gname=groupIDs[groupID];
	db.insert(pair<string, Article>(gname, Article(title,author,text, db.count(gname))));
	return true;
}

int memoryDB::deleteArticle(char groupID, char articleID){
	typedef multimap<string, Article>::iterator iterator;
	string gname=groupIDs[groupID];

	auto iterpair = db.equal_range(gname);
	if(iterpair.first==iterpair.second){
		return 1;
	}
	iterator it = iterpair.first;
	
	for (; it != iterpair.second; ++it) {
	    if (it->second.getID() == articleID) { 
			db.erase(it);
			return 2;
	    }
	}
	
	return 0;
}

Article* memoryDB::getArticle(char groupID,char articleID) {
	typedef multimap<string, Article>::iterator iterator;
	string gname=groupIDs[groupID];
	std::pair<iterator, iterator> iterpair = db.equal_range(gname);
	 
	iterator it = iterpair.first;
	for (; it != iterpair.second; ++it) {
	    if (it->second.getID() == articleID) { 
			return &(it->second);
	    }
	}
	return nullptr;
}


