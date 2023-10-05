# IIITB_Automated_visitor_Counter_using_RISC-V

This github repository summarizes the progress made in the ASIC class regarding the RISC-V project.

## Aim
The aim of the project is to measure and display the number of persons entering in any room like seminar hall, conference room etc. LCD displays number ofpersons inside the room. We can use this project to count and display the number of visitors entering inside any conference room or seminar hall. This works in atwo way. That means counter will be incremented if person enters the room and will be decremented if a person leaves the room. This design is made utilising a specialized RISC-V processor.

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

![Screenshot from 2023-10-04 15-21-12](https://github.com/NSampathIIITB/IIITB_Automated_visitor_Counter/assets/141038460/b6babf88-66ec-4dd2-8960-3c7f102caadd)

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

## C Code
```
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

```

## Assembly Code

### Assembly Code Generation
```
/home/nsaisampath/riscv32-toolchain/bin/riscv32-unknown-elf-gcc -c -mabi=ilp32 -march=rv32im -ffreestanding -o Automated_Visitor_Counter.o automated_visitor_counter.c

```

```
/home/nsaisampath/riscv32-toolchain/bin/riscv32-unknown-elf-objdump -d automated_visitor_counter.o > acv.txt

```

```
automated_visitor_counter.o:     file format elf32-littleriscv


Disassembly of section .text:

00000000 <main>:
   0:	ff010113          	add	sp,sp,-16
   4:	00112623          	sw	ra,12(sp)
   8:	00812423          	sw	s0,8(sp)
   c:	01010413          	add	s0,sp,16
  10:	00000097          	auipc	ra,0x0
  14:	000080e7          	jalr	ra # 10 <main+0x10>
  18:	00000793          	li	a5,0
  1c:	00078513          	mv	a0,a5
  20:	00c12083          	lw	ra,12(sp)
  24:	00812403          	lw	s0,8(sp)
  28:	01010113          	add	sp,sp,16
  2c:	00008067          	ret

00000030 <readpinvalues>:
  30:	ff010113          	add	sp,sp,-16
  34:	00112623          	sw	ra,12(sp)
  38:	00812423          	sw	s0,8(sp)
  3c:	01010413          	add	s0,sp,16

00000040 <.L7>:
  40:	001f7713          	and	a4,t5,1
  44:	000007b7          	lui	a5,0x0
  48:	00e7a023          	sw	a4,0(a5) # 0 <main>
  4c:	002f7713          	and	a4,t5,2
  50:	000007b7          	lui	a5,0x0
  54:	00e7a023          	sw	a4,0(a5) # 0 <main>
  58:	000007b7          	lui	a5,0x0
  5c:	0007a783          	lw	a5,0(a5) # 0 <main>
  60:	fe0790e3          	bnez	a5,40 <.L7>
  64:	0100006f          	j	74 <.L5>

00000068 <.L6>:
  68:	002f7713          	and	a4,t5,2
  6c:	000007b7          	lui	a5,0x0
  70:	00e7a023          	sw	a4,0(a5) # 0 <main>

00000074 <.L5>:
  74:	000007b7          	lui	a5,0x0
  78:	0007a703          	lw	a4,0(a5) # 0 <main>
  7c:	00100793          	li	a5,1
  80:	fef704e3          	beq	a4,a5,68 <.L6>
  84:	000007b7          	lui	a5,0x0
  88:	0007a783          	lw	a5,0(a5) # 0 <main>
  8c:	00178713          	add	a4,a5,1
  90:	000007b7          	lui	a5,0x0
  94:	00e7a023          	sw	a4,0(a5) # 0 <main>
  98:	12c00513          	li	a0,300
  9c:	00000097          	auipc	ra,0x0
  a0:	000080e7          	jalr	ra # 9c <.L5+0x28>
  a4:	f9dff06f          	j	40 <.L7>

000000a8 <delay>:
  a8:	fd010113          	add	sp,sp,-48
  ac:	02812623          	sw	s0,44(sp)
  b0:	03010413          	add	s0,sp,48
  b4:	fca42e23          	sw	a0,-36(s0)
  b8:	fe042623          	sw	zero,-20(s0)
  bc:	0340006f          	j	f0 <.L9>

000000c0 <.L12>:
  c0:	fe042423          	sw	zero,-24(s0)
  c4:	0100006f          	j	d4 <.L10>

000000c8 <.L11>:
  c8:	fe842783          	lw	a5,-24(s0)
  cc:	00178793          	add	a5,a5,1
  d0:	fef42423          	sw	a5,-24(s0)

000000d4 <.L10>:
  d4:	fe842703          	lw	a4,-24(s0)
  d8:	000027b7          	lui	a5,0x2
  dc:	70f78793          	add	a5,a5,1807 # 270f <.L9+0x261f>
  e0:	fee7d4e3          	bge	a5,a4,c8 <.L11>
  e4:	fec42783          	lw	a5,-20(s0)
  e8:	00178793          	add	a5,a5,1
  ec:	fef42623          	sw	a5,-20(s0)

000000f0 <.L9>:
  f0:	fec42703          	lw	a4,-20(s0)
  f4:	fdc42783          	lw	a5,-36(s0)
  f8:	fcf744e3          	blt	a4,a5,c0 <.L12>
  fc:	00000013          	nop
 100:	00000013          	nop
 104:	02c12403          	lw	s0,44(sp)
 108:	03010113          	add	sp,sp,48
 10c:	00008067          	ret
```

## Specific Instructions
```
Number of different instructions: 16
List of unique instructions:
ret
jalr
li
j
lw
nop
and
mv
bge
lui
blt
beq
sw
add
bnez
auipc
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
- https://how2electronics.com/bidirectional-visitor-counter-with-automatic-light-control-using-arduino 



