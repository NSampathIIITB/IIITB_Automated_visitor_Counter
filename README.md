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

![Screenshot-2022-12-25-at-12 51 02-AM-800x485](https://github.com/NSampathIIITB/IIITB_Automated_visitor_Counter/assets/141038460/316859d7-8cd1-4bbb-ae98-e8f450f13930)

## Block Diagram

![Screenshot from 2023-10-04 15-21-12](https://github.com/NSampathIIITB/IIITB_Automated_visitor_Counter/assets/141038460/b6babf88-66ec-4dd2-8960-3c7f102caadd)

## Testing

1. Open a terminal window.
2. Navigate to the directory containing the sample.c file.
3. Design a function that executes the intended logic you require.
4. Compile the code using the GCC compiler and verify the output:
   
  
```
gcc Automated_Visitor_Counter.c
./a.out
```
![Screenshot from 2023-10-04 15-39-04](https://github.com/NSampathIIITB/IIITB_Automated_visitor_Counter/assets/141038460/fcff0780-420d-4625-b835-3292a59218e9)

## C Code
```
#include <stdio.h>

// Simulated inputs for person detection
int sensor7 = 0; // Pin 7
int sensor8 = 0; // Pin 8

int total = 0;

void show() {
    //printf("There are %d people in the room.\n", total);
}

void delay(int milliseconds) {
    for (int i = 0; i < milliseconds; i++) {
        for (int j = 0; j < 10000; j++) {
            // Adjust the loop count based on your microcontroller's speed
        }
    }
}

int main() {
    // Setup code
    while (1) {
        // Simulated digitalRead for sensor7
        // Replace with actual code to read the state of sensor connected to pin 7
        // Example: sensor7 = digitalRead(7);

        // Simulated digitalRead for sensor8
        // Replace with actual code to read the state of sensor connected to pin 8
        // Example: sensor8 = digitalRead(8);

        if (sensor7 == 0) {
            while (sensor8 == 1) {
                // Wait for person to fully enter
                // Replace with your code to check sensor8 state
            }

            // Person entered 
            total++;
            show();
            delay(300); // Delay for 300 milliseconds
             
        } else if (sensor8 == 0) {
            while (sensor7 == 1) {
                // Wait for person to fully exit
                // Replace with your code to check sensor7 state
            }

            // Person exited
            total--;
            show();
            delay(300); // Delay for 300 milliseconds
        }

       
    }

    return 0;
}
```

## Assembly Code

### Assembly Code Generation

**To use the RISC-V gcc compiler or simulator**

    `riscv64-unknown-elf-gcc <compiler option -O1 ; Ofast> -mabi=lp64  -march=rv64i  -o <object filename.o> <Cfilename.c>`

   Here -01 gives 15 instructions set while -0fast gives us 12 instructions set
    
**To list the details of a file**
  
  ```
ls -ltr <filename.o>

```

**To disassemble the object file**

```

riscv64-unknown-elf-objdump  -d  <object filename.o> (or)
riscv64-unknown-elf-objdump  -d <object filename.o> | less

```

```
Automated_Visitor_Counter.o:     file format elf64-littleriscv


Disassembly of section .text:

00000000000100b0 <main>:
   100b0:	f681a783          	lw	a5,-152(gp) # 11d78 <sensor7>
   100b4:	f641a703          	lw	a4,-156(gp) # 11d74 <sensor8>
   100b8:	f601a603          	lw	a2,-160(gp) # 11d70 <_edata>
   100bc:	00100693          	li	a3,1
   100c0:	00079663          	bnez	a5,100cc <main+0x1c>
   100c4:	00d71063          	bne	a4,a3,100c4 <main+0x14>
   100c8:	0000006f          	j	100c8 <main+0x18>
   100cc:	fe071ae3          	bnez	a4,100c0 <main+0x10>
   100d0:	00d79663          	bne	a5,a3,100dc <main+0x2c>
   100d4:	f6c1a023          	sw	a2,-160(gp) # 11d70 <_edata>
   100d8:	0000006f          	j	100d8 <main+0x28>
   100dc:	fff6061b          	addiw	a2,a2,-1
   100e0:	fe0796e3          	bnez	a5,100cc <main+0x1c>
   100e4:	fe1ff06f          	j	100c4 <main+0x14>

00000000000100e8 <register_fini>:
   100e8:	ffff0797          	auipc	a5,0xffff0
   100ec:	f1878793          	addi	a5,a5,-232 # 0 <main-0x100b0>
   100f0:	00078863          	beqz	a5,10100 <register_fini+0x18>
   100f4:	00000517          	auipc	a0,0x0
   100f8:	11450513          	addi	a0,a0,276 # 10208 <__libc_fini_array>
   100fc:	0c40006f          	j	101c0 <atexit>
   10100:	00008067          	ret

0000000000010104 <_start>:
   10104:	00002197          	auipc	gp,0x2
   10108:	d0c18193          	addi	gp,gp,-756 # 11e10 <__global_pointer$>
   1010c:	f6018513          	addi	a0,gp,-160 # 11d70 <_edata>
   10110:	fa818613          	addi	a2,gp,-88 # 11db8 <__BSS_END__>
   10114:	40a60633          	sub	a2,a2,a0
   10118:	00000593          	li	a1,0
   1011c:	1dc000ef          	jal	ra,102f8 <memset>
   10120:	00000517          	auipc	a0,0x0
   10124:	0e850513          	addi	a0,a0,232 # 10208 <__libc_fini_array>
   10128:	098000ef          	jal	ra,101c0 <atexit>
   1012c:	138000ef          	jal	ra,10264 <__libc_init_array>
   10130:	00012503          	lw	a0,0(sp)
   10134:	00810593          	addi	a1,sp,8
   10138:	00000613          	li	a2,0
   1013c:	f75ff0ef          	jal	ra,100b0 <main>
   10140:	0940006f          	j	101d4 <exit>

0000000000010144 <__do_global_dtors_aux>:
   10144:	f701c783          	lbu	a5,-144(gp) # 11d80 <completed.5468>
   10148:	04079463          	bnez	a5,10190 <__do_global_dtors_aux+0x4c>
   1014c:	ffff0797          	auipc	a5,0xffff0
   10150:	eb478793          	addi	a5,a5,-332 # 0 <main-0x100b0>
   10154:	02078863          	beqz	a5,10184 <__do_global_dtors_aux+0x40>
   10158:	ff010113          	addi	sp,sp,-16
   1015c:	00001517          	auipc	a0,0x1
   10160:	49850513          	addi	a0,a0,1176 # 115f4 <__FRAME_END__>
   10164:	00113423          	sd	ra,8(sp)
   10168:	00000097          	auipc	ra,0x0
   1016c:	000000e7          	jalr	zero # 0 <main-0x100b0>
   10170:	00813083          	ld	ra,8(sp)
   10174:	00100793          	li	a5,1
   10178:	f6f18823          	sb	a5,-144(gp) # 11d80 <completed.5468>
   1017c:	01010113          	addi	sp,sp,16
   10180:	00008067          	ret
   10184:	00100793          	li	a5,1
   10188:	f6f18823          	sb	a5,-144(gp) # 11d80 <completed.5468>
   1018c:	00008067          	ret
   10190:	00008067          	ret

0000000000010194 <frame_dummy>:
   10194:	ffff0797          	auipc	a5,0xffff0
   10198:	e6c78793          	addi	a5,a5,-404 # 0 <main-0x100b0>
   1019c:	00078c63          	beqz	a5,101b4 <frame_dummy+0x20>
   101a0:	f7818593          	addi	a1,gp,-136 # 11d88 <object.5473>
   101a4:	00001517          	auipc	a0,0x1
   101a8:	45050513          	addi	a0,a0,1104 # 115f4 <__FRAME_END__>
   101ac:	00000317          	auipc	t1,0x0
   101b0:	00000067          	jr	zero # 0 <main-0x100b0>
   101b4:	00008067          	ret

00000000000101b8 <show>:
   101b8:	00008067          	ret

00000000000101bc <delay>:
   101bc:	00008067          	ret

00000000000101c0 <atexit>:
   101c0:	00050593          	mv	a1,a0
   101c4:	00000693          	li	a3,0
   101c8:	00000613          	li	a2,0
   101cc:	00000513          	li	a0,0
   101d0:	2040006f          	j	103d4 <__register_exitproc>

00000000000101d4 <exit>:
   101d4:	ff010113          	addi	sp,sp,-16
   101d8:	00000593          	li	a1,0
   101dc:	00813023          	sd	s0,0(sp)
   101e0:	00113423          	sd	ra,8(sp)
   101e4:	00050413          	mv	s0,a0
   101e8:	298000ef          	jal	ra,10480 <__call_exitprocs>
   101ec:	f4818793          	addi	a5,gp,-184 # 11d58 <_global_impure_ptr>
   101f0:	0007b503          	ld	a0,0(a5)
   101f4:	05853783          	ld	a5,88(a0)
   101f8:	00078463          	beqz	a5,10200 <exit+0x2c>
   101fc:	000780e7          	jalr	a5
   10200:	00040513          	mv	a0,s0
   10204:	3a0000ef          	jal	ra,105a4 <_exit>

0000000000010208 <__libc_fini_array>:
   10208:	fe010113          	addi	sp,sp,-32
   1020c:	00813823          	sd	s0,16(sp)
   10210:	00001797          	auipc	a5,0x1
   10214:	40078793          	addi	a5,a5,1024 # 11610 <__fini_array_end>
   10218:	00001417          	auipc	s0,0x1
   1021c:	3f040413          	addi	s0,s0,1008 # 11608 <__init_array_end>
   10220:	408787b3          	sub	a5,a5,s0
   10224:	00913423          	sd	s1,8(sp)
   10228:	00113c23          	sd	ra,24(sp)
   1022c:	4037d493          	srai	s1,a5,0x3
   10230:	02048063          	beqz	s1,10250 <__libc_fini_array+0x48>
   10234:	ff878793          	addi	a5,a5,-8
   10238:	00878433          	add	s0,a5,s0
   1023c:	00043783          	ld	a5,0(s0)
   10240:	fff48493          	addi	s1,s1,-1
   10244:	ff840413          	addi	s0,s0,-8
   10248:	000780e7          	jalr	a5
   1024c:	fe0498e3          	bnez	s1,1023c <__libc_fini_array+0x34>
   10250:	01813083          	ld	ra,24(sp)
   10254:	01013403          	ld	s0,16(sp)
   10258:	00813483          	ld	s1,8(sp)
   1025c:	02010113          	addi	sp,sp,32
   10260:	00008067          	ret

0000000000010264 <__libc_init_array>:
   10264:	fe010113          	addi	sp,sp,-32
   10268:	00813823          	sd	s0,16(sp)
   1026c:	01213023          	sd	s2,0(sp)
   10270:	00001417          	auipc	s0,0x1
   10274:	38840413          	addi	s0,s0,904 # 115f8 <__init_array_start>
   10278:	00001917          	auipc	s2,0x1
   1027c:	38090913          	addi	s2,s2,896 # 115f8 <__init_array_start>
   10280:	40890933          	sub	s2,s2,s0
   10284:	00113c23          	sd	ra,24(sp)
   10288:	00913423          	sd	s1,8(sp)
   1028c:	40395913          	srai	s2,s2,0x3
   10290:	00090e63          	beqz	s2,102ac <__libc_init_array+0x48>
   10294:	00000493          	li	s1,0
   10298:	00043783          	ld	a5,0(s0)
   1029c:	00148493          	addi	s1,s1,1
   102a0:	00840413          	addi	s0,s0,8
   102a4:	000780e7          	jalr	a5
   102a8:	fe9918e3          	bne	s2,s1,10298 <__libc_init_array+0x34>
   102ac:	00001417          	auipc	s0,0x1
   102b0:	34c40413          	addi	s0,s0,844 # 115f8 <__init_array_start>
   102b4:	00001917          	auipc	s2,0x1
   102b8:	35490913          	addi	s2,s2,852 # 11608 <__init_array_end>
   102bc:	40890933          	sub	s2,s2,s0
   102c0:	40395913          	srai	s2,s2,0x3
   102c4:	00090e63          	beqz	s2,102e0 <__libc_init_array+0x7c>
   102c8:	00000493          	li	s1,0
   102cc:	00043783          	ld	a5,0(s0)
   102d0:	00148493          	addi	s1,s1,1
   102d4:	00840413          	addi	s0,s0,8
   102d8:	000780e7          	jalr	a5
   102dc:	fe9918e3          	bne	s2,s1,102cc <__libc_init_array+0x68>
   102e0:	01813083          	ld	ra,24(sp)
   102e4:	01013403          	ld	s0,16(sp)
   102e8:	00813483          	ld	s1,8(sp)
   102ec:	00013903          	ld	s2,0(sp)
   102f0:	02010113          	addi	sp,sp,32
   102f4:	00008067          	ret

00000000000102f8 <memset>:
   102f8:	00f00313          	li	t1,15
   102fc:	00050713          	mv	a4,a0
   10300:	02c37a63          	bgeu	t1,a2,10334 <memset+0x3c>
   10304:	00f77793          	andi	a5,a4,15
   10308:	0a079063          	bnez	a5,103a8 <memset+0xb0>
   1030c:	06059e63          	bnez	a1,10388 <memset+0x90>
   10310:	ff067693          	andi	a3,a2,-16
   10314:	00f67613          	andi	a2,a2,15
   10318:	00e686b3          	add	a3,a3,a4
   1031c:	00b73023          	sd	a1,0(a4)
   10320:	00b73423          	sd	a1,8(a4)
   10324:	01070713          	addi	a4,a4,16
   10328:	fed76ae3          	bltu	a4,a3,1031c <memset+0x24>
   1032c:	00061463          	bnez	a2,10334 <memset+0x3c>
   10330:	00008067          	ret
   10334:	40c306b3          	sub	a3,t1,a2
   10338:	00269693          	slli	a3,a3,0x2
   1033c:	00000297          	auipc	t0,0x0
   10340:	005686b3          	add	a3,a3,t0
   10344:	00c68067          	jr	12(a3)
   10348:	00b70723          	sb	a1,14(a4)
   1034c:	00b706a3          	sb	a1,13(a4)
   10350:	00b70623          	sb	a1,12(a4)
   10354:	00b705a3          	sb	a1,11(a4)
   10358:	00b70523          	sb	a1,10(a4)
   1035c:	00b704a3          	sb	a1,9(a4)
   10360:	00b70423          	sb	a1,8(a4)
   10364:	00b703a3          	sb	a1,7(a4)
   10368:	00b70323          	sb	a1,6(a4)
   1036c:	00b702a3          	sb	a1,5(a4)
   10370:	00b70223          	sb	a1,4(a4)
   10374:	00b701a3          	sb	a1,3(a4)
   10378:	00b70123          	sb	a1,2(a4)
   1037c:	00b700a3          	sb	a1,1(a4)
   10380:	00b70023          	sb	a1,0(a4)
   10384:	00008067          	ret
   10388:	0ff5f593          	andi	a1,a1,255
   1038c:	00859693          	slli	a3,a1,0x8
   10390:	00d5e5b3          	or	a1,a1,a3
   10394:	01059693          	slli	a3,a1,0x10
   10398:	00d5e5b3          	or	a1,a1,a3
   1039c:	02059693          	slli	a3,a1,0x20
   103a0:	00d5e5b3          	or	a1,a1,a3
   103a4:	f6dff06f          	j	10310 <memset+0x18>
   103a8:	00279693          	slli	a3,a5,0x2
   103ac:	00000297          	auipc	t0,0x0
   103b0:	005686b3          	add	a3,a3,t0
   103b4:	00008293          	mv	t0,ra
   103b8:	f98680e7          	jalr	-104(a3)
   103bc:	00028093          	mv	ra,t0
   103c0:	ff078793          	addi	a5,a5,-16
   103c4:	40f70733          	sub	a4,a4,a5
   103c8:	00f60633          	add	a2,a2,a5
   103cc:	f6c374e3          	bgeu	t1,a2,10334 <memset+0x3c>
   103d0:	f3dff06f          	j	1030c <memset+0x14>

00000000000103d4 <__register_exitproc>:
   103d4:	f4818793          	addi	a5,gp,-184 # 11d58 <_global_impure_ptr>
   103d8:	0007b703          	ld	a4,0(a5)
   103dc:	1f873783          	ld	a5,504(a4)
   103e0:	06078063          	beqz	a5,10440 <__register_exitproc+0x6c>
   103e4:	0087a703          	lw	a4,8(a5)
   103e8:	01f00813          	li	a6,31
   103ec:	08e84663          	blt	a6,a4,10478 <__register_exitproc+0xa4>
   103f0:	02050863          	beqz	a0,10420 <__register_exitproc+0x4c>
   103f4:	00371813          	slli	a6,a4,0x3
   103f8:	01078833          	add	a6,a5,a6
   103fc:	10c83823          	sd	a2,272(a6)
   10400:	3107a883          	lw	a7,784(a5)
   10404:	00100613          	li	a2,1
   10408:	00e6163b          	sllw	a2,a2,a4
   1040c:	00c8e8b3          	or	a7,a7,a2
   10410:	3117a823          	sw	a7,784(a5)
   10414:	20d83823          	sd	a3,528(a6)
   10418:	00200693          	li	a3,2
   1041c:	02d50863          	beq	a0,a3,1044c <__register_exitproc+0x78>
   10420:	00270693          	addi	a3,a4,2
   10424:	00369693          	slli	a3,a3,0x3
   10428:	0017071b          	addiw	a4,a4,1
   1042c:	00e7a423          	sw	a4,8(a5)
   10430:	00d787b3          	add	a5,a5,a3
   10434:	00b7b023          	sd	a1,0(a5)
   10438:	00000513          	li	a0,0
   1043c:	00008067          	ret
   10440:	20070793          	addi	a5,a4,512
   10444:	1ef73c23          	sd	a5,504(a4)
   10448:	f9dff06f          	j	103e4 <__register_exitproc+0x10>
   1044c:	3147a683          	lw	a3,788(a5)
   10450:	00000513          	li	a0,0
   10454:	00c6e633          	or	a2,a3,a2
   10458:	00270693          	addi	a3,a4,2
   1045c:	00369693          	slli	a3,a3,0x3
   10460:	0017071b          	addiw	a4,a4,1
   10464:	30c7aa23          	sw	a2,788(a5)
   10468:	00e7a423          	sw	a4,8(a5)
   1046c:	00d787b3          	add	a5,a5,a3
   10470:	00b7b023          	sd	a1,0(a5)
   10474:	00008067          	ret
   10478:	fff00513          	li	a0,-1
   1047c:	00008067          	ret

0000000000010480 <__call_exitprocs>:
   10480:	fb010113          	addi	sp,sp,-80
   10484:	f4818793          	addi	a5,gp,-184 # 11d58 <_global_impure_ptr>
   10488:	01813023          	sd	s8,0(sp)
   1048c:	0007bc03          	ld	s8,0(a5)
   10490:	03313423          	sd	s3,40(sp)
   10494:	03413023          	sd	s4,32(sp)
   10498:	01513c23          	sd	s5,24(sp)
   1049c:	01613823          	sd	s6,16(sp)
   104a0:	04113423          	sd	ra,72(sp)
   104a4:	04813023          	sd	s0,64(sp)
   104a8:	02913c23          	sd	s1,56(sp)
   104ac:	03213823          	sd	s2,48(sp)
   104b0:	01713423          	sd	s7,8(sp)
   104b4:	00050a93          	mv	s5,a0
   104b8:	00058b13          	mv	s6,a1
   104bc:	00100a13          	li	s4,1
   104c0:	fff00993          	li	s3,-1
   104c4:	1f8c3903          	ld	s2,504(s8)
   104c8:	02090863          	beqz	s2,104f8 <__call_exitprocs+0x78>
   104cc:	00892483          	lw	s1,8(s2)
   104d0:	fff4841b          	addiw	s0,s1,-1
   104d4:	02044263          	bltz	s0,104f8 <__call_exitprocs+0x78>
   104d8:	00349493          	slli	s1,s1,0x3
   104dc:	009904b3          	add	s1,s2,s1
   104e0:	040b0463          	beqz	s6,10528 <__call_exitprocs+0xa8>
   104e4:	2084b783          	ld	a5,520(s1)
   104e8:	05678063          	beq	a5,s6,10528 <__call_exitprocs+0xa8>
   104ec:	fff4041b          	addiw	s0,s0,-1
   104f0:	ff848493          	addi	s1,s1,-8
   104f4:	ff3416e3          	bne	s0,s3,104e0 <__call_exitprocs+0x60>
   104f8:	04813083          	ld	ra,72(sp)
   104fc:	04013403          	ld	s0,64(sp)
   10500:	03813483          	ld	s1,56(sp)
   10504:	03013903          	ld	s2,48(sp)
   10508:	02813983          	ld	s3,40(sp)
   1050c:	02013a03          	ld	s4,32(sp)
   10510:	01813a83          	ld	s5,24(sp)
   10514:	01013b03          	ld	s6,16(sp)
   10518:	00813b83          	ld	s7,8(sp)
   1051c:	00013c03          	ld	s8,0(sp)
   10520:	05010113          	addi	sp,sp,80
   10524:	00008067          	ret
   10528:	00892783          	lw	a5,8(s2)
   1052c:	0084b703          	ld	a4,8(s1)
   10530:	fff7879b          	addiw	a5,a5,-1
   10534:	04878e63          	beq	a5,s0,10590 <__call_exitprocs+0x110>
   10538:	0004b423          	sd	zero,8(s1)
   1053c:	fa0708e3          	beqz	a4,104ec <__call_exitprocs+0x6c>
   10540:	31092783          	lw	a5,784(s2)
   10544:	008a16bb          	sllw	a3,s4,s0
   10548:	00892b83          	lw	s7,8(s2)
   1054c:	00d7f7b3          	and	a5,a5,a3
   10550:	0007879b          	sext.w	a5,a5
   10554:	00079e63          	bnez	a5,10570 <__call_exitprocs+0xf0>
   10558:	000700e7          	jalr	a4
   1055c:	00892783          	lw	a5,8(s2)
   10560:	f77792e3          	bne	a5,s7,104c4 <__call_exitprocs+0x44>
   10564:	1f8c3783          	ld	a5,504(s8)
   10568:	f92782e3          	beq	a5,s2,104ec <__call_exitprocs+0x6c>
   1056c:	f59ff06f          	j	104c4 <__call_exitprocs+0x44>
   10570:	31492783          	lw	a5,788(s2)
   10574:	1084b583          	ld	a1,264(s1)
   10578:	00d7f7b3          	and	a5,a5,a3
   1057c:	0007879b          	sext.w	a5,a5
   10580:	00079c63          	bnez	a5,10598 <__call_exitprocs+0x118>
   10584:	000a8513          	mv	a0,s5
   10588:	000700e7          	jalr	a4
   1058c:	fd1ff06f          	j	1055c <__call_exitprocs+0xdc>
   10590:	00892423          	sw	s0,8(s2)
   10594:	fa9ff06f          	j	1053c <__call_exitprocs+0xbc>
   10598:	00058513          	mv	a0,a1
   1059c:	000700e7          	jalr	a4
   105a0:	fbdff06f          	j	1055c <__call_exitprocs+0xdc>

00000000000105a4 <_exit>:
   105a4:	00000593          	li	a1,0
   105a8:	00000613          	li	a2,0
   105ac:	00000693          	li	a3,0
   105b0:	00000713          	li	a4,0
   105b4:	00000793          	li	a5,0
   105b8:	05d00893          	li	a7,93
   105bc:	00000073          	ecall
   105c0:	00054463          	bltz	a0,105c8 <_exit+0x24>
   105c4:	0000006f          	j	105c4 <_exit+0x20>
   105c8:	ff010113          	addi	sp,sp,-16
   105cc:	00813023          	sd	s0,0(sp)
   105d0:	00050413          	mv	s0,a0
   105d4:	00113423          	sd	ra,8(sp)
   105d8:	4080043b          	negw	s0,s0
   105dc:	00c000ef          	jal	ra,105e8 <__errno>
   105e0:	00852023          	sw	s0,0(a0)
   105e4:	0000006f          	j	105e4 <_exit+0x40>

00000000000105e8 <__errno>:
   105e8:	f5818793          	addi	a5,gp,-168 # 11d68 <_impure_ptr>
   105ec:	0007b503          	ld	a0,0(a5)
   105f0:	00008067          	ret

```

## Specific Instructions

```
Number of different instructions: 35
List of unique instructions:
j
negw
blt
addiw
sb
ld
jal
mv
addi
sub
bltz
jr
ret
beq
ecall
sllw
bne
auipc
srai
and
beqz
sw
slli
or
bgeu
andi
lbu
sext.w
bnez
sd
lw
jalr
li
bltu
add
```
## Acknowledgement

- Kunal Ghosh, VSD Corp. Pvt. Ltd.
- Alwin shaju,Colleague,IIIT B
- Kanish R,Colleague,IIIT B
- Mayank Kabra , IIIT B
- skywater Foundry
- chatgpt


## References

- https://www.vsdiat.com
- https://github.com/kunalg123/riscv_workshop_collaterals
- https://github.com/SakethGajawada/RISCV-GNU
- https://github.com/The-OpenROAD-Project/OpenSTA.git
- https://how2electronics.com/bidirectional-visitor-counter-with-automatic-light-control-using-arduino/ 



