#ifndef counting_sort_h__
#define counting_sort_h__

#include <limits>
#include <vector>
#include <assert.h>


namespace sort
{
     template< int MIN_VALUE, int MAX_VALUE, class T, int N >
     inline void counting_sort( const T ( & arr )[ N ], T ( & arr_out )[ N ] )
     {          
          assert( std::numeric_limits< T >::is_integer );          

          const size_t count_elem = MAX_VALUE - MIN_VALUE;

          T* items_counter = new T[ count_elem ];
          memset( items_counter, 0, sizeof( T ) * count_elem );

          for ( size_t idx = 0; idx < N; ++idx )
          {
               items_counter[ arr[ idx ] ]++;
          }

          for ( size_t idx = 1; idx < count_elem; ++idx )
          {
               items_counter[ idx ] += items_counter[ idx - 1 ];
          }

          for ( int idx = N - 1; idx >= 0; --idx )
          {
               const T& item = arr[ idx ];
               arr_out[ items_counter[ item ]-- - 1 ] = item;
          }
     }

     template< int OFFSET, int LENGTH, class T, int N >
     inline void counting_sort( const T ( & arr )[ N ], T ( & arr_out )[ N ] )
     {          
          assert( std::numeric_limits< T >::is_integer );

     }
}

#endif // counting_sort_h__
