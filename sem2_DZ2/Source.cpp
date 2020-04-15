#include <iostream>
#include <filesystem>

#include

namespace fs = std::filesystem;

using std::endl;
using std::cin;
using std::cout;




int main() {
	auto p = fs::current_path();
	cout << p;
	return 0;
}