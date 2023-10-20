int main()
{
    int sensor_1 = 0;
    int sensor_2 = 0;
    int total_people = 0;
    int ledpin[5],i,j,ledpin_reg[5];
    
    while (1) {
        // Simulated digitalRead for sensor1  and sensor2(Assuming x30 contains sensor values)
       
            asm volatile(
            "andi %0, x30, 0x01\n\t"
            "andi %0, x30, 0x02\n\t"
            : "=r"(sensor_1),"=r"(sensor_2)
            :
            );

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
                
            }

            // Person entered
            total_people++;
            if(total_people < 32)
            {
            for(i=1; total_people > 0;i++)
      {
      ledpin[i] = total_people % 2;
      total_people = total_people / 2;
      }
      }
      ledpin_reg[1] = ledpin[1]*2;
      ledpin_reg[2] = ledpin[2]*4;
      ledpin_reg[3] = ledpin[3]*8;
      ledpin_reg[4] = ledpin[4]*16;
      ledpin_reg[5] = ledpin[5]*32;
      
      asm volatile(
	"or x30, x30, %0\n\t"
	"or x30, x30, %1\n\t"
	"or x30, x30, %2\n\t"
	"or x30, x30, %3\n\t"
	"or x30, x30, %4\n\t"
	: 
	:"r"(ledpin_reg[1]),"r"(ledpin_reg[2]),"r"(ledpin_reg[3]),"r"(ledpin_reg[4]),"r"(ledpin_reg[5])
	:"x30"
	);
            //show();
            //displaytotalpeople();
           // delay(300); // Delay for 300 milliseconds
           
           for (int i = 0; i < 300; i++) {
        	for ( int j = 0; j < 10000; j++) {
            // Adjust the loop count based on your processor's speed
        }
    }
           
        }
       
    }
    return 0;
}

