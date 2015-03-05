#include <heap/include/precompiled.h>

#include <heap/include/heapify.h>
#include <utils/include/utils.h>

#include <assert.h>
#include <algorithm>

using namespace heapify;
using namespace utils;

int _tmain(int argc, _TCHAR* argv[])
{
     int heap_array[] = { 16, 14, 10, 8, 7, 9, 3, 2, 4, 1 };
     const size_t array_size = sizeof( heap_array ) / sizeof( heap_array[ 0 ] );
     assert( array_size == 10 );

     int changed_array[] = { 16, 14, 10, 8, 17, 9, 3, 2, 4, 1 };
     int fixup_array[] = { 17, 16, 10, 8, 14, 9, 3, 2, 4, 1 };

     fix_up( changed_array, 4 );
     print( changed_array, array_size );

     bool is_equal = std::equal( changed_array, changed_array + array_size, fixup_array );
     assert( is_equal );

     int changed_array_reduction[] = { 16, 4, 10, 14, 7, 9, 3, 2, 8, 1 };
     int fixdown_array[] = { 16, 14, 10, 8, 7, 9, 3, 2, 4, 1 };

     fix_down( changed_array_reduction, 1, array_size );
     print( changed_array_reduction, array_size );

     is_equal = std::equal( changed_array_reduction
          , changed_array_reduction + array_size, fixdown_array );
     assert( is_equal );

     int non_heap_array[] = { 4, 1, 3, 2, 16, 9, 10, 14, 8, 7 };
     int non_heap_array_std[ array_size ] = {};
     std::copy( non_heap_array, non_heap_array + array_size
          , non_heap_array_std );

     std::make_heap( non_heap_array_std, non_heap_array_std + array_size );
     is_equal = std::equal( heap_array
          , heap_array + array_size, non_heap_array_std );
     assert( is_equal );

     make_heap( non_heap_array, array_size );
     is_equal = std::equal( heap_array
          , heap_array + array_size, non_heap_array );
     assert( is_equal );

     int unsorted_array[] = { 16, 14, 10, 8, 7, 9, 3, 2, 4, 1 };
     int sorted_array[] = { 1, 2, 3, 4, 7, 8, 9, 10, 14, 16 };

     heap_sort( unsorted_array, array_size );
     
     is_equal = std::equal( unsorted_array
          , unsorted_array + array_size, sorted_array );
     assert( is_equal );
     
     return 0;
}