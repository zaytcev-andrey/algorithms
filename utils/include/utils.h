#ifndef utils_h__
#define utils_h__

#include <iostream>
#include <algorithm>
#include <vector>

namespace utils
{
     template< class T > 
     inline void print( const T array[], size_t len )
     {
          struct show_item
          {
               void operator() ( const T& item )
               {
                    std::cout << item << ' ';
               }
          };

          std::for_each( array, array + len, show_item() );
          std::cout << std::endl;
     }

     template< class T, size_t len > 
     inline void print( const T ( & array )[ len ] )
     {
          struct show_item
          {
               void operator() ( const T& item )
               {
                    std::cout << item << ' ';
               }
          };

          std::for_each( array, array + len, show_item() );
          std::cout << std::endl;
     }

     template< class T > 
     inline void print( const T& container )
     {          
          struct show_item
          {
               void operator() ( const typename T::value_type& item )
               {
                    std::cout << item << ' ';
               }
          };

          std::for_each( container.begin(), container.end(), show_item() );
          std::cout << std::endl;
     }

     template< class T, size_t N >
     inline size_t count_of( const T ( & array )[ N ] )
     {
          return N;
     }

     namespace insertion
     {
          template< class T >
          inline std::vector< T >& operator<< ( std::vector< T >& vec, const T& value )
          {
               vec.push_back( value );
               return vec;
          }
     }
}

#endif // utils_h__