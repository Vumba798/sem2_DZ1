#include "../includes/Cloth_stock.h"
using std::endl;
using std::cin;
using std::cout;

unordered_map<string,unordered_map<size_t, pair<size_t, size_t>>> Cloth_stock::get_sizes() const {
	return sizes;
}

void Cloth_stock::set_sizes(unordered_map<string, 
	unordered_map<size_t, pair<size_t, size_t>>> s) {
	
	sizes = s;
}

size_t Cloth_stock::count_goods() const {
	size_t amount = 0;
	
	for_each(sizes.begin(), sizes.end(), 
		[&amount](pair<string,
			unordered_map<size_t, pair<size_t, size_t>>> typeSizes){
		for_each(typeSizes.second.begin(), typeSizes.second.end(), 
			[&amount](pair<size_t, pair<size_t, size_t>> sizes) {
			amount += sizes.first;
			});
		
		});
	return amount;
}

