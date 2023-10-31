# IIITB_Automated_visitor_Counter_using_RISC-V

This github repository summarizes the progress made in the ASIC class regarding the RISC-V project.

## Aim
The aim of the project is to measure and display the number of persons entering in any room like seminar hall, conference room etc. LED's displays number of persons inside the room. We can use this project to count and display the number of visitors entering inside any conference room or seminar hall. we can make this works in two ways too. That means counter will be incremented if person enters the room and will be decremented if a person leaves the room. This design is made utilising a specialized RISC-V 32_bit processor.

## RISC-V 64 Bit Compiler Installation

**Steps to install RISC-V toolchain**

```
git clone https://github.com/kunalg123/riscv_workshop_collaterals.git
cd riscv_workshop_collaterals
chmod +x run.sh
./run.sh

```

 Once you run it you will get **make** error. ignore it  and type the following commands

 ```

cd ~/riscv_toolchain/iverilog/
git checkout --track -b v10-branch origin/v10-branch
git pull 
chmod 777 autoconf.sh 
./autoconf.sh 
./configure 
make
sudo make install

```

 To set the PATH variable in .bashrc

```
source .bashrc
gedit .bashrc
#Instead of **nsaisampath** put your **username**
export PATH="/home/nsaisampath/riscv_toolchain/riscv64-unknown-elf-gcc-8.3.0-2019.08.0-x86_64-linux-ubuntu14/bin:$PATH" #Type at last line # save and close the bashrc and type
source .bashrc

```
## Instruction set of RISC-V RV32I

![image](https://github.com/NSampathIIITB/IIITB_Automated_visitor_Counter/assets/141038460/86102c52-f600-4ea5-a11f-38b69d5cf254)
 
## IR Sensor 
The main element of this project is the IR Sensor which works as a Human Detector. Whenever the IR sensor detects an interrupt it counts the person and adds it to the previous value.

IR Sensor module has the great adaptive capability of the ambient light. It has an infrared transmitter and a receiver. The infrared emitting tube emits a certain frequency which when encounters an obstacle reflect back to the signal. The reflected signal is then received by the receiver tube. Apart from the IR Transmitter and Receiver the circuit also consists of Opamp, Variable Resistor (Trimmer pot) & output LED.

![images](https://github.com/NSampathIIITB/IIITB_Automated_visitor_Counter/assets/141038460/37ad4744-6c54-4c66-9420-ff46202e9137)

#### 1. IR LED Transmitter

IR LED emits light, in the range of Infrared frequency with a wavelength of 700nm – 1mm. IR LEDs have a light-emitting angle of approx. 20-60 degrees and has a range up to 5-10cm. IR LED white or transparent in color, so it can emit the maximum amount of light.

#### 2. Photodiode Receiver

Photodiode acts as the IR receiver as its conducts when light falls on it. Photodiode looks like a LED, with a black color coating on its outer side. The Black color absorbs the highest amount of light.

#### 3. LM358 Opamp

LM358 is an Operational Amplifier (Op-Amp) is used as a voltage comparator in the IR sensor. The comparator circuit compares the threshold voltage set using the preset and the photodiode’s series resistor voltage. When the Photodiode’s series resistor voltage drop is greater than the threshold voltage, the Op-Amp output is high. Similarly, when the Photodiode’s series resistor voltage drop is lesser than the threshold voltage, the Op-Amp output is low.

When the Op-Amp output is high the LED at the output terminal turns ON. This indicates an object or obstacle has been detected.

#### 4. Variable Resistor

The variable resistor used here is preset. It is used to calibrate the distance range at which the object should be detected.


## Working

First of all, we need to set one IR sensor (IR sensor-1) at the entry gate and another one (IR sensor-2) set at the exit gate. Normally when IR sensors do not detect any obstacle, it produces a HIGH (1) output value from the Output Pin.

When a visitor enters through the entry gate the IR sensor-1 detects the visitor (obstacle) and produces a Low (0) output value from the Output Pin.Then the processor read this value and counts 1+ using the code. Similarly, When the IR sensor-1 detects another visitor (obstacle), the processor increment the counting by 1+. In this way every time the processor adds +1 in the count when a visitor passes through this gate and calculates the total number of entering visitors.

## Circuit

The below shown is an assumed circuit not entirely accurate.

![Screenshot-2022-12-25-at-12 51 02-AM-800x485](https://github.com/NSampathIIITB/IIITB_Automated_visitor_Counter/assets/141038460/316859d7-8cd1-4bbb-ae98-e8f450f13930)

## Block Diagram

![Screenshot from 2023-10-09 19-10-18](https://github.com/NSampathIIITB/IIITB_Automated_visitor_Counter/assets/141038460/5ad037d4-4d7b-4bd4-8199-f1734d5dceae)

## Testing

1. Open a terminal window.
2. Navigate to the directory containing the sample.c file.
3. Design a function that executes the intended logic you require.
4. Compile the code using the GCC compiler and verify the output:
   
  
```
gcc automated_visitor_counter.c
./a.out
```

![Screenshot from 2023-10-25 16-26-26](https://github.com/NSampathIIITB/IIITB_Automated_visitor_Counter/assets/141038460/2b844fe0-a9b9-4752-8db0-01ba7a8db02d)

## x30 Register GPIO Assignment 

x30[0] = data read from IR sensor_1 (input)

x30[1] = data read from IR sensor_2 (input)

x30[9:2] = output to 8 LED's


## C Code

```

//#include <stdio.h>
//#include <stdlib.h>

int main() {
    int total_people = 0;
    int led1 = 0;
    int led2 = 0;
    int led3 = 0;
    int led4 = 0;
    int led5 = 0;
    int led6 = 0;
    int led7 = 0;
    int led8 = 0;
    int mask = 0xFFFFFC03;
    int z;
    int ledreg1, ledreg2, ledreg3, ledreg4, ledreg5,ledreg6,ledreg7,ledreg8;
    int sensor_1,sensor_2;
    ledreg1 = led1 * 4;
    ledreg2 = led2 * 8;
    ledreg3 = led3 * 16;
    ledreg4 = led4 * 32;
    ledreg5 = led5 * 64;
    ledreg6 = led6 * 128;
    ledreg7 = led7 * 256;
    ledreg8 = led8 * 512;

    //for (z = 0; z<100 ; z++) 
    while(1) 
    { 
        //printf("Reading sensor values and showing total no of people\n");
        asm volatile(
                    "andi %0, x30, 0x01\n\t"
                    : "=r"(sensor_1)
                    :
                    :
                );
        // Simulated digitalRead for sensor1 and sensor2 (Assuming x30 contains sensor values)
        // sensor_1 = 0;
        // sensor_2 = 1;
       
        if (sensor_1 == 0) {
           // while (sensor_2 == 1)
           asm volatile(
                    "andi %0, x30, 0x02\n\t"
                    : "=r"(sensor_2)
                    :
                    :
                ); 
               // sensor_2 = 0;
           if (sensor_2 == 1)
             	total_people = total_people;//Here sensor_2=1 i.e the person is about to enter inside the room or just outside the room
           else
                total_people++; //Here sensor_2=0 i.e  it detected the person completely entered into the room and it will increment the total_people

            if (total_people < 256) 
            {
                // Control five LEDs based on individual bits of total_people
                led1 = (total_people & 0x01) ? 1 : 0;
                led2 = (total_people & 0x02) ? 1 : 0;
                led3 = (total_people & 0x04) ? 1 : 0;
                led4 = (total_people & 0x08) ? 1 : 0;
                led5 = (total_people & 0x10) ? 1 : 0;
                led6 = (total_people & 0x20) ? 1 : 0;
                led7 = (total_people & 0x40) ? 1 : 0;
                led8 = (total_people & 0x80) ? 1 : 0;

                // Recalculate ledreg values
                ledreg1 = led1 * 4;
                ledreg2 = led2 * 8;
                ledreg3 = led3 * 16;
                ledreg4 = led4 * 32;
                ledreg5 = led5 * 64;
                ledreg6 = led6 * 128;
                ledreg7 = led7 * 256;
                ledreg8 = led8 * 512;
                
                // Update the mask and x30 register
                asm volatile(
                    "and x30, x30, %8\n\t"
                    "or x30, x30, %0\n\t"
                    "or x30, x30, %1\n\t"
                    "or x30, x30, %2\n\t"
                    "or x30, x30, %3\n\t"
                    "or x30, x30, %4\n\t"
                    "or x30, x30, %5\n\t"
                    "or x30, x30, %6\n\t"
                    "or x30, x30, %7\n\t"
                    :
                    : "r"(ledreg1), "r"(ledreg2), "r"(ledreg3), "r"(ledreg4), "r"(ledreg5),"r"(ledreg6),"r"(ledreg7),"r"(ledreg8), "r"(mask)
                    : "x30"
                );

              // printf("sensor_1 = %d, sensor_2 = %d, total_people = %d\n\n", sensor_1, sensor_2, total_people);
              //  printf("led's displaying binary value of total_people\n");
              //  printf("%d,%d,%d,%d,%d,%d,%d,%d\n\n",led8,led7,led6,led5,led4,led3,led2,led1);
            }
            else
            {
            	//printf("Limit Reached for 256 \n");
            	total_people = 0;
            }

            
                // Add a delay here (replace with your delay logic)
                for (int i = 0; i < 100; i++) 
                {
                        // Adjust the loop count based on your processor's speed
                    
                }
            }
        }

    return 0;
}


```
## Spike Simulation Results For Functionality Verification

I have done the spike simulatiion using *avcspike.c* which was mentioned below.

```
#include <stdio.h>
#include <stdlib.h>

int main() {
    int total_people = 0;
    int led1 = 0;
    int led2 = 0;
    int led3 = 0;
    int led4 = 0;
    int led5 = 0;
    int led6 = 0;
    int led7 = 0;
    int led8 = 0;
    int mask = 0xFFFFFC03;
    int z;
    int ledreg1, ledreg2, ledreg3, ledreg4, ledreg5,ledreg6,ledreg7,ledreg8;
    int sensor_1,sensor_2;
    ledreg1 = led1 * 4;
    ledreg2 = led2 * 8;
    ledreg3 = led3 * 16;
    ledreg4 = led4 * 32;
    ledreg5 = led5 * 64;
    ledreg6 = led6 * 128;
    ledreg7 = led7 * 256;
    ledreg8 = led8 * 512;

    //for (z = 0; z<100 ; z++) 
    while(1) 
    {
      //total_people=0; 
        printf("Reading sensor values and showing total no of people\n");
       /* asm volatile(
                    "andi %0, x30, 0x01\n\t"
                    : "=r"(sensor_1)
                    :
                    :
                );*/
        // Simulated digitalRead for sensor1 and sensor2 (Assuming x30 contains sensor values)
         sensor_1 = 0;
        // sensor_2 = 1;
       
        if (sensor_1 == 0) {
           // while (sensor_2 == 1)
          /* asm volatile(
                    "andi %0, x30, 0x02\n\t"
                    : "=r"(sensor_2)
                    :
                    :
                ); */
                sensor_2 = 0;
           if (sensor_2 == 1)
             	total_people = total_people;//Here sensor_2=1 i.e the person is about to enter inside the room or just outside the room
           else
                total_people++; //Here sensor_2=0 i.e  it detected the person completely entered into the room and it will increment the total_people

            if (total_people < 256) 
            {
                // Control 8 LEDs based on individual bits of total_people
                led1 = (total_people & 0x01) ? 1 : 0;
                led2 = (total_people & 0x02) ? 1 : 0;
                led3 = (total_people & 0x04) ? 1 : 0;
                led4 = (total_people & 0x08) ? 1 : 0;
                led5 = (total_people & 0x10) ? 1 : 0;
                led6 = (total_people & 0x20) ? 1 : 0;
                led7 = (total_people & 0x40) ? 1 : 0;
                led8 = (total_people & 0x80) ? 1 : 0;

                // Recalculate ledreg values
                ledreg1 = led1 * 4;
                ledreg2 = led2 * 8;
                ledreg3 = led3 * 16;
                ledreg4 = led4 * 32;
                ledreg5 = led5 * 64;
                ledreg6 = led6 * 128;
                ledreg7 = led7 * 256;
                ledreg8 = led8 * 512;
                
                // Update the mask and x30 register
               /* asm volatile(
                    "and x30, x30, %8\n\t"
                    "or x30, x30, %0\n\t"
                    "or x30, x30, %1\n\t"
                    "or x30, x30, %2\n\t"
                    "or x30, x30, %3\n\t"
                    "or x30, x30, %4\n\t"
                    "or x30, x30, %5\n\t"
                    "or x30, x30, %6\n\t"
                    "or x30, x30, %7\n\t"
                    :
                    : "r"(ledreg1), "r"(ledreg2), "r"(ledreg3), "r"(ledreg4), "r"(ledreg5),"r"(ledreg6),"r"(ledreg7),"r"(ledreg8), "r"(mask)
                    : "x30"
                );*/

                printf("sensor_1 = %d, sensor_2 = %d, total_people = %d\n\n", sensor_1, sensor_2, total_people);
                printf("led's displaying binary value of total_people\n");
                printf("%d,%d,%d,%d,%d,%d,%d,%d\n\n",led8,led7,led6,led5,led4,led3,led2,led1);
            }
            else
            {
            	printf("Limit Reached for 256 \n");
            	total_people = 0;
            }

            
                // Add a delay here (replace with your delay logic)
                /*for (int i = 0; i < 100; i++) {
                   // Adjust the loop count based on your processor's speed  
                }*/
            }
        }
   
    return 0;
}

```

```
riscv64-unknown-elf-gcc -march=rv64i -mabi=lp64 -ffreestanding -o out avcspike.c
```
```
spike pk out
```
Here when sensor_1=0  detects the person, we are checking the detection of person at sensor_2 ,when the sensor_2=1 it means the person is about to enter the room the value of total people remains same as the previous value as no one is completey going into the room and the value of total_people gets incremented  when the person completely enters inside the room i.e sensor_2=0(detected the person) further we will get the binary value of total_people entered in LED's.

In the below case sensor_1=0 , sensor_2=0 , total_people =0, when we run spike simulation the value of total_people remains constant which is equal to 0

![Screenshot from 2023-10-25 15-36-31](https://github.com/NSampathIIITB/IIITB_Automated_visitor_Counter/assets/141038460/518cd69b-3d1f-4442-9b64-2ca55235cf33)

In this case sensor_1=0 and sensor_2=0 ,when we run the spike simulation the value of total_people gets incremented as the person is completely enterd the room

![Screenshot from 2023-10-25 15-37-33](https://github.com/NSampathIIITB/IIITB_Automated_visitor_Counter/assets/141038460/31704e82-6d27-4f2f-b381-e9810d65d4cc)

## Assembly Code

### Assembly Code Generation

```
riscv64-unknown-elf-gcc -march=rv32i -mabi=ilp32 -ffreestanding -nostdlib -o out automated_visitor_counter.c
```

```
riscv64-unknown-elf-objdump -d -r out> automated_visitor_counter.txt
```


```

out:     file format elf32-littleriscv


Disassembly of section .text:

00010054 <main>:
   10054:	f9010113          	addi	sp,sp,-112
   10058:	06812623          	sw	s0,108(sp)
   1005c:	07010413          	addi	s0,sp,112
   10060:	fe042623          	sw	zero,-20(s0)
   10064:	fe042223          	sw	zero,-28(s0)
   10068:	fe042023          	sw	zero,-32(s0)
   1006c:	fc042e23          	sw	zero,-36(s0)
   10070:	fc042c23          	sw	zero,-40(s0)
   10074:	fc042a23          	sw	zero,-44(s0)
   10078:	fc042823          	sw	zero,-48(s0)
   1007c:	fc042623          	sw	zero,-52(s0)
   10080:	fc042423          	sw	zero,-56(s0)
   10084:	c0300793          	li	a5,-1021
   10088:	fcf42223          	sw	a5,-60(s0)
   1008c:	fe442783          	lw	a5,-28(s0)
   10090:	00279793          	slli	a5,a5,0x2
   10094:	fcf42023          	sw	a5,-64(s0)
   10098:	fe042783          	lw	a5,-32(s0)
   1009c:	00379793          	slli	a5,a5,0x3
   100a0:	faf42e23          	sw	a5,-68(s0)
   100a4:	fdc42783          	lw	a5,-36(s0)
   100a8:	00479793          	slli	a5,a5,0x4
   100ac:	faf42c23          	sw	a5,-72(s0)
   100b0:	fd842783          	lw	a5,-40(s0)
   100b4:	00579793          	slli	a5,a5,0x5
   100b8:	faf42a23          	sw	a5,-76(s0)
   100bc:	fd442783          	lw	a5,-44(s0)
   100c0:	00679793          	slli	a5,a5,0x6
   100c4:	faf42823          	sw	a5,-80(s0)
   100c8:	fd042783          	lw	a5,-48(s0)
   100cc:	00779793          	slli	a5,a5,0x7
   100d0:	faf42623          	sw	a5,-84(s0)
   100d4:	fcc42783          	lw	a5,-52(s0)
   100d8:	00879793          	slli	a5,a5,0x8
   100dc:	faf42423          	sw	a5,-88(s0)
   100e0:	fc842783          	lw	a5,-56(s0)
   100e4:	00979793          	slli	a5,a5,0x9
   100e8:	faf42223          	sw	a5,-92(s0)
   100ec:	001f7793          	andi	a5,t5,1
   100f0:	faf42023          	sw	a5,-96(s0)
   100f4:	fa042783          	lw	a5,-96(s0)
   100f8:	fe079ae3          	bnez	a5,100ec <main+0x98>
   100fc:	002f7793          	andi	a5,t5,2
   10100:	f8f42e23          	sw	a5,-100(s0)
   10104:	f9c42703          	lw	a4,-100(s0)
   10108:	00100793          	li	a5,1
   1010c:	00f70863          	beq	a4,a5,1011c <main+0xc8>
   10110:	fec42783          	lw	a5,-20(s0)
   10114:	00178793          	addi	a5,a5,1
   10118:	fef42623          	sw	a5,-20(s0)
   1011c:	fec42703          	lw	a4,-20(s0)
   10120:	0ff00793          	li	a5,255
   10124:	12e7c663          	blt	a5,a4,10250 <main+0x1fc>
   10128:	fec42783          	lw	a5,-20(s0)
   1012c:	0017f793          	andi	a5,a5,1
   10130:	fef42223          	sw	a5,-28(s0)
   10134:	fec42783          	lw	a5,-20(s0)
   10138:	4017d793          	srai	a5,a5,0x1
   1013c:	0017f793          	andi	a5,a5,1
   10140:	fef42023          	sw	a5,-32(s0)
   10144:	fec42783          	lw	a5,-20(s0)
   10148:	4027d793          	srai	a5,a5,0x2
   1014c:	0017f793          	andi	a5,a5,1
   10150:	fcf42e23          	sw	a5,-36(s0)
   10154:	fec42783          	lw	a5,-20(s0)
   10158:	4037d793          	srai	a5,a5,0x3
   1015c:	0017f793          	andi	a5,a5,1
   10160:	fcf42c23          	sw	a5,-40(s0)
   10164:	fec42783          	lw	a5,-20(s0)
   10168:	4047d793          	srai	a5,a5,0x4
   1016c:	0017f793          	andi	a5,a5,1
   10170:	fcf42a23          	sw	a5,-44(s0)
   10174:	fec42783          	lw	a5,-20(s0)
   10178:	4057d793          	srai	a5,a5,0x5
   1017c:	0017f793          	andi	a5,a5,1
   10180:	fcf42823          	sw	a5,-48(s0)
   10184:	fec42783          	lw	a5,-20(s0)
   10188:	4067d793          	srai	a5,a5,0x6
   1018c:	0017f793          	andi	a5,a5,1
   10190:	fcf42623          	sw	a5,-52(s0)
   10194:	fec42783          	lw	a5,-20(s0)
   10198:	4077d793          	srai	a5,a5,0x7
   1019c:	0017f793          	andi	a5,a5,1
   101a0:	fcf42423          	sw	a5,-56(s0)
   101a4:	fe442783          	lw	a5,-28(s0)
   101a8:	00279793          	slli	a5,a5,0x2
   101ac:	fcf42023          	sw	a5,-64(s0)
   101b0:	fe042783          	lw	a5,-32(s0)
   101b4:	00379793          	slli	a5,a5,0x3
   101b8:	faf42e23          	sw	a5,-68(s0)
   101bc:	fdc42783          	lw	a5,-36(s0)
   101c0:	00479793          	slli	a5,a5,0x4
   101c4:	faf42c23          	sw	a5,-72(s0)
   101c8:	fd842783          	lw	a5,-40(s0)
   101cc:	00579793          	slli	a5,a5,0x5
   101d0:	faf42a23          	sw	a5,-76(s0)
   101d4:	fd442783          	lw	a5,-44(s0)
   101d8:	00679793          	slli	a5,a5,0x6
   101dc:	faf42823          	sw	a5,-80(s0)
   101e0:	fd042783          	lw	a5,-48(s0)
   101e4:	00779793          	slli	a5,a5,0x7
   101e8:	faf42623          	sw	a5,-84(s0)
   101ec:	fcc42783          	lw	a5,-52(s0)
   101f0:	00879793          	slli	a5,a5,0x8
   101f4:	faf42423          	sw	a5,-88(s0)
   101f8:	fc842783          	lw	a5,-56(s0)
   101fc:	00979793          	slli	a5,a5,0x9
   10200:	faf42223          	sw	a5,-92(s0)
   10204:	fc042783          	lw	a5,-64(s0)
   10208:	fbc42703          	lw	a4,-68(s0)
   1020c:	fb842683          	lw	a3,-72(s0)
   10210:	fb442603          	lw	a2,-76(s0)
   10214:	fb042583          	lw	a1,-80(s0)
   10218:	fac42503          	lw	a0,-84(s0)
   1021c:	fa842803          	lw	a6,-88(s0)
   10220:	fa442883          	lw	a7,-92(s0)
   10224:	fc442303          	lw	t1,-60(s0)
   10228:	006f7f33          	and	t5,t5,t1
   1022c:	00ff6f33          	or	t5,t5,a5
   10230:	00ef6f33          	or	t5,t5,a4
   10234:	00df6f33          	or	t5,t5,a3
   10238:	00cf6f33          	or	t5,t5,a2
   1023c:	00bf6f33          	or	t5,t5,a1
   10240:	00af6f33          	or	t5,t5,a0
   10244:	010f6f33          	or	t5,t5,a6
   10248:	011f6f33          	or	t5,t5,a7
   1024c:	0080006f          	j	10254 <main+0x200>
   10250:	fe042623          	sw	zero,-20(s0)
   10254:	fe042423          	sw	zero,-24(s0)
   10258:	0100006f          	j	10268 <main+0x214>
   1025c:	fe842783          	lw	a5,-24(s0)
   10260:	00178793          	addi	a5,a5,1
   10264:	fef42423          	sw	a5,-24(s0)
   10268:	fe842703          	lw	a4,-24(s0)
   1026c:	06300793          	li	a5,99
   10270:	fee7d6e3          	bge	a5,a4,1025c <main+0x208>
   10274:	e79ff06f          	j	100ec <main+0x98>



```

## Specific Instructions

```
Number of different instructions: 14
List of unique instructions:
beq
srai
or
lw
sw
addi
andi
bnez
blt
j
bge
and
li
slli

```
![Screenshot from 2023-10-25 17-00-35](https://github.com/NSampathIIITB/IIITB_Automated_visitor_Counter/assets/141038460/7b356cdc-bb9c-45cd-83fc-827f3cd29ea2)


## Functionality verification using GTKWave Simulations

After generating the core we have to verify the functionality of the core using GTKWave simulations.Necessary modifications has been made in the processor.v and testbench.v according to our functionality.

```
iverilog -o test processor.v testbench.v
.\test
gtkwave waveform.vcd
```
### Case-1
   
 when the input is given as `2'b01` i.e ```sensor_1 = 0``` (person is detected at sensor_1 while entering) and ```sensor_2 = 1``` (person is not detected at sensor_2 while entering) the output value is zero which means the binary value of total people in the room displayed by the LED's is zero.In case there are some people intially inside the room the value of the total people remains constant for the given set of inputs. 
 
![Screenshot from 2023-10-27 21-03-19](https://github.com/NSampathIIITB/IIITB_Automated_visitor_Counter/assets/141038460/921d8116-763b-427c-a9a0-f8854d926b64)

![Screenshot from 2023-10-31 20-41-41](https://github.com/NSampathIIITB/IIITB_Automated_visitor_Counter/assets/141038460/d6e5418d-0d98-43ea-a84e-76ad5a6eb480)

### Case-2
     
when the input is given as `2'b00` i.e ```sensor_1 = 0``` (person is detected at sensor_1 while entering) and ```sensor_2 = 0``` (person is detected at sensor_2 while entering) the output value i.e the total people value gets incremented when the people are entering one after the other and the binary value of the total people is displayed by the LED's ,when the total people inside the room reaches 255 the output(counter) starts to increment from zero again i.e the people inside the room are counted in sets of 255.

**In the below waveforms we can clearly obsereve that the outputs are generated according to our logic or functionallity**

![Screenshot from 2023-10-27 21-10-15](https://github.com/NSampathIIITB/IIITB_Automated_visitor_Counter/assets/141038460/51b01916-8939-4a3e-bad1-8f68b13da481)
![Screenshot from 2023-10-27 21-11-15](https://github.com/NSampathIIITB/IIITB_Automated_visitor_Counter/assets/141038460/fd3972ab-4211-4dc9-bca0-2b0a6f7de396)

**In these two waveforms we can obsereve the masking**

![Screenshot from 2023-10-30 10-43-57](https://github.com/NSampathIIITB/IIITB_Automated_visitor_Counter/assets/141038460/f548a1d4-a309-462e-a09a-ae6bd0ca870a)
![Screenshot from 2023-10-30 10-47-35](https://github.com/NSampathIIITB/IIITB_Automated_visitor_Counter/assets/141038460/6275f0c6-ec02-4c98-8498-9051a8d406b1)

In the below waveform we can observe the first output ***01*** is coming after the instruction ***00ff6f33 or	t5,t5,a5***
![Screenshot from 2023-10-31 20-44-09](https://github.com/NSampathIIITB/IIITB_Automated_visitor_Counter/assets/141038460/76e1269f-3ced-4a2b-82d4-80a059847274)

In the below waveform we can observe the last output count value ***FF*** is coming after the instruction ***011f6f33 or	t5,t5,a7***
![Screenshot from 2023-10-31 20-48-01](https://github.com/NSampathIIITB/IIITB_Automated_visitor_Counter/assets/141038460/ef3fbab6-1959-44a4-add5-eab64cc15916)

In the below waveform the instructions between the markers A and B depicts the delay which is `140sec` and according to my code these set of instructions will run in a loop for 100 times which gives us a total delay of `140000sec`

![Screenshot from 2023-10-31 20-55-16](https://github.com/NSampathIIITB/IIITB_Automated_visitor_Counter/assets/141038460/2c27cfd5-c6cf-4028-a853-d79ce02448fe)



## Instruction Verification

The execution of some of the above instructions in above assembly code were tested and verified in GTKWave.

Here,

1. **$signal$45** represents x2 register which is SP (Stack Pointer)
2. **$signal$51** represents x8 register which is s0 (Saved register 0)
3. **$signal$58** represents x15 register which is a5 (function argument 5)

### Instruction-1:
 
 ```f9010113   addi	sp,sp,-112```
 
 ![Screenshot from 2023-10-27 21-16-06](https://github.com/NSampathIIITB/IIITB_Automated_visitor_Counter/assets/141038460/110ecd48-6f1b-4971-ac24-e1de69c3afff)

 Here the instruction is **addi(add immediate)** i.e the default value of SP is FF (255 in decimal) it is added with -48(immediate decimal value) and again stored in SP which is 8F(143 in decimal).

### Instruction-2:
 
```c0300793   li	a5,-1021```

![Screenshot from 2023-10-27 21-23-38](https://github.com/NSampathIIITB/IIITB_Automated_visitor_Counter/assets/141038460/a42e11cf-1c36-4db0-b5f3-524dadbab82b)

Here the instruction is **li(load immediate)** i.e the value -1021(immediate value FFFFFC03 in hexa) is loaded into the a5 register.

### Instruction-3:

```0017f793    andi	a5,a5,1```

![Screenshot from 2023-10-27 21-39-03](https://github.com/NSampathIIITB/IIITB_Automated_visitor_Counter/assets/141038460/889cf176-22e7-41e5-8a3f-188f973bd626)

Here the instruction is **andi(and immediate)** ,1 is the immediate value, and it is used as the other operand for the AND operation. The contents of "a5" will be bitwise ANDed with the immediate value 1 and again stored in a5.

### Instruction-4:

```4017d793    srai	a5,a5,0x1```

![Screenshot from 2023-10-27 21-37-29](https://github.com/NSampathIIITB/IIITB_Automated_visitor_Counter/assets/141038460/b066ea17-bf26-41c2-8f92-6f8b4f6ac29e)

Here the instruction is **srai(shift right arithmetic immediate)**,"a5" is the destination register where the result of the right shift operation will be stored.
The second "a5" is the source register, indicating that you want to perform the right shift operation on the value in register "a5.""0x1" is the immediate value by which the value in register "a5" is right-shifted. In this case, you're right-shifting by 1 bit.The value in a5 register is 00000001 it is right shifted by 1 results in 00000000.


## Gate Level Simulation

Before doing Gate level simulation we need to convert our RTL design logic into Gate level Netlist ,this can be done by using a synthesis tool.

Synthesis transforms the simple RTL design into a gate-level netlist with all the constraints as specified by the designer. In simple language, Synthesis is a process that converts the abstract form of design to a properly implemented chip in terms of logic gates.

Synthesis takes place in multiple steps:

1. Converting RTL into simple logic gates.
2. Mapping those gates to actual technology-dependent logic gates available in the technology libraries.
3. Optimizing the mapped netlist keeping the constraints set by the designer intact.

Yosys is the tool we use to convert out RTL design code to netlist.


After invoking the Yosys these are the commands we need to give for the generation of Gate level Netlist

```
 read_liberty -lib sky130_fd_sc_hd__tt_025C_1v80_256.lib
 read_verilog processor.v
 synth -top wrapper
 dfflibmap -liberty sky130_fd_sc_hd__tt_025C_1v80_256.lib
 abc -liberty sky130_fd_sc_hd__tt_025C_1v80_256.lib 
 write_verilog synth_test.v
 show wrapper

```

![Screenshot from 2023-10-30 21-37-33](https://github.com/NSampathIIITB/IIITB_Automated_visitor_Counter/assets/141038460/0b11c725-8a19-4476-b41d-abbd2c1502dd)
![Screenshot from 2023-10-30 21-41-03](https://github.com/NSampathIIITB/IIITB_Automated_visitor_Counter/assets/141038460/fe03d13a-7c10-494f-b6c6-0174a485fa18)

**Wrapper module after Netlist generation**

![Screenshot from 2023-10-30 23-46-12](https://github.com/NSampathIIITB/IIITB_Automated_visitor_Counter/assets/141038460/e62765d3-720f-48dc-b210-a31463b21d4b)


***GLS*** is generating the simulation output by running test bench with netlist file generated from synthesis as Design under test. Netlist is logically same as RTL code, therefore, same test bench can be used for it.We perform this to verify logical functionality of the  RTL design after synthesizing it. Also ensuring the timing of the design is met.

Following are the commands to run the GLS simulation:

```
iverilog -o test_new testbench.v synth_processor.v sky130_sram_1kbyte_1rw1r_32x256_8.v sky130_fd_sc_hd.v primitives.v

```
The gtkwave output for the netlist should match the output waveform for the RTL design file. As netlist and design code have same set of inputs and outputs, we can use the same testbench and compare the waveforms.

The output waveforms of the synthesized Netlist for Case-1' and Case-2' are given below

### Case-1' 

The inputs here are given similar to the inputs given in Functional Verification using GTKWave simulation *Case-1* and the output we observed is also same as the output we got in *Case-1*

![Screenshot from 2023-10-31 00-11-26](https://github.com/NSampathIIITB/IIITB_Automated_visitor_Counter/assets/141038460/685b534a-f0bd-49db-91e5-dd11ebe7c2e8)

### Case-2'

The inputs here are given similar to the inputs given in Functional Verification using GTKWave simulation *Case-2* and the output we observed is also same as the output we got in *Case-2*

![Screenshot from 2023-10-31 00-15-11](https://github.com/NSampathIIITB/IIITB_Automated_visitor_Counter/assets/141038460/47c88707-28bd-43f9-a7dd-12aeb6d30b8f)
![Screenshot from 2023-10-31 12-32-54](https://github.com/NSampathIIITB/IIITB_Automated_visitor_Counter/assets/141038460/53900d39-4ea8-4923-b911-4d9ec20a18a0)


## Acknowledgement

- Kunal Ghosh, VSD Corp. Pvt. Ltd.
- Alwin shaju,Colleague,IIIT B
- Kanish R,Colleague,IIIT B
- Emil Jayanth Lal, Colleague, IIITB
- Shant Rakshit, Colleague, IIITB
- Mayank Kabra, iMtech, IIIT B
- skywater Foundry
- chatgpt


## References

- https://www.vsdiat.com
- https://github.com/kunalg123/riscv_workshop_collaterals
- https://github.com/SakethGajawada/RISCV-GNU
- https://github.com/The-OpenROAD-Project/OpenSTA.git
- https://how2electronics.com/bidirectional-visitor-counter-with-automatic-light-control-using-arduino
- https://en.wikichip.org/wiki/risc-v/registers
- https://github.com/vinayrayapati/iiitb_rv32i 



