#include <iostream>
#include "product.h"
#include "parser.h"
#include <queue>
#include <algorithm>
using namespace std;

void Product::load_features() {
	string line;
	bool first_line = true;
	while(true) {
		getline(cin, line);
		if(line == "#")
			break;
		vector < pair < string, Type > > features = get_features(line);
		if(first_line) {
			root_feature = new Feature(features[0].first, features[0].second);
			root_feature->set_children(features);
			root_feature->parent = NULL;
		} else {
			Feature* feature = root_feature->find_among_children(features[0].first);
			feature->set_children(features);
		}
		first_line = false;
	}
}

void Product::dump_feature_model() {
	Feature* root = root_feature;
	queue<Feature*> q;
	q.push(root);

	while(!q.empty()) {
		Feature* front = q.front();
		q.pop();
		cout << "-----> front:  " << front->get_feature_name() << endl;
		cout << "===============" << endl;
		for(int i = 0; i < front->children.size(); i++) {
			cout << "child:  " << front->children[i]->get_feature_name() << endl;
			q.push(front->children[i]);
		}
		cout << "===============" << endl;
	}
}


void Product::load_and_validate_request() {
	string line;
	while(true) {
		getline(cin, line);
		if(line == "##")
			break;
		vector < string > req = get_requested_features(line);
		if(!preprocess_request(req))
			cout << "INVALID!" << endl;
		else
			cout << (root_feature->validate_request(req) ? "VALID!" : "INVALID!") << endl;
	}
}

vector < string > Product::load_request() {
	string line;
	getline(cin, line);
	return get_requested_features(line);
}

bool Product::preprocess_request(vector < string > & req) {
	//cout << "### preprocessing request ###" << endl;
	map<string, bool> check;
	queue<Feature*> parents;

	for(int i = 0; i < req.size(); i++) {
		Feature* f = root_feature->find_among_children(req[i]);
		if(f == NULL) {
			cout << "INVALID INPUT!" << endl;
			return false;
		}
		if(f->parent != NULL) // take care of root
			parents.push(f->parent);
	}

	while(!parents.empty()) {
		Feature* front = parents.front();
		if(find(req.begin(), req.end(), front->get_feature_name()) == req.end()) //parent not found
			return false;
		else
			//cout << "parent feature " << front->get_feature_name() << " found among request" << endl;
		parents.pop();
		if(front->parent)
			if(!check[front->parent->get_feature_name()]) {
				//cout << "pushing " << front->parent->get_feature_name() << " as parent of " << front->get_feature_name() << endl;
				parents.push(front->parent);
				check[front->parent->get_feature_name()] = true;
			}
	}
	return true;
}
