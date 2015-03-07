/*
 * Interface NameServerInterface -- all name server implementations must
 * implement this interface.
 */
#ifndef ARTICLE_H
#define ARTICLE_H

#include <string>

class Article {
public:
	Article(std::string authorIn ,std::string titleIn ,std::string textIn) : author(authorIn), title(titleIn), text(textIn){};
	std::string getAuthor(){return author;};
	std::string getTitle(){return title;};
	std::string getText(){return text;};
	
private:
	std::string author;
	std::string title;
	std::string text;
};

#endif
