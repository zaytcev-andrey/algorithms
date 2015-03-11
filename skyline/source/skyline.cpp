// skyline.cpp : Defines the entry point for the console application.
//

#include <skyline/include/precompiled.h>

#include <skyline/include/skyline.h>
#include <utils/include/utils.h>

#include <algorithm>
#include <assert.h>

int _tmain(int argc, _TCHAR* argv[])
{
     using namespace utils::insertion;

     std::vector< int > buildings_data;

     buildings_data << 1 << 11 << 5 << 2 << 6 << 7 << 3 << 13 << 9 << 12 << 7 << 16 <<
          14 << 3 << 25 << 19 << 18 << 22 << 23 << 13 << 29 << 24 << 4 << 28;

     std::vector< int > skyline_data_ref;
     skyline_data_ref << 1 << 11 << 3 << 13 << 9 << 0 <<
          12 << 7 << 16 << 3 << 19 << 18 << 22 << 3 << 23 << 13 << 29 << 0;

     std::vector< int > skyline_data;

     skyline::make_skyline( buildings_data, skyline_data );

     bool is_equal = std::equal( 
          skyline_data_ref.begin(), skyline_data_ref.end(), skyline_data.begin() );
     assert( is_equal );
    
     return 0;
}