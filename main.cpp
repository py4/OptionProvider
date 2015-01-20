#include "parser.h"
#include <iostream>
#include "product.h"
using namespace std;

int main() {
	Product p;
	p.load_features();
	//p.dump_feature_model();
	p.load_and_validate_request();
	return 0;
}
