#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

int main()
{
	srand(time(NULL));
	
	ofstream outfile("numbers.txt");
	for(int i = 0; i < 99; i++)
	{
		outfile << rand() % 1000 + 1 << " ";
	}
	outfile << rand() % 1000 + 1;
	
	outfile.close();
	return 0;
}