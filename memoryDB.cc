#include "article.h" 
#include "database.h"
#include "memoryDB.h"
#include <map>
#include <string>
#include <cstddef>
#include <vector>
#include <algorithm>
#include <iostream>
#include <typeinfo>

using namespace std;

vector<pair<int,string>> memoryDB::listNewsGroups(){
	vector<pair<int,string>> v;
	for(auto n: ng){
		v.push_back(make_pair(n.id,n.name));
	}
	return v;   
}

bool memoryDB::createNewsGroup(std::string name){
	auto it= find_if(ng.begin(), ng.end(),[name](newsGroup& n){return n.name==name;});

	if(it==ng.end()){
		newsGroup n;
		n.name=name;
		n.id=nbr;
		++nbr;
		ng.push_back(n);
		return true;
	}
	return false;
}

bool memoryDB::deleteNewsGroup(int groupID){
	auto it= find_if(ng.begin(), ng.end(),[groupID](newsGroup& n){return n.id==groupID;});
	
	ng.erase(it);
	return true;
}

std::vector<Article> memoryDB::listArticles(int groupID) {
	auto it= find_if(ng.begin(), ng.end(),[groupID](newsGroup& n){return n.id==groupID;});
	
	if (it == ng.end())
		throw 24; 
	vector<Article> a=(*it).arts;
	return a;
}

bool memoryDB::createArticle(int groupID, string title,string author, string text){
	auto it= find_if(ng.begin(), ng.end(),[groupID](newsGroup& n){return n.id==groupID;});
	
	Article a(author ,title , text, ++(*it).c) ;
	
	(*it).arts.push_back(a);
	
	return true;
}

int memoryDB::deleteArticle(int groupID, int articleID){
	auto it= find_if(ng.begin(), ng.end(),[groupID](newsGroup& n){return n.id==groupID;});
	if(it==ng.end()){
		return 1;
	}
	auto it2= find_if((*it).arts.begin(), (*it).arts.end(),[articleID](Article& n){return n.getID()==articleID;});
	
	
	if(it2==(*it).arts.end()){
		return 0;
	}
	(*it).arts.erase(it2);
	return 2;
}

Article* memoryDB::getArticle(int groupID, int articleID) {
	auto it= find_if(ng.begin(), ng.end(),[groupID](newsGroup& n){return n.id==groupID;});
	if(it==ng.end()){
		return nullptr;
	}
	auto it2= find_if((*it).arts.begin(), (*it).arts.end(),[articleID](Article& n){return n.getID()==articleID;});
	if(it2==(*it).arts.end()){
		return nullptr;
	}
	return &(*it2);
}


