#include "article.h" 
#include "database.h"
#include "memoryDB.h"
#include <map>
#include <string>

#include <vector>
#include  <algorithm>
using  namespace std,map;

 memoryDB::memoryDB(){
	 
	 }
 std::vector<string> memoryDB::listNewsGroups(){
		vector<string> tmp;
		unique_copy(db.first,db.last,tmp.first)[](const pair<char,int> &entry1,
			const pair<char,int> &entry2) {
				return (entry1.first == entry2.first);
			}
		);
			
		return tmp;
	       
	 }
 bool memoryDB::createNewsGroup(std::string name){
		db.insert(name,nullptr);
	 }
 bool memoryDB::deleteNewsGroup(std::string groupID){
	 db.erase(groupID);
	 return true;
	 }
std::vector<Article> memoryDB::listArticles(std::string groupID) {
	 	vector<Article> tmp;
		copy(db.first,db.last,tmp.first)[](const pair<char,int> &entry1) {
				return (entry1.first == groupID);
			}
		);
			
		return tmp;
	 }
 bool memoryDB::createArticle(std::string groupID,std::string title,std::string author, std::string text){
	 db.insert(pair(groupID,new Articel(title,author,text)));
	 return true;
	 }
 bool memoryDB::deleteArticle(std::string groupID,std::string articleID){
	 typedef multimap<char, int>::iterator iterator;
	std::pair<iterator, iterator> iterpair = mymap.equal_range(groupID);
	 
	 iterator it = iterpair.first;
	for (; it != iterpair.second; ++it) {
	    if (it->second == articleID) { 
		mymap.erase(it);
		return ture;
	    }
	}
	return false;
	 }
 article:Article memoryDB::getArticle(std::string groupID,std::string articleID) {
	typedef multimap<char, int>::iterator iterator;
	std::pair<iterator, iterator> iterpair = mymap.equal_range(groupID);
	 
	 iterator it = iterpair.first;
	for (; it != iterpair.second; ++it) {
	    if (it->second == articleID) { 
		return it->secound;
	    }
	}
	return nullptr;
	 }


