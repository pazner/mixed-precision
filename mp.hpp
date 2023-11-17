#if defined(ENABLE_FP64)
#define USE_FP64
#include "vector.hpp"
#undef USE_FP64
#endif

#if defined(ENABLE_FP32)
#define USE_FP32
#include "vector.hpp"
#undef USE_FP32
#endif

namespace mp
{

#if DEFAULT_PRECISION == FP64
using namespace fp64;
#elif DEFAULT_PRECISION == FP32
using namespace fp32;
#endif

}
