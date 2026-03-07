#include "tree.h"
#include <cstdio>
#include <fstream>
#include <sstream>
#include <string>

int main(int argc, char **argv)
{
	std::string file = argc > 1 ? argv[1] : "data.csv";

	std::ifstream read(file);
	std::string line;
	std::vector<double> p, q, val;
	double a, b;
	int c;
	
	getline(read, line);
	read >> a; q.push_back(a);

	while(getline(read, line))
	{
		for(int i = 0; i < line.size(); i++) if(line[i] == ';') line[i] = ' ';
		std::stringstream ss(line);
		ss >> a >> b >> c;
		q.push_back(a);
		p.push_back(b);
		val.push_back(c);
	}

	Tree *tree = new Tree(val, p, q);

	tree->print();

	return 0;
}
