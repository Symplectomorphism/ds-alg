#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <climits>

#define TOTAL_SIZE 70000000
#define NEEDED_FREE_SIZE 30000000


struct file
{
	file(unsigned long long size, std::string name) : m_size(size), m_name(name){}
	unsigned long long m_size;
	std::string m_name;
};

struct directory
{
	directory(std::string name) : m_name(name), m_parent(NULL){}
	directory(std::string name, directory* parent) : m_name(name), m_parent(parent) {}

	unsigned long long GetDirSize();
	unsigned long long GetFileSize();
	std::string m_name;
    directory* m_parent;
	std::vector<directory*> dirs;
	std::vector<file*>files;
};

unsigned long long directory::GetDirSize()
{
	unsigned long long dirSize = 0;
	dirSize = GetFileSize();
	for (directory* dir : dirs)
	{
		dirSize += dir->GetDirSize();
	}
	return dirSize;
}

unsigned long long directory::GetFileSize()
{
	unsigned long long fileSize = 0;
	for (file* f : files)
	{
		fileSize += f->m_size;
	}

	return fileSize;
}

// might change the current directory so we return a pointer to it
directory* ProcessCommand(std::stringstream& stream, directory* dir)
{
	std::string word;

	// get the command			can either be cd or ls
	stream >> word;

	if (word == "cd")
	{
		// move into
		stream >> word;

		if (word == "/")
		{
			while (dir->m_parent)
			{
				dir = dir->m_parent;
			}
		}
		else if (word == "..")
		{
			if (dir->m_parent)
			{
				dir = dir->m_parent;
			}
		}
		else
		{
			directory* moveInto = new directory(word, dir);
			dir->dirs.push_back(moveInto);
			dir = moveInto;
		}
	}

	// we don't care about list operations
	// all the data that we read will be handled by ProcessData function
	return dir;
}


void ProcessData(const std::string& dataIdentifier, std::stringstream& stream, directory* dir)
{
	if (dataIdentifier == "dir")
	{
		return;
	}

	// calculate size of file
	unsigned long long size = 0;
	int i = 0;
	int dataLength = dataIdentifier.size();
	short digit = 0;
	while (i < dataLength)
	{
		size *= 10;
		digit = dataIdentifier[i] & 0x0F;
		size += digit;
		i++;
	}

	std::string name;
	stream >> name;

	dir->files.push_back(new file(size, name));
}

unsigned long long part1(directory* dir)
{
	std::queue<directory*> q;
	q.push(dir);

	unsigned long long val = 0;
	while (!q.empty())
	{
		directory* current = q.front();
		q.pop();
		unsigned long long  cVal = current->GetDirSize();
		std::cout << current->m_name << ": " << cVal << '\n';
		
		if (cVal <= 100000)
		{
			std::cout << current->m_name << " added to value" << '\n';
			val += cVal;
		}
		for (int i = 0; i != current->dirs.size(); i++)
		{
			q.push(current->dirs[i]);
		}
	}

	return val;
}

unsigned long long part2(directory* dir)
{
	unsigned long long currentlyUsedData = dir->GetDirSize();
	unsigned long long neededSpace = NEEDED_FREE_SIZE - (TOTAL_SIZE - currentlyUsedData);
	std::queue<directory*> q;
	q.push(dir);

	unsigned long long result = ULLONG_MAX;
	while (!q.empty())
	{
		directory* current = q.front();
		q.pop();
		unsigned long long dirSize = current->GetDirSize();
		if (dirSize < neededSpace)
		{
			continue;
		}

		result = std::min(result, dirSize);
		for (int i = 0; i != current->dirs.size(); i++)
		{
			q.push(current->dirs[i]);
		}
	}

	return result;
}

int main()
{
	directory* base = new directory("/");
	directory* current = base;
	std::ifstream input("input");

	std::string line;
	std::stringstream stream;
	std::string word;
	while (std::getline(input, line))
	{
		stream.str(line);
		stream >> word;
		if (word == "$")
		{
			current = ProcessCommand(stream, current);
		}
		else
		{
			ProcessData(word, stream, current);
		}
		stream.clear();
	}
	
	unsigned long long val = part1(base);
	unsigned long long val2 = part2(base);
	std::cout << val << std::endl;
	std::cout << val2 << std::endl;
	return 0;
}
