extern strtok
extern strcmp
extern strlen
extern qsort

global get_words
global compare_func
global sort

section .data
    delim db " .,", 10, 0

section .text

compare_func:
    enter 0, 0

    mov edx, [ebp + 8]
    mov ecx, [ebp + 12]

    push dword [ecx]
    push dword [edx] ; pentru strcmp

    push dword [ecx] ; strlen primul cuvant
    push dword [edx] ; strlen al doilea cuvant  strcmp(string a, string b)

    call strlen
    add esp, 4

    mov edx, [ebp + 8]
    mov ebx, eax

    call strlen
    mov ecx, [ebp + 12]
    add esp, 4

    sub eax, ebx
    neg eax
    je compare

    add esp, 8
    jmp final_call

;; sort(char **words, int number_of_words, int size)
;  functia va trebui sa apeleze qsort pentru soratrea cuvintelor 
;  dupa lungime si apoi lexicografic
sort:
    enter 0, 0

    mov edx, [ebp + 8]
    mov ebx, [ebp + 12] 
    mov ecx, [ebp + 16]

    push compare_func
    push ecx
    push ebx
    push edx

    call qsort

    leave
    ret

;; get_words(char *s, char **words, int number_of_words)
;  separa stringul s in cuvinte si salveaza cuvintele in words
;  number_of_words reprezinta numarul de cuvinte
get_words:
    enter 0, 0

    mov esi, [ebp + 16]
    mov ebx, [ebp + 12]
    mov edx, [ebp + 8]
    mov edi, 1 ; initializare contor

    push delim ; Primul call de strtok - pentru primul cuvant din string
    push edx
    call strtok
    add esp, 8
    
    mov [ebx], eax

    add ebx, 4 ; Mut pointerul lui ebx cu un element la dreapta

    jmp while_loop

call_strtok:
    push delim
    push 0
    call strtok
    add esp, 8

    mov [ebx], eax ; Il adaug in vector
    add ebx, 4

    inc edi ; Incrementez contorul

while_loop:
    cmp edi, esi
    jl call_strtok

compare:
    call strcmp
    add esp, 8

final_call:
    leave
    ret