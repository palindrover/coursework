#ifndef TREE_H	
#define TREE_H

#include <vector>
#include <string>

class OBST
{
public:
	double root;
	OBST *left = nullptr;
	OBST *right = nullptr;

	OBST (std::vector<double> values, std::vector<double> p, std::vector<double> q);
	OBST (std::vector<std::vector<int>> r, int i, int j, std::vector<double> values);
	OBST (std::string file);

	int height();

	bool find(double value);

	void print();

private:
	std::vector<std::vector<int>> bst(std::vector<double> p, std::vector<double> q, int n);
};

#endif
