void readpinvalues(); 
void delay(int);

int sensor_1 = 0;
int sensor_2 = 0;
int total_people = 0;

int main()
{
     readpinvalues();
     return 0;
}     

void readpinvalues() {
    // Setup code
    while (1) {
        // Simulated digitalRead for sensor7
        // Replace with actual code to read the state of sensor connected to pin 7
        // Example: sensor7 = digitalRead(7);
        asm(
	"andi %0, x30, 0x01\n\t"
	: "=r" (sensor_1));
	
	asm(
	"andi %0, x30, 0x02\n\t"
	: "=r" (sensor_2));

        // Simulated digitalRead for sensor8
        // Replace with actual code to read the state of sensor connected to pin 8
        // Example: sensor8 = digitalRead(8);

        if (sensor_1 == 0) {
            while (sensor_2 == 1) {
                // Wait for person to fully enter
                // Replace with your code to check sensor8 state
                asm(
	            "andi %0, x30, 0x02\n\t"
	            : "=r" (sensor_2));
            }

            // Person entered 
            total_people++;
            //show();
            delay(300); // Delay for 300 milliseconds
             
        } 
              //printf("There are %d people in the room.\n", total);
       
    }

  
}
void delay(int milliseconds) {
    for (int i = 0; i < milliseconds; i++) {
        for (int j = 0; j < 10000; j++) {
            // Adjust the loop count based on your processsor's speed
        }
    }
}

