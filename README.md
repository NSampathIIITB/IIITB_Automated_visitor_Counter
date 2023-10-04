# IIITB_Automated_visitor_Counter_using_RISC-V

This github repository summarizes the progress made in the ASIC class regarding the RISC-V project.

# Aim
The aim of the project is to measure and display the number of persons entering in any room like seminar hall, conference room etc. LCD displays number ofpersons inside the room. We can use this project to count and display the number of visitors entering inside any conference room or seminar hall. This works in atwo way. That means counter will be incremented if person enters the room and will be decremented if a person leaves the room. This design is made utilising a specialized RISC-V processor.

# Requirements



# Working
First of all, we need to set one IR sensor (IR sensor-1) at the entry gate and another one (IR sensor-2) set at the exit gate. Normally when IR sensors do not detect any obstacle, it produces a HIGH (1) output value from the Output Pin.

When a visitor enters through the entry gate the IR sensor-1 detects the visitor (obstacle) and produces a Low (0) output value from the Output Pin.Then the processor read this value and counts 1+ using the code. Similarly, When the IR sensor-1 detects another visitor (obstacle), the processor increment the counting by 1+. In this way every time the processor adds +1 in the count when a visitor passes through this gate and calculates the total number of entering visitors.

 In the same way, when a visitor leaves through the exit gate the IR sensor-2 detects the visitor (obstacle) and produces a Low (0) output value from the Output Pin. Then the processor read this value and counts 1- using the code. Similarly, When the IR sensor-2 detects another visitor (obstacle), the processor increment the counting by 11. In this way every time the processor adds +1 in the count when a visitor passes through this exit gate.

# Circuit

# Block Diagram


# Testing



# C Code


# Assembly Code




# Specific Instructions


# Acknowledgement


# References

#
