#pragma once
#include "Stock.h"



class Cloth_stock : public Stock {
private:
	THING_SIZES_MAP sizes;
public:
	inline Cloth_stock() : Stock() {
		type = cloth;
	};
	inline Cloth_stock(string n) : Stock(n) {
		type = cloth;
	};
	unordered_map<string,AMOUNT_SIZE_MAP> get_sizes() const override final;
	void set_sizes(unordered_map<string,AMOUNT_SIZE_MAP>) override final;
	size_t count_goods() const;		
	void edit_record() override final;
};

