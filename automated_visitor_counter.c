//#include <stdio.h>
//#include <stdlib.h>

int main() {
    int total_people = 0;
    int led1 = 0;
    int led2 = 0;
    int led3 = 0;
    int led4 = 0;
    int led5 = 0;
    int mask = 0xFFFFFF83;
    int z;
    int ledreg1, ledreg2, ledreg3, ledreg4, ledreg5;
    int sensor_1,sensor_2;
    ledreg1 = led1 * 4;
    ledreg2 = led2 * 8;
    ledreg3 = led3 * 16;
    ledreg4 = led4 * 32;
    ledreg5 = led5 * 64;

    //for (z = 0; z < 10; z++) 
    
    while(1) {
       
       // printf("Reading sensor values and showing total no of people\n");
       
        // Simulated digitalRead for sensor1 and sensor2 (Assuming x30 contains sensor values)
        //int sensor_1 = 0;
        //int sensor_2 = 1;
        asm volatile(
            "andi %0, x30, 0x01\n\t"
            : "=r"(sensor_1)
            :
            :
        );

        if (sensor_1 == 0) {
            while (sensor_2 == 1) 
           // if (sensor_2 == 1)
            {
                // Wait for a person to fully enter
                // Replace with your code to check sensor2 state
                // This loop should actively monitor sensor_2
                asm volatile(
                    "andi %0, x30, 0x02\n\t"
                    : "=r"(sensor_2)
                    :
                    :
                );
                
               //people entered 
                total_people++;

            if (total_people < 32) {
                // Control five LEDs based on individual bits of total_people
                led1 = (total_people & 0x01) ? 1 : 0;
                led2 = (total_people & 0x02) ? 1 : 0;
                led3 = (total_people & 0x04) ? 1 : 0;
                led4 = (total_people & 0x08) ? 1 : 0;
                led5 = (total_people & 0x10) ? 1 : 0;

                // Recalculate ledreg values
                ledreg1 = led1 * 4;
                ledreg2 = led2 * 8;
                ledreg3 = led3 * 16;
                ledreg4 = led4 * 32;
                ledreg5 = led5 * 64;

                // Update the mask and x30 register
                asm volatile(
                    "and x30, x30, %5\n\t"
                    "or x30, x30, %0\n\t"
                    "or x30, x30, %1\n\t"
                    "or x30, x30, %2\n\t"
                    "or x30, x30, %3\n\t"
                    "or x30, x30, %4\n\t"
                    :
                    : "r"(ledreg1), "r"(ledreg2), "r"(ledreg3), "r"(ledreg4), "r"(ledreg5), "r"(mask)
                    : "x30"
                );

               /* printf("sensor_1 = %d, sensor_2 = %d, total_people = %d\n\n", sensor_1, sensor_2, total_people);
                printf("led's displaying binary value of total_people\n");
                printf("%d,%d,%d,%d,%d\n\n",led5,led4,led3,led2,led1);*/
            }

            
                // Add a delay here (replace with your delay logic)
                for (int i = 0; i < 3000; i++) {
                    for (int j = 0; j < 1000000; j++) {
                        // Adjust the loop count based on your processor's speed
                    }
                }*/
            }
        }
    }

    return 0;
}
