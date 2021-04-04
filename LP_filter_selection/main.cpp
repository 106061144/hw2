#include "mbed.h"
#include "uLCD_4DGL.h"

uLCD_4DGL uLCD(D1, D0, D2);
DigitalIn Up_button(D3);
DigitalIn Down_button(D6);
DigitalIn Confirm_button(D9);
AnalogOut Aout(D7);
DigitalOut led(LED1);
DigitalOut flash(LED2);

int mode=1;
void situation1()
{
    uLCD.text_width(1); 
    uLCD.text_height(1);
    uLCD.color(BLUE);
    uLCD.printf("\nPlease select from the below options\n");   
    uLCD.text_width(1); 
    uLCD.text_height(1);
    uLCD.textbackground_color(WHITE);
    uLCD.printf("\n  first mode");
    uLCD.text_width(1); 
    uLCD.text_height(1);
    uLCD.textbackground_color(BLACK);
    uLCD.printf("\n  second mode\n  third mode");
    ThisThread::sleep_for(1s);
}
void situation2()
{
    uLCD.text_width(1); 
    uLCD.text_height(1);
    uLCD.color(BLUE);
    uLCD.printf("\nPlease select from the below options\n");    
    uLCD.text_width(1); 
    uLCD.text_height(1);
    uLCD.textbackground_color(BLACK);
    uLCD.printf("\n  first mode");
    uLCD.text_width(1); 
    uLCD.text_height(1);
    uLCD.textbackground_color(WHITE);
    uLCD.printf("\n  second mode");
    uLCD.text_width(1); 
    uLCD.text_height(1);
    uLCD.textbackground_color(BLACK);            
    uLCD.printf("\n  third mode");
    ThisThread::sleep_for(1s);
}
void situation3()
{
    uLCD.text_width(1); 
    uLCD.text_height(1);
    uLCD.color(BLUE);
    uLCD.printf("\nPlease select from the below options\n");   
    uLCD.text_width(1); 
    uLCD.text_height(1);
    uLCD.textbackground_color(BLACK);
    uLCD.printf("\n  first mode\n  second mode");
    uLCD.text_width(1); 
    uLCD.text_height(1);
    uLCD.textbackground_color(WHITE);
    uLCD.printf("\n  third mode");
    ThisThread::sleep_for(1s);
}

void wave(){
    if (mode==1){// frequency=80
        while (1) {
            led = !led;
            for (float i = 0.0; i < 1.0; i += 1.0/300.0) {
                Aout = i;
                ThisThread::sleep_for(1ms/10000);
            }
            for (float j = 1.0; j > 0.0; j -= 1.0f/700.0){
                Aout = j;
                ThisThread::sleep_for(1ms/10000);
            }
        } 
    } else if(mode==2) {// frequency=0.08
        while (1) {
            flash = !flash;
            for (float i = 0.0; i <= 1.0; i += 1.0/300000.0) {
                Aout = i;
                ThisThread::sleep_for(1ms/10000);
            }
            for (float j = 1.0; j >= 0.0; j -= 1.0f/700000.0){
                Aout = j;
                ThisThread::sleep_for(1ms/10000);
            }
        }
    } else {
        while (1) {// frequency=0.8
            for (float i = 0.0; i <= 1.0; i += 1.0/30000.0) {
                Aout = i;
                ThisThread::sleep_for(1ms/10000);
            }
            for (float j = 1.0; j >= 0.0; j -= 1.0f/70000.0){
                Aout = j;
                ThisThread::sleep_for(1ms/10000);
            }
        }
    }
}
int main()
{
    //button.rise(&flip);
    situation1();
    Up_button.mode(PullNone);
    Down_button.mode(PullNone);
    Confirm_button.mode(PullNone);
    
    while (1)
    {
        ThisThread::sleep_for(250ms);
        if (mode==1){  
            if (Confirm_button) {
                wave();
            }      
            if (Down_button){
                uLCD.cls();
                situation2();
                mode=2;
            }
        } else if (mode==2){ 
            if (Confirm_button) {
                wave();
            }         
            if (Up_button){
                uLCD.cls();
                situation1();
                mode=1;
            } else if (Down_button) {
                uLCD.cls();
                situation3();
                mode=3;
            }
        } else {
            if (Confirm_button) {
                wave();
            }  
            if (Up_button){
                uLCD.cls();
                situation2();
                mode=2;
            } 
        }
    }
}