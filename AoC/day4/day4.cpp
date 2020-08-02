#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include<string>  

using namespace std;

auto check_valid_password1 = []( const string& input )->bool
{
	return
		ceil( log10( stoi( input ) ) ) == 6 &&
		is_sorted( input.cbegin(), input.cend() ) &&
		adjacent_find( input.cbegin(), input.cend() ) != input.cend();
};

auto check_valid_password2 = []( const string& input )->bool
{

	bool correct_double = false;
	const auto length = input.length();
	for ( short i = 0; i < length; ++i )
	{
		short count = 0;
		for ( auto j = i + 1; j < length && input[i] == input[j++]; )
		{
			++count;
		}
		if ( count == 1 )
		{
			correct_double = true;
			break;
		}
		i += count;
	}

	return
		ceil( log10( stoi( input ) ) ) == 6 &&
		is_sorted( input.cbegin(), input.cend() ) &&
		correct_double;
};


int main()
{
	const int
		puzzle_input_min = 183564u,
		puzzle_input_max = 657474u;

	unsigned int count_part1 = 0, count_part2 = 0;
	for ( int possible_password = puzzle_input_min; possible_password < puzzle_input_max; ++possible_password )
	{
		if ( check_valid_password1( to_string( possible_password ) ) )
		{
			++count_part1;
		}
		if ( check_valid_password2( to_string( possible_password ) ) )
		{
			++count_part2;
		}
	}

	cout << "part 1 result: " << count_part1 << " number of possible passwords." << endl;
	cout << "part 2 result: " << count_part2 << " number of possible passwords." << endl;
}