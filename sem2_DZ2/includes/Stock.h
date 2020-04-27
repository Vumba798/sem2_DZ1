#pragma once
#ifndef _STOCK_
#define _STOCK_

#include <algorithm>
#include <string>
#include <iostream>
#include <unordered_map>
#include <map>

using std::unordered_map;
using std::string;
using std::pair;

enum stockType {cloth,shoes};



class Stock {
protected:
	stockType type;
	static size_t objCounter;
	size_t stockID;
	size_t capacity;
	string stockCity;
	string stockName;

public:
	Stock() {
		stockID = objCounter;
		++objCounter;
	}
	explicit inline Stock(std::string n) {
		stockName = n;
	};
	virtual size_t get_capacity() const;
	virtual string get_city() const;
	virtual size_t get_ID() const;
	virtual string get_name() const;
	virtual stockType get_type() const;
	virtual void set_name(const string&);
	virtual void set_city(const string&);
	virtual void set_capacity(const size_t&);
	virtual size_t count_goods() const = 0;
	virtual unordered_map<string, 
		unordered_map<size_t, pair<size_t, size_t>>> get_sizes() const = 0;
	virtual void set_sizes(unordered_map<string, 
		unordered_map<size_t, pair<size_t, size_t>>>) = 0;


};

#endif
