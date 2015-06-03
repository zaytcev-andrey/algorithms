#ifndef skyline_h__
#define skyline_h__

#include <skyline/include/triple_building.h>

#include <vector>
#include <algorithm>
#include <assert.h>
#include <memory>
#include <utils/include/utils.h>

namespace skyline
{
     namespace detail
     {
          enum skyline_order { LEFT, RIGHT, BOTH };

          struct skyline_point
          {
               skyline_point( 
                    int coord
                    , int height
                    , skyline_order building )
                    : coord_( coord )
                    , height_( height )              
                    , building_( building )
                    , left_height_()
                    , right_height_()
               {
               }

               skyline_point( 
                    int coord
                    , int left_height
                    , int right_height )
                    : coord_( coord )
                    , height_( left_height >= right_height? left_height : right_height )              
                    , building_( BOTH )
                    , left_height_( left_height )
                    , right_height_( right_height )
               {
               }
               
               int coord_;
               int height_;              
               skyline_order building_;

               int left_height_;
               int right_height_;
          };

          class skyline_point_manager
          {
          public:

               skyline_point_manager( 
                    const std::vector< int >& left_skyline,
                    const std::vector< int >& right_skyline )
                    : left_skyline_( left_skyline )
                    , right_skyline_( right_skyline )
                    , left_len_( left_skyline.size() )
                    , right_len_( right_skyline.size() )
                    , left_idx_()
                    , right_idx_()
               {                    
               }

               skyline_point* get_next_point()
               {                    
                    if ( left_idx_ >= left_len_ && right_idx_ >= right_len_ )
                    {                             
                         return 0;
                    }
                    
                    if ( left_idx_ >= left_len_ && right_idx_ < right_len_ )
                    {                             
                         skyline_point* point = new skyline_point(
                              right_skyline_[ right_idx_ ]
                              , right_skyline_[ right_idx_ + 1 ] 
                              , RIGHT );


                         right_idx_ += 2;

                         return point;
                    }

                    if ( left_idx_ < left_len_ && right_idx_ >= right_len_ )
                    {
                         skyline_point* point = new skyline_point( 
                              left_skyline_[ left_idx_ ]
                              , left_skyline_[ left_idx_ + 1 ] 
                              , LEFT );

                         left_idx_ += 2;

                         return point;
                    }

                    if ( left_skyline_[ left_idx_ ] == right_skyline_[ right_idx_ ] )
                    {                                                 
                         int height_left = left_skyline_[ left_idx_ + 1 ];
                         int height_right = right_skyline_[ right_idx_ + 1 ];
                         
                         skyline_point* point = new skyline_point(
                              left_skyline_[ left_idx_ ]
                              , left_skyline_[ left_idx_ + 1 ] 
                              , right_skyline_[ right_idx_ + 1 ] );

                         left_idx_ += 2;
                         right_idx_ += 2;

                         return point;
                    }

                    if ( left_skyline_[ left_idx_ ] < right_skyline_[ right_idx_ ] )
                    {    
                         skyline_point* point = new skyline_point( 
                              left_skyline_[ left_idx_ ]
                              , left_skyline_[ left_idx_ + 1 ] 
                              , LEFT );

                         left_idx_ += 2;

                         return point;
                    }                    
                    else if ( left_skyline_[ left_idx_ ] > right_skyline_[ right_idx_ ] )
                    {
                         skyline_point* point = new skyline_point( 
                              right_skyline_[ right_idx_ ]
                              , right_skyline_[ right_idx_ + 1 ] 
                              , RIGHT );

                         right_idx_ += 2;

                         return point;
                    }                   

                    assert( false );
               }

          private:
               const std::vector< int >& left_skyline_;
               const std::vector< int >& right_skyline_;
               const size_t left_len_;
               const size_t right_len_;
               size_t left_idx_;
               size_t right_idx_;
          };
          
          void merge_skyline( const std::vector< int >& left_skyline
               , const std::vector< int >& right_skyline
               , std::vector< int >& res_skyline )
          {                              
               skyline_point_manager points_manager( left_skyline, right_skyline );

               int current_left_height = 0;
               int current_right_height = 0;
               
               std::auto_ptr< skyline_point > new_point;
               new_point.reset( points_manager.get_next_point() );
               while( new_point.get() )
               {                    
                    std::cout << "{ " << new_point->coord_ << ", " <<
                         new_point->height_ << ", " <<
                         (new_point->building_ == 0? "LEFT" : "RIGHT") << " }" << std::endl;
                    
                    if ( new_point->building_ == BOTH )
                    {
                         res_skyline.push_back( new_point->coord_ );
                         res_skyline.push_back( new_point->height_ );

                         current_left_height = new_point->left_height_;
                         current_right_height = new_point->right_height_;
                    }
                    else if ( new_point->building_ == LEFT )
                    {
                         if ( current_right_height == 0 )
                         {
                              res_skyline.push_back( new_point->coord_ );
                              res_skyline.push_back( new_point->height_ );                              
                         }
                         else
                         {
                              if ( current_right_height > current_left_height && 
                                   new_point->height_ > current_right_height ) // up
                              {
                                   res_skyline.push_back( new_point->coord_ );
                                   res_skyline.push_back( new_point->height_ );
                              }
                              else if ( current_right_height < current_left_height && 
                                   new_point->height_ < current_right_height ) // down
                              {
                                   res_skyline.push_back( new_point->coord_ );
                                   res_skyline.push_back( current_right_height );
                              }
                         }

                         current_left_height = new_point->height_;
                    }
                    else if ( new_point->building_ == RIGHT )
                    {
                         if ( current_left_height == 0 )
                         {
                              res_skyline.push_back( new_point->coord_ );
                              res_skyline.push_back( new_point->height_ );                              
                         }
                         else
                         {
                              if ( current_left_height > current_right_height && 
                                   new_point->height_ > current_left_height ) // up
                              {
                                   res_skyline.push_back( new_point->coord_ );
                                   res_skyline.push_back( new_point->height_ );
                              }
                              else if ( current_right_height > current_left_height && 
                                   new_point->height_ < current_left_height ) // down
                              {
                                   res_skyline.push_back( new_point->coord_ );
                                   res_skyline.push_back( current_left_height );
                              }
                         }

                         current_right_height = new_point->height_;
                    }

                    new_point.reset( points_manager.get_next_point() );
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

          std::vector< int > merged_points;
          detail::merge_skyline( left_skyline, right_skyline, merged_points );

          skyline_points.assign( merged_points.begin(), merged_points.end() );
     }
}

#endif // skyline_h__