// GPL (General Purpose Library) export
//

#pragma once

#ifdef _WIN32

#ifdef TSG_EXPORT
#define TSG_API __declspec(dllexport)
#else
#define TSG_API  __declspec(dllimport)
#endif
#else	// case unix /* TODO: test */
#define TSG2_API __attribute__ ((visibility ("default")))
#endif