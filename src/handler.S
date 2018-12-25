.syntax unified
.cpu cortex-m4
.thumb
 
.global HardFault_Handler
.global BusFault_Handler
.extern hard_fault_handler_c
 
HardFault_Handler:
  TST LR, #4
  ITE EQ
  MRSEQ R0, MSP
  MRSNE R0, PSP
  B hard_fault_handler_c
	
BusFault_Handler:
  TST LR, #4
  ITE EQ
  MRSEQ R0, MSP
  MRSNE R0, PSP
  B hard_fault_handler_c
