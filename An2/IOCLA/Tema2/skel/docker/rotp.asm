section .text
    global rotp

;; void rotp(char *ciphertext, char *plaintext, char *key, int len);
rotp:
    ;; DO NOT MODIFY
    push    ebp
    mov     ebp, esp
    pusha

    mov     edx, [ebp + 8]  ; ciphertext
    mov     esi, [ebp + 12] ; plaintext
    mov     edi, [ebp + 16] ; key
    mov     ecx, [ebp + 20] ; len
    ;; DO NOT MODIFY
    ;; TODO: Implment rotp
    ;; FREESTYLE STARTS HERE
    
for:
    dec ecx
    mov al, byte[esi]
    inc esi
    mov bl, byte[edi + ecx]

    xor al, bl

    mov byte[edx], al
    inc edx

    cmp ecx, 0
    jge for

    ;; FREESTYLE ENDS HERE
    ;; DO NOT MODIFY
    popa
    leave
    ret
    ;; DO NOT MODIFY
    