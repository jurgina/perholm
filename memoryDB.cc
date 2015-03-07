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
		
	 }
 bool memoryDB::deleteNewsGroup(std::string groupID){
	 
	 }
 std::string memoryDB::listArticles(std::string groupID) {
	 
	 }
 bool memoryDB::createArticle(std::string groupID,std::string title,std::string author, std::string text){
	 
	 }
 bool memoryDB::deleteArticle(std::string groupID,std::string articleID){
	 }
 article:Article memoryDB::getArticle(const HostName&) {
	 }


#endif