#pragma once
#ifndef _DATA_BASE_
#define _DATA_BASE_

#include "Stock.h"
#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <unordered_map>

using std::endl;
using std::cin;
using std::cout;
using std::unordered_map;
using std::pair;
using std::string;



class Data_base {
private:
	
	
public:
	std::vector<Stock*> stocks;
	std::filesystem::path path;
	Data_base() {};
	explicit Data_base(std::filesystem::path p) : path(p) {};
	void print() const;
	~Data_base() {};
};



#endif
