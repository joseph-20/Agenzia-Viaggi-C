#include <stdio.h>
#include <stdlib.h>
#include "header.h"

void clear_screen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}