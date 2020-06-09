#include "../includes/Cloth_stock.h"
using std::endl;
using std::cin;
using std::cout;

unordered_map<string,multimap<size_t, pair<size_t, size_t>>> Cloth_stock::get_sizes() const {
	return sizes;
}

void Cloth_stock::set_sizes(unordered_map<string, 
	multimap<size_t, pair<size_t, size_t>>> s) {
	
	sizes = s;
}

size_t Cloth_stock::count_goods() const {
	size_t amount = 0;
	
	for_each(sizes.begin(), sizes.end(), 
		[&amount](pair<string,
			multimap<size_t, pair<size_t, size_t>>> typeSizes){
		for_each(typeSizes.second.begin(), typeSizes.second.end(), 
			[&amount](pair<size_t, pair<size_t, size_t>> sizes) {
			amount += sizes.first;
			});
		
		});
	return amount;
}

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

void Cloth_stock::edit_record() {
	string msg;
	bool open = true;

	cout << "if you want to delete some kind of things input 'delete <name>'" << endl << endl;
	cout << "if you want to add new kind of things input 'add <name>'" << endl << endl;
	cout << "if you want edit name of thing input 'change <oldName> <newName>" << endl << endl;
	cout << "if you want to close editor, input 'exit'" << endl << endl;
	cout << "if you want to print the stock, input 'print'" << endl << endl;
	cout << "if you want to see avaible commands, input 'help'" << endl << endl;

	while (open) {
		cout << ">>> ";
			getline(cin, msg);
		if (msg == "close") {
			open = false;
		}
		else if (msg == "help") {
			cout << "if you want to delete some kind of things input 'delete <name>'" << endl << endl;
			cout << "if you want to add new kind of things input 'add <name>'" << endl << endl;
			cout << "if you want edit name of thing input 'change <oldName> <newName>" << endl << endl;
			cout << "if you want to print the stock, input 'print'" << endl << endl;
			cout << "if you want to close editor, input 'exit'" << endl << endl;
		}
		else if (msg == "print") {
			print();
		}
		else if (msg == "name") {
			cout << ">>>> ";
			getline(cin, msg);
			if (msg == "print") {
				print();
			}
			else if (msg.find("delete ") == 0) {
				string name = msg.substr(7, msg.size());
				auto iter = sizes.begin();
				bool deleted = false;
				while (iter != sizes.end()) {
					if (iter->first == name) {
						for_each(iter->second.begin(), iter->second.end(), [this](pair<size_t, pair<size_t, size_t>> p) {
							thingsAmount -= p.first;
							});
						iter = sizes.erase(iter);
						cout << "Type was deleted successfully" << endl << endl;
						break;
					}
					++iter;
				}
				if (!deleted) {
					cout << "There is no any item with such name" << endl << endl;
				}
			}

			else if (msg.find("add ") == 0) {
				string name = msg.substr(4, msg.size());
				bool check3 = true;
				multimap<size_t, pair<size_t,size_t>> amountSizes;
				if (sizes.find(name) == std::end(sizes)) {
					while (check3) {
						size_t s1, s2, amount;
						while (1) {
							try {
								cout << endl << "Input the first size: ";
								cin_protect(s1);
								cout << endl << "Input the second size: ";
								cin_protect(s2);
								cout << endl << "Input the amount of this size clothes: ";
								cin_protect(amount);
								for_each(amountSizes.begin(), amountSizes.end(),
									[&s1, &s2](pair < size_t, pair<size_t, size_t>> p) {
										if (s1 == p.second.first && s2 == p.second.second) {
											throw std::invalid_argument("this size is already exists");
										}
									});
								if (get_amount() + amount > get_capacity()) {
									throw std::invalid_argument("amount of things is greater than capacity");
								}
								break;
							}
							catch (const std::exception& ex) {
								cout << "#####################################################################################" << endl << endl;
								std::cerr << "An error has occured: " << ex.what() << ". Please, try again:" << endl << endl;
							}
						}
						increase_amount(amount);
						amountSizes.insert(std::make_pair(amount, std::make_pair(s1, s2)));
						cout << endl << endl << "Do you want to add one more size? 1/0 ";
						cin_protect(check3);
					}
					sizes.insert(std::make_pair(name, amountSizes));
				}
				else {
					cout << "This type of clothes is already exists" << endl << endl;
				}
			}
			else if (msg.find("change ") == 0) {
				string tmp = msg.substr(7, msg.size());
				string oldName = tmp.substr(0, tmp.find(" "));
				string newName = tmp.substr(tmp.find(" ")+1, tmp.size());
				auto iter = sizes.begin();
				while (iter != sizes.end()) {
					if (iter->first == oldName) {
						const_cast<string&>(iter->first) = newName;
						cout << "The name was successfully changed" << endl << endl;
						break;
					}
					++iter;
				}
				if (iter == std::end(sizes)) {
					cout << "There is no any items with such type" << endl << endl;
				}
			}
			else {
				cout << "unknown command" << endl << endl;
			}
		}
		
		else if (msg == "sizes") {

			cout << "if you want to delete some size input 'delete <name> <size1> <size2>'" << endl << endl;
			cout << "if you want to add new size of things input 'add <name> <size1> <size2> <amount>'" << endl << endl;
			cout << "if you want edit name of thing inpuut 'change <name> <size1> <size2> <newAmount>'" << endl << endl;
			cout << "if you want to print the stock, input 'print'" << endl << endl;
			cout << ">>>> ";
			getline(cin, msg);
			if (msg == "print") {
				print();
			}
			else if (msg.find("delete ") == 0) {
				string tmp = msg.substr(7, msg.size());
				string name = tmp.substr(0, tmp.find(" "));
				tmp = tmp.substr(tmp.find(" ")+1, tmp.size());
				size_t s1 = stoi(tmp.substr(0, tmp.find(" ")));
				size_t s2 = stoi(tmp.substr(tmp.find(" ")+1, tmp.size()));
				bool foundSize = false;
				auto thingSizes = sizes.find(name);
				if (thingSizes != std::end(sizes)) {

					auto iter = thingSizes->second.begin();
					while (iter != thingSizes->second.end()) {
						if (iter->second.first == s1 && iter->second.second == s2) {
							thingsAmount -= iter->first;
							thingSizes->second.erase(iter);
							foundSize = true;
							break;
						}
						++iter;
					}
					if (foundSize) {
						cout << "the size was deleted successfully" << endl << endl;
					}
					else {
						cout << "there is no matched sizes" << endl << endl;
					}
				}
				else {
					cout << "there is no any thing with such name" << endl << endl;
				}
			}
			else if (msg.find("add ") == 0) {
				string tmp = msg.substr(4, msg.size());
				string name = tmp.substr(0, tmp.find(" "));
				tmp = tmp.substr(tmp.find(" ")+1, tmp.size());
				size_t s1 = stoi(tmp.substr(0, tmp.find(" ")));
				tmp = tmp.substr(tmp.find(" ")+1, tmp.size());
				size_t s2 = stoi(tmp.substr(0, tmp.find(" ")));
				size_t amount = stoi(tmp.substr(tmp.find(" "), tmp.size()));
				if (amount + thingsAmount > capacity) {
					cout << "You can't add more items than the stock's capacity" << endl << endl;
				}
				else {
					auto thingSizes = sizes.find(name);
					if (thingSizes != std::end(sizes)) {
						auto iter = thingSizes->second.begin();
						while (iter != thingSizes->second.end()) {
							if (iter->second.first == s1 && iter->second.second == s2) {
								break;
							}
							++iter;
						}
						if (iter == std::end(thingSizes->second)) {
							thingSizes->second.insert(std::make_pair(amount, std::make_pair(s1,s2)));
							increase_amount(amount);
						}
						else {
							cout << "There is a pair with such size already" << endl << endl;
						}
					}
					else {
						cout << "There is no any thing with such name" << endl << endl;
					}
				}
			}
			else if (msg.find("change ") == 0) {
				string tmp = msg.substr(7, msg.size());
				string name = tmp.substr(0, tmp.find(" "));
				tmp = tmp.substr(tmp.find(" ")+1, tmp.size());
				size_t s1 = stoi(tmp.substr(0, tmp.find(" ")));
				tmp = tmp.substr(tmp.find(" ")+1, tmp.size());
				size_t s2 = stoi(tmp.substr(0, tmp.find(" ")+1));
				size_t newAmount = stoi(tmp.substr(tmp.find(" "), tmp.size()));
				auto thingSizes = sizes.find(name);
				if (thingSizes != std::end(sizes)) {
					auto iter = thingSizes->second.begin();
					while (iter != thingSizes->second.end()) {
						if (iter->second.first == s1 && iter->second.second == s2) {
							int dif = static_cast<int>(newAmount) - static_cast<int>(iter->first);
							if (thingsAmount + dif > capacity) {
								cout << "You can't add more items than the stock's capacity" << endl << endl;
							}
							else {
								thingsAmount += dif;
								const_cast<size_t&>(iter->first) = newAmount;
								cout << "The size was succesfully changed" << endl << endl;
							}
							break;
						}
						++iter;
					}
					if (iter == std::end(thingSizes->second)) {
						cout << "there is no any matched sizes" << endl << endl;
					}
				}
				else {
					cout << "There is no any thing with such name" << endl << endl;
				}
			}
		}
		else {
			cout << "Unknown command" << endl << endl;
		}
	}
}
