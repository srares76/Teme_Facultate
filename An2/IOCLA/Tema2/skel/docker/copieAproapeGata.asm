%include "./io.mac"
extern printf

section .data
    extern len_cheie, len_haystack

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

    ; PRINTF32 `%c\n\x0`, [esi + 2]
    xor edx, edx
    mov dword ecx, 0 ; contor_key
    mov eax, [len_haystack]
    mov ecx, [len_cheie]
    div ecx
    inc eax
    xor ecx, ecx
    ; PRINTF32 `de linii -> %hd\n\x0`, eax

for_key:
    PRINTF32 `%d\n\x0`, ecx
    push ecx
    mov dword edx, 0

    push edx

    xor edx, edx
    mov edx, [edi + 4 * ecx] ; edx --> edi
    mov ecx, edx
    PRINTF32 `primul char %d\n\x0`, ecx

    pop edx
; -->
for_haystack:
    ; PRINTF32 `primul char %c\n\x0`, ecx
    ; mov ..., esi + [edi + ecx] + [len_cheie * edx]
    ; mov ..., ebx + [len_cheie * edx]
    push eax
    push edx
    push ecx

    mov eax, [len_cheie]   ; eax --> multiplicitatea
    mov ecx, edx
    xor edx, edx
    mul ecx

    PRINTF32 `multiplicitate %d\n\x0`, eax
    pop ecx ; -> edi
    add eax, ecx
    mov ebx, [esi + eax]
    PRINTF32 `charul %c\n\x0`, ebx

    ; add ebx, eax
    ; xor ecx, ecx
    ; mov ecx, [ebx + eax]
    ; mov ebx, [ecx]
    ; add ebx, eax
    ; PRINTF32 `charul %c\n\x0`, [ebx + eax]

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

    ;; FREESTYLE ENDS HERE
    ;; DO NOT MODIFY
    popa
    leave
    ret
    ;; DO NOT MODIFY