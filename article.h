/*
 * Interface NameServerInterface -- all name server implementations must
 * implement this interface.
 */
#ifndef ARTICLE_H
#define ARTICLE_H

#include <string>

class Article {
public:
	Article(std::string authorIn ,std::string titleIn ,std::string textIn, char ID) : author(authorIn), title(titleIn), text(textIn), id(ID){};
	Article(const Article& a) {author = a.author, title = a.title, text = a.text};
	char getID(){return id;};
	std::string getAuthor(){return author;};
	std::string getTitle(){return title;};
	std::string getText(){return text;};
	
private:
	char id;
	std::string author;
	std::string title;
	std::string text;
};

#endif
