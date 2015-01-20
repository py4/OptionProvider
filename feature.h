#ifndef FEATURE_H_
#define FEATURE_H_

#include <string>
#include "parser.h"
#include <vector>

class Feature {

public:
	friend class Product;
	Feature();
	Feature(const std::string&, Type t);
	void set_feature_name(const std::string&);
	void set_feature_type(Type t);
	std::string get_feature_name();

private:
	Type type;
	std::string feature_name;
	Feature* parent;
	std::vector < Feature* > children;
	Feature* find_among_children(const std::string&);	
	void set_children(const std::vector < std::pair < std::string, Type > > &);
	
	bool validate_request(const std::vector < std::string >&);
	bool validate_or_children(const std::vector < std::string > &);
	bool validate_xor_children(const std::vector < std::string> &);
	bool validate_mand_and_optional_children(const std::vector < std::string > &);
};

#endif