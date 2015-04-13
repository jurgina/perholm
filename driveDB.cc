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
#include <fstream>
#include <dirent.h>
using namespace std;
typedef struct dirent dirent;
vector<pair<int,string>> driveDB::listNewsGroups(){
	DIR* dir=opendir(path.c_str());
	dirent* entry; 
	vector<pair<int,string>> v;
	while ( (entry = readdir(dir)) != NULL) {
		string tmp=entry->d_name;
		
		if(tmp[0]!='.'){		
			size_t pos=tmp.find("_");
			if(pos!=tmp.size()){
				string name=tmp.substr(0,pos);
				string idT=tmp.substr(pos+1);
				istringstream dirName (idT);
				int id;
				dirName>>id;
				v.push_back(make_pair(id,name));
			}
		}
	}
	return v;   
}

bool driveDB::createNewsGroup(std::string nameDir){
	DIR* dir=opendir(path.c_str());
	dirent* entry; 
	vector<int> v;
	while ( (entry = readdir(dir)) != NULL) {
		
		string tmp=entry->d_name;
		if(tmp[0]!='.'){		
			size_t pos=tmp.find("_");
			if(pos!=tmp.size()){
				string name=tmp.substr(0,pos);
				if(name == nameDir){
				return false;
				}
				string idT=tmp.substr(pos+1);
				istringstream dirName (idT);
				int id;
				dirName>>id;
				v.push_back(id);
			}
		}
	}
	int i=0;
	auto itr=find(v.begin(),v.end(),i);
	while(itr!=v.end()){
		++i;
		 itr=find(v.begin(),v.end(),i);
	}
	string newpath=path+"/"+nameDir+"_"+to_string(i);
	mkdir(newpath.c_str(),S_IRWXU);
	return true;
}

bool driveDB::deleteNewsGroup(int groupID){
	DIR* dir=opendir(path.c_str());
	dirent* entry; 
	vector<int> v;
	while ( (entry = readdir(dir)) != NULL) {
		
		string tmp=entry->d_name;
		if(tmp[0]!='.'){		
			size_t pos=tmp.find("_");
			if(pos!=tmp.size()){
				string name=tmp.substr(0,pos);
				string idT=tmp.substr(pos+1);
				istringstream dirName (idT);
				int id;
				dirName>>id;
				if(id==groupID){
				vector<Article> a=listArticles(groupID);
				for(auto art:a){
					deleteArticle(groupID, art.getID());
				}
				remove((path + "/" + tmp).c_str());
				return true;
			}
			}
		}
		
	}
	return false;
}

std::vector<Article> driveDB::listArticles(int groupID) {
	vector<Article> a;
	DIR* dir=opendir(path.c_str());
	dirent* entry; 
	vector<int> v;
	while ( (entry = readdir(dir)) != NULL) {
		string tmp=entry->d_name;
		if(tmp[0]!='.'){		
			size_t pos=tmp.find("_");
			if(pos!=tmp.size()){
				string name=tmp.substr(0,pos);
				string idT=tmp.substr(pos+1);
				istringstream dirName (idT);
				int id;
				dirName>>id;
				cout<<"hej"<<id<<endl;
				
				cout<<"hej igen "<<groupID<<endl;
				bool m =id==groupID;
				cout<<m<<endl;
				if(id==groupID){
					DIR* dir=opendir((path+"/"+tmp).c_str());
					dirent* articelEnt; 
					while ( (articelEnt = readdir(dir)) != NULL) {
						
						string tmp2=articelEnt->d_name;
						if(tmp2[0]!='.'){		
							size_t pos=tmp2.find("_");
							if(pos!=tmp2.size()){
								string name=tmp2.substr(0,pos);
								string idT=tmp2.substr(pos+1);
								istringstream dirName (idT);
								int id;
								dirName>>id;
								string m="";
								std::transform (name.begin(), name.end(), name.begin(), [] (char c) {if(c == ':'){ return ' ';} return c;});
								Article art(m,name,m,id);
								cout<<name<<"denna borde inte finnas"<<endl;
								a.push_back(art);
								
							}
						}
						
					}
					sort(a.begin(),a.end(),[](const Article& a1, const Article& a2){return a1.getID() < a2.getID();});
					return a;
				}
			}
		}
		
	}
	throw 1337;
	
}

bool driveDB::createArticle(int groupID, string title,string author, string text){
	DIR* dir=opendir(path.c_str());
	dirent* entry; 
	while ( (entry = readdir(dir)) != NULL) {
		
		string tmp=entry->d_name;
		
		if(tmp[0]!='.'){		
			size_t pos=tmp.find("_");
			if(pos!=tmp.size()){
				string name=tmp.substr(0,pos);
				string idT=tmp.substr(pos+1);
				istringstream dirName (idT);
				int id;
				dirName>>id;
				if(id==groupID){
					DIR* dir2=opendir((path+"/"+tmp).c_str());
					vector<int> v;
					dirent* articelEnt; 
					while ( (articelEnt = readdir(dir2)) != NULL) {
						string tmp2=articelEnt->d_name;
						if(tmp2[0]!='.'){		
							size_t pos=tmp2.find("_");
							if(pos!=tmp2.size()){
								string name=tmp2.substr(0,pos);
								string idT=tmp2.substr(pos+1);
								istringstream artName (idT);
								int id;
								artName>>id;
								v.push_back(id);
							}
						}
						
						
					}
					int i=0;
					auto itr=find(v.begin(),v.end(),i);
					while(itr!=v.end()){
						++i;
						 itr=find(v.begin(),v.end(),i);
					}
					ofstream myfile;
					std::transform (title.begin(), title.end(), title.begin(), [] (char c) {if(c == ' '){ return ':';} return c;});
					myfile.open (path + "/"+ tmp + "/" + title+"_"+to_string(i));
					myfile << author<<"\n";
					myfile<<text;
					myfile.close();
					return true;
				}
			}
		}
		
	}
	return false;
}

int driveDB::deleteArticle(int groupID, int articleID){
	DIR* dir=opendir(path.c_str());
	dirent* entry; 
	while ( (entry = readdir(dir)) != NULL) {
		string tmp=entry->d_name;
		if(tmp[0]!='.'){		
			size_t pos=tmp.find("_");
			if(pos!=tmp.size()){
				string name=tmp.substr(0,pos);
				string idT=tmp.substr(pos+1);
				istringstream dirName (idT);
				int id;
				dirName>>id;
		
		
				if(id==groupID){
					DIR* dir=opendir((path+"/"+tmp).c_str());
					dirent* articelEnt; 
					while ( (articelEnt = readdir(dir)) != NULL) {
						string tmp2=articelEnt->d_name;
						if(tmp2[0]!='.'){		
							size_t pos=tmp2.find("_");
							if(pos!=tmp2.size()){
								string name=tmp2.substr(0,pos);
								string idT=tmp2.substr(pos+1);
								istringstream artName (idT);
								int id;
								artName>>id;
								cout<<"id for "<<tmp2<<"  "<<idT<<" "<<articleID<<endl;
								if(articleID==id){
									cout<<"id match"<<articleID<<endl;
									remove((path+"/"+tmp+"/"+tmp2).c_str());
									return 2;
								}
							}
						}
						
					}
					return 0;
				}	
			}
		}
		
	}
	return 1;
}

Article driveDB::getArticle(int groupID, int articleID) {
	DIR* dir=opendir(path.c_str());
	dirent* entry; 
	while ( (entry = readdir(dir)) != NULL) {
		string tmp=entry->d_name;
		if(tmp[0]!='.'){		
			size_t pos=tmp.find("_");
			if(pos!=tmp.size()){
				string name=tmp.substr(0,pos);
				string idT=tmp.substr(pos+1);
				istringstream dirName (idT);
				int id;
				dirName>>id;
				cout<<"id for "<<tmp<<endl;
				cout<<id<<endl;
				if(id==groupID){
					DIR* dir=opendir((path+"/"+tmp).c_str());
					dirent* articelEnt; 
					while ( (articelEnt = readdir(dir)) != NULL) {
						string tmp2=articelEnt->d_name;
						if(tmp2[0]!='.'){		
							size_t pos=tmp2.find("_");
							if(pos!=tmp2.size()){
								string name=tmp2.substr(0,pos);
								string idT=tmp2.substr(pos+1);
								istringstream artName (idT);
								int artid;
								artName>>artid;
								if(articleID==artid){
									ifstream myFile(path + "/"+ tmp + "/" + tmp2);
									string author;
									char c=1;
									while (myFile.get(c)&&c!='\n'){
										author+= c;
									}
									string text;
									char c2;
									while (myFile.get(c2)){
										text+= c2;
									}
									std::transform (name.begin(), name.end(), name.begin(), [] (char c) {if(c == ':'){ return ' ';} return c;});
									Article a=Article(author, name, text, artid);
									return a;
								}
							}
						}
						
					}
					throw 1337; 
				}
			}
		}
		
						
						
		
		
		
	}
	throw 7331; 
}


