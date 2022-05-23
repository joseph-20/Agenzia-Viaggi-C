#include <stdio.h>
#include <stdlib.h>
#include "header.h"

void clear_screen() {
#ifdef WINDOWS
    system("cls");
#else
    system("clear");
#endif
}