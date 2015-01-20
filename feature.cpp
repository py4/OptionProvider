#include <string>
#include "feature.h"
#include <iostream>
#include <algorithm>
using namespace std;

Feature::Feature() {}

Feature::Feature(string& name, Type t) {
	set_feature_name(name);
	set_feature_type(t);
}

void Feature::set_feature_name(string& name) {
	feature_name = name;
}

void Feature::set_feature_type(Type t) {
	type = t;
}

string Feature::get_feature_name() {
	return feature_name;
}

Feature* Feature::find_among_children(std::string& name) {
	Feature* f;
	if(feature_name == name)
		return this;
	for(int i = 0; i < children.size(); i++) {
		f = children[i]->find_among_children(name);
		if(f != NULL)
			return f;
	}
	return NULL;
}

void Feature::set_children(vector< pair < string, Type > > & sub_features) {
	for(int i = 1; i < sub_features.size(); i++) {
		Feature* child = new Feature(sub_features[i].first, sub_features[i].second);
		child->parent = this;
		children.push_back(child);
	}
}

bool Feature::validate_request(vector < string > & req) {
	if(find(req.begin(), req.end(), feature_name) == req.end()) {
		cout << ">> feature not found:  " << feature_name << endl;
		return false;
	}
	if(children.size() == 0)
		return true;
	if(children[0]->type == _OR)
		return validate_or_children(req);
	if(children[0]->type == _XOR)
		return validate_xor_children(req);
	return validate_mand_and_optional_children(req);
}


bool Feature::validate_or_children(vector < string > & req) {	
	bool check = false;
	for(int i = 0; i < children.size(); i++)
		if(find(req.begin(), req.end(), children[i]->get_feature_name()) != req.end()) {
			check = true;
			if(!children[i]->validate_request(req))
				return false;
		}
	if(!check)
		cout << "no feature among or children of " << feature_name << endl;
	return check ? true : false;
}

bool Feature::validate_xor_children(vector < string > & req) {
	bool check = false;
	for(int i = 0; i < children.size(); i++) {
		if(find(req.begin(), req.end(), children[i]->get_feature_name()) != req.end()) {
			if(check) {
				cout << "more than one among xor children of " << feature_name << endl;
				return false;
			}
			if(!children[i]->validate_request(req))
				return false;
			check = true;
		}
	}
	if(!check)
		cout << "no feature among xor children of " << feature_name << endl;
	return check ? true : false;
}

bool Feature::validate_mand_and_optional_children(vector < string > & req) {
	for(int i = 0; i < children.size(); i++) {
		if(find(req.begin(), req.end(), children[i]->get_feature_name()) != req.end()) {
			if(!children[i]->validate_request(req))
				return false;
		} else if(children[i]->type == _MANDATORY) {
			cout << "mandatory children of  " << feature_name << " which is " << children[i]->get_feature_name() << " not found among request"  << endl;
			return false;
		}
	}
	return true;
}