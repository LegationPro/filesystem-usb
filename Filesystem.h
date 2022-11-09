#pragma once
#include<vector>

class path_ref;
class vector_ref;

class Os_Filesystem
{
public:
	explicit Os_Filesystem(const char* path);
	bool exists(path_ref* dir) const;
	bool isDir(path_ref* dir) const;
	bool isFile(path_ref* dir) const;
	auto getCurrentPath() const;
	std::vector<const char*> getDirectory(path_ref* dir) const;
	std::vector<const char*> findAllFilesInDirectory(path_ref* dir) const;
private:
	path_ref* _path;
};

