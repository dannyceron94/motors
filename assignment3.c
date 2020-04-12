// resources:
// https://www.electronicwings.com/raspberry-pi/raspberry-pi-pwm-generation-using-python-and-c
// https://github.com/sbcshop/MotorShield/blob/master/PiMotor.py
// #include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <time.h>
#include <string.h>
#include <stdio.h>

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

struct motor motor1 = {"motor1",11,15,13,11,13,15,4};
struct motor *motor1Ptr = &motor1;

struct motor motor2 = {"motor2",22,16,18,22,18,16,3};
struct motor *motor2Ptr = &motor2;

struct motor motor3 = {"motor3",11,15,13,11,13,15,4};
struct motor *motor3Ptr = &motor3;

struct motor motor4 = {"motor4",22,16,18,22,18,16,3};
struct motor *motor4Ptr = &motor4;

int init(char[6],char[7]);
int initHelper(struct motor *, char[7]);
int foward(struct motor *,int,char[7]);
int stop(struct motor *, char[7]);


int main(void){
    
    int m1 = init("motor1","config1");
    printf("check = %d\n",m1);
    int m2 = init("motor2","config2");
    printf("check = %d\n",m2);
    m1 = foward(&motor1,20,"config1");
    m2 = foward(&motor2,50,"config2");
    return 0;
}

int init(char motor[6],char config[7]){
    int check =-1;
    if( motor == NULL ||  config == NULL ||(strcmp(motor,"")==0) || (strcmp(config,"")==0)){
        printf("invalid input, ");
        printf("%s motor: ",motor);
        printf("%s config: ",config);
    }
    else if(strcmp(motor,"motor1") == 0){
        check = initHelper(&motor1,config);
    }
    else if(strcmp(motor,"motor2") == 0){ 
        check = initHelper(&motor2,config);
    }
    else if(strcmp(motor,"motor3") == 0){
        check = initHelper(&motor3,config);
    }
    else if(strcmp(motor,"motor4") == 0){
        check = initHelper(&motor4,config);
    }
    return check;
    
}

int initHelper(struct motor *mot, char config[7]){
    if(wiringPiSetUp()== -1){
        printf("WiringPiSetUp failed");
        return-1;
    }
    // using pointer type 1
    if(strcmp(config,"config1")==0){
        int e = (*mot).config1.e;
        int f = (*mot).config1.f;
        int r = (*mot).config1.r;
        // set the pins
        printf("e= %d,f= %d,r=%d",e,f,r);
        PinMode((*mot).config1.e,OUTPUT);
        PinMode((*mot).config1.f,OUTPUT);
        PinMode((*mot).config1.r,OUTPUT);
        softPwmCreate((*mot).config1.e,0,100);//set PWM channal with range
        softPwmWrite((*mot).config1.e,0);

        // PinMode((*mot).config1.e,PWM_OUTPUT);
        // pwmWrite((*mot).config.e,0)
        softPwmWrite((*mot).config1.e,0);
        digitalWrite((*mot).config1.f,LOW);
        digitalWrite((*mot).config1.r,LOW);
        return 0;
    }
    // using pointer type 2
    if(strcmp(config,"config2")==0){
        int e = mot->config2.e;
        int f = mot->config2.f;
        int r = mot->config2.r;
        // set the pins
        printf("e= %d,f= %d,r=%d",e,f,r);
        // setting pins
        PinMode(mot->config1.e,OUTPUT);
        PinMode(mot->config1.f,OUTPUT);
        PinMode(mot->config1.r,OUTPUT);
        softPwmCreate(mot->config1.e,0,100);//set PWM channal with range

        // PinMode(mot->config1.e,PWM_OUTPUT);
        // pwmWrite(mot->config.e,0)
        softPwmWrite(mot->config2.e,0);
        digitalWrite(mot->config2.f,LOW);
        digitalWrite(mot->config2.r,LOW);
    }
    else{printf("invalid config");}
    return -1;

}

int foward(struct motor &mot, int speed,char[7] config){
    // pwmWrite(mot->config.e,speed)
    if(strcmp(config,"config1")){
        softPwmWrite(mot->config1.e,speed);
        digitalWrite(mot->config1.f,High);
        digitalWrite(mot->config1.r,LOW);
        return 0;
    }
    if(strcmp(config,"config2")){
        softPwmWrite(mot->config2.e,speed);
        digitalWrite(mot->config2.f,High);
        digitalWrite(mot->config2.r,LOW);
        return 0;
    }
    return -1;


}

int stop(truct motor &mot,char[7] config){
    // pwmWrite(mot->config.e,speed)
    if(strcmp(config,"config1")){
        softPwmWrite(mot->config1.e,0);
        digitalWrite(mot->config1.f,LOW);
        digitalWrite(mot->config1.r,LOW);
        return 0;
    }
    if(strcmp(config,"config2")){
        softPwmWrite(mot->config2.e,0);
        digitalWrite(mot->config2.f,LOW);
        digitalWrite(mot->config2.r,LOW);
        return 0;
    }
    return -1;

}
