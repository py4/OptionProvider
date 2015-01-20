#include "product_manager.h"
#include <iostream>
#include <string>
using namespace std;

void ProductManager::respond() {
	while(true) {
		Product* p = new Product;
		if(!handle_features(p)) {
			delete p;
			break;
		}
		handle_requests(p);
		delete p;
	}
}

bool ProductManager::handle_features(Product* p) {
	string line;
	bool done_something = false;
	while(getline(cin, line)) {
		if(line == "#")
			break;
		done_something = true;
		vector < pair < string, Type > > features = get_features(line);
		p->set_features(features);
	}
	return done_something;
}

bool ProductManager::handle_requests(Product* p) {
	bool done_something = false;
	string line;
	while(getline(cin, line)) {
		if(line == "##")
			break;
		done_something = true;
		vector < string > req = get_requested_features(line);
		p->respond_to_request(req);
	}
	return done_something;
}