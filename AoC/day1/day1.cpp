#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

int main()
{
	int total_fuel = 0;
	int module_mass;
	auto mass_to_fuel = []( const int& input )->int { return input / 3 - 2; };

	//part 1
	{
		std::ifstream infile( "day1input.txt" );
		while ( infile >> module_mass )
		{
			//go over each, convert mass to fuel, accumulate
			total_fuel += mass_to_fuel( module_mass );
		}
		cout << "Part 1 total: " << total_fuel << endl;
	}

	//part 2
	{
		std::ifstream infile( "day1input.txt" );
		total_fuel = 0;

		auto extra_cost = [mass_to_fuel]( const int& input )
		{
			int remainder = input;
			int result = 0;

			do
			{
				remainder = mass_to_fuel( remainder );
				result += remainder;
			}
			while ( remainder > 6 );

			return result;
		};

		while ( infile >> module_mass )
		{
			total_fuel += extra_cost( module_mass );
		}

		cout << "Part 2 total: " << total_fuel << endl;
	}
}

