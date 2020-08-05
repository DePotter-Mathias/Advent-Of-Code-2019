#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>  

using namespace std;

auto check_valid_password1 = []( const string& input )->bool
{
	return
		input.length() == 6 &&
		is_sorted( input.cbegin(), input.cend() ) &&
		adjacent_find( input.cbegin(), input.cend() ) != input.cend();
};

auto check_valid_password2 = []( const string& input )->bool
{

	bool correct_double = false;
	const size_t length = input.length();
	for ( size_t i = 0; i < length - 1 && !correct_double; ++i )
	{
		//check if next one is the same
		bool next_same = input[i] == input[i + 1];
		//make sure next one after that one isn't the same; so the chain is only 2 long. if outside the array just return true
		bool next_but_one_same = (i + 2 < length) ? input[i] != input[i + 2] : true;
		//check previous one if not same; indicating i is the start of this chain. again, outside = ok
		bool previous_not_same = (i > 0) ? input[i] != input[i - 1] : true;

		correct_double = next_same && previous_not_same && next_but_one_same;
	}

	return
		input.length() == 6 &&
		is_sorted( input.cbegin(), input.cend() ) &&
		correct_double;
};


int main()
{
	constexpr unsigned int
		puzzle_input_min = 183564u,
		puzzle_input_max = 657474u;

	unsigned int count_part1 = 0, count_part2 = 0;
	for ( unsigned int possible_password = puzzle_input_min; possible_password < puzzle_input_max; ++possible_password )
	{
		//increment if true; branchless
		count_part1 += check_valid_password1( to_string( possible_password ) );
		count_part2 += check_valid_password2( to_string( possible_password ) );
	}

	cout << "part 1 result: " << count_part1 << " number of possible passwords." << endl;
	cout << "part 2 result: " << count_part2 << " number of possible passwords." << endl;
}