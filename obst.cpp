#include "obst.h"
#include <cfloat>
#include <queue>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

OBST::OBST(string file)
{
	ifstream read(file);
	string line;
	vector<double> p, q, val;
	double a, b, c;
	
	getline(read, line);
	
	getline(read, line);
	if(line.back() == ';') line.pop_back(), line.pop_back();
	q.push_back(stod(line));

	while(getline(read, line))
	{
		for(long unsigned int i = 0; i < line.size(); i++) if(line[i] == ';') line[i] = ' ';
		stringstream ss(line);
		ss >> a >> b >> c;
		q.push_back(a);
		p.push_back(b);
		val.push_back(c);
	}

	read.close();

	*this = OBST(val, p, q);
}

OBST::OBST(vector<double> values, vector<double> p, vector<double> q)
{
	int n = values.size() + 1;
	vector<vector<int>> r = bst(p, q, n);
	root = values[r[0][n] - 2];
	left = 0 == r[0][n] - 1 || r[0][r[0][n]-1] == 1 ? nullptr : new OBST(r, 0, r[0][n]-1, values);
	right = r[0][n] == n || r[r[0][n]][n] == 1 ? nullptr : new OBST(r, r[0][n], n, values);
}

OBST::OBST(vector<vector<int>> r, int i, int j, vector<double> values)
{
	root = values[r[i][j]-2];
	left = i == r[i][j] - 1 || r[i][r[i][j]-1] == 1 ? nullptr : new OBST(r, i, r[i][j] - 1, values);
	right = r[i][j] == j || r[r[i][j]][j] == 1 ? nullptr : new OBST(r, r[i][j], j, values);
}

vector<vector<int>> OBST::bst(vector<double> p, vector<double> q, int n)
{
	vector<vector<double>> c(n+1, vector<double>(n+1));
	vector<vector<int>> r(n+1, vector<int>(n+1));
	vector<vector<double>> w(n+1, vector<double>(n+1));

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

int OBST::height()
{
    queue<OBST*> q;
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

bool OBST::find(double key)
{
	OBST *i = this;

	while(i != nullptr)
	{
		if(i->root == key) return 1;
		i = key > i->root ? i->right : i->left;
	}

	return 0;
}

void OBST::print()
{
	queue<OBST*> q;
	q.push(this);
	int h = height();

	for(int j = 0; j < h; j++)
	{
		for(int i = 0; i < 1 << j && !q.empty(); i++)
		{
			OBST *cur = q.front();
			if(cur == nullptr)
			{
				cout << "* ";
				q.pop();
				q.push(nullptr);
				q.push(nullptr);
				continue;
			}
			cout << cur->root << ' ';
			q.push(cur->left);
			q.push(cur->right);
			q.pop();
		}
		cout << '\n';
	}
}
