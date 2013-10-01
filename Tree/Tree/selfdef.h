#ifndef _SELFDEF_H
#define _SELFDEF_H

#include <stddef.h>
#define TRUE 1
#define  FALSE 0
#define  CMP(X,Y) (X>Y?1:(X==Y?0:-1))
#define new(x,...) _##x(malloc(sizeof(x)),__VA_ARGS__)

typedef int bool;

#endif