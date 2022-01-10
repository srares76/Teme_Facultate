section .data
    extern len_cheie, len_haystack
    contor dw 0

section .text
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

    ;; TODO: Implment columnar_transposition
    ;; FREESTYLE STARTS HERE

    mov edx, 0
    mov dword ecx, 0 ; contor_key
    mov eax, [len_haystack]
    mov ecx, [len_cheie]
    div ecx
    inc eax
    mov ecx, 0

for_key:
    push ecx
    mov dword edx, 0

    push edx

    mov edx, 0
    mov edx, [edi + 4 * ecx]
    mov ecx, edx

    pop edx
; -->
for_haystack:
    push eax
    push edx
    push ecx

    mov eax, [len_cheie]
    mov ecx, edx
    mul ecx

    pop ecx
    add eax, ecx

    cmp [len_haystack], eax
    jle skipfinals

    push ecx

    mov cl, 0
    mov cl, [esi + eax]

    mov eax, 0
    mov eax, [contor]
    mov [ebx + eax], cl
    inc eax
    mov [contor], eax

    pop ecx
    
skipfinals:

    pop edx
    pop eax

    inc edx
    cmp edx, eax
    jl for_haystack

    pop ecx
    inc ecx
    cmp ecx, [len_cheie]
    jl for_key

finish:
    mov word [contor], 0
    ;; FREESTYLE ENDS HERE
    ;; DO NOT MODIFY
    popa
    leave
    ret
    ;; DO NOT MODIFY