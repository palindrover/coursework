#ifndef TREE_H	
#define TREE_H

#include <vector>

class Tree
{
public:
	double root;
	Tree *left;
	Tree *right;

	Tree (std::vector<double> values, std::vector<double> p, std::vector<double> q);
	Tree (std::vector<std::vector<int>> r, int i, int j, std::vector<double> values);

	int height(Tree *tree = nullptr, int h = -1);

	bool find(double value);

	void print();

private:
	std::vector<std::vector<int>> bst(std::vector<double> p, std::vector<double> q, int n);
};

#endif
