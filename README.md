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
![Screenshot from 2023-10-24 14-22-02](https://github.com/NSampathIIITB/IIITB_Automated_visitor_Counter/assets/141038460/c32649f3-137e-44e9-a825-3a50cbb51bed)
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
                for (int i = 0; i < 3000; i++) {
                    for (int j = 0; j < 100000; j++) {
                        // Adjust the loop count based on your processor's speed
                    }
                }
            }
        }

    return 0;
}


```
## Spike Simulation Result For Functionality Verification

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
        asm volatile(
                    "andi %0, x30, 0x01\n\t"
                    : "=r"(sensor_1)
                    :
                    :
                );
        // Simulated digitalRead for sensor1 and sensor2 (Assuming x30 contains sensor values)
         sensor_1 = 0;
        // sensor_2 = 1;
       
        if (sensor_1 == 0) {
           // while (sensor_2 == 1)
           asm volatile(
                    "andi %0, x30, 0x02\n\t"
                    : "=r"(sensor_2)
                    :
                    :
                ); 
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
                /*for (int i = 0; i < 3000; i++) {
                    for (int j = 0; j < 100000; j++) {
                        // Adjust the loop count based on your processor's speed
                    }
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
   10064:	fe042023          	sw	zero,-32(s0)
   10068:	fc042e23          	sw	zero,-36(s0)
   1006c:	fc042c23          	sw	zero,-40(s0)
   10070:	fc042a23          	sw	zero,-44(s0)
   10074:	fc042823          	sw	zero,-48(s0)
   10078:	fc042623          	sw	zero,-52(s0)
   1007c:	fc042423          	sw	zero,-56(s0)
   10080:	fc042223          	sw	zero,-60(s0)
   10084:	c0300793          	li	a5,-1021
   10088:	fcf42023          	sw	a5,-64(s0)
   1008c:	fe042783          	lw	a5,-32(s0)
   10090:	00279793          	slli	a5,a5,0x2
   10094:	faf42e23          	sw	a5,-68(s0)
   10098:	fdc42783          	lw	a5,-36(s0)
   1009c:	00379793          	slli	a5,a5,0x3
   100a0:	faf42c23          	sw	a5,-72(s0)
   100a4:	fd842783          	lw	a5,-40(s0)
   100a8:	00479793          	slli	a5,a5,0x4
   100ac:	faf42a23          	sw	a5,-76(s0)
   100b0:	fd442783          	lw	a5,-44(s0)
   100b4:	00579793          	slli	a5,a5,0x5
   100b8:	faf42823          	sw	a5,-80(s0)
   100bc:	fd042783          	lw	a5,-48(s0)
   100c0:	00679793          	slli	a5,a5,0x6
   100c4:	faf42623          	sw	a5,-84(s0)
   100c8:	fcc42783          	lw	a5,-52(s0)
   100cc:	00779793          	slli	a5,a5,0x7
   100d0:	faf42423          	sw	a5,-88(s0)
   100d4:	fc842783          	lw	a5,-56(s0)
   100d8:	00879793          	slli	a5,a5,0x8
   100dc:	faf42223          	sw	a5,-92(s0)
   100e0:	fc442783          	lw	a5,-60(s0)
   100e4:	00979793          	slli	a5,a5,0x9
   100e8:	faf42023          	sw	a5,-96(s0)
   100ec:	001f7793          	andi	a5,t5,1
   100f0:	f8f42e23          	sw	a5,-100(s0)
   100f4:	f9c42783          	lw	a5,-100(s0)
   100f8:	fe079ae3          	bnez	a5,100ec <main+0x98>
   100fc:	002f7793          	andi	a5,t5,2
   10100:	f8f42c23          	sw	a5,-104(s0)
   10104:	f9842703          	lw	a4,-104(s0)
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
   10130:	fef42023          	sw	a5,-32(s0)
   10134:	fec42783          	lw	a5,-20(s0)
   10138:	4017d793          	srai	a5,a5,0x1
   1013c:	0017f793          	andi	a5,a5,1
   10140:	fcf42e23          	sw	a5,-36(s0)
   10144:	fec42783          	lw	a5,-20(s0)
   10148:	4027d793          	srai	a5,a5,0x2
   1014c:	0017f793          	andi	a5,a5,1
   10150:	fcf42c23          	sw	a5,-40(s0)
   10154:	fec42783          	lw	a5,-20(s0)
   10158:	4037d793          	srai	a5,a5,0x3
   1015c:	0017f793          	andi	a5,a5,1
   10160:	fcf42a23          	sw	a5,-44(s0)
   10164:	fec42783          	lw	a5,-20(s0)
   10168:	4047d793          	srai	a5,a5,0x4
   1016c:	0017f793          	andi	a5,a5,1
   10170:	fcf42823          	sw	a5,-48(s0)
   10174:	fec42783          	lw	a5,-20(s0)
   10178:	4057d793          	srai	a5,a5,0x5
   1017c:	0017f793          	andi	a5,a5,1
   10180:	fcf42623          	sw	a5,-52(s0)
   10184:	fec42783          	lw	a5,-20(s0)
   10188:	4067d793          	srai	a5,a5,0x6
   1018c:	0017f793          	andi	a5,a5,1
   10190:	fcf42423          	sw	a5,-56(s0)
   10194:	fec42783          	lw	a5,-20(s0)
   10198:	4077d793          	srai	a5,a5,0x7
   1019c:	0017f793          	andi	a5,a5,1
   101a0:	fcf42223          	sw	a5,-60(s0)
   101a4:	fe042783          	lw	a5,-32(s0)
   101a8:	00279793          	slli	a5,a5,0x2
   101ac:	faf42e23          	sw	a5,-68(s0)
   101b0:	fdc42783          	lw	a5,-36(s0)
   101b4:	00379793          	slli	a5,a5,0x3
   101b8:	faf42c23          	sw	a5,-72(s0)
   101bc:	fd842783          	lw	a5,-40(s0)
   101c0:	00479793          	slli	a5,a5,0x4
   101c4:	faf42a23          	sw	a5,-76(s0)
   101c8:	fd442783          	lw	a5,-44(s0)
   101cc:	00579793          	slli	a5,a5,0x5
   101d0:	faf42823          	sw	a5,-80(s0)
   101d4:	fd042783          	lw	a5,-48(s0)
   101d8:	00679793          	slli	a5,a5,0x6
   101dc:	faf42623          	sw	a5,-84(s0)
   101e0:	fcc42783          	lw	a5,-52(s0)
   101e4:	00779793          	slli	a5,a5,0x7
   101e8:	faf42423          	sw	a5,-88(s0)
   101ec:	fc842783          	lw	a5,-56(s0)
   101f0:	00879793          	slli	a5,a5,0x8
   101f4:	faf42223          	sw	a5,-92(s0)
   101f8:	fc442783          	lw	a5,-60(s0)
   101fc:	00979793          	slli	a5,a5,0x9
   10200:	faf42023          	sw	a5,-96(s0)
   10204:	fbc42783          	lw	a5,-68(s0)
   10208:	fb842703          	lw	a4,-72(s0)
   1020c:	fb442683          	lw	a3,-76(s0)
   10210:	fb042603          	lw	a2,-80(s0)
   10214:	fac42583          	lw	a1,-84(s0)
   10218:	fa842503          	lw	a0,-88(s0)
   1021c:	fa442803          	lw	a6,-92(s0)
   10220:	fa042883          	lw	a7,-96(s0)
   10224:	fc042303          	lw	t1,-64(s0)
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
   10258:	0340006f          	j	1028c <main+0x238>
   1025c:	fe042223          	sw	zero,-28(s0)
   10260:	0100006f          	j	10270 <main+0x21c>
   10264:	fe442783          	lw	a5,-28(s0)
   10268:	00178793          	addi	a5,a5,1
   1026c:	fef42223          	sw	a5,-28(s0)
   10270:	fe442703          	lw	a4,-28(s0)
   10274:	000187b7          	lui	a5,0x18
   10278:	69f78793          	addi	a5,a5,1695 # 1869f <__global_pointer$+0x6bff>
   1027c:	fee7d4e3          	bge	a5,a4,10264 <main+0x210>
   10280:	fe842783          	lw	a5,-24(s0)
   10284:	00178793          	addi	a5,a5,1
   10288:	fef42423          	sw	a5,-24(s0)
   1028c:	fe842703          	lw	a4,-24(s0)
   10290:	000017b7          	lui	a5,0x1
   10294:	bb778793          	addi	a5,a5,-1097 # bb7 <main-0xf49d>
   10298:	fce7d2e3          	bge	a5,a4,1025c <main+0x208>
   1029c:	e51ff06f          	j	100ec <main+0x98>


```

## Specific Instructions

```
Number of different instructions: 15
List of unique instructions:
bge
and
or
sw
li
andi
slli
blt
beq
j
lw
bnez
lui
addi
srai

```
![Screenshot from 2023-10-25 16-15-40](https://github.com/NSampathIIITB/IIITB_Automated_visitor_Counter/assets/141038460/1ecce641-2792-4949-8571-43a2f2348186)

## Acknowledgement

- Kunal Ghosh, VSD Corp. Pvt. Ltd.
- Alwin shaju,Colleague,IIIT B
- Kanish R,Colleague,IIIT B
- Emil Jayanth Lal, Colleague, IIITB
- Shant Rakshit, Colleague, IIITB
- Mayank Kabra , IIIT B
- skywater Foundry
- chatgpt


## References

- https://www.vsdiat.com
- https://github.com/kunalg123/riscv_workshop_collaterals
- https://github.com/SakethGajawada/RISCV-GNU
- https://github.com/The-OpenROAD-Project/OpenSTA.git
- https://github.com/bhargav-vlsi
- https://how2electronics.com/bidirectional-visitor-counter-with-automatic-light-control-using-arduino 



