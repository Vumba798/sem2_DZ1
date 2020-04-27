#include "../includes/Stock.h"

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

void Stock::set_capacity(const size_t &n) {
	capacity = n;
}

void Stock::set_city(const std::string &city) {
	stockCity = city;
}

void Stock::set_name(const std::string &name) {
	stockName = name;
}