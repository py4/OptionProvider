#ifndef PRODUCT_MANAGER_H_
#define PRODUCT_MANAGER_H_

#include "product.h"
class ProductManager {

public:

	bool handle_features(Product*);
	bool handle_requests(Product*);
	void respond();

};
#endif