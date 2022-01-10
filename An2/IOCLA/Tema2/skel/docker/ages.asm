; This is your structure
struc  my_date
    .day: resw 1
    .month: resw 1
    .year: resd 1
endstruc

section .text
    global ages



; void ages(int len, struct my_date* present, struct my_date* dates, int* all_ages);
ages:
    ;; DO NOT MODIFY
    push    ebp
    mov     ebp, esp
    pusha

    mov     edx, [ebp + 8]  ; len
    mov     esi, [ebp + 12] ; present
    mov     edi, [ebp + 16] ; dates
    mov     ecx, [ebp + 20] ; all_ages
    ;; DO NOT MODIFY
    ;; TODO: Implement ages
    ;; FREESTYLE STARTS HERE

    mov dword eax, [esi + my_date.year] ; present year
    dec edx;
    jmp for

treat_zero:
    mov dword [ecx], 0
    jmp continue_treat_zero

continue_for:
    add edi, my_date_size ; go to next person in array
    add ecx, 4
    dec edx ; decrement contor
    cmp edx, 0
    jge for

equal_years:
    xor eax, eax
    xor ebx, ebx
    mov word eax, [esi + my_date.day]
    mov word ebx, [edi + my_date.day]
    sub eax, ebx

    cmp eax, 0
    jl decrementmonth

    add edi, my_date_size ; go to next person in array
    add ecx, 4
    dec edx ; decrement contor
    cmp edx, 0
    jge for

    cmp edx, 0
    jl finish

for:
    mov dword eax, [esi + my_date.year] ; present year   
    mov dword ebx, [edi + my_date.year] ; person's year
    sub eax, ebx ; subtract person's year from present year

    mov [ecx], eax ; add to output array

    xor eax, eax
    xor ebx, ebx
    mov word eax, [esi + my_date.month]
    mov word ebx, [edi + my_date.month]
    sub eax, ebx

    test ax, ax
    je equal_years

    test ax, ax
    jg continue_for

    cmp eax, 0
    jl decrementmonth

    cmp edx, 0
    jl finish

decrementmonth:
    mov eax, [ecx]
    sub eax, 1
    mov [ecx], eax

    cmp word[ecx], -1
    je treat_zero

continue_treat_zero:    
    add edi, my_date_size ; go to next person in array
    add ecx, 4
    dec edx ; decrement contor
    cmp edx, 0
    jge for

finish:

    ;; FREESTYLE ENDS HERE
    ;; DO NOT MODIFY
    popa
    leave
    ret
    ;; DO NOT MODIFY
