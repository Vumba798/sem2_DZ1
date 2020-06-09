#include "../includes/Shoes_stock.h"

using std::endl;
using std::cin;
using std::cout;

unordered_map<string, AMOUNT_SIZE_MAP> Shoes_stock::get_sizes() const {
	unordered_map<string, AMOUNT_SIZE_MAP> newSizes;
	for_each(sizes.begin(), sizes.end(), 
		[&newSizes](pair<string,multimap<size_t, size_t>> p)
		{
			AMOUNT_SIZE_MAP newAmountSizes;
			for_each(p.second.begin(), p.second.end(),
				[&newAmountSizes, &p](pair < size_t, size_t> amountSizes)
				{
					newAmountSizes.insert(std::make_pair(amountSizes.first, std::make_pair(amountSizes.second, 0)));
				});
			newSizes.insert(std::make_pair(p.first, newAmountSizes));
		});
	return newSizes;
}

void Shoes_stock::set_sizes(unordered_map<string, AMOUNT_SIZE_MAP> s) {

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

void Shoes_stock::edit_record() {
	bool open = true;

	cout << "First of all, you should choose what you want to change, name of thing or size, use 'name' or 'size'" << endl << endl;

	cout << "\t\tList for edititng names" << endl << endl;
	cout << "if you want to delete some kind of things input 'delete <name>'" << endl << endl;
	cout << "if you want to add new kind of things input 'add <name>'" << endl << endl;
	cout << "if you want edit name of thing input 'change <oldName> <newName>" << endl << endl;
	cout << "if you want to see avaible commands, input 'help'" << endl << endl;

	cout << "\t\tList for editing sizes" << endl << endl;\
	cout << "if you want to delete some size input 'delete <name> <size>'" << endl << endl;
	cout << "if you want to add new size of things input 'add <name> <size> <amount>'" << endl << endl;
	cout << "if you want edit name of thing inpuut 'change <name> <size> <newAmount>'" << endl << endl;
	cout << "----------------------------------------------------------------------------------------------------" << endl << endl;
	string msg;

	while (open) {
		cout << ">>> ";
		getline(cin, msg);
		if (msg == "close") {
			open = false;
		}
		else if (msg == "help") {

			cout << "If you want to edit records, you should open datebase," << endl << 
				"then find stock and choose mode of editing, either names, or sizes" << endl << endl;
			cout << "First of all, you should choose what you want to change, name of thing or size, use 'names' or 'sizes'" << endl << endl ;

			cout << "\t\tList for edititng names" << endl << endl;
			cout << "if you want to delete some kind of things input 'delete <name>'" << endl << endl;
			cout << "if you want to add new kind of things input 'add <name>'" << endl << endl;
			cout << "if you want edit name of thing input 'change <oldName> <newName>" << endl << endl;
			cout << "if you want to see avaible commands, input 'help'" << endl << endl;

			cout << "\t\tList for editing sizes" << endl << endl;
			cout << "if you want to delete some size input 'delete <name> <size>'" << endl << endl;
			cout << "if you want to add new size of things input 'add <name> <size> <amount>'" << endl << endl;
			cout << "if you want edit name of thing inpuut 'change <name> <size> <newAmount>'" << endl << endl;
			cout << "----------------------------------------------------------------------------------------------------" << endl << endl;
		}
		else if (msg == "print") {
			print();
		}
		else if (msg == "name") {


			getline(cin, msg);
			if (msg.find("delete ") == 0) {
				string name = msg.substr(7, msg.size());
				bool deleted = false;
				auto iter = sizes.begin();
				while (iter != sizes.end()) {
					if (iter->first == name) {
						for_each(iter->second.begin(), iter->second.end(), [this](pair<size_t, size_t> p) {

							thingsAmount -= p.first;
							});
						iter = sizes.erase(iter);
						deleted = true;
						cout << "Type was deleted successfully" << endl << endl;
						break;
					}
					++iter;
				}

				if (!deleted) {
					cout << "There is no any item with such name" << endl << endl;
				}
			}
			else if (msg == "help") {
				cout << "\t\tlist for edititng names" << endl << endl;
				cout << "if you want to delete some kind of things input 'delete <name>'" << endl << endl;
				cout << "if you want to add new kind of things input 'add <name>'" << endl << endl;
				cout << "if you want edit name of thing input 'change <oldName> <newName>" << endl << endl;
				cout << "if you want to see avaible commands, input 'help'" << endl << endl;
			}
			else if (msg.find("add ") == 0) {
				string name = msg.substr(4, msg.size());
				bool check3 = true;
				multimap<size_t,size_t> amountSizes;
				if (sizes.find(name) == std::end(sizes)) {
					while (check3) {
						size_t s, amount;
						while (1) {
							try {
								cout << endl << "Input the size: ";
								cin_protect(s);
								cout << endl << "Input the amount of this size clothes: ";
								cin_protect(amount);
								for_each(amountSizes.begin(), amountSizes.end(),
									[&s](pair < size_t, size_t> p) {
										if (s == p.second) {
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
						amountSizes.insert(std::make_pair(amount, s));
						cout << endl << endl << "Do you want to add one more size? 1/0 ";
						cin_protect(check3);
					}
					sizes.insert(std::make_pair(name, amountSizes));
				}
				else {
					cout << "This type of cloth is already in stock" << endl << endl;
				}
			}
			else if (msg.find("change ") == 0) {
				string tmp = msg.substr(7, msg.size());
				string oldName = tmp.substr(0, tmp.find(" "));
				string newName = tmp.substr(tmp.find(" "), tmp.size());
				bool foundIt = false;
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

			cout << ">>> ";
			getline(cin, msg);
			if (msg == "help") {
				cout << "\t\tList for editing sizes" << endl << endl;
				cout << "if you want to delete some size input 'delete <name> <size>'" << endl << endl;
				cout << "if you want to add new size of things input 'add <name> <size> <amount>'" << endl << endl;
				cout << "if you want edit name of thing inpuut 'change <name> <size> <newAmount>'" << endl << endl;
			}
			if (msg.find("delete ") == 0) {
				string tmp = msg.substr(7, msg.size());
				string name = tmp.substr(0, tmp.find(" "));
				size_t size = stoi(msg.substr(msg.find(" "), msg.size()));
				bool foundSize = false;
				auto thingSizes = sizes.find(name);
				if (thingSizes != std::end(sizes)) {
					
					auto iter = thingSizes->second.begin();
					while (iter != thingSizes->second.end()) {
						if (iter->second == size) {
							thingsAmount -= iter->first;
							thingSizes->second.erase(iter);
							foundSize = true;
							break;
						}
						++iter;
					}
					if (foundSize){
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
				string tmp1 = tmp.substr(0, tmp.find(" "));
				tmp = tmp.substr(tmp.find(" ")+1, tmp.size());
				size_t size = stoi(tmp1);
				size_t amount = stoi(tmp);
				if (amount + thingsAmount > capacity) {
					cout << "You can't add more items than the stock's capacity" << endl << endl;
				}
				else {
					thingsAmount += amount;
					auto thingSizes = sizes.find(name);
					if (thingSizes != std::end(sizes)) {
						auto iter = thingSizes->second.begin();
						while (iter != thingSizes->second.end()) {
							if (iter->second == size) {
								break;
							}
							++iter;
						}
						if (iter == std::end(thingSizes->second)) {
							thingSizes->second.insert(std::make_pair(amount, size));
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
				tmp = tmp.substr(tmp.find(" ") + 1, tmp.size());
				string tmp1 = tmp.substr(0, tmp.find(" "));
				tmp = tmp.substr(tmp.find(" ") + 1, tmp.size());
				size_t size = stoi(tmp1);
				size_t newAmount = stoi(tmp);
				auto thingSizes = sizes.find(name);
				if (thingSizes != std::end(sizes)) {
					bool foundIt = false;

					auto iter = thingSizes->second.begin();
					while (iter != thingSizes->second.end()) {
						if (iter->second == size) {
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
