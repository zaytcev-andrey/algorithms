#ifndef quick_sort_h__
#define quick_sort_h__

#include <assert.h>
#include <algorithm>

namespace sort
{
     namespace detail
     {
          template< class T >
          inline int partition( T array[], int p, int r, int arr_size )
          {
               assert( p >= 0 && r < arr_size );

               int less_idx = p - 1; // ������, ������� �������� ������ <= pivot
               T pivot = array[ r ]; // ������� �������

               for ( int greater_idx = p; greater_idx < r - 1; ++greater_idx )
               {
                    if ( array[ greater_idx ] <= pivot )
                    {
                         // ������ ������� ������ ������ ��������, ��� ���� �����������
                         // � ����� ������� (������� �������� less_idx)
                         ++less_idx; // ��������� ����� ��� ������ ��������
                         std::swap( array[ less_idx ], array[ greater_idx ] );
                    }
               }

               // �������� ������� ������� � ������ ���������, ������� ������ ��������
               ++less_idx; // ������ ������� ��������, ������� ������ ��������
               assert( less_idx >= 0 && less_idx < arr_size ); //?
               
               std::swap( array[ less_idx ], pivot );

               return less_idx ? less_idx : r;
          }
          
          template< class T >
          inline void recursive_quick_sort( T array[], int p, int r, int arr_size )
          {
               if ( r <= 0 || p >= r )
               {
                    return;
               }

               int pivot_idx = partition( array, p, r, arr_size );

               recursive_quick_sort( array, p, pivot_idx - 1, arr_size );
               recursive_quick_sort( array, pivot_idx + 1, r, arr_size );
          }

     }
     
     template< class T, int N >
     inline void quick_sort( T ( & arr )[ N ] )
     {
          return detail::recursive_quick_sort( arr, 0, N - 1, N );
     }
}

#endif // quick_sort_h__