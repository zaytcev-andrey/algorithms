#ifndef heapify_h__
#define heapify_h__

#include <algorithm>
#include <assert.h>

namespace heapify
{
     template< class T > 
     inline void fix_up( T array[], size_t idx )
     {
          while ( idx > 0 && array[ idx ] > array[ ( idx - 1 ) / 2 ] )
          {
               std::swap( array[ idx ], array[ ( idx - 1 ) / 2 ] );
               idx = ( idx - 1 ) / 2;
          }
     }

     template< class T > 
     inline void fix_down( T array[], size_t idx, size_t len )
     {
          while ( 2 * ( idx + 1 ) <= len )
          {
               const size_t left = 2 * ( idx + 1 ) - 1;
               const size_t right = left + 1;
               size_t child_elem = left;
               if ( right < len && array[ left ] < array[ right ] )
               {
                    child_elem = right;
               }

               assert( child_elem < len );

               if ( array[ idx ] < array[ child_elem ] )
               {
                    std::swap( array[ idx ], array[ child_elem ] );
                    idx = child_elem;
               }
               else
               {
                    break;
               }
               
          }
     }

     template< class T > 
     inline void make_heap( T array[], size_t len )
     {
          if ( len == 0 )
          {
               return;
          }
          
          const size_t length = len / 2;
          for ( int it = length - 1; it >= 0; it-- )
          {
               fix_down< T >( array, static_cast< size_t >( it ), len );
          }
     }

     template< class T > 
     inline void heap_sort( T array[], size_t len )
     {
          make_heap< T >( array, len );

          while( len > 1 )
          {
               const size_t large_idx = len - 1;
               std::swap( array[ 0 ], array[ large_idx ] );
               fix_down< T >( array, 0, --len );
          }
     }
}

#endif // heapify_h__