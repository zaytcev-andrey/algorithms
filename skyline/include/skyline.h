#ifndef skyline_h__
#define skyline_h__

#include <skyline/include/triple_building.h>

#include <vector>
#include <assert.h>
#include <utils/include/utils.h>

namespace skyline
{
     namespace detail
     {
     }
     
     void make_skyline( const std::vector< int >& buildings
          , std::vector< int >& skyline_points )
     {    
          assert( buildings.size() % 3 == 0 );

          const size_t buildings_count = buildings.size() / 3;
          const size_t left_buildings_count = buildings_count / 2;
          const size_t right_buildings_count = buildings_count - left_buildings_count;
 
          std::vector< int >::const_iterator left_begin = buildings.begin();
          std::vector< int >::const_iterator left_end = buildings.begin();
          //std::advance( left_end, left_buildings_count * 3 );
          const std::vector< int > left_buildings( left_begin, left_end );
     }
}

#endif // skyline_h__