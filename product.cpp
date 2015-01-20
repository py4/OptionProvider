#include <iostream>
#include "product.h"
#include "parser.h"
#include <queue>
#include <algorithm>
#include <map>
using namespace std;

Product::Product() {
	root_feature = NULL;
}

Product::~Product() {
	delete root_feature;
}

void Product::set_features(const vector < pair < string, Type > >& features) {
	if(root_feature) {
		Feature* feature = root_feature->find_among_children(features[0].first);
		feature->set_children(features);
	} else {
		root_feature = new Feature(features[0].first, features[0].second);
		root_feature->set_children(features);
		root_feature->parent = NULL;
	}
}

void Product::respond_to_request(const vector<string> & req) {
	if(!preprocess_request(req))
		cout << "INVALID!" << endl;
	else
		cout << (root_feature->validate_request(req) ? "VALID!" : "INVALID!") << endl;
}

bool Product::preprocess_request(const vector < string > & req) {
	map<string, bool> seen;

	for(int i = 0; i < req.size(); i++) {
		Feature* f = root_feature->find_among_children(req[i]);
		if(f == NULL) {
			cout << "INVALID INPUT!" << endl;
			return false;
		}
		while(f != NULL and !seen[f->get_feature_name()]) {
			if(find(req.begin(), req.end(), f->get_feature_name()) == req.end()) //parent not found
				return false;	
			seen[f->get_feature_name()] = true;
			f = f->parent;
		}
	}
	return true;
}
