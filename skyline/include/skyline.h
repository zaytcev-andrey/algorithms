#ifndef skyline_h__
#define skyline_h__

#include <skyline/include/triple_building.h>

#include <vector>
#include <algorithm>
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
               const size_t left_len = left_skyline.size();
               const size_t right_len = right_skyline.size();
               
               size_t left_idx = 0;
               size_t right_idx = 0;

               int current_height_left = 0;
               int current_height_right = 0;

               int current_left = left_skyline[ left_idx ];
               int current_right = right_skyline[ right_idx ];

               while( left_idx < left_len || right_idx < right_len )
               {
                    if ( current_left < current_right && left_idx < left_len )
                    {    
                         const int prev_height_left = current_height_left;

                         current_height_left = left_skyline[ left_idx + 1 ];                         
                         
                         if ( current_height_left > current_height_right )
                         {
                              res_skyline.push_back( left_skyline[ left_idx ] );                                                  
                              res_skyline.push_back( current_height_left );

                         }

                         if ( prev_height_left > current_height_right &&
                              current_height_right != 0 && current_height_left == 0 )
                         {
                              res_skyline.push_back( left_skyline[ left_idx ] );                                                  
                              res_skyline.push_back( current_height_right );
                         }

                         if ( current_height_right == 0 && current_height_left == 0 )
                         {
                              res_skyline.push_back( left_skyline[ left_idx ] );                                                  
                              res_skyline.push_back( 0 );
                         }

                         left_idx += 2;
                         if ( left_idx < left_len )
                         {
                              current_left = left_skyline[ left_idx ];
                         }
                    }                    
                    else if ( right_idx < right_len )
                    {
                         const int prev_height_right = current_height_right;

                         current_height_right = right_skyline[ right_idx + 1 ];

                         if ( current_height_right > current_height_left )
                         {
                              res_skyline.push_back( right_skyline[ right_idx ] );                                                  
                              res_skyline.push_back( current_height_right );

                         }

                         if ( prev_height_right > current_height_left &&
                              current_height_left != 0 && current_height_right == 0 )
                         {
                              res_skyline.push_back( right_skyline[ right_idx ] );                                                  
                              res_skyline.push_back( current_height_left );
                         }

                         if ( current_height_right == 0 && current_height_left == 0 )
                         {
                              res_skyline.push_back( right_skyline[ right_idx ] );                                                  
                              res_skyline.push_back( 0 );
                         }

                         right_idx += 2;
                         if ( right_idx < right_len )
                         {
                              current_right = right_skyline[ right_idx ];
                         }
                    }

                    continue;
                    ////////
                    if ( left_skyline[ left_idx ] > right_skyline[ right_idx ] )
                    {    
                         const int prev_height_left = current_height_left;

                         current_height_left = left_skyline[ left_idx + 1 ];

                         if ( current_height_left > current_height_right )
                         {
                              res_skyline.push_back( left_skyline[ left_idx ] );                                                  
                              res_skyline.push_back( current_height_left );

                         }

                         if ( prev_height_left > current_height_right && current_height_left == 0 )
                         {
                              res_skyline.push_back( left_skyline[ left_idx ] );                                                  
                              res_skyline.push_back( current_height_right );
                         }

                         if ( current_height_right == current_height_left == 0 )
                         {
                              res_skyline.push_back( left_skyline[ left_idx ] );                                                  
                              res_skyline.push_back( 0 );
                         }

                         left_idx += 2;
                    }
                    else
                    {
                         const int prev_height_right = current_height_right;
                         
                         current_height_right = right_skyline[ right_idx + 1 ];

                         if ( current_height_right > current_height_left )
                         {
                              res_skyline.push_back( right_skyline[ right_idx ] );                                                  
                              res_skyline.push_back( current_height_right );

                         }

                         if ( prev_height_right > current_height_left && current_height_right == 0 )
                         {
                              res_skyline.push_back( right_skyline[ right_idx ] );                                                  
                              res_skyline.push_back( current_height_left );
                         }

                         if ( current_height_right == current_height_left == 0 )
                         {
                              res_skyline.push_back( right_skyline[ right_idx ] );                                                  
                              res_skyline.push_back( 0 );
                         }

                         right_idx += 2;
                    }
               }
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