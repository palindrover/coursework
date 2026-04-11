#include "obst.h"

int main()
{
	OBST<char> tree("data.csv");

	tree.print();

	return 0;
}
