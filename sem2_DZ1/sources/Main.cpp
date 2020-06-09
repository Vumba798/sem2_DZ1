#include <algorithm>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <vector>
#include <string>


#include "../includes/Data_base.h"
#include "../includes/Cloth_stock.h"
#include "../includes/Shoes_stock.h"

namespace fs = std::filesystem;

using std::endl;
using std::cerr;
using std::cin;
using std::cout;
using std::exception;
using std::ios;
using std::pair;
using std::string;
using std::multimap;

size_t Stock::objCounter = 0;

string name_to_path(const string& str) {
	string path = "data/";
	path += str;
	path += ".txt";
	return path;
}



bool open_db(const std::vector<string>& dbList, Data_base& db, string name, std::fstream& file) {
	if (std::find(dbList.begin(), dbList.end(), name) != std::end(dbList)) {
		db.path = name_to_path(name);
		try {
			file.open(db.path, ios::in | ios::app);
			if (!file.is_open()) {
				throw exception("file is not open");
			}
			return true;
		}
		catch (const exception & ex) {
			cerr << "An error has occured: " << ex.what() << endl;
			return false;
		}
	}
	else {
		return false;
	}
}



int main(int argc, char* argv[]) {
	fs::path p(fs::current_path());
	p += "\\hello.txt";
	Data_base db;
	std::fstream file;
	std::ofstream fout;
	std::vector<string> dbList;
	string line;
	//INITI	SALISATION
	for (auto& it : fs::directory_iterator("data")) {

		string name = it.path().string();
		name = name.substr(name.find("\\") + 1);
		name = name.substr(0, name.size() - 4);
		dbList.push_back(name);
	}
	cout << "Welcome, username" << endl << endl;
	cout << "Use 'help' to see functions" << endl << endl << endl;

	bool shtdwn = false;
	string msg;
	while (shtdwn != true) {
		cout << endl << endl << "> ";
		getline(cin, msg);

		if (msg == "help") {
			cout << endl << "-------------------------------------------------------------------------------------" << endl;
			cout << "To close this programm use 'shutdown'" << endl << endl;
			cout << "To create DB enter 'create <name>'" << endl << endl;
			cout << "To show list of DBs enter 'show databases'" << endl << endl;
			cout << "To rename DB enter 'rename <oldName> <newName>'" << endl << endl;
			cout << "To delete DB enter 'delete <name>'" << endl << endl;
			cout << "To open DB enter 'open <name>', after openning db you are able:" << endl << endl;
			cout << "\t To sort DB by name use 'sort by name'" << endl << endl;
			cout << "\t To sort DB by capacity use 'sort by capacity'" << endl << endl;
			cout << "\t To rename DB use 'rename <newName>'" << endl << endl;
			cout << "\t To delete DB use 'delete'" << endl << endl;
			cout << "\t To choose stocks with big sizes use 'choose big sizes'" << endl << endl;
			cout << "\t To choose stocks with small sizes use 'choose small sizes'" << endl << endl;
			cout << "\t To choose stocks in city use 'choose in <city>'" << endl << endl;
			cout << "\t To close DB use 'close'" << endl << endl;
			cout << "\t To save current DB selection use 'save' or 'save as <newnName>'" << endl << endl;
			cout << "\t To undo DB selection use 'undo'" << endl << endl;


			cout << "\t\tIf you want to edit records, you should open datebase," << endl <<
				"\t\tthen find stock and choose mode of editing, either names, or sizes" << endl << endl;
			cout << "\t\tFirst of all, you should choose what you want to change," <<  
				"\t\tname of thing or size, use 'name' or 'size'" << endl << endl;

			cout << "\t\t\t\tList for edititng names" << endl << endl;
			cout << "\t\tif you want to delete some kind of things input 'delete <name>'" << endl << endl;
			cout << "\t\tif you want to add new kind of things input 'add <name>'" << endl << endl;
			cout << "\t\tif you want edit name of thing input 'change <oldName> <newName>" << endl << endl;
			cout << "\t\tif you want to see avaible commands, input 'help'" << endl << endl;

			cout << "\t\t\t\tList for editing sizes" << endl << endl;
			cout << "\t\tif you want to delete some size input 'delete <name> <size>'" << endl << endl;
			cout << "\t\tif you want to add new size of things input 'add <name> <size> <amount>'" << endl << endl;
			cout << "\t\tif you want edit name of thing inpuut 'change <name> <size> <newAmount>'" << endl << endl;
		}

		else if (msg == "shutdown") {
			shtdwn = true;
		}
		else if (msg.find("delete ") == 0) {
			cout << endl << "-------------------------------------------------------------------------------------" << endl;
			string name = msg.substr(7, msg.size());
			fs::remove(name_to_path(name));
			cout << endl << "\tDATABASE HAS BEEN DELETED" << endl << endl;
		}
		else if (msg.find("rename ") == 0) {
			cout << endl << "-------------------------------------------------------------------------------------" << endl;
			try {
				string oldName = msg.substr(7, msg.size());
				string name = oldName.substr(oldName.find(" ") + 1, oldName.size());
				oldName = oldName.substr(0, oldName.find(" "));
				cout << "OLD NAME: " << oldName << "\tNEW NAME: " << name << endl;
				if (find(dbList.begin(), dbList.end(), name) == std::end(dbList) && 
					find(dbList.begin(), dbList.end(), oldName) != std::end(dbList)) {
					fs::path p = fs::current_path() / "data";
					oldName += ".txt";
					name += ".txt";
					fs::rename(p / oldName, p / name);
				}
				else {
					cout << "Wrong database name!" << endl;
				}
			}
			catch (...) {
				cerr << "Unknown command" << endl << endl;
			}
		}
		else if (msg.find("open ") == 0) {
			string name = msg.substr(5, msg.size());

			if (open_db(dbList, db, name, file)) {
				db.init(file);

				cout << "=====================================================================================" << endl;
				cout << "\t\t\tDATABASE " << name << endl;
				cout << "=====================================================================================" << endl;

				bool close = false;
				while (close != true) {

					cout << endl << ">> ";
					getline(cin, msg);
					if (msg == "close") {
						close = true;
					}
					else if (msg == "help") {
						cout << endl << "-------------------------------------------------------------------------------------" << endl;
						cout << "\t Now you are in DB. Aviable commands: " << endl << endl;
						cout << "\t To sort DB by name use 'sort by name'" << endl << endl;
						cout << "\t To sort DB by capacity use 'sort by capacity'" << endl << endl;
						cout << "\t To rename DB use 'rename <newName>'" << endl << endl;
						cout << "\t To delete DB use 'delete'" << endl << endl;
						cout << "\t To choose stocks with big sizes use 'choose big sizes'" << endl << endl;
						cout << "\t To choose stocks with small sizes use 'choose small sizes'" << endl << endl;
						cout << "\t To choose stocks in city use 'choose in <city>'" << endl << endl;
						cout << "\t To close DB use 'close'" << endl << endl;
						cout << "\t To save current DB selection use 'save' or 'save as <newName>'" << endl << endl;
						cout << "\t To undo DB selection use 'undo'" << endl << endl;
						cout << "\t To print DB use 'print'" << endl << endl;
						cout << "\t To count things in stocks use 'count <stockName>'" << endl << endl;
					}
					else if (msg.find("rename ") == 0) {
						cout << endl << "-------------------------------------------------------------------------------------" << endl;
						string name = msg.substr(7, msg.size());
						name += ".txt";
						fs::path p = fs::current_path() / "data";
						fs::path old = fs::current_path() / "data" / db.path;
						cout << "OLD: " << old << endl;
						fs::rename(db.path, p / name);
						db.path = "data/";
						db.path += name;
						db.path += ".txt";
						file.open(db.path, ios::out);
						db.write_to_file(file);
						file.close();
						cout << db.path << endl;
					}
					else if (msg == "delete") {
						cout << endl << "-------------------------------------------------------------------------------------" << endl;
						fs::remove(db.path);
						close = true;
						cout << endl << "\tDATABASE HAS BEEN DELETED" << endl << endl;
					}
					else if (msg == "undo") {
						file.open(db.path, ios::in | ios::app);
						db.init(file);
					}
					else if (msg == "sort by name") {
						cout << endl << "-------------------------------------------------------------------------------------" << endl;
						db.sort_by_name();
						db.print();
					}
					else if (msg == "sort by capacity") {
						cout << endl << "-------------------------------------------------------------------------------------" << endl;
						db.sort_by_capacity();
						db.print();
					}
					else if (msg.find("choose in ") == 0) {
						cout << endl << "-------------------------------------------------------------------------------------" << endl;
						string city = msg.substr(10, msg.size());
						for (size_t i = 0; i < db.stocks.size();) {
							if (db.stocks[i]->get_city() != city) {
								db.stocks.erase(db.stocks.begin() + i);
							}
							else {
								++i;
							}
						}
					}
					else if (msg == "choose big sizes") {
						cout << endl << "-------------------------------------------------------------------------------------" << endl;
						for (size_t i = 0; i != db.stocks.size();) {
							bool big = false;

							unordered_map<string,
								AMOUNT_SIZE_MAP> sizes = db.stocks[i]->get_sizes();
							stockType type = db.stocks[i]->get_type();
							for (auto it1 = sizes.begin(); it1 != sizes.end(); ++it1) {
								if (big) {
									break;
								}
								for (auto it2 = it1->second.begin(); it2 != it1->second.end();++it2) {
									if (it2->first > 0) {
										if (type == cloth) {
											if (it2->second.first > 50) {
												big = true;
												break;
											}
										}
										else {
											if (it2->second.first > 45) {
												big = true;
												break;
											}
										}
									}
								}
							}
							if (!big) {
								db.stocks.erase(db.stocks.begin() + i);
							}
							else {
								++i;
							}

						}
					}
					else if (msg == "choose small sizes") {
						cout << endl << "-------------------------------------------------------------------------------------" << endl;
						for (size_t i = 0; i < db.stocks.size();) {
							bool small = false;
							unordered_map<string,
								AMOUNT_SIZE_MAP> sizes = db.stocks[i]->get_sizes();
							stockType type = db.stocks[i]->get_type();
							for (auto it1 = sizes.begin(); it1 != sizes.end(); ++it1) {
								if (small) {
									break;
								}
								for (auto it2 = it1->second.begin(); it2 != it1->second.end();++it2) {
									if (it2->first > 0) {
										if (type == cloth) {
											if (it2->second.first < 40) {
												small = true;
												break;
											}
										}
										else {
											if (it2->second.first < 36) {
												small = true;
												break;
											}
										}
									}
								}
							}
							if (!small) {
								db.stocks.erase(db.stocks.begin() + i);
							}
							else {
								++i;
							}
						}
						db.print();
					}
					else if (msg == "save") {
						cout << endl << "-------------------------------------------------------------------------------------" << endl;
						file.close();
						file.open(db.path, ios::out);
						db.write_to_file(file);
						file.close();
						cout << endl << endl << "\tDATABASE SAVED SUCCESSFULLY" << endl << endl;
					}
					else if (msg.find("save as ") == 0) {
						name = msg.substr(8, msg.size());
						db.path = name_to_path(name);
						file.close();
						file.open(db.path, ios::out);
						db.write_to_file(file);
						file.close();
						dbList.push_back(name);
						cout << endl << endl << "\tDATABASE SAVED SUCCESSFULLY" << endl << endl;
					}
					else if (msg == "print") {
						cout << "=====================================================================================" << endl;
						cout << "\t\t\tDATABASE " << name << endl;
						cout << "=====================================================================================" << endl;
						cout << endl << "-------------------------------------------------------------------------------------" << endl;
						db.print();
					}
					else if (msg.find("count ") == 0) {
						name = msg.substr(6, msg.size());
						auto stock = db.find(name);
						if (stock != NULL) {
							cout << "Amount of things in " << name << ":\t" << stock->count_goods();
						}
						else {
							cout << "There is no any stock with such name" << endl;
						}
						cout << endl << "-------------------------------------------------------------------------------------" << endl;
					}
					else if (msg.find("find ") == 0) {
						string name = msg.substr(5, msg.size());
						auto stock = db.find(name);
						if (stock != NULL) {
							cout << "Stock " << stock->get_name() << " was opened" << endl << endl;
							cout << "You've opened " << stock->get_name() << " stock" << endl << endl;
							stock->edit_record();

						}
						else {
							cout << "There is no any stock with such name" << endl;
						}
					}
					else {
						cout << endl << "Unknown command" << endl;
					}
				}
				file.close();

			}
		}
		else if (msg.find("create ") == 0) {
			cout << endl << "-------------------------------------------------------------------------------------" << endl;
			string name = msg.substr(7, msg.size());
			if (!open_db(dbList, db, name, file)) {
				file.close();
				string name = msg.substr(7, msg.size());
				dbList.push_back(name);
				db.path = name_to_path(name);
				file.open(db.path, ios::out);
				db.create();
				db.write_to_file(file);
				file.close();
			}
		}
		else if (msg == "show databases") {
			cout << endl << "-------------------------------------------------------------------------------------" << endl;
			for (auto& it : fs::directory_iterator("data")) {
	
				string name = it.path().string();
				name = name.substr(name.find("\\") + 1);
				name = name.substr(0, name.size() - 4);
				cout << name << endl;
			}
		}
		else {
			cout << "unknown command" << endl;
		}
	}



		return 0;
}
