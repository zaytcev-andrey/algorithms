// quick_sort.cpp : Defines the entry point for the console application.
//

#include <quick_sort/include/precompiled.h>

#include <quick_sort/include/quick_sort.h>
#include <utils/include/utils.h>

#include <assert.h>

int _tmain(int argc, _TCHAR* argv[])
{
     int unsorted_array[] = { 16, 14, 10, 8, 7, 9, 3, 2, 4, 1 };
     const size_t array_size = utils::count_of( unsorted_array );
     assert( array_size == 10 );

     sort::quick_sort( unsorted_array );
     
     return 0;
}