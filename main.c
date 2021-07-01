#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Task 7.h"


void main()
{
    int N,c;
    printf("How would you run program?\n");
    printf("1. Choose amount of requests and show detailed information every step\n");
    printf("2. Start for processing 1000 requests \n");
    scanf("%d",&c);
    switch(c)
    {
    case 1:
    printf("Enter amount of requests:\n");
    scanf("%d",&N);
    var_1(N);
    break;
    case 2:
    var_2();
    break;
    }
}
