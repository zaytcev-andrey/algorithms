#ifndef triple_building_h__
#define triple_building_h__

namespace skyline
{
     namespace detail
     {
          struct skyline_point
          {
               int left_;
               int height_;
          };
     }
     
     struct triple_building
     {
          triple_building( int left, int right, int height )
               : left_( left )
               , right_( right )
               , height_( height )
          {
          }
 
          int left_;
          int right_;
          int height_;
     };
}

#endif // triple_building_h__