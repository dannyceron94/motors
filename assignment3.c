#include <stdio.h>
#include <stdlib.h>
// #include <wiringPi.h>
#include <time.h>
#include <string.h>

struct config
{
    int e;
    int f;
    int r;
};

struct motor
{
    char motor[6];
    struct config config1;
    struct config config2;
    
    int arrow;
};


int main(void){
    struct motor motor1 = {"motor1",32,24,26,32,26,24,1};
    if(strcmp(motor1.motor, "motor1") == 0){
        printf("e = %d", motor1.config1.e);
    }
    else{
        printf("motor not found");
    }
    
    return 0;
}