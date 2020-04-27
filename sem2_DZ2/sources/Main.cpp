#include <algorithm>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <vector>
#include <string>


#include "../includes/Data_base.h"
#include "../includes/Cloth_stock.h"
#include "../includes/Shoes_stock.h"
#include "Source.cpp"

namespace fs = std::filesystem;

using std::endl;
using std::cerr;
using std::cin;
using std::cout;
using std::exception;
using std::ios;
using std::pair;
using std::string;
using std::unordered_map;

size_t Stock::objCounter = 0;

string name_to_path(const string& str) {
	string path = "data/";
	path += str;
	path += ".txt";
	return path;
}

void open_data_base(Data_base& db, std::fstream& file) {

	db.stocks.clear();
	unordered_map<string, unordered_map<size_t, pair<size_t, size_t>>> cSizes;
	string line;
	

	while (getline(file,line)) {
		std::string name;
		getline(file, line); // считываем тип склада
		getline(file, name);
		if (line == "C") {
			static Cloth_stock cStock(name);
			unordered_map<string,unordered_map<size_t, pair<size_t, size_t>>> cSizes;

			string clothType;
			db.stocks.push_back(&cStock);

			getline(file, line); // считываем символ разделитель $ для типов одежды
			while (line != "@")
			{
				getline(file, clothType); // считываем тип одежды

				unordered_map<size_t, pair<size_t, size_t>> amountSizes;

				getline(file, line); // считываем количество
				while (line != ";") { // считываем пока не встретим символ-конец для типа
					size_t amount, s1, s2;
					amount = std::stoi(line);
					getline(file, line); // считываем первый размер
					s1 = std::stoi(line);
					getline(file, line); // считываем второй размер
					s2 = std::stoi(line);
					amountSizes.insert(std::make_pair(amount, std::make_pair(s1, s2)));
					getline(file, line); // read either amount or symbol-end of type ;
				}
				cSizes.insert(std::make_pair(clothType, amountSizes));

				getline(file, line); // read end of type $ or end of sizes @
			}
			db.stocks.back()->set_sizes(cSizes);
		}
		else if (line == "S") {
			static Shoes_stock sStock(name);
			unordered_map<string,unordered_map<size_t, pair<size_t, size_t>>> sSizes;
			string clothType;

			db.stocks.push_back(&sStock);
			getline(file, line); // считываем символ разделитель $ для типов одежды
			while (line != "@") {
				getline(file, clothType); // считываем тип одежды

				unordered_map<size_t, pair<size_t, size_t>> amountSizes;
				getline(file, line); // считываем количество
				while (line != ";") { // считываем пока не встретим символ-конец для типа
					size_t amount, s;
					amount = std::stoi(line);
					getline(file, line); // считываем единственный размер
					s = std::stoi(line);
					amountSizes.insert(std::make_pair(amount, std::make_pair(s, 0)));
					getline(file, line); // skips 0 size
					getline(file, line); // reads either amount or end of type ;
				}
				sSizes.insert(std::make_pair(clothType, amountSizes));
				getline(file, line); // считываем символ разделитель $ для типов одежды
			}
			db.stocks.back()->set_sizes(sSizes);
		}

		getline(file, line); // read capacity
		db.stocks.back()->set_capacity(std::stoi(line));
		getline(file, line); // read city
		db.stocks.back()->set_city(line);


	}
}

void write_to_file(std::fstream& file, Stock* &stock) {
	file << "#" << endl;
	if (stock->get_type() == shoes) {
		file << "S" << endl;
	}
	else {
		file << "C" << endl;
	}
	file << stock->get_name() << endl;
	
	unordered_map<string, unordered_map<size_t, pair<size_t, size_t>>> sizes;
	sizes = stock->get_sizes();
	for_each(sizes.begin(), sizes.end(), [&file](pair<string, unordered_map<size_t, pair<size_t,size_t>>> p) {
		file << "$" << endl;
		file << p.first << endl;
		for_each(p.second.begin(), p.second.end(), [&file](std::pair<size_t, pair<size_t,size_t>> amountSizes) {
			file << amountSizes.first << endl;
			file << amountSizes.second.first << endl;
			file << amountSizes.second.second << endl;
		});
		file << ";" << endl;
	});
	file << "@" << endl;
	file << stock->get_capacity() << endl;
	file << stock->get_city() << endl;
}

void print_db(const Data_base& db) {

}

template <typename T>
void cin_protect(T& num) { //keeps you from cases when you input a symbol instead of number
	bool isOk = false;
	while (!isOk) {
		cin >> num;
		if (cin.fail()) {
			cout << "failed in cin, try again" << endl;
			cin.clear();
			cin.ignore(100, '\n');
		}
		isOk = true;
	}	
}


int main() {

	fs::path p(fs::current_path());
	p += "\\hello.txt";
	Data_base db;
	std::fstream file;
	std::ofstream fout;
	std::vector<string> dbList;
	string line;
	//INITISALISATION
	try {
		// В этом файле находятся пути к БД
		file.open("data/data_base_list.txt", ios::in);
		if (!file.is_open()) {
			throw exception("file is not open");
		}
		while (getline(file,line)) { // reads db names in loop
			dbList.push_back(line);
		}
		file.close();
	}
	catch (const exception & ex) {
		cerr << "An error has occured: " << ex.what() << endl;
	}

	cout << "Welcome, username" << endl << endl;
	cout << "Use 'help' to see functions" << endl << endl;

	bool shtdwn = false;
	string msg;
	while (shtdwn != true) {
		getline(cin, msg);

		if (msg == "help") {
			cout << endl << endl;
			cout << "To create DB enter 'create database <name>'" << endl << endl;
			cout << "To show list of DBs enter 'show databases'" << endl << endl;
		}
		
		else if (msg == "shutdown") {
			shtdwn = true;
		}
		else if (msg.find("screate database ") == 0) {
			string name = msg.substr(16, msg.size());
		}
		else if (msg.find("open database ") == 0) {
			string name = msg.substr(14, msg.size());
			if (std::find(dbList.begin(), dbList.end(), name) != std::end(dbList)) {
				db.path = name_to_path(name);
				try {
					file.open(db.path, ios::in | ios::app);
					if (!file.is_open()) {
						throw exception("file is not open");
					}
				}
				catch (const exception & ex) {
					cerr << "An error has occured: " << ex.what() << endl;
				}
				open_data_base(db, file);
				db.print();
				file.close();
			}
			else {
				cout << "There is no any database with such name" << endl << endl;
			}

		}
		else if (msg.find("create database ") == 0) {
			string name = msg.substr(16, msg.size());
			if (find(dbList.begin(), dbList.end(), name) != std::end(dbList)) {
				string name = msg.substr(16, msg.size());
				string path = name_to_path(name);
				db.stocks.clear();
				db.path = path;

				file.open("data/data_base_list.txt", ios::in | ios::app); // Adding DB to db list
				file << name << endl;
				file.close();
				dbList.push_back(name);

				file.open(path, ios::in | ios::app);

				bool check1 = true;
				while (check1) {

					cout << endl << "input the type of stock: cloth/shoes" << endl << endl;
					getline(cin, msg);
					if (msg == "cloth") {
						static Cloth_stock stockC(name);
						string tmp;
						size_t amount;
						cout << endl << "Input stock's name: ";
						getline(cin, tmp);
						stockC.set_name(tmp);
						cout << endl << "Input stock's city: ";
						getline(cin, tmp);
						stockC.set_city(tmp);
						cout << endl << "Input stock's capacity: ";
						cin_protect(amount);
						stockC.set_capacity(amount);


						unordered_map<string, unordered_map<size_t, pair<size_t, size_t>>> sizes;
						bool check2 = true;
						string name;
						while (check2) {
							bool check3 = true;
							cout << endl << "Please, input the name of thing: ";
							getline(cin, name);
							unordered_map<size_t, pair<size_t, size_t>> typeSizes;
							while (check3) {
								size_t s1, s2, amount;
								cout << endl << "Input the first size: ";
								cin_protect(s1);
								cout << endl << "Input the second size: ";
								cin_protect(s2);
								cout << endl << "Input the amount of this size clothes: ";
								cin_protect(amount);
								typeSizes.insert(std::make_pair(amount, std::make_pair(s1, s2)));
								cout << endl << endl << "Do you want to add one more record? 1/0 ";
								cin_protect(check3);
							}
							sizes.insert(std::make_pair(name, typeSizes));
							cout << "Do you want to add another thing? 1/0 ";
							cin_protect(check2);
						}
						stockC.set_sizes(sizes);
						db.stocks.push_back(&stockC);
					}
					else if (msg == "shoes") {

						static Shoes_stock stockS;
						string tmp;
						size_t amount;
						cout << endl << "Input stock's name: ";
						getline(cin, tmp);
						stockS.set_name(tmp);
						cout << endl << "Input stock's city: ";
						getline(cin, tmp);
						stockS.set_city(tmp);
						cout << endl << "Input stock's capacity: ";
						cin >> amount;
						stockS.set_capacity(amount);


						unordered_map<string, unordered_map<size_t, pair<size_t, size_t>>> sizes;
						bool check2 = true;
						string name;
						while (check2) {
							bool check3 = true;
							cout << endl << "Please, input the name of thing: ";
							cin >> name;
							unordered_map<size_t, pair<size_t, size_t>> typeSizes;
							while (check3) {
								size_t s, amount;
								cout << endl << "Input the size: ";
								cin_protect(s);
								cout << endl << "Input the amount of this size clothes: ";
								cin_protect(s);
								typeSizes.insert(std::make_pair(amount, std::make_pair(s, 0)));
								cout << endl << endl << "Do you want to add one more record? 1/0 ";
								cin_protect(check3);
							}
							sizes.insert(std::make_pair(name, typeSizes));
							cout << "Do you want to add another thing? 1/0 ";
							cin >> check2;
						}
						stockS.set_sizes(sizes);
						db.stocks.push_back(&stockS);
					}


					cout << endl << endl << "Do you want to add another stock? 1/0 ";
					cin >> check1;
					cin.ignore();
				}

				for (size_t i = 0; i < db.stocks.size(); ++i) {
					write_to_file(file, db.stocks[i]);
				}

				file.close();

			}
			else {
				cout << "Database with such name is already exists" << endl << endl;
			}
		}
		else if (msg == "show databases") {
			for (size_t i = 0; i < dbList.size(); ++i) {
				cout << dbList[i] << endl;
			}
		}
		else {
			cout << "unknown command" << endl;
		}
	}



	return 0;
}