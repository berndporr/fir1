#ifndef __ASSERT_PRINT_H
#define __ASSERT_PRINT_H

#include <stdlib.h>

inline void assert_print(int b, const char* t) {
	if (b) return;
	fprintf(stderr,"%s\n",t);
	throw t;
}

// placed there so that it only affects the cpp files
using namespace std;

#endif
