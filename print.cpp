#include <iostream>
#include <queue>
#include "tree.h"

void print(Tree *tree)
{
//	std::queue <Node*> q;
//	q.push(tree.root);
//	int h = tree.height();
//
//	for(int j = 0; j < h; j++)
//	{
//		for(int i = 0; i < 1 << j && !q.empty(); i++)
//		{
//			Node *cur = q.front();
//			if(cur == nullptr)
//			{
//				std::cout << "* ";
//				q.pop();
//				q.push(nullptr);
//				q.push(nullptr);
//				continue;
//			}
//			std::cout << cur->value << ' ';
//			q.push(cur->left);
//			q.push(cur->right);
//			q.pop();
//		}
//		std::cout << '\n';
//	}

	std::queue<Tree*> q;
	q.push(tree);
	int h = tree->height();

	for(int j = 0; j < h; j++)
	{
		for(int i = 0; i < 1 << j && !q.empty(); i++)
		{
			Tree *cur = q.front();
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
