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
	  memoryDB::~memoryDB(){
	 
	 }
 std::vector<pair<string,int>> memoryDB::listNewsGroups(){
		vector<string> tmp;
		vector<pair<string,int>> v;
		unique_copy(db.first,db.last,tmp.first)[](const pair<char,int> &entry1,
			const pair<char,int> &entry2) {
				return (entry1.first == entry2.first);
			}
		);
			std::vector<int>::iterator found;
		for (auto it = tmp.begin(); it != tmp.end(); ++it) {
			found=find (tmp.begin(), tmp.end(), it);
			if(found != tmp.end()){
				v.insert(pair<string,int>(it,found-tmp.begin);
			}
		}
		return v;
	       
	 }
 bool memoryDB::createNewsGroup(std::string name){
		db.insert(name,nullptr);
		groupIDs.insert(name);
	 }
 bool memoryDB::deleteNewsGroup(std::string groupID){
	 db.erase(groupIDs.get(groupID));
	 return true;
	 }
std::vector<Article> memoryDB::listArticles(std::string groupID) {
	 	vector<Article> tmp;
		string gname=groupIDs.get(groupID);
		copy(db.first,db.last,tmp.first)[](const pair<char,int> &entry1) {
				return (entry1.first == gname);
			}
		);
			
		return tmp;
	 }
 bool memoryDB::createArticle(std::string groupID,std::string title,std::string author, std::string text){
	 string gname=groupIDs.get(groupID);
	 db.insert(pair(gname,new Articel(title,author,text)));
	 return true;
	 }
 bool memoryDB::deleteArticle(std::string groupID,std::string articleID){
	 typedef multimap<char, int>::iterator iterator;
	 	 string gname=groupIDs.get(groupID);

	std::pair<iterator, iterator> iterpair = mymap.equal_range(gname);
	 
	 iterator it = iterpair.first;
	for (; it != iterpair.second; ++it) {
	    if (it->second == articleID) { 
		mymap.erase(it);
		return true;
	    }
	}
	return false;
	 }
 article:Article memoryDB::getArticle(std::string groupID,std::string articleID) {
	typedef multimap<char, int>::iterator iterator;
	  string gname=groupIDs.get(groupID);
	std::pair<iterator, iterator> iterpair = mymap.equal_range(groupID);
	 
	 iterator it = iterpair.first;
	for (; it != iterpair.second; ++it) {
	    if (it->second == articleID) { 
		return it->secound;
	    }
	}
	return nullptr;
	 }


