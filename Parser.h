/*
 * Parser.h
 *
 *  Created on: 5 Mar 2017
 *      Author: alon
 */
#include <vector>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

#ifndef PARSER_H_
#define PARSER_H_

template<typename Out>
void split(const std::string &s, char delim, Out result);

std::vector<std::string> split(const std::string &s, char delim);

std::string numberToString ( int number );



#endif /* PARSER_H_ */
