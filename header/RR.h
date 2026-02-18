#ifndef RR_H
#define RR_H

#include "process.h"
#include "queue.h"
#include <stdlib.h>

void robin(process p[], int n, int maxTime, char result[], int quantum);

#endif // RR_H