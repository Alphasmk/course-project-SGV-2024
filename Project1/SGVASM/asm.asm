.586
	.model flat, stdcall
	includelib libucrt.lib
	includelib kernel32.lib
	ExitProcess PROTO :DWORD

	_exp PROTO :DWORD
	_pow PROTO :DWORD, :DWORD
	_printInt PROTO :DWORD
	_printStr PROTO :DWORD
	_printBool PROTO :DWORD
	_printChar PROTO :DWORD
	_pause PROTO

.stack 4096
.CONST
	null_division BYTE 'ERROR: DIVISION BY ZERO', 0
	OVER_FLOW BYTE 'ERROR: OVERFLOW', 0
	true BYTE "true", 0
	false BYTE "false", 0
	empty_string BYTE 0
	L1 DWORD 2
	L2 DWORD 2
	L3 DWORD 2
	L4 BYTE "Результат:", 0
	L5 DWORD 2
	L6 BYTE "it true", 0
	L7 BYTE "it false", 0
	L8 DWORD 2
	L9 DWORD 1
	L10 DWORD 2
	L11 DWORD 3
	L12 DWORD 1
	L13 DWORD 3
	L14 DWORD 5
	L15 DWORD 0
.DATA
	tsa DWORD 0
	saa DWORD empty_string
	sab DWORD 0
	mainx DWORD 0
	mainy DWORD 0
	mainz DWORD 0
	mainksa DWORD empty_string

.CODE
ts PROC tsz:DWORD, tsx:DWORD
	push L1
	push L2
	pop eax
	pop ebx
	add eax, ebx
	push eax
	push L3
	pop eax
	pop ebx
	mul ebx
	push eax
	pop eax
	cmp eax, 255
	jg overflow
	cmp eax, 0
	jl overflow
	mov tsa, eax

push offset L4
call _printStr

push tsa
call _printInt
	push tsx
	push tsz
	call _pow
	push eax
	pop eax
	cmp eax, 255
	jg overflow
	cmp eax, 0
	jl overflow
	mov tsa, eax
	push tsa
	jmp local0
local0:
	pop eax
	ret
ts ENDP

sa PROC sak:DWORD
	push L5
	push sak
	call _pow
	push eax
	pop eax
	cmp eax, 255
	jg overflow
	cmp eax, 0
	jl overflow
	mov sab, eax
	mov eax, sab
	cmp eax, sak
	jz ifi1
	jnz else1
ifi1:
push offset L6
	pop saa

else1:
push offset L7
	pop saa

ifEnd1:

push saa
call _printStr
	push OFFSET saa
	jmp local1
local1:
	pop eax
	ret
sa ENDP

main PROC
	push L8
	pop eax
	cmp eax, 255
	jg overflow
	cmp eax, 0
	jl overflow
	mov mainx, eax
	push L9
	push L10
	push L11
	pop eax
	pop ebx
	mul ebx
	push eax
	pop eax
	pop ebx
	add eax, ebx
	push eax
	pop eax
	cmp eax, 255
	jg overflow
	cmp eax, 0
	jl overflow
	mov mainy, eax
	mov eax, mainx
	cmp eax, mainy
	jz ifi2
	jnz else2
ifi2:
	push mainy
	push L12
	pop ebx
	pop eax
	sub eax, ebx
	push eax
	pop eax
	cmp eax, 255
	jg overflow
	cmp eax, 0
	jl overflow
	mov mainx, eax
else2:
	push mainy
	pop eax
	cmp eax, 255
	jg overflow
	cmp eax, 0
	jl overflow
	mov mainx, eax
ifEnd2:
	push mainx
	call sa
	push eax

	push L13
	call _exp
	push eax
	push L14
	pop eax
	pop ebx
	add eax, ebx
	push eax
	pop eax
	cmp eax, 255
	jg overflow
	cmp eax, 0
	jl overflow
	mov mainz, eax

push mainz
call _printInt
	push mainy
	push mainx
	call ts
	push eax
	pop eax
	cmp eax, 255
	jg overflow
	cmp eax, 0
	jl overflow
	mov mainz, eax

push mainz
call _printInt
	push L15
	jmp theend

jmp theend
SOMETHINGWRONG::
	push offset null_division
	call _printStr
jmp THEEND
THEEND:
	call _pause
	pop eax
	ret
	call ExitProcess
overflow::
	push offset OVER_FLOW
	call _printStr
main ENDP
end main