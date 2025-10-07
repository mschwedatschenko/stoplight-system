#include<stdio.h>
#include<time.h>
#include<stdbool.h>

int main(){

    typedef enum{
        GREEN,
        YELLOW,
        RED
    } light_states;
    
    light_states current_state = GREEN;
    light_states next_state = NULL;

    // starts a new timer
    time_t time_start = time(NULL);
    int state_duration = 10;
    bool pedestrian = 0;

    //checks if there is a pedestrian waiting to cross, rough idea - not fully fleshed out yet
    if(fscanf("%d", stdin)){
        pedestrian = 1;
    }


    while(1){
        current_state = next_state;
        
        //if the amount of time that has elapsed between loop starting and program starting is more than 10
        if(difftime(time(NULL), time_start) >= state_duration){

        switch(current_state){
            case GREEN:
                if(pedestrian == 1){
                    state_duration = 3;
                    next_state = YELLOW;
                }

                next_state = YELLOW;
                state_duration = 3;
                break;

            case YELLOW:
                next_state = RED;
                state_duration = 6;
                break;

            case RED:
                next_state = GREEN;
                state_duration = 10;
                break;
        }

        //resets the duration timer for the new state transition
        time_start = time(NULL);
    }

        switch (current_state) {
            case GREEN:
                printf("GREEN light");
                break;
            case YELLOW:
                printf("YELLOW light");
                break;
            case RED:
                printf("RED light");
                break;
        }
    }
    return 0;
    
}