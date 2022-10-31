#include <iostream>
#include "main.h"

int main()
{
#ifdef CLOSE
    return 0;
#else
    return 1;
#endif
    CLOSE