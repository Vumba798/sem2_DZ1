#include "../includes/Shoes_stock.h"

using std::endl;
using std::cin;
using std::cout;

unordered_map<string, multimap<size_t, 
	pair<size_t, size_t>>> Shoes_stock::get_sizes() const {
	unordered_map<string, multimap<size_t, pair<size_t, size_t>>> newSizes;
	for_each(sizes.begin(), sizes.end(), 
		[&newSizes](pair<string,multimap<size_t, size_t>> p)
		{
			multimap<size_t, pair<size_t, size_t>> newAmountSizes;
			for_each(p.second.begin(), p.second.end(),
				[&newAmountSizes, &p](pair < size_t, size_t> amountSizes)
				{
					newAmountSizes.insert(std::make_pair(amountSizes.first, std::make_pair(amountSizes.second, 0)));
				});
			newSizes.insert(std::make_pair(p.first, newAmountSizes));
		});
	return newSizes;
}

void Shoes_stock::set_sizes(unordered_map<string,
	multimap<size_t, pair<size_t, size_t>>> s) {

	unordered_map<string, multimap<size_t, size_t>> newSizes;

	for_each(s.begin(), s.end(), 
		[&newSizes](pair<string,multimap<size_t, pair<size_t,size_t>>> p) 
		{
			multimap <size_t, size_t> newAmountSizes;
			for_each(p.second.begin(), p.second.end(), 
				[&newAmountSizes, &p](pair<size_t,pair<size_t,size_t>> amountSizes)
				{
					newAmountSizes.insert(std::make_pair (amountSizes.first, amountSizes.second.first));
				});
			newSizes.insert(std::make_pair(p.first, newAmountSizes));
		});
	sizes = newSizes;
}



size_t Shoes_stock::count_goods() const {
	size_t amount = 0;
	for_each(sizes.begin(), sizes.end(), // Сначала из карты выбираем пары
		[&amount](pair<string,
			multimap<size_t, size_t>>  typeSizes) {
				for_each(typeSizes.second.begin(), typeSizes.second.end(), //Из пар выбираем карту
					[&amount](pair<size_t, size_t> sizesAmount) {
						amount += sizesAmount.first;
					});
		});
	return amount;
}
