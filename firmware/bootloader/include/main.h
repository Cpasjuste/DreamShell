#ifndef __MAIN_H
#define __MAIN_H

/* KOS */
#include <kos.h>
#include <math.h>
#include <assert.h>
#include <zlib/zlib.h>

void loading_core(int no_thd);
int show_message(const char *fmt, ...);

extern const char title[28];
extern int start_pressed;

#define RES_PATH "/brd"

#endif	/* __MAIN_H */
