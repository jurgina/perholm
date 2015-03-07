
#include <string>
#include "connection.h"



/* Writes a string to a specific connection */
void writeString(const std::string& s, Connection::Connection& c);

/* Reads a string from a connection */
std::string readString(Connection::Connection& c);

/* Converts a string to string_p format */
std::string convertStringToStringP(const string& s);

/* Converts a number to num_p format */
std::string convertNumberToNumP(int num);