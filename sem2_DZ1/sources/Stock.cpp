#include "../includes/Stock.h"

size_t  Stock::get_amount() {
	return thingsAmount;
}

void Stock::increase_amount(const size_t &amount) {
	thingsAmount += amount;
}

size_t Stock::get_capacity() const {
	return capacity;
}

std::string Stock::get_city() const {
	return stockCity;
}

size_t Stock::get_ID() const {
	return stockID;
}

std::string Stock::get_name() const {
	return stockName;
}

stockType Stock::get_type() const {
	return type;
}

void Stock::set_amount(const size_t& n) {
	thingsAmount = n;
}

void Stock::set_capacity(const size_t &n) {
	capacity = n;
}

void Stock::set_city(const std::string &city) {
	stockCity = city;
}

void Stock::set_name(const std::string &name) {
	stockName = name;
}

void Stock::print() {
	cout << "=====================================" << endl;
	cout << "NAME\t" << get_name() << endl;
	cout << "TYPE\t";
	if (get_type() == cloth) {
		cout << "cloth" << endl;
	}
	else {
		cout << "shoes" << endl;
	}
	cout << "CITY\t" << get_city() << endl;
	cout << "CAPACITY " << get_capacity() << endl;
	cout << "AMOUNT\t" << get_amount() << endl;
	cout << "SIZES" << endl;
	THING_SIZES_MAP sizes = get_sizes();
	for_each(sizes.begin(), sizes.end(), [](pair<string, AMOUNT_SIZE_MAP> p) {
		cout << " ###\t" << p.first << endl;
		for_each(p.second.begin(), p.second.end(), [](pair<size_t, pair<size_t, size_t>> amountSizes) {
			cout << "\t Size:\t" << amountSizes.second.first << "  ";
			if (amountSizes.second.second != 0) {
				cout << amountSizes.second.second;
			}
			cout << "\tAmount:\t" << amountSizes.first << endl;
			});
		cout << endl;
		});

	cout << "-------------------------------------" << endl;
}