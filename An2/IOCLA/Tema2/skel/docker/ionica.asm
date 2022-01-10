%include "./io.mac"

section .data
    extern len_cheie, len_haystack
    index dd 0
    contor_key dd 0
    contor_haystack dd 0

section .text
    extern printf   
    global columnar_transposition

;; void columnar_transposition(int key[], char *haystack, char *ciphertext);
columnar_transposition:
    ;; DO NOT MODIFY
    push    ebp
    mov     ebp, esp
    pusha 

    mov edi, [ebp + 8]   ;key
    mov esi, [ebp + 12]  ;haystack
    mov ebx, [ebp + 16]  ;ciphertext
    ;; DO NOT MODIFY

    mov dword [index], 0
     
    mov eax, [len_haystack]
    mov ecx, [len_cheie]
    xor edx, edx
    div ecx
    add eax, 1
    xor ecx, ecx

for_key:
    mov [contor_key], ecx

    xor edx, edx
    mov edx, [edi + 4 * ecx]
    mov ecx, edx

    xor edx, edx
; -->
for_haystack:
    mov [contor_haystack], edx
    push eax
    push ecx

    mov eax, [len_cheie]   ; eax --> multiplicitatea
    mov ecx, edx
    xor edx, edx
    mul ecx

    ;PRINTF32 `multiplicitate %d\n\x0`, eax
    pop ecx ; -> edi
    add eax, ecx

    cmp eax, [len_haystack]
    jge gunoi


    push ecx

    xor ch, ch
    mov ch, [esi + eax]
    xor edx, edx
    mov edx, [index]
    mov [ebx + edx], ch
    add edx, 1
    mov [index], edx


    pop ecx
    
gunoi:
    
    pop eax

    mov edx, [contor_haystack]
    inc edx
    cmp eax, edx
    jg for_haystack

    xor ecx, ecx
    mov ecx, [contor_key]
    inc ecx
    cmp [len_cheie], ecx
    jg for_key

    ;; FREESTYLE ENDS HERE
    ;; DO NOT MODIFY
    popa
    leave
    ret
    ;; DO NOT MODIFY