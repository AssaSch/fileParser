#include "Parser_t.h"
#include <string>
#include <iostream>

using namespace std;


int main(int argc, char* argv[])
{
	try
	{
		Parser_t parser;
	
		for (int i = 1; i < argc; ++i)
		{
			cout << endl << argv[i] << " - compilation" << endl << endl;
			if (!parser.Run(argv[i]))
			{
				cout << endl << argv[i] << " - not valid file name - compilation Failed!" << endl << endl;
			}
		}	
	}
	catch (bad_alloc& ba)
	{
		cout << endl << " memory allocation Failed!" << endl << endl;
	}
	
	return 0;
}

