#include <stdio.h>

// Simulated inputs for person detection
int sensor7 = 0; // Pin 7
int sensor8 = 0; // Pin 8

int total = 0;

void show() {
    //printf("There are %d people in the room.\n", total);
}

void delay(int milliseconds) {
    for (int i = 0; i < milliseconds; i++) {
        for (int j = 0; j < 10000; j++) {
            // Adjust the loop count based on your microcontroller's speed
        }
    }
}

int main() {
    // Setup code
    while (1) {
        // Simulated digitalRead for sensor7
        // Replace with actual code to read the state of sensor connected to pin 7
        // Example: sensor7 = digitalRead(7);

        // Simulated digitalRead for sensor8
        // Replace with actual code to read the state of sensor connected to pin 8
        // Example: sensor8 = digitalRead(8);

        if (sensor7 == 0) {
            while (sensor8 == 1) {
                // Wait for person to fully enter
                // Replace with your code to check sensor8 state
            }

            // Person entered 
            total++;
            show();
            delay(300); // Delay for 300 milliseconds
             
        } else if (sensor8 == 0) {
            while (sensor7 == 1) {
                // Wait for person to fully exit
                // Replace with your code to check sensor7 state
            }

            // Person exited
            total--;
            show();
            delay(300); // Delay for 300 milliseconds
        }

       
    }

    return 0;
}

