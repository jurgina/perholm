/*
 * Interface NameServerInterface -- all name server implementations must
 * implement this interface.
 */
#ifndef ARTICLE_H
#define ARTICLE_H

#include <string>

class Article {
public:
	article(std::string author,std::string title,std::string text);
		
	std::string getAuthor();
	std::string getTitle();
	std::string getText();
	
private:
	std::string author;
	std::string title;
	std::string text;
};

#endif
