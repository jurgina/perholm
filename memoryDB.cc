#include "article.h" 
#include "database.h"
#include "memoryDB.h"
#include <map>
#include <string>
#include <cstddef>
#include <vector>
#include  <algorithm>
using  namespace std;

 memoryDB::memoryDB(){
	 
	 }

	  memoryDB::~memoryDB(){
	 
	 }

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
		vector<Article> tmp(itpair.first, itpair.second);
/*
		copy(db.begin(),db.end(),tmp.begin(), [gname](const pair<string,Article> &entry1) {
				return (entry1.first == gname);
			}
		);
		vector<Article> tmp2;
		for (auto itr=tmp.begin();itr!=tmp.end(); itr++){
			tmp2.push_back(itr.)
		}
	*/		
		return tmp;
	 }
 bool memoryDB::createArticle(char groupID, string title,string author, string text){
	 string gname=groupIDs[groupID];
	 db.insert(pair<string, Article>(gname, Article(title,author,text, db.count(gname))));
	 return true;
	 }
 bool memoryDB::deleteArticle(char groupID, char articleID){
	 typedef multimap<string, Article>::iterator iterator;
	 	 string gname=groupIDs[groupID];

	auto iterpair = db.equal_range(gname);

	 iterator it = iterpair.first;
	for (; it != iterpair.second; ++it) {
	    if (it->second.getID() == articleID) { 
		db.erase(it);
		return true;
	    }
	}
	return false;
	 }
 Article& memoryDB::getArticle(char groupID,char articleID) {
	typedef multimap<string, Article>::iterator iterator;
	  string gname=groupIDs[groupID];
	std::pair<iterator, iterator> iterpair = db.equal_range(gname);
	 
	 iterator it = iterpair.first;
	for (; it != iterpair.second; ++it) {
	    if (it->second.getID() == articleID) { 
		return it->second;
	    }
	}
	return nullptr;
	}


