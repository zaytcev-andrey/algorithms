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
          void merge_skyline( const std::vector< int >& left_skyline
               , const std::vector< int >& right_skyline
               , std::vector< int >& res_skyline )
          {

          }
     }
     
     void make_skyline( const std::vector< int >& buildings
          , std::vector< int >& skyline_points )
     {    
          assert( buildings.size() % 3 == 0 );

          const size_t buildings_count = buildings.size() / 3;

          if ( buildings_count == 0 )
          {
               return;
          }

          if ( buildings_count == 1 )
          {
               skyline_points.push_back( buildings[ 0 ] );
               skyline_points.push_back( buildings[ 1 ] );
               skyline_points.push_back( buildings[ 2 ] );
               skyline_points.push_back( 0 );

               utils::print( skyline_points );

               return;
          }

          const size_t left_buildings_count = buildings_count / 2;
          const size_t right_buildings_count = buildings_count - left_buildings_count;
 
          std::vector< int >::const_iterator left_begin = buildings.begin();
          std::vector< int >::const_iterator left_end = buildings.begin();
          std::advance( left_end, left_buildings_count * 3 );
          const std::vector< int > left_buildings( left_begin, left_end );

          std::vector< int >::const_iterator right_begin = buildings.begin();
          std::vector< int >::const_iterator right_end = buildings.end();
          std::advance( right_begin, left_buildings_count * 3 );
          const std::vector< int > right_buildings( right_begin, right_end );

          std::vector< int > left_skyline;
          make_skyline( left_buildings, left_skyline );

          std::vector< int > right_skyline;
          make_skyline( right_buildings, right_skyline );

          detail::merge_skyline( left_skyline, right_skyline, skyline_points );
     }
}

#endif // skyline_h__