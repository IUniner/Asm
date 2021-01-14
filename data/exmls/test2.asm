; .model small
; .stack 100h
; .data
; 	maxLen        =  128
; 	newLine       db 10,13,'$'
; 	initialString db maxLen, maxLen DUP('$')	
; 	count         db 0
; 	blockNumber   db ?
; 	blockCount    db ?
; 	strLength       db ?
; .code
; writeAX PROC
; 	                    PUSH DX
; 	                    PUSH BX
; 	                    PUSH CX
; 	                    PUSH AX
	
; 	                    MOV  BX, 10
; 	                    XOR  CX, CX
		
; 	Cycle1:             
; 	                    XOR  DX, DX
; 	                    DIV  BX
; 	                    PUSH DX
; 	                    INC  CX
; 	                    CMP  AX, 0
; 	                    JNE  Cycle1
			
; 	Cycle2:             
; 	                    POP  DX
; 	                    ADD  DL,'0'
; 	                    MOV  AH, 02h
; 	                    INT  21h
; 	                    LOOP Cycle2

; 	                    POP  AX
; 	                    POP  CX
; 	                    POP  BX
; 	                    POP  DX
; 	                    RET
; writeAX ENDP
; 	main:               
; 	                    mov  bx, @data
; 	                    mov  ds, bx
; 	                    mov  es, bx
		 
; 	;Ввод входной строки
; 	                    XOR  DL, DL
; 	                    LEA  CX, initialString
; 	                    MOV  si, CX
; 	CycleEnteringString:
; 	                    MOV  AH, 01h
; 	                    INT  21h
; 	                    CMP  AL, 10
; 	                    JE   ExitCycle
; 	                    CMP  AL, 13
; 	                    JE   ExitCycle
; 	                    MOV  [si+2], AL
; 	                    INC  DL
; 	                    INC  si
; 	                    JMP  CycleEnteringString
; 	ExitCycle:          
; 	                    MOV  strLength, DL
; 	IncCount:           
; 	                    INC  count
; 	                    XOR  AX,AX
; 	                    MOV  AL, strLength
; 	                    DIV  count                     	;AL (AH)
; 	                    CMP  AH, 0                     	;If count not divider of strLength then inc count
; 	                    JNE  IncCount

; 	                    MOV  blockCount, AL
; 	                    MOV  AL, strLength
; 	                    CMP  count, AL
; 	                    JE   ExitProgramm

; 	                    MOV  blockNumber, 0
; 	NextPermutation:    
; 	                    INC  blockNumber
; 	                    MOV  AL, blockCount
; 	                    CMP  blockNumber, AL
; 	                    JE   ExitProgramm              	;if all blocks are valid
; 	                    lea  SI, initialString+2	;first symbol of str
; 	                    lea  DI, initialString+2
; 	                    MOV  AL, count
; 	                    MUL  blockNumber
; 	                    ADD  DI, AX
; 	                    XOR  CX, CX
; 	                    MOV  CL, count
; 	                    REPE CMPSB                     	;Comp SI and DI count times
; 	                    JNE  IncCount                  	;If not equal skip other blocks
; 	                    JMP  NextPermutation
					
; 	ExitProgramm:       
; 	                    XOR  AX, AX
; 	                    MOV  AL, count
; 	                    CALL writeAX
; 	                    mov  bx, 4c00h
; 		 		 int 21h
; 	end main

.model small
.stack 1000
.data
        FUNCTIONAL_BUTTON db 10," Button is functional",10,'$'
.code
.486
        FLAG  db ?
        CEZAR db ?
        TEMP_CEZAR db ?
        CEZAR_FLAG db 0
shift db 13
RAZR DB 10 


    SYS_HANDLER DD 0

    SHIFR_CESAR PROC
    CMP AL,'9'
    JA LETTERS
    SUB AL,'0'
    ADD AL,CEZAR
    MOV AH,0
    DIV RAZR
    MOV AL,AH
    ADD AL,'0'
    MOV AH,0
    JMP END_SHIFR
LETTERS:
    XOR CX,CX
    CMP CEZAR,26
    JNA MENSHE_26
    MOV DL, CEZAR
    CALCULATE:
    SUB CEZAR,26
    INC CX
    CMP CEZAR,26
    JA CALCULATE
    MENSHE_26:
    CMP AL, 'z'
    JA UP_LET
    ADD AL,CEZAR
    CMP AL,'z'
    JB END_SHIFR
    SUB AL,26
    JMP END_SHIFR
UP_LET:
    ADD AL,CEZAR
    CMP AL,'Z'
    JB END_SHIFR
    SUB AL,26
END_SHIFR:
    RET
SHIFR_CESAR ENDP

    KB_HANDLER PROC
        PUSHF
        CALL CS:SYS_HANDLER
        PUSH DS ES AX BX CX DX DI  
        POP DS

       
        
INPUT:
        XOR AX,AX
        XOR BX,BX
        XOR DX,DX
        
        MOV AH,00h
        INT 16H

        CMP AL,0
        JE NOT_SYMBOL
        CMP FLAG,0
        JNE NEXT
        SUB AL,'0'
        MOV CEZAR,AL
        ADD AL,'0'
        INC FLAG
        NEXT:
        CMP AL,08H
        JE BACKSPACE
        CMP AL, 0DH
        JE ENTER_
        CMP AH,01h
        JE ESC_
        CMP AL, 20h
        JE SPACE
        CALL SHIFR_CESAR
        JMP OUTPUT
SPACE:
    MOV AH,02H
    MOV DL,20H
    INT 21H
    JMP INPUT

ESC_:
    CMP CEZAR_FLAG,0
    JNE ON
    INC CEZAR_FLAG
    MOV BL,CEZAR
    MOV TEMP_CEZAR,BL
    MOV CEZAR,0
    JMP INPUT
    ON:
    DEC CEZAR_FLAG
    MOV BL,TEMP_CEZAR
    MOV CEZAR,BL
    JMP INPUT
ENTER_:
    MOV DL, 0AH
    MOV AH, 02H
    INT 21H
    JMP INPUT

OUTPUT:
    MOV DL, AL
    MOV AH, 02H
    INT 21H
    JMP INPUT 

BACKSPACE:
    MOV AH,02H
    MOV DL, 08H
    INT 21H
    MOV AH,02H
    MOV DL,20H
    INT 21H
    MOV AH,02H
    MOV DL, 08H
    INT 21H
    XOR AX,AX
    JMP INPUT

NOT_SYMBOL:
    MOV DX, OFFSET FUNCTIONAL_BUTTON
    MOV AH, 09H
    INT 21H
EXIT:
     XOR AX,AX
     MOV AL,20h
     OUT 20h,AL
        POP DI
        POP DX
        POP CX
        POP BX
        POP AX
        POP ES
        POP DS 
        IRET
    KB_HANDLER ENDP
    KB_END:
 

start:
    mov ax, @data
        mov ds, ax
        
        cli 
        pushf 
        push 0        
        pop ds
        mov eax, ds:[09h*4] 
        mov cs:[SYS_HANDLER], eax 
        
        mov ax, cs
        shl eax, 16
        mov ax, offset KB_HANDLER
        mov ds:[09h*4], eax 
        sti 
        
        xor ax, ax
        mov ah, 31h
        MOV DX, (KB_END - @code + 10FH) / 16 
        INT 27h

    
end start