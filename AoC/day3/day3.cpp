#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

#define small_long 0.0000000001l

struct wire_point
{
	/*signed*/ long x = 0, y = 0;

	inline long Length( const wire_point& w )const
	{
		return abs( x - w.x ) + abs( y - w.y );
	}

	inline bool operator <( const wire_point& w )const
	{
		return this->Manhattan_distance() < w.Manhattan_distance();
	}

	inline long Manhattan_distance() const
	{
		return abs( x ) + abs( y );
	}

	inline bool Is_empty() const
	{
		return x == 0 && y == 0;
		//return abs( x ) < small_long && abs( y ) < small_long;
	}
};

struct wire_segment
{
	wire_point begin, end;
	long length = 0;
};

using wire = vector<wire_segment>;

vector<wire> Get_input_data()
{
	enum class direction
	{
		up = 'U',
		down = 'D',
		left = 'L',
		right = 'R'
	};

	std::ifstream infile( "day3input.txt" );
	unsigned int len;
	char separator_char, dir;

	vector<wire> wires;
	wire wire;
	wire_segment segment;

	auto displace = []( wire_segment& seg, const direction& dir, const unsigned int len )
	{
		seg.length = len;

		switch ( dir )
		{
		case direction::up:
			seg.end.y += len;
			break;
		case direction::down:
			seg.end.y -= len;
			break;
		case direction::left:
			seg.end.x -= len;
			break;
		case direction::right:
			seg.end.x += len;
			break;
		}
	};

	while ( infile >> dir >> len )
	{
		segment.begin = segment.end;

		displace( segment, direction( toupper( dir ) ), len );

		wire.push_back( segment );

		if ( infile >> separator_char, separator_char != ',' )
		{
			wires.push_back( wire );
			wire.clear();
			segment = {};
			//one step back as we just ate the next line's info
			infile.unget();
		}
	}
	wires.push_back( wire );

	return wires;
}

static bool Intersect( const wire_segment& p, const wire_segment& q, wire_point& i )
{
	//is p horizontal?
	const bool hor = p.begin.y == p.end.y;

	//then put horizontal in h and vertical in v
	const wire_segment&
		h = hor ? p : q,
		v = hor ? q : p;

	//intersection is crossing of lines the segments lie on, (might be outside of segments)
	i.x = v.begin.x;
	i.y = h.begin.y;

	//check if on both line segments
	return
		//intersection bigger than left most of horizontal segment
		i.x > min( h.begin.x, h.end.x ) &&
		//intersection smaller than right most of horizontal segment
		i.x < max( h.begin.x, h.end.x ) &&
		//intersection higher than bottom most of vertical segment
		i.y > min( v.begin.y, v.end.y ) &&
		//intersection lower than top most of vertical segment
		i.y < max( v.begin.y, v.end.y );
}

int main()
{
	const vector<wire> wires( Get_input_data() );

	//could be generalized for more
	if ( wires.size() < 2 )
	{
		return NULL;
	}

	//pair, but could be (anonymous) struct
	vector<pair<wire_point, long>> intersection_points;

	long distance_traveled1 = 0;
	long distance_traveled2 = 0;
	wire_point result;

	//every segment of first wire
	for ( auto wire1 : wires.front() )
	{
		//every segment of second wire
		for ( auto wire2 : wires.back() )
		{
			if ( Intersect( wire1, wire2, result ) )
			{
				if ( !result.Is_empty() )
				{
					long wire_distances =
						//wire sums so far 
						distance_traveled1 + distance_traveled2
						//plus part of the wires
						+ result.Length( wire1.begin ) + result.Length( wire2.begin );

					intersection_points.push_back( { result, wire_distances } );
				}
			}
			distance_traveled2 += wire2.length;
		}
		distance_traveled1 += wire1.length;
		distance_traveled2 = 0;
	}

	if ( !intersection_points.empty() )
	{
		auto smallest_intersection = min_element( intersection_points.cbegin(), intersection_points.cend() );
		//not needed? implicitly takes first from pair?
		//, []( auto a, auto b ) { return a.first < b.first; });

		cout << "part 1 result: " << smallest_intersection->first.Manhattan_distance() << endl;

		auto shortest_intersection = min_element( intersection_points.cbegin(), intersection_points.cend(),
												  []( auto a, auto b ) { return a.second < b.second; } );

		cout << "part 2 result: " << shortest_intersection->second << endl;

	}
}