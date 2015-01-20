#include "parser.h"
#include <sstream>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <cctype>

using namespace std;

Type scan_for_type(const string& line) {
	bool found_question = false;
	for(int i = 0; i < line.length(); i++) {
		switch(line[i]) {
			case '?':
				found_question = true;
			case '+':
				return _MANDATORY;
			case '^':
				return _XOR;
			case '|':
				return _OR;
		}
	}
	return (found_question ? _OPTIONAL : _MANDATORY);
}

char get_rep_of_type(Type t) {
	switch(t) {
		case _MANDATORY:
			return '+';
		case _OPTIONAL:
			return '?';
		case _XOR:
			return '^';
		case _OR:
			return '|';
	}
}

vector <string> tokenize_input(const string& line, char delimiter) {
	vector<string> result;
	istringstream iss(line);
	string s;
	while(getline(iss, s, delimiter))
		result.push_back(s);
	return result;
}

bool is_optional(const string& s) {
	return s[0] == '?';
}

vector < pair < string, Type > > get_features(const string& line) { 
	vector < pair < string, Type > > result;
	vector < string > initial_tokens = tokenize_input(line, '=');
	strip_str(initial_tokens[0]);
	string main_name = initial_tokens[0];

	Type desc_type = scan_for_type(initial_tokens[1]);
	vector < string > tokens = tokenize_input(initial_tokens[1], get_rep_of_type(desc_type));
		
	result.push_back(make_pair(main_name, desc_type)); // main feature name

	for(int i = 0; i < tokens.size(); i ++) {
		strip_str(tokens[i]);
		if(desc_type != _MANDATORY)
			result.push_back(make_pair(tokens[i], desc_type));
		else {
			if(is_optional(tokens[i]))
				result.push_back(make_pair(tokens[i].substr(1), _OPTIONAL));
			else
				result.push_back(make_pair(tokens[i], _MANDATORY));
		}
	}
	return result;
}

vector < string > get_requested_features(string& line) {
	strip_str(line);
	line.erase(0, 1);
	line.erase(line.length() - 1);
	return tokenize_input(line, ',');
}

void strip_str(string& str) {
	str.erase(remove_if(str.begin(), str.end(), ::isspace), str.end());
}