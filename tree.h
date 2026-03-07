#ifndef TREE_H	
#define TREE_H

#include <vector>

class Tree
{
public:
	int root;
	Tree *left;
	Tree *right;

	Tree (std::vector<int> values, std::vector<double> p, std::vector<double> q, int n);
	Tree (std::vector<std::vector<int>> r, int i, int j, std::vector<int> values);

	int height(Tree *tree = nullptr, int h = -1);

	bool find(int value);

private:
	std::vector<std::vector<int>> bst(std::vector<double> p, std::vector<double> q, int n);
};

#endif
