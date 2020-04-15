#pragma once
#include "Stock.h"
#include <vector>
class Shoes_stock : public Stock {
private:
	int stockID;
	std::vector<int> sizes;
public:
	Shoes_stock();
	~Shoes_stock();
	void get_sizes() const override final;
	void get_capacity() const override final;
	void set_sizes() override final;
	void set_capacity() override final;
	void count_goods() override final;
};

