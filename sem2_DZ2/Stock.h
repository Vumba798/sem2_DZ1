#pragma once
#include <string>

enum stockType { Cloth, Shoes };


class Stock {
protected:
	size_t objCounter;
	std::string stockName;
	stockType type;
public:
	inline Stock(std::string name, stockType t) :
		stockName(name),
		type(t)
	{
		++objCounter;
	};
	virtual void get_sizes() const = 0;
	virtual void get_capacity() const = 0;
	virtual void set_sizes() = 0;
	virtual void set_capacity() = 0;
	virtual void count_goods() = 0;
};
