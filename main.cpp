#include<iostream>
#include<filesystem>
#include"Filesystem.h"

#define LOG(x) std::cout << x << std::endl;

namespace fs = std::filesystem;

int main() {

	auto dir_path = fs::current_path();

	Os_Filesystem os_file_sys{(const char*)&dir_path};

	bool truthy = os_file_sys.exists((path_ref*)&dir_path);

	std::cout << truthy << std::endl;

	return 0;
}