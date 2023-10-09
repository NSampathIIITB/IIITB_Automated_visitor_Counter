# IIITB_Automated_visitor_Counter_using_RISC-V

This github repository summarizes the progress made in the ASIC class regarding the RISC-V project.

## Aim
The aim of the project is to measure and display the number of persons entering in any room like seminar hall, conference room etc. LCD displays number ofpersons inside the room. We can use this project to count and display the number of visitors entering inside any conference room or seminar hall. This works in atwo way. That means counter will be incremented if person enters the room and will be decremented if a person leaves the room. This design is made utilising a specialized RISC-V 32_bit processor.

## RISC-V 32 Bit Compiler Installation

```
sudo apt install libc6-dev
git clone https://github.com/riscv/riscv-gnu-toolchain --recursive
mkdir riscv32-toolchain
cd riscv-gnu-toolchain
./configure --prefix=/home/bhargav/riscv32-toolchain/ --with-arch=rv32i --with-abi=ilp32
sudo apt-get install libgmp-dev
make

```
**Path to access the riscv32-unknown-elf-gcc**

```
/home/nsaisampath/riscv32-toolchain/bin/riscv32-unknown-elf-gcc
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

 In the same way, when a visitor leaves through the exit gate the IR sensor-2 detects the visitor (obstacle) and produces a Low (0) output value from the Output Pin. Then the processor read this value and counts 1- using the code. Similarly, When the IR sensor-2 detects another visitor (obstacle), the processor increment the counting by 11. In this way every time the processor adds +1 in the count when a visitor passes through this exit gate.

## Circuit

The below shown is an assumed circuit not entirely accurate.

![Screenshot-2022-12-25-at-12 51 02-AM-800x485](https://github.com/NSampathIIITB/IIITB_Automated_visitor_Counter/assets/141038460/316859d7-8cd1-4bbb-ae98-e8f450f13930)

## Block Diagram

![Screenshot from 2023-10-09 15-37-31](https://github.com/NSampathIIITB/IIITB_Automated_visitor_Counter/assets/141038460/a5e9a99a-c6d7-4339-99a0-1014e52e67e9)

## Testing

1. Open a terminal window.
2. Navigate to the directory containing the sample.c file.
3. Design a function that executes the intended logic you require.
4. Compile the code using the GCC compiler and verify the output:
   
  
```
gcc automated_visitor_counter.c
./a.out
```
![Screenshot from 2023-10-04 15-39-04](https://github.com/NSampathIIITB/IIITB_Automated_visitor_Counter/assets/141038460/fcff0780-420d-4625-b835-3292a59218e9)

## C Program
```
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
    while (1)
    {
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


```

## Assembly Code

### Assembly Code Generation

```
/home/nsaisampath/riscv32-toolchain/bin/riscv32-unknown-elf-gcc -mabi=ilp32 -march=rv32i -ffreestanding -nostdlib -o ./out automated_visitor_counter.c

```

```
/home/nsaisampath/riscv32-toolchain/bin/riscv32-unknown-elf-objdump -d -r out > automated_visitor_counter.txt
```


```
out:     file format elf32-littleriscv


Disassembly of section .text:

00010094 <main>:
   10094:	ff010113          	add	sp,sp,-16
   10098:	00112623          	sw	ra,12(sp)
   1009c:	00812423          	sw	s0,8(sp)
   100a0:	01010413          	add	s0,sp,16
   100a4:	001f7693          	and	a3,t5,1
   100a8:	002f7693          	and	a3,t5,2
   100ac:	000117b7          	lui	a5,0x11
   100b0:	26d7a023          	sw	a3,608(a5) # 11260 <__DATA_BEGIN__>
   100b4:	000117b7          	lui	a5,0x11
   100b8:	26e7a223          	sw	a4,612(a5) # 11264 <sensor_2>
   100bc:	002f7713          	and	a4,t5,2
   100c0:	000117b7          	lui	a5,0x11
   100c4:	26e7a223          	sw	a4,612(a5) # 11264 <sensor_2>
   100c8:	000117b7          	lui	a5,0x11
   100cc:	2607a783          	lw	a5,608(a5) # 11260 <__DATA_BEGIN__>
   100d0:	fc079ae3          	bnez	a5,100a4 <main+0x10>
   100d4:	0100006f          	j	100e4 <main+0x50>
   100d8:	002f7713          	and	a4,t5,2
   100dc:	000117b7          	lui	a5,0x11
   100e0:	26e7a223          	sw	a4,612(a5) # 11264 <sensor_2>
   100e4:	000117b7          	lui	a5,0x11
   100e8:	2647a703          	lw	a4,612(a5) # 11264 <sensor_2>
   100ec:	00100793          	li	a5,1
   100f0:	fef704e3          	beq	a4,a5,100d8 <main+0x44>
   100f4:	8081a783          	lw	a5,-2040(gp) # 11268 <total_people>
   100f8:	00178713          	add	a4,a5,1
   100fc:	80e1a423          	sw	a4,-2040(gp) # 11268 <total_people>
   10100:	010000ef          	jal	10110 <displaytotalpeople>
   10104:	12c00513          	li	a0,300
   10108:	0f0000ef          	jal	101f8 <delay>
   1010c:	f99ff06f          	j	100a4 <main+0x10>

00010110 <displaytotalpeople>:
   10110:	fe010113          	add	sp,sp,-32
   10114:	00812e23          	sw	s0,28(sp)
   10118:	02010413          	add	s0,sp,32
   1011c:	fe042623          	sw	zero,-20(s0)
   10120:	fe042423          	sw	zero,-24(s0)
   10124:	fec42783          	lw	a5,-20(s0)
   10128:	00179793          	sll	a5,a5,0x1
   1012c:	fef42223          	sw	a5,-28(s0)
   10130:	fe842783          	lw	a5,-24(s0)
   10134:	00279793          	sll	a5,a5,0x2
   10138:	fef42023          	sw	a5,-32(s0)
   1013c:	fe442783          	lw	a5,-28(s0)
   10140:	fe042703          	lw	a4,-32(s0)
   10144:	00ff6f33          	or	t5,t5,a5
   10148:	00ef6f33          	or	t5,t5,a4
   1014c:	8081a703          	lw	a4,-2040(gp) # 11268 <total_people>
   10150:	00100793          	li	a5,1
   10154:	02f71263          	bne	a4,a5,10178 <displaytotalpeople+0x68>
   10158:	00100793          	li	a5,1
   1015c:	fef42623          	sw	a5,-20(s0)
   10160:	fe442783          	lw	a5,-28(s0)
   10164:	00179793          	sll	a5,a5,0x1
   10168:	fef42623          	sw	a5,-20(s0)
   1016c:	fe442783          	lw	a5,-28(s0)
   10170:	00ff6f33          	or	t5,t5,a5
   10174:	0740006f          	j	101e8 <displaytotalpeople+0xd8>
   10178:	8081a703          	lw	a4,-2040(gp) # 11268 <total_people>
   1017c:	00200793          	li	a5,2
   10180:	02f71263          	bne	a4,a5,101a4 <displaytotalpeople+0x94>
   10184:	00100793          	li	a5,1
   10188:	fef42423          	sw	a5,-24(s0)
   1018c:	fe042783          	lw	a5,-32(s0)
   10190:	00179793          	sll	a5,a5,0x1
   10194:	fef42423          	sw	a5,-24(s0)
   10198:	fe042783          	lw	a5,-32(s0)
   1019c:	00ff6f33          	or	t5,t5,a5
   101a0:	0480006f          	j	101e8 <displaytotalpeople+0xd8>
   101a4:	8081a703          	lw	a4,-2040(gp) # 11268 <total_people>
   101a8:	00200793          	li	a5,2
   101ac:	02e7de63          	bge	a5,a4,101e8 <displaytotalpeople+0xd8>
   101b0:	00100793          	li	a5,1
   101b4:	fef42623          	sw	a5,-20(s0)
   101b8:	00100793          	li	a5,1
   101bc:	fef42423          	sw	a5,-24(s0)
   101c0:	fec42783          	lw	a5,-20(s0)
   101c4:	00179793          	sll	a5,a5,0x1
   101c8:	fef42223          	sw	a5,-28(s0)
   101cc:	fe842783          	lw	a5,-24(s0)
   101d0:	00279793          	sll	a5,a5,0x2
   101d4:	fef42023          	sw	a5,-32(s0)
   101d8:	fe442783          	lw	a5,-28(s0)
   101dc:	fe042703          	lw	a4,-32(s0)
   101e0:	00ff6f33          	or	t5,t5,a5
   101e4:	00ef6f33          	or	t5,t5,a4
   101e8:	00000013          	nop
   101ec:	01c12403          	lw	s0,28(sp)
   101f0:	02010113          	add	sp,sp,32
   101f4:	00008067          	ret

000101f8 <delay>:
   101f8:	fd010113          	add	sp,sp,-48
   101fc:	02812623          	sw	s0,44(sp)
   10200:	03010413          	add	s0,sp,48
   10204:	fca42e23          	sw	a0,-36(s0)
   10208:	fe042623          	sw	zero,-20(s0)
   1020c:	0340006f          	j	10240 <delay+0x48>
   10210:	fe042423          	sw	zero,-24(s0)
   10214:	0100006f          	j	10224 <delay+0x2c>
   10218:	fe842783          	lw	a5,-24(s0)
   1021c:	00178793          	add	a5,a5,1
   10220:	fef42423          	sw	a5,-24(s0)
   10224:	fe842703          	lw	a4,-24(s0)
   10228:	000027b7          	lui	a5,0x2
   1022c:	70f78793          	add	a5,a5,1807 # 270f <main-0xd985>
   10230:	fee7d4e3          	bge	a5,a4,10218 <delay+0x20>
   10234:	fec42783          	lw	a5,-20(s0)
   10238:	00178793          	add	a5,a5,1
   1023c:	fef42623          	sw	a5,-20(s0)
   10240:	fec42703          	lw	a4,-20(s0)
   10244:	fdc42783          	lw	a5,-36(s0)
   10248:	fcf744e3          	blt	a4,a5,10210 <delay+0x18>
   1024c:	00000013          	nop
   10250:	00000013          	nop
   10254:	02c12403          	lw	s0,44(sp)
   10258:	03010113          	add	sp,sp,48
   1025c:	00008067          	ret
```

## Specific Instructions

```
Number of different instructions: 17
List of unique instructions:
bnez
bne
sll
and
j
li
add
lui
beq
blt
lw
ret
nop
bge
sw
or
jal

```

## Acknowledgement

- Kunal Ghosh, VSD Corp. Pvt. Ltd.
- Alwin shaju,Colleague,IIIT B
- Kanish R,Colleague,IIIT B
- Emil Jayanth Lal, Colleague, IIITB
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



