#ifndef ENCODING_H
#define ENCODING_H

#include <string>
#include <memory>
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

#endif
