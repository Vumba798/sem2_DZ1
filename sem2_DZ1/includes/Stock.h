#pragma once
#ifndef _STOCK_
#define _STOCK_

#include <algorithm>
#include <string>
#include <iostream>
#include <unordered_map>
#include <map>

using std::multimap;
using std::unordered_map;
using std::string;
using std::pair;
using std::cin;
using std::cout;
using std::endl;

enum stockType {cloth,shoes};


typedef unordered_map<string, multimap<size_t, pair<size_t, size_t>>> THING_SIZES_MAP;
typedef std::pair<string, multimap<size_t, pair<size_t, size_t>>> THING_SIZES_PAIR;
typedef multimap<size_t, pair<size_t, size_t>> AMOUNT_SIZE_MAP;


class Stock {
protected:
	size_t thingsAmount = 0;
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
	virtual size_t get_amount();
	virtual size_t get_capacity() const;
	virtual string get_city() const;
	virtual size_t get_ID() const;
	virtual string get_name() const;
	virtual stockType get_type() const;
	virtual void increase_amount(const size_t&);
	virtual void set_amount(const size_t&);
	virtual void set_name(const string&);
	virtual void set_city(const string&);
	virtual void set_capacity(const size_t&);
	virtual size_t count_goods() const = 0;  // i don't know why i wrote this function, i use simple counter
	virtual THING_SIZES_MAP get_sizes() const = 0;
	virtual void set_sizes(THING_SIZES_MAP) = 0;
	virtual void edit_record() = 0;
	virtual void print();
};

#endif
