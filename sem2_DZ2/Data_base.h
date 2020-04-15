#pragma once
#include "Stock.h"
#include <string>
#include <vector>
#include <filesystem>



class Data_base {
private:
	std::vector<Stock> stocks;
	std::filesystem::path path;
public:
	void find_db();
};

class DBMS {
private:
	std::vector<Data_base> data_bases;
	std::vector<std::filesystem::path> paths;
public:
	void print() const;
	void create();
	void open();
	void add();
	void edit_records();
	void sort_records();
	void choose();
	void save();
};





