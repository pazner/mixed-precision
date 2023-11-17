#undef FP_NAMESPACE
#undef FP_TYPE

#if defined(USE_FP64)
   #define FP_NAMESPACE fp64
   #define FP_TYPE double
#elif defined(USE_FP32)
   #define FP_NAMESPACE fp32
   #define FP_TYPE float
#else
   #error "Precision must be specified"
#endif

namespace mp { namespace FP_NAMESPACE { using fp = FP_TYPE; } }
