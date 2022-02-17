#ifndef SHAPE_WRAPPER_H
#define SHAPE_WRAPPER_H
template<typename ShapeStruct>
class ShapeWrap
{
   ShapeStruct shape;
   public:
      ShapeWrap()                    = delete;
      ShapeWrap( const ShapeWrap & ) = default;
      constexpr ShapeWrap( const float x, const float y, const float width, const float height ) : shape()
      {
         shape.x      = x;
         shape.y      = y;
         shape.width  = width;
         shape.height = height;
      }

      ShapeStruct getShape() const { return shape; }

};

#endif // SHAPE_WRAPPER_H
