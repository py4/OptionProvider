#include "parser.h"
#include <sstream>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <cctype>

using namespace std;
using namespace parser;

namespace parser {

	Type scanf_for_type(const string& line) {
		bool found_question = false;
		for(int i = 0; i < line.length(); i++) {
			if(line[i] == '?')
				found_question = true;
			if(line[i] == '+')
				return _MANDATORY;
			if(line[i] == '^')
				return _XOR;
			if(line[i] == '|')
				return _OR;
		}
		if(found_question)
			return _OPTIONAL;
		return _MANDATORY;
	}

	Type get_type(const string& token) {
		if(token == "+")
			return _MANDATORY;
		if(token == "|")
			return _OR;
		if(token == "^")
			return _XOR;
		if(token == "?")
			return _OPTIONAL;
	}

	char get_rep_of_type(Type t) {
		if(t == _MANDATORY)
			return '+';
		if(t == _OPTIONAL)
			return '?';
		if(t == _XOR)
			return '^';
		if(t == _OR)
			return '|';
	}

	string get_clear_string(string const& input) {
		istringstream buff(input);
		ostringstream result;

		copy(istream_iterator <string> (buff),
				istream_iterator<string> (),
				ostream_iterator<string> (result, " "));

		return result.str();
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
		if(s[0] == '?')
			return true;
		return false;
	}

	vector < pair < string, Type > > get_features(const string& line) { 
		vector < pair < string, Type > > result;
		vector < string > initial_tokens = tokenize_input(line, '=');
		strip_str(initial_tokens[0]);
		string main_name = initial_tokens[0];

		Type desc_type = scanf_for_type(initial_tokens[1]);
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

	void strip_str(string& str) {
		str.erase(remove_if(str.begin(), str.end(), ::isspace), str.end());
	}

	vector < string > get_requested_features(string& line) {
		strip_str(line);
		line.erase(0, 1);
		line.erase(line.length() - 1);
		return tokenize_input(line, ',');
	}
	
}