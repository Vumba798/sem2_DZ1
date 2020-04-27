#include "../includes/Data_base.h"



void Data_base::print() const {
	cout << "STOCK PATH: " << path << endl << endl;

	for (size_t i = 0; i < stocks.size();++i) {
		cout << endl << "=====================================" << endl;
		cout << "\tSTOCK #" << i << endl;
		cout << "=====================================" << endl;
		cout << "NAME\t" << stocks[i]->get_name() << endl;
		cout << "TYPE\t";
		if (stocks[i]->get_type() == cloth) {
			cout << "cloth" << endl;
		}
		else {
			cout << "shoes" << endl;
		}
		cout << "CITY\t" << stocks[i]->get_city() << endl;
		cout << "CAPACITY " << stocks[i]->get_capacity() << endl;
		cout << "SIZES" << endl;
		unordered_map<string, unordered_map<size_t, pair<size_t, size_t>>> sizes = stocks[i]->get_sizes();
		for_each(sizes.begin(), sizes.end(), [](pair<string, unordered_map<size_t, pair<size_t, size_t>>> p) {
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
}