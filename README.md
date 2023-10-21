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
![Screenshot from 2023-10-04 15-39-04](https://github.com/NSampathIIITB/IIITB_Automated_visitor_Counter/assets/141038460/fcff0780-420d-4625-b835-3292a59218e9)

## C Program
```
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
           
           for (int i = 0; i < 3000; i++) {
        	for ( int j = 0; j < 1000000; j++) {
            // Adjust the loop count based on your processor's speed
        }
    }
           
        }
       
    }
    return 0;
}


```

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
   10060:	fc042c23          	sw	zero,-40(s0)
   10064:	fe042623          	sw	zero,-20(s0)
   10068:	fe042423          	sw	zero,-24(s0)
   1006c:	001f7713          	andi	a4,t5,1
   10070:	002f7713          	andi	a4,t5,2
   10074:	fce42c23          	sw	a4,-40(s0)
   10078:	fef42623          	sw	a5,-20(s0)
   1007c:	fd842783          	lw	a5,-40(s0)
   10080:	fe0796e3          	bnez	a5,1006c <main+0x18>
   10084:	00c0006f          	j	10090 <main+0x3c>
   10088:	002f7793          	andi	a5,t5,2
   1008c:	fef42623          	sw	a5,-20(s0)
   10090:	fec42703          	lw	a4,-20(s0)
   10094:	00100793          	li	a5,1
   10098:	fef708e3          	beq	a4,a5,10088 <main+0x34>
   1009c:	fe842783          	lw	a5,-24(s0)
   100a0:	00178793          	addi	a5,a5,1
   100a4:	fef42423          	sw	a5,-24(s0)
   100a8:	fe842703          	lw	a4,-24(s0)
   100ac:	01f00793          	li	a5,31
   100b0:	06e7c463          	blt	a5,a4,10118 <main+0xc4>
   100b4:	00100793          	li	a5,1
   100b8:	fef42223          	sw	a5,-28(s0)
   100bc:	0540006f          	j	10110 <main+0xbc>
   100c0:	fe842703          	lw	a4,-24(s0)
   100c4:	41f75793          	srai	a5,a4,0x1f
   100c8:	01f7d793          	srli	a5,a5,0x1f
   100cc:	00f70733          	add	a4,a4,a5
   100d0:	00177713          	andi	a4,a4,1
   100d4:	40f707b3          	sub	a5,a4,a5
   100d8:	00078713          	mv	a4,a5
   100dc:	fe442783          	lw	a5,-28(s0)
   100e0:	00279793          	slli	a5,a5,0x2
   100e4:	ff040693          	addi	a3,s0,-16
   100e8:	00f687b3          	add	a5,a3,a5
   100ec:	fce7aa23          	sw	a4,-44(a5)
   100f0:	fe842783          	lw	a5,-24(s0)
   100f4:	01f7d713          	srli	a4,a5,0x1f
   100f8:	00f707b3          	add	a5,a4,a5
   100fc:	4017d793          	srai	a5,a5,0x1
   10100:	fef42423          	sw	a5,-24(s0)
   10104:	fe442783          	lw	a5,-28(s0)
   10108:	00178793          	addi	a5,a5,1
   1010c:	fef42223          	sw	a5,-28(s0)
   10110:	fe842783          	lw	a5,-24(s0)
   10114:	faf046e3          	bgtz	a5,100c0 <main+0x6c>
   10118:	fc842783          	lw	a5,-56(s0)
   1011c:	00179793          	slli	a5,a5,0x1
   10120:	faf42a23          	sw	a5,-76(s0)
   10124:	fcc42783          	lw	a5,-52(s0)
   10128:	00279793          	slli	a5,a5,0x2
   1012c:	faf42c23          	sw	a5,-72(s0)
   10130:	fd042783          	lw	a5,-48(s0)
   10134:	00379793          	slli	a5,a5,0x3
   10138:	faf42e23          	sw	a5,-68(s0)
   1013c:	fd442783          	lw	a5,-44(s0)
   10140:	00479793          	slli	a5,a5,0x4
   10144:	fcf42023          	sw	a5,-64(s0)
   10148:	fd842783          	lw	a5,-40(s0)
   1014c:	00579793          	slli	a5,a5,0x5
   10150:	fcf42223          	sw	a5,-60(s0)
   10154:	fb442783          	lw	a5,-76(s0)
   10158:	fb842703          	lw	a4,-72(s0)
   1015c:	fbc42683          	lw	a3,-68(s0)
   10160:	fc042603          	lw	a2,-64(s0)
   10164:	fc442583          	lw	a1,-60(s0)
   10168:	00ff6f33          	or	t5,t5,a5
   1016c:	00ef6f33          	or	t5,t5,a4
   10170:	00df6f33          	or	t5,t5,a3
   10174:	00cf6f33          	or	t5,t5,a2
   10178:	00bf6f33          	or	t5,t5,a1
   1017c:	fe042023          	sw	zero,-32(s0)
   10180:	0340006f          	j	101b4 <main+0x160>
   10184:	fc042e23          	sw	zero,-36(s0)
   10188:	0100006f          	j	10198 <main+0x144>
   1018c:	fdc42783          	lw	a5,-36(s0)
   10190:	00178793          	addi	a5,a5,1
   10194:	fcf42e23          	sw	a5,-36(s0)
   10198:	fdc42703          	lw	a4,-36(s0)
   1019c:	000f47b7          	lui	a5,0xf4
   101a0:	23f78793          	addi	a5,a5,575 # f423f <__global_pointer$+0xe2877>
   101a4:	fee7d4e3          	bge	a5,a4,1018c <main+0x138>
   101a8:	fe042783          	lw	a5,-32(s0)
   101ac:	00178793          	addi	a5,a5,1
   101b0:	fef42023          	sw	a5,-32(s0)
   101b4:	fe042703          	lw	a4,-32(s0)
   101b8:	000017b7          	lui	a5,0x1
   101bc:	bb778793          	addi	a5,a5,-1097 # bb7 <main-0xf49d>
   101c0:	fce7d2e3          	bge	a5,a4,10184 <main+0x130>
   101c4:	ea9ff06f          	j	1006c <main+0x18>


```

## Specific Instructions

```
Number of different instructions: 19
List of unique instructions:
andi
or
beq
lui
li
lw
bnez
addi
srai
srli
sw
bgtz
mv
add
slli
blt
j
sub
bge

```
![Screenshot from 2023-10-21 11-20-38](https://github.com/NSampathIIITB/IIITB_Automated_visitor_Counter/assets/141038460/aaa8a3d9-83f4-4888-b4b5-5cc542f70870)

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



