#ifndef PARSER_H_
#define PARSER_H_

#include <string>
#include <vector>
#include "type.h"

bool is_optional(const std::string&);

void strip_str(std::string&);

std::vector <std::string> tokenize_input(const std::string&, char);
std::vector < std::pair < std::string, Type > > get_features(const std::string&);
std::vector < std::string > get_requested_features(std::string&);


#endif
