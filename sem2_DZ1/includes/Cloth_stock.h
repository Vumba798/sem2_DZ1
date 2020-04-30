#pragma once
#include "Stock.h"



class Cloth_stock : public Stock {
private:
	unordered_map<string, multimap<size_t, pair<size_t, size_t>>> sizes;
public:
	inline Cloth_stock() : Stock() {
		type = cloth;
	};
	inline Cloth_stock(string n) : Stock(n) {
		type = cloth;
	};
//	~Cloth_stock();
	unordered_map<string,multimap<size_t, pair<size_t, size_t>>> get_sizes() const override final;
	void set_sizes(unordered_map<string,multimap<size_t, pair<size_t, size_t>>>) override final;
	size_t count_goods() const;
};

