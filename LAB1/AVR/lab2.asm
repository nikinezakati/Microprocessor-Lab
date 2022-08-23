; Niki Nezakati - 98522094

.include "m32def.inc"

		; Initialize Stack Pointer
		LDI		R16,HIGH(RAMEND)
		OUT		SPH,R16
		LDI		R16,LOW(RAMEND)
		OUT		SPL,R16

		LDI		R16,0xFF
		OUT		DDRC,R16		;Initialize PORTC as OUTPUT
		OUT		DDRD,R16		;Initialize PORTD as OUTPUT

		OUT		PORTA,R16		
		LDI		R16,0x00
		OUT		DDRA,R16		;Initialize PORTA as INPUT
		OUT		DDRB,R16		;Initialize PORTB as INPUT



BEGIN:	
		IN		R16,PINA
		CPI 	R16,0
		BREQ 	BEGINREVERSE
		LDI		R20,0			
		LDI		R21,0			
		LDI		R22,0			
		LDI     R23,0			
		RJMP	FORWARD0

BEGINREVERSE:
		LDI		R20,9			
		LDI		R21,9			
		LDI		R22,9			
		LDI     R23,9			
		RJMP	REVERSE0

Start: 	
		IN		R16,PINA
		CPI 	R16,0
		BREQ 	REVERSE0

FORWARD0:		
		CPI 	R20,0x09
		BREQ 	FORWARD1
		INC 	R20
		RJMP	DISPLAY

FORWARD1:		
		LDI 	R20,0x00
		CPI 	R21,0x09
		BREQ 	FORWARD2
		INC 	R21
		RJMP	DISPLAY

FORWARD2:		
		LDI 	R21,0x00
		CPI 	R22,0x09
		BREQ 	FORWARD3
		INC 	R22
		RJMP	DISPLAY

FORWARD3: 	
		LDI 	R22,0x00
		CPI 	R23,0x09
		BREQ 	FORWARD4
		INC 	R23

FORWARD4: 	
		LDI 	R23,0x00
		BREQ 	DISPLAY
		

REVERSE0: 	
		CPI 	R20,0x00
		BREQ 	REVERSE1
		DEC		R20
		RJMP	DISPLAY


REVERSE1:		
		LDI 	R20,0x09
		CPI 	R21,0x00
		BREQ 	REVERSE2
		DEC 	R21
		RJMP	DISPLAY

REVERSE2:		
		LDI 	R21,0x09
		CPI 	R22,0x00
		BREQ 	REVERSE3
		DEC 	R22
		RJMP	DISPLAY

REVERSE3: 	
		LDI 	R22,0x09
		CPI 	R23,0x00
		BREQ 	REVERSE4
		DEC 	R22

REVERSE4:	
		LDI 	R23,0x09
		RJMP 	DISPLAY


DISPLAY: ;Display Number
		LDI		R16,0b1110	
		OUT		PORTD,R16
		MOV		R16,R23
		CALL	CONVERT
		OUT		PORTC,R16
		CALL	DELAY

		LDI		R16,0b1101	 
		OUT		PORTD,R16
		MOV		R16,R22
		CALL	CONVERT
		OUT		PORTC,R16
		CALL	DELAY
		

		LDI		R16,0b1011	
		OUT		PORTD,R16
		MOV		R16,R21
		CALL	CONVERT
		OUT		PORTC,R16
		CALL	DELAY

		LDI		R16,0b0111	
		OUT		PORTD,R16
		MOV		R16,R20
		CALL	CONVERT
		OUT		PORTC,R16
		CALL	DELAY
		RJMP	START



CONVERT:				;converts a digit to 7seg code 
		CPI		R16,0
		BRNE	C1
		LDI		R16,0x3F
		RET
C1:		CPI		R16,1
		BRNE	C2
		LDI		R16,0x06
		RET
C2:		CPI		R16,2
		BRNE	C3
		LDI		R16,0x5B
		RET
C3:		CPI		R16,3
		BRNE	C4
		LDI		R16,0x4F
		RET
C4:		CPI		R16,4
		BRNE	C5
		LDI		R16,0x66
		RET
C5:		CPI		R16,5
		BRNE	C6
		LDI		R16,0x6D
		RET
C6:		CPI		R16,6
		BRNE	C7
		LDI		R16,0x7D
		RET
C7:		CPI		R16,7
		BRNE	C8
		LDI		R16,0x07
		RET
C8:		CPI		R16,8
		BRNE	C9
		LDI		R16,0x7F
		RET
C9:		CPI		R16,9
		BRNE	C10
		LDI		R16,0x6F
C10:	RET
					


DELAY:	LDI		R17,0x01
L1:		LDI		R18,0x10
L2:		LDI		R19,0xA0
L3:		DEC		R19
		BRNE	L3
		DEC		R18
		BRNE	L2
		DEC		R17
		BRNE	L1
		RET
