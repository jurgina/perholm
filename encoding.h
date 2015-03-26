#ifndef ENCODING_H
#define ENCODING_H

#include <string>
#include <memory>
#include <vector>
#include "connection.h"



/* Writes a string to a specific connection */
void writeString(const std::string& s, const std::shared_ptr<Connection>& conn);

/* Reads a string from a connection */
std::string readString(const std::shared_ptr<Connection>& conn);

/* Converts a string to string_p format */
std::string convertStringToStringP(const std::string& s);

/* Converts a number to num_p format */
std::string convertNumberToNumP(int num);

/* Converts a string_p to string format */
std::string convertStringPToString(std::istringstream& message);

/* Converts a num_p to num format */
int convertNumPToNum(std::istringstream& message);

/*Converts a int to a vectors of four chars */
std::vector<unsigned char> intToBytes(int num);

/*Converts a vector of four bytes to an int */
int bytesToInt(std::vector<unsigned char>& v);

#endif
