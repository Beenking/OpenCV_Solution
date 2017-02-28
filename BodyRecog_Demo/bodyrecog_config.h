#pragma once

#if (defined WIN32 || defined _WIN32 || defined WINCE) && defined KFUSION_API_EXPORTS
#define BM_EXPORTS __declspec(dllexport)
#else
#define BM_EXPORTS
#endif

#define  SAFE_DELETE_PTR(T)	{	\
    if (T)						\
              {					\
          delete T;				\
          T = NULL;				\
              } }	