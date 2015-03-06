#ifndef quick_sort_h__
#define quick_sort_h__

#include <assert.h>
#include <algorithm>
#include <stdlib.h>
#include <time.h>

namespace sort
{
     namespace detail
     {                    
          template< class T >
          inline int partition( T array[], int p, int r, int arr_size )
          {
               assert( p >= 0 && r < arr_size );

               int less_idx = p - 1; // индекс, который заведует частью <= pivot
               T pivot = array[ r ]; // опорный элемент

               for ( int greater_idx = p; greater_idx < r; ++greater_idx )
               {
                    if ( array[ greater_idx ] <= pivot )
                    {
                         // найден элемент меньше равный опорному, его надо переместить
                         // в левую область (которой заведует less_idx)
                         ++less_idx; // выделение места для нового элемента
                         std::swap( array[ less_idx ], array[ greater_idx ] );
                    }
               }

               // обменять опорный элемент с первым элементом, который больше опорного
               ++less_idx; // индекс первого элемента, который больше опорного
               assert( less_idx >= p && less_idx < arr_size ); //?
               
               // note: если less_idx == p, значит pivot - наименьший в массиве,
               // последующий swap переместит его на место p и p вернется как индекс опорного элемента
               // если less_idx == r, значит pivot - наибольший в массиве
               // и r вернется как индекс опорного элемента

               std::swap( array[ less_idx ], array[ r ] );

               return less_idx;
          }

          inline int get_random_idx( int p, int r )
          {
               assert( p <= r );

               const int range = r - p;               
               const int rand_idx = int( static_cast< double >( rand() ) / ( RAND_MAX + 1 ) * range ) + p;

               assert( rand_idx >= p && rand_idx <= r );

               return rand_idx;
          }

          template< class T >
          inline int random_partition( T array[], int p, int r, int arr_size )
          {        
               const int rand_idx = get_random_idx( p, r );
               std::swap( array[ rand_idx ], array[ r ] );
               
               return partition( array, p, r, arr_size );
          }
          
          template< class T >
          inline void recursive_quick_sort( T array[], int p, int r, int arr_size )
          {
               if ( p >= r )
               {
                    return;
               }

               int pivot_idx = random_partition( array, p, r, arr_size );

               recursive_quick_sort( array, p, pivot_idx - 1, arr_size );
               recursive_quick_sort( array, pivot_idx + 1, r, arr_size );
          }

     }
     
     template< class T, int N >
     inline void quick_sort( T ( & arr )[ N ] )
     {          
          srand( static_cast< unsigned >( time( 0 ) ) );

          return detail::recursive_quick_sort( arr, 0, N - 1, N );
     }
}

#endif // quick_sort_h__