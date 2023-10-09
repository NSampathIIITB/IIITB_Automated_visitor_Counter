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
![Screenshot from 2023-10-04 15-39-04](https://github.com/NSampathIIITB/IIITB_Automated_visitor_Counter/assets/141038460/fcff0780-420d-4625-b835-3292a59218e9)

## C Program
```
void displaytotalpeople();
void delay(int);
int sensor_1 = 0;
int sensor_2 = 0;
int total_people = 0;


int main()
{
    
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
            //show();
            displaytotalpeople();
            delay(300); // Delay for 300 milliseconds
        }
       
    }
    return 0;
}

void displaytotalpeople()
{
      int ledpin[5],i,j,ledpin_reg[5];
      for(i=1; total_people > 0;i++)
      {
      ledpin[i] = total_people % 2;
      total_people = total_people / 2;
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
      
}


void delay(int milliseconds) {
    for (int i = 0; i < milliseconds; i++) {
        for (volatile int j = 0; j < 10000; j++) {
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
   100b0:	24d7aa23          	sw	a3,596(a5) # 11254 <__DATA_BEGIN__>
   100b4:	000117b7          	lui	a5,0x11
   100b8:	24e7ac23          	sw	a4,600(a5) # 11258 <sensor_2>
   100bc:	000117b7          	lui	a5,0x11
   100c0:	2547a783          	lw	a5,596(a5) # 11254 <__DATA_BEGIN__>
   100c4:	fe0790e3          	bnez	a5,100a4 <main+0x10>
   100c8:	0100006f          	j	100d8 <main+0x44>
   100cc:	002f7713          	and	a4,t5,2
   100d0:	000117b7          	lui	a5,0x11
   100d4:	24e7ac23          	sw	a4,600(a5) # 11258 <sensor_2>
   100d8:	000117b7          	lui	a5,0x11
   100dc:	2587a703          	lw	a4,600(a5) # 11258 <sensor_2>
   100e0:	00100793          	li	a5,1
   100e4:	fef704e3          	beq	a4,a5,100cc <main+0x38>
   100e8:	8081a783          	lw	a5,-2040(gp) # 1125c <total_people>
   100ec:	00178713          	add	a4,a5,1
   100f0:	80e1a423          	sw	a4,-2040(gp) # 1125c <total_people>
   100f4:	010000ef          	jal	10104 <displaytotalpeople>
   100f8:	12c00513          	li	a0,300
   100fc:	0f0000ef          	jal	101ec <delay>
   10100:	fa5ff06f          	j	100a4 <main+0x10>

00010104 <displaytotalpeople>:
   10104:	fc010113          	add	sp,sp,-64
   10108:	02812e23          	sw	s0,60(sp)
   1010c:	04010413          	add	s0,sp,64
   10110:	00100793          	li	a5,1
   10114:	fef42623          	sw	a5,-20(s0)
   10118:	0580006f          	j	10170 <displaytotalpeople+0x6c>
   1011c:	8081a703          	lw	a4,-2040(gp) # 1125c <total_people>
   10120:	41f75793          	sra	a5,a4,0x1f
   10124:	01f7d793          	srl	a5,a5,0x1f
   10128:	00f70733          	add	a4,a4,a5
   1012c:	00177713          	and	a4,a4,1
   10130:	40f707b3          	sub	a5,a4,a5
   10134:	00078713          	mv	a4,a5
   10138:	fec42783          	lw	a5,-20(s0)
   1013c:	00279793          	sll	a5,a5,0x2
   10140:	ff078793          	add	a5,a5,-16
   10144:	008787b3          	add	a5,a5,s0
   10148:	fee7a423          	sw	a4,-24(a5)
   1014c:	8081a783          	lw	a5,-2040(gp) # 1125c <total_people>
   10150:	01f7d713          	srl	a4,a5,0x1f
   10154:	00f707b3          	add	a5,a4,a5
   10158:	4017d793          	sra	a5,a5,0x1
   1015c:	00078713          	mv	a4,a5
   10160:	80e1a423          	sw	a4,-2040(gp) # 1125c <total_people>
   10164:	fec42783          	lw	a5,-20(s0)
   10168:	00178793          	add	a5,a5,1
   1016c:	fef42623          	sw	a5,-20(s0)
   10170:	8081a783          	lw	a5,-2040(gp) # 1125c <total_people>
   10174:	faf044e3          	bgtz	a5,1011c <displaytotalpeople+0x18>
   10178:	fdc42783          	lw	a5,-36(s0)
   1017c:	00179793          	sll	a5,a5,0x1
   10180:	fcf42423          	sw	a5,-56(s0)
   10184:	fe042783          	lw	a5,-32(s0)
   10188:	00279793          	sll	a5,a5,0x2
   1018c:	fcf42623          	sw	a5,-52(s0)
   10190:	fe442783          	lw	a5,-28(s0)
   10194:	00379793          	sll	a5,a5,0x3
   10198:	fcf42823          	sw	a5,-48(s0)
   1019c:	fe842783          	lw	a5,-24(s0)
   101a0:	00479793          	sll	a5,a5,0x4
   101a4:	fcf42a23          	sw	a5,-44(s0)
   101a8:	fec42783          	lw	a5,-20(s0)
   101ac:	00579793          	sll	a5,a5,0x5
   101b0:	fcf42c23          	sw	a5,-40(s0)
   101b4:	fc842783          	lw	a5,-56(s0)
   101b8:	fcc42703          	lw	a4,-52(s0)
   101bc:	fd042683          	lw	a3,-48(s0)
   101c0:	fd442603          	lw	a2,-44(s0)
   101c4:	fd842583          	lw	a1,-40(s0)
   101c8:	00ff6f33          	or	t5,t5,a5
   101cc:	00ef6f33          	or	t5,t5,a4
   101d0:	00df6f33          	or	t5,t5,a3
   101d4:	00cf6f33          	or	t5,t5,a2
   101d8:	00bf6f33          	or	t5,t5,a1
   101dc:	00000013          	nop
   101e0:	03c12403          	lw	s0,60(sp)
   101e4:	04010113          	add	sp,sp,64
   101e8:	00008067          	ret

000101ec <delay>:
   101ec:	fd010113          	add	sp,sp,-48
   101f0:	02812623          	sw	s0,44(sp)
   101f4:	03010413          	add	s0,sp,48
   101f8:	fca42e23          	sw	a0,-36(s0)
   101fc:	fe042623          	sw	zero,-20(s0)
   10200:	0340006f          	j	10234 <delay+0x48>
   10204:	fe042423          	sw	zero,-24(s0)
   10208:	0100006f          	j	10218 <delay+0x2c>
   1020c:	fe842783          	lw	a5,-24(s0)
   10210:	00178793          	add	a5,a5,1
   10214:	fef42423          	sw	a5,-24(s0)
   10218:	fe842703          	lw	a4,-24(s0)
   1021c:	000027b7          	lui	a5,0x2
   10220:	70f78793          	add	a5,a5,1807 # 270f <main-0xd985>
   10224:	fee7d4e3          	bge	a5,a4,1020c <delay+0x20>
   10228:	fec42783          	lw	a5,-20(s0)
   1022c:	00178793          	add	a5,a5,1
   10230:	fef42623          	sw	a5,-20(s0)
   10234:	fec42703          	lw	a4,-20(s0)
   10238:	fdc42783          	lw	a5,-36(s0)
   1023c:	fcf744e3          	blt	a4,a5,10204 <delay+0x18>
   10240:	00000013          	nop
   10244:	00000013          	nop
   10248:	02c12403          	lw	s0,44(sp)
   1024c:	03010113          	add	sp,sp,48
   10250:	00008067          	ret


```

## Specific Instructions

```
Number of different instructions: 21
List of unique instructions:
mv
bge
beq
sw
j
li
and
srl
sll
or
ret
bgtz
add
bnez
sub
jal
sra
lui
lw
blt
nop


```
![Screenshot from 2023-10-09 18-35-31](https://github.com/NSampathIIITB/IIITB_Automated_visitor_Counter/assets/141038460/66fb425f-0e0d-4ec4-9670-c6ffd7c3b306)

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



