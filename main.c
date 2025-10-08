#include <stdio.h>
#include <time.h>
#include <string.h>
#include <sys/select.h>
#include <unistd.h>

typedef enum {
    GREEN,
    YELLOW,
    RED
} light_states;

// this function was adapted from ChatGPT when prompted on how to check for user input without blocking the program
int (input_available)() {
    struct timeval tv = {0L, 0L};
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);
    return select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv) > 0;
}

// help dialog and main program
int main(int argc, char *argv[]) {
    if (argc > 1 && (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)) {
        printf("Simulates a traffic light finite state machine.\n\n");
        printf("-h - Show help message\n\n");
        printf("During simulation:\n");
        printf("p, enter - Request pedestrian crossing (only during GREEN)\n");
        return 0;
    }

    // initializes states
    light_states current_state = GREEN;
    light_states next_state = GREEN;

    time_t time_start = time(NULL); // time when program starts
    int state_duration = 10;
    int pedestrian = 0; // sets pedestrian to false
    time_t last_print = 0;

    printf("Traffic light simulation started\n");
    printf("Press 'p' for pedestrian crossing.\n\n");

    while (1) {
        double elapsed = difftime(time(NULL), time_start);      // time elapsed = time now - time when state started
        double remaining = state_duration - elapsed;            // time remaining = state's set duration - time elapsed

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

            // reset timer and pedestrian request
            time_start = time(NULL);
            pedestrian = 0;
            printf("\nTransitioned to new light\n");
        }

        // prints every second : if time since last print >= 1 second
        if (difftime(time(NULL), last_print) >= 1) {
            last_print = time(NULL);
            switch (current_state) {
                case GREEN:
                    printf("Light is GREEN | %.0f sec remaining\n", remaining);
                    break;
                case YELLOW:
                    printf("Light is YELLOW | %.0f sec remaining\n", remaining);
                    break;
                case RED:
                    printf("Light is RED | %.0f sec remaining\n", remaining);
                    break;
            }

            // non-blocking user input check
            if (input_available()) {
                char ch = getchar();

                // checks for user input
                if (ch == 's') {
                    switch (current_state) {
                        case GREEN:
                            printf("Current state: GREEN | %.0f sec remaining\n", remaining);
                            break;
                        case YELLOW:
                            printf("Current state: YELLOW | %.0f sec remaining\n", remaining);
                            break;
                        case RED:
                            printf("Current state: RED | %.0f sec remaining\n", remaining);
                            break;
                    }
                }

                // if pedestrian button pressed during green
                else if (ch == 'p' && current_state == GREEN) {
                    pedestrian = 1; // sets pedestrian to true
                    printf("Pedestrian button pressed, light will change soon\n");
                }
            }
        }
    }

    return 0;
}
