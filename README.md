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
                }
            }
        }
    }

    return 0;
}

```
## Spike Simulation Result For Functionality Verification

I have done the spike simulatiion using *avcspike.c* which was mentioned above

```
riscv64-unknown-elf-gcc -march=rv64i -mabi=lp64 -ffreestanding -o out avcspike.c
```
```
spike pk out
```
![Screenshot from 2023-10-24 23-39-19](https://github.com/NSampathIIITB/IIITB_Automated_visitor_Counter/assets/141038460/4ce8623b-fc74-4743-979c-85866f63a793)

Here after when sensor_1=0  detects the person, we are checking the detection of person at sensor_2 ,when the sensor_2=1 it means the person is about to enter the room and the total_people value gets incremented and we will observe the sensor2=0 when the person completely enters inside the room and we will get the binary value of total_people value in LED's.

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
   10054:	fb010113          	addi	sp,sp,-80
   10058:	04812623          	sw	s0,76(sp)
   1005c:	05010413          	addi	s0,sp,80
   10060:	fe042623          	sw	zero,-20(s0)
   10064:	fc042e23          	sw	zero,-36(s0)
   10068:	fc042c23          	sw	zero,-40(s0)
   1006c:	fc042a23          	sw	zero,-44(s0)
   10070:	fc042823          	sw	zero,-48(s0)
   10074:	fc042623          	sw	zero,-52(s0)
   10078:	f8300793          	li	a5,-125
   1007c:	fcf42423          	sw	a5,-56(s0)
   10080:	fdc42783          	lw	a5,-36(s0)
   10084:	00279793          	slli	a5,a5,0x2
   10088:	fcf42223          	sw	a5,-60(s0)
   1008c:	fd842783          	lw	a5,-40(s0)
   10090:	00379793          	slli	a5,a5,0x3
   10094:	fcf42023          	sw	a5,-64(s0)
   10098:	fd442783          	lw	a5,-44(s0)
   1009c:	00479793          	slli	a5,a5,0x4
   100a0:	faf42e23          	sw	a5,-68(s0)
   100a4:	fd042783          	lw	a5,-48(s0)
   100a8:	00579793          	slli	a5,a5,0x5
   100ac:	faf42c23          	sw	a5,-72(s0)
   100b0:	fcc42783          	lw	a5,-52(s0)
   100b4:	00679793          	slli	a5,a5,0x6
   100b8:	faf42a23          	sw	a5,-76(s0)
   100bc:	001f7793          	andi	a5,t5,1
   100c0:	faf42823          	sw	a5,-80(s0)
   100c4:	fb042783          	lw	a5,-80(s0)
   100c8:	fe079ae3          	bnez	a5,100bc <main+0x68>
   100cc:	1240006f          	j	101f0 <main+0x19c>
   100d0:	002f7793          	andi	a5,t5,2
   100d4:	fef42423          	sw	a5,-24(s0)
   100d8:	fec42783          	lw	a5,-20(s0)
   100dc:	00178793          	addi	a5,a5,1
   100e0:	fef42623          	sw	a5,-20(s0)
   100e4:	fec42703          	lw	a4,-20(s0)
   100e8:	01f00793          	li	a5,31
   100ec:	0ae7ce63          	blt	a5,a4,101a8 <main+0x154>
   100f0:	fec42783          	lw	a5,-20(s0)
   100f4:	0017f793          	andi	a5,a5,1
   100f8:	fcf42e23          	sw	a5,-36(s0)
   100fc:	fec42783          	lw	a5,-20(s0)
   10100:	4017d793          	srai	a5,a5,0x1
   10104:	0017f793          	andi	a5,a5,1
   10108:	fcf42c23          	sw	a5,-40(s0)
   1010c:	fec42783          	lw	a5,-20(s0)
   10110:	4027d793          	srai	a5,a5,0x2
   10114:	0017f793          	andi	a5,a5,1
   10118:	fcf42a23          	sw	a5,-44(s0)
   1011c:	fec42783          	lw	a5,-20(s0)
   10120:	4037d793          	srai	a5,a5,0x3
   10124:	0017f793          	andi	a5,a5,1
   10128:	fcf42823          	sw	a5,-48(s0)
   1012c:	fec42783          	lw	a5,-20(s0)
   10130:	4047d793          	srai	a5,a5,0x4
   10134:	0017f793          	andi	a5,a5,1
   10138:	fcf42623          	sw	a5,-52(s0)
   1013c:	fdc42783          	lw	a5,-36(s0)
   10140:	00279793          	slli	a5,a5,0x2
   10144:	fcf42223          	sw	a5,-60(s0)
   10148:	fd842783          	lw	a5,-40(s0)
   1014c:	00379793          	slli	a5,a5,0x3
   10150:	fcf42023          	sw	a5,-64(s0)
   10154:	fd442783          	lw	a5,-44(s0)
   10158:	00479793          	slli	a5,a5,0x4
   1015c:	faf42e23          	sw	a5,-68(s0)
   10160:	fd042783          	lw	a5,-48(s0)
   10164:	00579793          	slli	a5,a5,0x5
   10168:	faf42c23          	sw	a5,-72(s0)
   1016c:	fcc42783          	lw	a5,-52(s0)
   10170:	00679793          	slli	a5,a5,0x6
   10174:	faf42a23          	sw	a5,-76(s0)
   10178:	fc442783          	lw	a5,-60(s0)
   1017c:	fc042703          	lw	a4,-64(s0)
   10180:	fbc42683          	lw	a3,-68(s0)
   10184:	fb842603          	lw	a2,-72(s0)
   10188:	fb442583          	lw	a1,-76(s0)
   1018c:	fc842503          	lw	a0,-56(s0)
   10190:	00af7f33          	and	t5,t5,a0
   10194:	00ff6f33          	or	t5,t5,a5
   10198:	00ef6f33          	or	t5,t5,a4
   1019c:	00df6f33          	or	t5,t5,a3
   101a0:	00cf6f33          	or	t5,t5,a2
   101a4:	00bf6f33          	or	t5,t5,a1
   101a8:	fe042223          	sw	zero,-28(s0)
   101ac:	0340006f          	j	101e0 <main+0x18c>
   101b0:	fe042023          	sw	zero,-32(s0)
   101b4:	0100006f          	j	101c4 <main+0x170>
   101b8:	fe042783          	lw	a5,-32(s0)
   101bc:	00178793          	addi	a5,a5,1
   101c0:	fef42023          	sw	a5,-32(s0)
   101c4:	fe042703          	lw	a4,-32(s0)
   101c8:	000f47b7          	lui	a5,0xf4
   101cc:	23f78793          	addi	a5,a5,575 # f423f <__global_pointer$+0xe283f>
   101d0:	fee7d4e3          	bge	a5,a4,101b8 <main+0x164>
   101d4:	fe442783          	lw	a5,-28(s0)
   101d8:	00178793          	addi	a5,a5,1
   101dc:	fef42223          	sw	a5,-28(s0)
   101e0:	fe442703          	lw	a4,-28(s0)
   101e4:	000017b7          	lui	a5,0x1
   101e8:	bb778793          	addi	a5,a5,-1097 # bb7 <main-0xf49d>
   101ec:	fce7d2e3          	bge	a5,a4,101b0 <main+0x15c>
   101f0:	fe842703          	lw	a4,-24(s0)
   101f4:	00100793          	li	a5,1
   101f8:	ecf70ce3          	beq	a4,a5,100d0 <main+0x7c>
   101fc:	ec1ff06f          	j	100bc <main+0x68>


```

## Specific Instructions

```
Number of different instructions: 15
List of unique instructions:
andi
bnez
blt
lui
li
or
sw
srai
j
addi
slli
beq
bge
and
lw

```
![Screenshot from 2023-10-24 23-51-31](https://github.com/NSampathIIITB/IIITB_Automated_visitor_Counter/assets/141038460/a27d2b08-f553-4631-8b50-21cf3fdf234e)

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



