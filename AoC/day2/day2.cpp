#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;
using intcode_iter = vector<int>::iterator;

vector<int> get_input_data()
{
	std::ifstream infile( "day2input.txt" );
	int data;
	char separator_car;
	vector<int> intcode;
	while ( infile >> data >> separator_car )
	{
		intcode.push_back( data );
	}
	return intcode;
}

bool execute_operation( intcode_iter start, const intcode_iter op )
{
	const int operation = *(op + 0);
	const int left_value = *(op + 1);
	const int right_value = *(op + 2);
	const int store = *(op + 3);

	if ( operation == 1 )
	{
		start[store] = start[left_value] + start[right_value];
		return true;
	}
	else if ( operation == 2 )
	{
		start[store] = start[left_value] * start[right_value];
		return true;
	}

	return false;
};

int execute_operation_with_inital_values( const int a, const int b, vector<int> intcode )
{
	//"correct"
	intcode[1] = a;
	intcode[2] = b;

	intcode_iter p = intcode.begin();
	for/*ever*/ ( ;;)
	{
		if ( !execute_operation( intcode.begin(), p ) )
		{
			if ( *p == 99 )
			{
				//end reached
				break;
			}
			else
			{
				//invalid
				/*cout << "An error occurred at index: " << p - intcode.begin() << ", value: " << *p;
				return NULL;*/
				break;
			}
		}

		p += 4;
	}
	return intcode[0];
}

int main()
{
	vector<int> intcode( get_input_data() );

	//part 1
	{
		cout << "part 1 result: " << execute_operation_with_inital_values( 12, 2, intcode ) << endl;
	}

	//part2
	{
		constexpr int result_to_find = 19690720;

		for ( int i = 0; i < 100; ++i )
		{
			for ( int j = 0; j < 100; ++j )
			{
				if ( execute_operation_with_inital_values( i, j, intcode ) == result_to_find )
				{
					cout << "AAAND SUCCESS!!!! >> " << 100 * i + j;
					return NULL;
				}
			}
		}
	}
}