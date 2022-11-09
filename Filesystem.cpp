#include "Filesystem.h"
#include<iostream>
#include<thread>
#include<filesystem>
#include<winusb.h>
namespace fs = std::filesystem;

static auto convert_to_fs(path_ref* dir) {
	return std::_Bit_cast<fs::path const*>(dir);
}

Os_Filesystem::Os_Filesystem(const char* path)
{
	fs::path filePath{ path };
	this->_path = (path_ref*)&filePath;
}

bool Os_Filesystem::exists(path_ref* dir) const
{
	fs::file_status status{};
	auto path_to_file = convert_to_fs(dir);

	if (fs::status_known(status) ? fs::exists(status) : fs::exists(*path_to_file)) {
		return true;
	}
}

bool Os_Filesystem::isDir(path_ref* dir) const
{
	return fs::is_directory(*convert_to_fs(dir));
}

bool Os_Filesystem::isFile(path_ref* dir) const
{
	return fs::is_regular_file(*convert_to_fs(dir));
}

auto Os_Filesystem::getCurrentPath() const
{
	return fs::current_path();
}

std::vector<const char*> Os_Filesystem::getDirectory(path_ref* dir) const
{
	std::vector<const char*> pathsInDirectory {};

	for (auto path = convert_to_fs(dir); auto& entry : fs::directory_iterator(*path)) {
		fs::path dir_path = entry.path();
		pathsInDirectory.push_back((char const*)dir_path.c_str());
	}

	return pathsInDirectory;
}

std::vector<const char*> Os_Filesystem::findAllFilesInDirectory(path_ref* dir) const
{
	std::vector<const char*> pathsInDirectory{};

	for (auto path = convert_to_fs(dir); auto& entry : fs::directory_iterator(*path)) {
		fs::path dir_path = entry.path();

		if (fs::is_regular_file(dir_path)) {
			pathsInDirectory.push_back((const char*)dir_path.c_str());
		}
		else if (fs::is_directory(dir_path)) {
			auto* const new_dir = (path_ref* const*)&dir_path;

			std::jthread th{ [this, new_dir]() {
				this->findAllFilesInDirectory(*new_dir);
			}};

			th.join();
		}
	}

	return std::vector<const char*>();
}

