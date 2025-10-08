#include <stdio.h>
#include <time.h>
#include <string.h>

typedef enum {
    GREEN,
    YELLOW,
    RED
} light_states;

int main(int argc, char *argv[]) {
    if (argc > 1 && (strcmp(argv[1], "-h") == 0)) {
    printf("Simulates a traffic light finite state machine.\n\n");
    printf("-h - Show help message\n\n");
    printf("During simulation:\n");
    printf("s - Show current state and remaining time\n");
    printf("p - Request pedestrian crossing (only during GREEN)\n");
    return 0;
    }

    light_states current_state = GREEN;
    light_states next_state = GREEN;

    time_t time_start = time(NULL);
    int state_duration = 10;
    int pedestrian = 0;

    printf("Traffic light simulation started\n");
    printf("Press 's' to show current state.\n");
    printf("Press 'p' for pedestrian crossing.\n\n");

    while (1) {
        double elapsed = difftime(time(NULL), time_start);
        double remaining = state_duration - elapsed;

        // if time expired or pedestrian requested during green
        if (remaining <= 0 || (pedestrian && current_state == GREEN)) {
            switch (current_state) {
                case GREEN:
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
            current_state = next_state;
            time_start = time(NULL);
            pedestrian = 0;
            printf("\nTransitioned to new light\n");
        }

        // ask for user input
        printf("Press 's' to show state, 'p' to request crossing: ");
        char input;
        if(scanf(" %c", &input) == 1) {
            if (input == 's') {
                switch (current_state) {
                    case GREEN:  {
                        printf("Current state: GREEN | %.0f sec remaining\n", remaining); 
                        break;
                    }
                    case YELLOW: {
                        printf("Current state: YELLOW | %.0f sec remaining\n", remaining); 
                        break;
                    }
                    case RED: {
                        printf("Current state: RED | %.0f sec remaining\n", remaining); 
                        break;
                    }
                }
            } else if (input == 'p' && current_state == GREEN) {
                pedestrian = 1;
                printf("Pedestrian button pressed, light will change soon\n");
            }
        }
    }

    return 0;
}