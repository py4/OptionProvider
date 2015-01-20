#ifndef PRODUCT_H_
#define PRODUCT_H_

#include "feature.h"

class Product {

public:
	Product();
	~Product();
	void set_features(std::vector < std::pair < std::string, Type > > &);
	void respond_to_request(std::vector < std::string> &);

private:

	bool preprocess_request(std::vector < std::string > &);
	bool validate_request( std::vector < std::string > &);

	Feature* root_feature;
};

#endif