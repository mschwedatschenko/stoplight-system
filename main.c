#include<stdio.h>
#include<time.h>

int main(){
    time_t time(time_t *tloc);

    typedef enum{
        GREEN,
        YELLOW,
        RED
    } light_states;
    
    light_states current_state = GREEN;


    while(1){
        current_state = next_state;
        switch(current_state);
        
        case GREEN:
            if(time == tloc + 10){
                next_state = RED;
            }
        break;

        case YELLOW:
            if(time == tloc + 10){
                next_state = RED;
            }
        break;

        case RED:
            if(time == tloc + 10){
                next_state = GREEN;
            }
        break;
    }
    
}