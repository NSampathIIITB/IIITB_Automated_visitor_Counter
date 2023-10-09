//void readpinvalues();
void delay(int);
void displaytotalpeople();
int sensor_1 = 0;
int sensor_2 = 0;
int total_people = 0;

// Define the pins for the LEDs
//int ledpin_1 = 0; 
//int ledpin_2 = 0; 

int main()
{
    

    //readpinvalues();
    //displaytotalpeople();
    //return 0;
//}

//void readpinvalues()
//{
    while (1)
    {
        // Simulated digitalRead for sensor1 (Assuming x30 contains sensor values)
       /* asm volatile(
            "andi %0, x30, 0x01\n\t"
            : "=r"(sensor_1));

        // Simulated digitalRead for sensor2
        asm volatile(
            "andi %0, x30, 0x02\n\t"
            : "=r"(sensor_2));*/
            
            asm volatile(
            "andi %0, x30, 0x01\n\t"
            "andi %0, x30, 0x02\n\t"
            : "=r"(sensor_1),"=r"(sensor_2)
            :
            );

        // Simulated digitalRead for sensor2
        /*asm volatile(
            "andi %0, x30, 0x02\n\t"
            : "=r"(sensor_2));*/
            
           /* asm volatile(
            
            "andi %0, x30, 0x02\n\t"
            : "=r"(sensor_2)
            :
            );*/

        if (sensor_1 == 0)
        {
            while (sensor_2 == 1)
            {
                // Wait for person to fully enter
                // Replace with your code to check sensor2 state
                asm volatile(
            
            "andi %0, x30, 0x02\n\t"
            : "=r"(sensor_2)
            :
            );
                /*asm volatile(
                    "andi %0, x30, 0x02\n\t"
                    : "=r"(sensor_2));*/
            }

            // Person entered
            total_people++;
            //show();
            displaytotalpeople();
            delay(300); // Delay for 300 milliseconds
        }
       // else
       // {
            // You may want to add handling for when sensor_1 is not 0
            // (e.g., if sensor_1 == 1)
       // }
    }
    return 0;
}

void displaytotalpeople()
{
      int ledpin_1,ledpin_2,ledpin_1_reg,ledpin_2_reg;
    // Display the total value using LEDs
    // You can use digitalWrite or equivalent functions to control the LEDs
    // For simplicity, let's assume HIGH turns the LED on and LOW turns it off

    // Turn off both LEDs
     ledpin_1 = 0; 
     ledpin_2 = 0; 
     ledpin_1_reg = ledpin_1*2;
     ledpin_2_reg = ledpin_2*4;
     
     asm volatile(
	"or x30, x30, %0\n\t"
	"or x30, x30, %1\n\t"
	: 
	:"r"(ledpin_1_reg),"r"(ledpin_2_reg)
	//:"r"(ledpin_2_reg)
	:"x30"
	);
    // Display the total value using LEDs
    if (total_people == 1)
    {
        // Turn on LED 1
        ledpin_1 = 1;
        ledpin_1 = ledpin_1_reg*2;
            asm volatile(
		"or x30, x30, %0\n\t" 
		:
		:"r"(ledpin_1_reg)
		:"x30"
		);
    }
    else if (total_people == 2)
    {
        // Turn on LED 2
         ledpin_2 = 1;
        ledpin_2 = ledpin_2_reg*2;
            asm volatile(
		"or x30, x30, %0\n\t" 
		:
		:"r"(ledpin_2_reg)
		:"x30"
		);
    }
    else if (total_people > 2)
    {
        // Turn on both LEDs (or use additional LEDs if needed)
        ledpin_1 = 1; 
        ledpin_2 = 1; 
        ledpin_1_reg = ledpin_1*2;
        ledpin_2_reg = ledpin_2*4;
     
        asm volatile(
	    "or x30, x30, %0\n\t"
	    "or x30, x30, %1\n\t" 
	    :
	    :"r"(ledpin_1_reg),"r"(ledpin_2_reg)
	    :"x30"
	    );
    }
}

void delay(int milliseconds)
{
    for (int i = 0; i < milliseconds; i++)
    {
        for (int j = 0; j < 10000; j++)
        {
            // Adjust the loop count based on your processor's speed
        }
    }
}

