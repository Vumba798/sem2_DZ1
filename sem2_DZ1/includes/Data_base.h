#pragma once
#ifndef _DATA_BASE_
#define _DATA_BASE_

#include "Cloth_stock.h"
#include "Shoes_stock.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>
#include <map>

using std::endl;
using std::cin;
using std::cout;
using std::map;
using std::pair;
using std::string;



class Data_base {
private:
	
	
public:
	std::vector<Stock*> stocks;
	std::filesystem::path path;
	Data_base() {};
	explicit Data_base(std::filesystem::path p) : path(p) {};
	void create();
	void init(std::fstream& file);
	void print() const;
	void sort_by_name();
	void sort_by_capacity();
	void write_to_file(std::fstream& file);
	~Data_base() {};
};



#endif
