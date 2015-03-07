#include <string>
#include "database.h"
#include "protocol.h"
#include "encoding.h"


/* Gets an message from the client, interprets it and does stuff with it and sends back the r
	the results */
std::string interpret(const std::string& message);

