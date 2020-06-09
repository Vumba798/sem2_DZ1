#pragma once
#include "Stock.h"
#include <map>
#include <vector>



class Shoes_stock : public Stock {
private:
	unordered_map<string,multimap<size_t, size_t>> sizes;
public:
	inline Shoes_stock() : Stock() {
		type = shoes;
	};
	inline Shoes_stock(std::string n) : Stock(n) {
		type = shoes;
	};
	unordered_map<string,AMOUNT_SIZE_MAP>  get_sizes() const override final;
	void set_sizes(THING_SIZES_MAP s) override final;
	size_t count_goods() const override final;
	void edit_record() override final;
};

