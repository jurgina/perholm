#include "article.h" 
#include "database.h"
#include "driveDB.h"
#include <map>
#include <string>
#include <cstddef>
#include <vector>
#include  <algorithm>
#include <sstream>
#include <iostream>
#include <sys/stat.h>
#include <dirent.h>
using namespace std;

vector<pair<int,string>> driveDB::listNewsGroups(){
	DIR* dir=opendir(path.c_str());
	struct dirent* entry; 
	vector<pair<int,string>> v;
	while ( (entry = readdir(dir)) != NULL) {
		string tmp=entry->d_name;
		istringstream dirName (tmp);
		string name;
		dirName>>name;
		int id;
		dirName>>id;
		v.push_back(make_pair(id,name));
	}
	return v;   
}

bool driveDB::createNewsGroup(std::string name){
	DIR* dir=opendir(path.c_str());
	struct dirent* entry; 
	vector<int> v;
	while ( (entry = readdir(dir)) != NULL) {
		string tmp=entry->d_name;
		istringstream dirName (tmp);
		string name;
		dirName>>name;
		int id;
		dirName>>id;
		v.push_back(id);
	}
	int i=0;
	auto itr=find(v.begin(),v.end(),i);
	while(itr!=v.end()){
		++i;
		 itr=find(v.begin(),v.end(),i);
	}
	string newpath=path+"/"+name+" "+to_string(i);
	mkdir(newpath.c_str(),S_IRWXU);
	return false;
}

bool driveDB::deleteNewsGroup(int groupID){
	DIR* dir=opendir(path.c_str());
	struct dirent* entry; 
	vector<int> v;
	while ( (entry = readdir(dir)) != NULL) {
		string tmp=entry->d_name;
		istringstream dirName (tmp);
		string name;
		dirName>>name;
		int id;
		dirName>>id;
		if(id==groupID){
			
			//remove
		}
	}
	return false;
}

std::vector<Article> driveDB::listArticles(int groupID) {
	vector<Article> a;
	return a;
}

bool driveDB::createArticle(int groupID, string title,string author, string text){
	
	return true;
}

int driveDB::deleteArticle(int groupID, int articleID){
	
	return 2;
}

Article* driveDB::getArticle(int groupID, int articleID) {
	
	return nullptr;
}


