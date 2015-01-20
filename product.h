#ifndef PRODUCT_H_
#define PRODUCT_H_

#include "feature.h"

class Product {

public:
	void load_features();
	void dump_feature_model();
	void load_and_validate_request();
private:
	std::vector < std::string > load_request();
	bool preprocess_request(std::vector < std::string > &);
	bool validate_request( std::vector < std::string > &);

	Feature* root_feature;
};

#endif