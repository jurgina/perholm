#include "connection.h"



/* Writes a string to a specific connection */
void writeString(const std::string& s, Connection::Connection& c);

/* Reads a string from a connection */
std::string readString(Connection::Connection& c);