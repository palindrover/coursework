#include "obst.h"
#include "avl.h"
#include <chrono>
#include <cstddef>
#include <fstream>
#include <string>
#include <sstream>

int main(int argc, char **argv)
{
	std::string file = argc > 1 ? argv[1] : "data.csv";

	std::ifstream read(file);
	std::string line;
	std::vector<double> p, q, val;
	double a, b, c;
	
	getline(read, line);
	
	getline(read, line);
	if(line.back() == ';') line.pop_back(), line.pop_back();
	q.push_back(stod(line));

	while(getline(read, line))
	{
		for(long unsigned int i = 0; i < line.size(); i++) if(line[i] == ';') line[i] = ' ';
		std::stringstream ss(line);
		ss >> a >> b >> c;
		q.push_back(a);
		p.push_back(b);
		val.push_back(c);
	}

	read.close();

	OBST obst(val, p, q);
	AVL<double> avl;

	for(auto i : val) avl.insert(i);

	std::vector<double> keys;

	for(size_t i = 0; i < p.size(); i++)
	{
		for(int j = 0; j < p[i] * 200000; j++) keys.push_back(val[j]);
	}

	int cnt = keys.size(), iter = 0;

	double obstTime = 0, avlTime = 0;

	for(; iter < 100; iter++)
	{

		auto start = std::chrono::high_resolution_clock::now();
	
		for(double x : keys) obst.find(x);
	
		auto end = std::chrono::high_resolution_clock::now();
	
		obstTime += std::chrono::duration_cast<std::chrono::microseconds>(end-start).count() * 1.0 / cnt;
	
		start = std::chrono::high_resolution_clock::now();
	
		for(double x : keys) avl.find(x);
	
		end = std::chrono::high_resolution_clock::now();
	
		avlTime += std::chrono::duration_cast<std::chrono::microseconds>(end-start).count() * 1.0 / cnt;
	}

	//std::cout << "OBST time " << obstTime / iter << "\nAVL time " << avlTime / iter << '\n';
	
	std::cout << "OBST быстрее на " << (avlTime / obstTime - 1) * 100 << "%\n";

	std::cout << "Кол-во итераций: " << cnt * iter;

	return 0;
}
