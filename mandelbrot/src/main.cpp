#include <iostream>
#include <unistd.h>

#define NO_THREADS 16       // max 16 for Orangecart!
#define STACK_SIZE 1024
#define PIXELW 2 // 2
#define MAX_ITER 24
#define IMG_W 320 // 320
#define IMG_H 200 // 200
#define MTYPE float

#define CSIZE (IMG_W * IMG_H) / 8
#define PAL_SIZE (2 * PIXELW)
#include "mandelbrot.h"

//#define C64
#ifdef C64
static char *cv = (char *)0x4000;      // VIC Memory
#else
static char cv[CSIZE] = {};
#endif

#ifdef ZEPHYR
#if (NO_THREADS > 16)
#error "too many threads for Orangencart's STACK_SIZE"
#endif
static char *stacks = (char *)0x10000000;   // fast SRAM on Orangecart, only 16k! so NO_THREADS <= 16
#else
static char stacks[NO_THREADS * STACK_SIZE] = {};
#endif


int main(int argc, char *argv[])
{
    std::cout << "Hello Mandelbrot World.\n";
    mandel<MTYPE> *m = new mandel<MTYPE>{cv, stacks, -1.5, -1.0, 0.5, 1.0, IMG_W / PIXELW, IMG_H};
    std::cout << "done.\n";
    delete m;
#ifdef ZEPHYR
    std::cout << "system halted.\n";
    while(1)
        usleep(1000 * 500);
#endif
    return 0;
}