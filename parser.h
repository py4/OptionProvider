#ifndef PARSER_H_
#define PARSER_H_

#include <string>
#include <vector>
#include <map>
#include "type.h"

Type get_type(char);
std::string get_clear_str(const std::string&);
std::vector <std::string> tokenize_input(const std::string&, char);
bool is_optional(const std::string&);
std::vector < std::pair < std::string, Type > > get_features(const std::string&);
void strip_str(std::string&);
std::vector < std::string > get_requested_features(std::string&);

#endif