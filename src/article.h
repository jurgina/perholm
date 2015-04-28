/*
 * Interface NameServerInterface -- all name server implementations must
 * implement this interface.
 */
#ifndef ARTICLE_H
#define ARTICLE_H

#include <string>

class Article {
public:
	Article(std::string authorIn ,std::string titleIn ,std::string textIn, int ID) : author(authorIn), title(titleIn), text(textIn), id(ID){};
	Article(const Article& a) :  author(a.author), title(a.title), text(a.text), id(a.id) {};
	int getID() const {return id;};
	std::string getAuthor() const {return author;};
	std::string getTitle() const {return title;};
	std::string getText() const {return text;};
	
private:
	std::string author;
	std::string title;
	std::string text;
	int id;
};

#endif
