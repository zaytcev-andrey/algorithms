#ifndef utils_h__
#define utils_h__

#include <iostream>
#include <algorithm>
#include <vector>

namespace utils
{
     template< class T > 
     inline void print( T array[], size_t len )
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
}

#endif // utils_h__