#include "config.hpp"
#include <vector>

namespace mp
{

namespace FP_NAMESPACE
{

struct Vector
{
   std::vector<fp> data;
public:
   using ElemType = fp;
   Vector(std::size_t size);
};

}

}
