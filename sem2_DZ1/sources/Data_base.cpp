#include "../includes/Data_base.h"

template <typename T> // Additional function
void cin_protect(T& num) { //keeps you from cases when you input a symbol instead of number
	cin >> num;
	if (static_cast<int>(num) < 0) {
		throw std::invalid_argument("impossible value");
	}
	if (cin.fail()) {
		cin.clear();
		cin.ignore(100, '\n');
		throw std::invalid_argument("failed in cin");
	}
	cin.ignore();
}

void Data_base::create() {

	stocks.clear();
	bool check1 = true;
	while (check1) {
		string msg;
		cout << endl << "input the type of stock: cloth/shoes: ";
		getline(cin, msg);
		if (msg == "cloth") {
			stocks.push_back(new Cloth_stock);
			string tmp;
			size_t amount;
			cout << endl << "Input stock's name: ";
			getline(cin, tmp);
			stocks.back()->set_name(tmp);
			cout << endl << "Input stock's city: ";
			getline(cin, tmp);
			stocks.back()->set_city(tmp);
			while (1) {
				try {
					cout << endl << "Input stock's capacity: ";
					cin_protect(amount);
					break;
				}
				catch (const std::invalid_argument & ex) {
					cout << "#####################################################################################" << endl << endl;
					std::cerr << "An error has occured: " << ex.what() << endl;
					continue;
				}
			}
			stocks.back()->set_capacity(amount);


			unordered_map<string, multimap<size_t, pair<size_t, size_t>>> sizes;
			bool check2 = true;
			string name;
			while (check2) {
				bool check3 = true;
				while (1) {
					try {
						cout << endl << "Please, input the name of thing: ";
						
						getline(cin, name);
						for_each(sizes.begin(), sizes.end(),
							[&name](std::pair<string, multimap<size_t, pair<size_t, size_t>>> p) {
								if (name == p.first) {
									throw std::invalid_argument("This type of clothes is already exists");
								}

							});
						break;
					}
					catch (const std::invalid_argument & ex) {
						cout << "#####################################################################################" << endl << endl;
						std::cerr << "An error has occured: " << ex.what() << endl;
						continue;
					}
				}
				multimap<size_t, pair<size_t, size_t>> amountSizes;
				while (check3) {
					try {
						size_t s1, s2, amount;
						while (true) {
							try {
								cout << endl << "Input the first size: ";
								cin_protect(s1);
								cout << endl << "Input the second size: ";
								cin_protect(s2);
								for_each(amountSizes.begin(), amountSizes.end(),
									[&s1,&s2](pair < size_t, pair<size_t, size_t>> p) {
										if (s1 == p.second.first && s2 == p.second.second) {
											throw std::invalid_argument("this size is already exists");
										}

									});
								cout << endl << "Input the amount of this size clothes: ";
								cin_protect(amount);
								if (stocks.back()->get_amount() + amount > stocks.back()->get_capacity()) {
									throw std::invalid_argument("amount of things is greater than capacity");
								}
								break;
							}
							catch (const std::invalid_argument & ex) {
								cout << "#####################################################################################" << endl << endl;
								cout << "An error has occured: " << ex.what() << ".Please, try again: " << endl;
								continue;
							}
						}
						stocks.back()->increase_amount(amount);
						amountSizes.insert(std::make_pair(amount, std::make_pair(s1, s2)));
					}
					catch (const std::exception & ex) {
						cout << "#####################################################################################" << endl << endl;
						std::cerr << "An error has occured: " << ex.what() << endl << endl;
					}
					cout << endl << endl << "Do you want to add one more record? 1/0 ";
					cin_protect(check3);

				}
				sizes.insert(std::make_pair(name, amountSizes));
				cout << "Do you want to add another thing? 1/0 ";
				cin_protect(check2);
			}
			stocks.back()->set_sizes(sizes);
			cout << endl << endl << "Do you want to add another stock? 1/0 ";
			cin >> check1;
		}
		else if (msg == "shoes") {

			stocks.push_back(new Shoes_stock);
			string tmp;
			size_t amount;
			cout << endl << "Input stock's name: ";
			getline(cin, tmp);
			stocks.back()->set_name(tmp);
			cout << endl << "Input stock's city: ";
			getline(cin, tmp);
			stocks.back()->set_city(tmp);
			while (1) {
				try {
					cout << endl << "Input stock's capacity: ";
					cin_protect(amount);
					break;
				}
				catch (const std::invalid_argument & ex) {
					cout << "#####################################################################################" << endl << endl;
					std::cerr << "An error has occured: " << ex.what() << endl;
					continue;
				}
			}
			stocks.back()->set_capacity(amount);


			unordered_map<string, multimap<size_t, pair<size_t, size_t>>> sizes;
			bool check2 = true;
			string name;
			while (check2) {
				bool check3 = true;
				while (1) {
					try {
						cout << endl << "Please, input the name of thing: ";
						getline(cin, name);
						for_each(sizes.begin(), sizes.end(),
							[&name](std::pair<string, multimap<size_t, pair<size_t, size_t>>> p) {
								if (name == p.first) {
									throw std::invalid_argument("This type of clothes is already exists");
								}

							});
						break;
					}
					catch (const std::invalid_argument & ex) {
						cout << "#####################################################################################" << endl << endl;
						std::cerr << "An error has occured: " << ex.what() << endl;
						continue;
					}
				}
				multimap<size_t, pair<size_t, size_t>> amountSizes;
				while (check3) {
					size_t s, amount;
					while (1) {
						try {
							cout << endl << "Input the size: ";
							cin_protect(s);
							cout << endl << "Input the amount of this size clothes: ";
							cin_protect(amount);
							for_each(amountSizes.begin(), amountSizes.end(),
								[&s](pair < size_t, pair<size_t, size_t>> p) {
									if (s == p.second.first) {
										throw std::invalid_argument("this size is already exists");
									}
								});
							if (stocks.back()->get_amount() + amount > stocks.back()->get_capacity()) {
								throw std::invalid_argument("amount of things is greater than capacity");
							}
							break;
						}
						catch (const std::exception & ex) {
							cout << "#####################################################################################" << endl << endl;
							std::cerr << "An error has occured: " << ex.what() << ". Please, try again:" << endl << endl;
						}
					}
					stocks.back()->increase_amount(amount);
					amountSizes.insert(std::make_pair(amount, std::make_pair(s, 0)));
					cout << endl << endl << "Do you want to add one more record? 1/0 ";
					cin_protect(check3);
				}
				sizes.insert(std::make_pair(name, amountSizes));
				cout << "Do you want to add another thing? 1/0 ";
				cin_protect(check2);
			}
			stocks.back()->set_sizes(sizes);
			cout << endl << endl << "Do you want to add another stock? 1/0 ";
			cin >> check1;
		}
		else {
			cout << "Unknown command, try again" << endl;
			cin.clear();
		}
		cin.ignore();		
	}
}

void Data_base::init(std::fstream& file) {
	stocks.clear();
	unordered_map<string, multimap<size_t, pair<size_t, size_t>>> cSizes;
	string line;


	while (getline(file, line)) {
		std::string name;
		getline(file, line); // reads type of stock
		getline(file, name);
		if (line == "C") {
			stocks.push_back(new Cloth_stock(name));
			unordered_map<string, multimap<size_t, pair<size_t, size_t>>> cSizes;

			string clothType;

			getline(file, line); // read capacity
			stocks.back()->set_capacity(std::stoi(line));

			getline(file, line); // reads delimeter $
			while (line != "@")
			{
				getline(file, clothType); // считываем тип одежды

				multimap<size_t, pair<size_t, size_t>> amountSizes;

				getline(file, line); // read amount
				while (line != ";") { // read type-sizes
					bool exists = false;
					size_t amount, s1, s2;
					amount = std::stoi(line);
					stocks.back()->increase_amount(amount);
					getline(file, line); // read first size
					s1 = std::stoi(line);
					getline(file, line); // read second size
					s2 = std::stoi(line);
					amountSizes.insert(std::make_pair(amount, std::make_pair(s1, s2)));
					getline(file, line); // read either amount or symbol-end of type ;
				}
				cSizes.insert(std::make_pair(clothType, amountSizes));

				getline(file, line); // read end of type $ or end of sizes @
			}
			stocks.back()->set_sizes(cSizes);
		}
		else if (line == "S") {
			static Shoes_stock sStock(name);
			unordered_map<string, multimap<size_t, pair<size_t, size_t>>> sSizes;
			string clothType;

			stocks.push_back(&sStock);

			getline(file, line); // read capacity
			stocks.back()->set_capacity(std::stoi(line));

			getline(file, line); // считываем символ разделитель $ для типов одежды
			while (line != "@") {
				getline(file, clothType); // reads cloth type

				multimap<size_t, pair<size_t, size_t>> amountSizes;
				getline(file, line); // read amount
				while (line != ";") { // read delimeter of begin of type-sizes
					size_t amount, s;
					amount = std::stoi(line);
					getline(file, line); // read single size
					s = std::stoi(line);
					amountSizes.insert(std::make_pair(amount, std::make_pair(s, 0)));
					getline(file, line); // skips 0 size
					getline(file, line); // reads either amount or end of type ;
				}
				sSizes.insert(std::make_pair(clothType, amountSizes));
				getline(file, line); // считываем символ разделитель $ для типов одежды
			}
			stocks.back()->set_sizes(sSizes);
		}

		getline(file, line); // read amount of things
		stocks.back()->set_amount(std::stoi(line));
		getline(file, line); // read city
		stocks.back()->set_city(line);


	}
	file.close();
}


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
		cout << "AMOUNT\t" << stocks[i]->get_amount() << endl;
		cout << "SIZES" << endl;
		unordered_map<string, multimap<size_t, pair<size_t, size_t>>> sizes = stocks[i]->get_sizes();
		for_each(sizes.begin(), sizes.end(), [](pair<string, multimap<size_t, pair<size_t, size_t>>> p) {
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


bool name_comp(Stock* a, Stock* b) {
	return a->get_name() < b->get_name();
}

void Data_base::sort_by_name() {
	sort(stocks.begin(), stocks.end(), name_comp);
}

bool capacity_comp(Stock* a, Stock* b) {
	return a->get_capacity() < b->get_capacity();
}

void Data_base::sort_by_capacity() {
	sort(stocks.begin(), stocks.end(), capacity_comp);
}

void Data_base::write_to_file(std::fstream& file) {
	for (size_t i = 0; i < stocks.size(); ++i) {
		file << "#" << endl;
		if (stocks[i]->get_type() == shoes) {
			file << "S" << endl;
		}
		else {
			file << "C" << endl;
		}
		file << stocks[i]->get_name() << endl;
		file << stocks[i]->get_capacity() << endl;

		unordered_map<string, multimap<size_t, pair<size_t, size_t>>> sizes;
		sizes = stocks[i]->get_sizes();
		for_each(sizes.begin(), sizes.end(), [&file](pair<string, multimap<size_t, pair<size_t, size_t>>> p) {
			file << "$" << endl;
			file << p.first << endl;
			for_each(p.second.begin(), p.second.end(), [&file](std::pair<size_t, pair<size_t, size_t>> amountSizes) {
				file << amountSizes.first << endl;
				file << amountSizes.second.first << endl;
				file << amountSizes.second.second << endl;
				});
			file << ";" << endl;
			});
		file << "@" << endl;
		file << stocks[i]->get_amount() << endl;
		file << stocks[i]->get_city() << endl;
	}
}