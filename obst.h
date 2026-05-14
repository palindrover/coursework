#pragma once

#include <vector>
#include <string>
#include <cfloat>
#include <queue>
#include <iostream>
#include <fstream>
#include <sstream>

template <typename T>
class OBST
{
public:
	T root;
	OBST<T> *left = nullptr;
	OBST<T> *right = nullptr;

	OBST (std::vector<T> values, std::vector<double> p, std::vector<double> q);
	OBST (std::vector<std::vector<int>> r, int i, int j, std::vector<T> values);
	OBST (std::string file);

	int height();

	bool find(T value);

	void print();

private:
	std::vector<std::vector<int>> bst(std::vector<double> p, std::vector<double> q);
};

template<typename T>
OBST<T>::OBST(std::string file)
{
	std::ifstream read(file);
	std::string line;
	std::vector<double> p, q;
	std::vector<T> val;
	double a, b;
	T c;
	
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

	*this = OBST(val, p, q);
}

template <typename T>
OBST<T>::OBST(std::vector<T> values, std::vector<double> p, std::vector<double> q)
{
	int n = values.size();
	std::vector<std::vector<int>> r = bst(p, q);

	int root_index = r[0][n] - 1;
	root = values[root_index];

	if(root_index > 0) left = new OBST(r, 0, root_index, values);
	if(root_index + 1 < n) right = new OBST(r, root_index + 1, n, values);
}

template <typename T>
OBST<T>::OBST(std::vector<std::vector<int>> r, int i, int j, std::vector<T> values)
{
	if(i >= j || i < 0 || j > (int)values.size())
	{
		root = T{};
		return;
	}

	int root_index = r[i][j] - 1;
	root = values[root_index];

	if(root_index > i) left = new OBST(r, i, root_index, values);
	if(root_index + 1 < j) right = new OBST(r, root_index + 1, j, values);
}

template<typename T>
std::vector<std::vector<int>> OBST<T>::bst(std::vector<double> p, std::vector<double> q)
{
	int n = p.size();
	std::vector<std::vector<double>> c(n+1, std::vector<double>(n+1));
	std::vector<std::vector<int>> r(n+1, std::vector<int>(n+1));
	std::vector<std::vector<double>> w(n+1, std::vector<double>(n+1));

	for(int i = 0; i <= n; i++)
	{
		w[i][i] = q[i];
		for(int j = i+1; j <= n; j++) w[i][j] = w[i][j-1] + p[j-1] + q[j];
	}

	for(int j = 1; j <= n; j++)
	{
		int i = j-1;
		c[i][j] = w[i][j];
		r[i][j] = j;
	}

	double current_val, min_val;
	int min_k;

	for(int d = 2; d <= n; d++)
	{
		for(int j = d; j <= n; j++)
		{
			int i = j - d;

			min_val = DBL_MAX;
			min_k = -1;

			for(int k = r[i][j-1]; k <= r[i+1][j]; k++)
			{
				current_val =c[i][k-1] + c[k][j];
				if(current_val < min_val)
				{
					min_val = current_val;
					min_k = k;
				}
			}

			c[i][j] = w[i][j] + min_val;
			r[i][j] = min_k;
		}
	}

	return r;
}

template <typename T>
int OBST<T>::height()
{
	std::queue<OBST<T>*> q;
    q.push(this);
    
    int h = 0;

    while (!q.empty())
    {
        int levelSize = q.size();        
        for (int i = 0; i < levelSize; ++i)
        {
            OBST* node = q.front();
            q.pop();

            if (node->left != nullptr) q.push(node->left);
            if (node->right != nullptr) q.push(node->right);
        }
        h++; 
	}

    return h;
}

template<typename T>
bool OBST<T>::find(T key)
{
	OBST *i = this;

	while(i != nullptr)
	{
		if(i->root == key) return 1;
		i = key > i->root ? i->right : i->left;
	}

	return 0;
}

template<typename T>
void OBST<T>::print()
{
	std::queue<OBST<T>*> q;
	q.push(this);
	int h = height();

	for(int j = 0; j < h; j++)
	{
		for(int i = 0; i < 1 << j && !q.empty(); i++)
		{
			OBST *cur = q.front();
			if(cur == nullptr)
			{
				std::cout << "* ";
				q.pop();
				q.push(nullptr);
				q.push(nullptr);
				continue;
			}
			std::cout << cur->root << ' ';
			q.push(cur->left);
			q.push(cur->right);
			q.pop();
		}
		std::cout << '\n';
	}
}
