// counting_sort.cpp : Defines the entry point for the console application.
//

#include <counting_sort/include/precompiled.h>

#include <counting_sort/include/counting_sort.h>
#include <utils/include/utils.h>

#include <assert.h>

int _tmain(int argc, _TCHAR* argv[])
{
     int unsorted_array[] = { 16, 14, 10, 8, 7, 9, 3, 2, 4, 1 };
     const size_t array_size = utils::count_of( unsorted_array );
     assert( array_size == 10 );

     int array_out[ sizeof( unsorted_array ) / sizeof( unsorted_array[ 0 ] ) ] = {};
     sort::counting_sort< 0, 255 >( unsorted_array, array_out );

     const int sorted_array[] = { 1, 2, 3, 4, 7, 8, 9, 10, 14, 16 };

     bool is_equal = std::equal( array_out
          , array_out + array_size, sorted_array );
     assert( is_equal );
     
     return 0;
}

