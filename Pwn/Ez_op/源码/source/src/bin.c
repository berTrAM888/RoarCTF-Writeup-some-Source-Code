#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "utility.h"


typedef struct{
    int *data;
    int count;
    int cursor;
} Stack;

const char *delims = " \n\r\t";


Stack *stack_create(int count);
void stack_delete(Stack *s);
void stack_clear(Stack *s);
// return 0 if failed
int stack_push(Stack *s, int data);
int stack_pop(Stack *s, int *data);

void load_stack(Stack *s, char *input);
void show_stack(Stack *s);
// return 0 if parse failed
int parser(Stack *code, Stack *data);


int main(int argc, char *argv[]){
    Stack *data = stack_create(64);
    Stack *code = stack_create(128);
    char *input = malloc(sizeof(int) * 128);

    read_char(input, sizeof(int) * 128);
    load_stack(code, input);
    read_char(input, sizeof(int) * 128);
    load_stack(data, input);

    if(parser(code, data)){
        show_stack(data);
    }

    free(input);
    stack_delete(code);
    stack_delete(data);

    return 0;
}

// Stack

void stack_clear(Stack *s){
    if(s == NULL){
        return;
    }
    else{
        s->cursor = -1;
    }
}

void stack_delete(Stack *s){
    if(s == NULL){
        return;
    }

    free(s->data);
    free(s);
}

Stack *stack_create(int count){
    int *d;
    Stack *s;

    if((s = malloc(sizeof(Stack))) == NULL){
        return NULL;
    }
    if((d = malloc(sizeof(int) * count)) == NULL){
        free(s);
        return NULL;
    }

    memset(d, 0, sizeof(int) * count);

    s->data = d;
    s->count = count;
    s->cursor = -1;

    return s;
}

int stack_push(Stack *s, int data){
    if(s == NULL){
        return 0;
    }

    int next = s->cursor + 1;

    if(next == s->count){
        return 0;
    }
    else{
        s->data[next] = data;
        s->cursor = next;
        return 1;
    }
}

int stack_pop(Stack *s, int *data){
    if(s == NULL){
        return 0;
    }
    
    if(s->cursor == -1){
        return 0;
    }
    else{
        *data = s->data[s->cursor];
        s->cursor = s->cursor - 1;
        return 1;
    }
}

// Parser

#define PUSH 0x2A3D
#define POP 0xFFFF28
#define ADD 0x0
#define SUB 0x11111
#define MUL 0xABCEF
#define DIV 0x514
#define LOAD 0xFFFFFFFF
#define SAVE 0x10101010

int code_push(Stack *stack, Stack *data);
int code_pop(Stack *stack, Stack *data);
int code_add(Stack *stack, Stack *data);
int code_sub(Stack *stack, Stack *data);
int code_mul(Stack *stack, Stack *data);
int code_div(Stack *stack, Stack *data);
int code_load(Stack *stack, Stack *data);
int code_save(Stack *stack, Stack *data);


void load_stack(Stack *s, char *input){
    char *str;
    int count;

    if(s == NULL){
        return;
    }

    int *tmp = malloc(sizeof(int) * s->count);

    for(count = 0, str = strtok(input, delims);
        count < s->count && str != NULL;
        count += 1, str = strtok(NULL, delims))
    {
        tmp[count] = atoi(str);
    }

    for(int i = count - 1; i >= 0; --i){
        if(!stack_push(s, tmp[i])){
            break;
        }
    }

    free(tmp);
}

void show_stack(Stack *s){
    int data;

    if(s == NULL){
        return;
    }
    if(s->cursor == -1){
        return;
    }

    for(int i = 0; i < s->cursor; ++i){
        printf("%d ", s->data[i]);
    }
    printf("%d\n", s->data[s->cursor]);
}

int parser(Stack *code, Stack *data){
    int c;
    int result = 1;
    Stack *stack = stack_create(64);

    while(result && stack_pop(code, &c)){
        switch(c){
        case PUSH:
            result = code_push(stack, data);
            break;
        case POP:
            result = code_pop(stack, data);
            break;
        case ADD:
            result = code_add(stack, data);
            break;
        case SUB:
            result = code_sub(stack, data);
            break;
        case MUL:
            result = code_mul(stack, data);
            break;
        case DIV:
            result = code_div(stack, data);
            break;
        case LOAD:
            result = code_load(stack, data);
            break;
        case SAVE:
            result = code_save(stack, data);
            break;
        default:
            result = 0;
        }
    }

    stack_delete(stack);
    return result;
}


int code_push(Stack *stack, Stack *data){
    int d;

    if(stack_pop(data, &d) && stack_push(stack, d)){
        return 1;
    }

    return 0;
}

int code_pop(Stack *stack, Stack *data){
    int d;

    if(stack_pop(stack, &d) && stack_push(data, d)){
        return 1;
    }

    return 0;
}

int code_add(Stack *stack, Stack *data){
    int x, y;

    if(stack_pop(stack, &x) && stack_pop(stack, &y)){
        return stack_push(stack, x + y);
    }

    return 0;
}

int code_sub(Stack *stack, Stack *data){
    int x, y;

    if(stack_pop(stack, &x) && stack_pop(stack, &y)){
        return stack_push(stack, x - y);
    }

    return 0;
}

int code_mul(Stack *stack, Stack *data){
    int x, y;

    if(stack_pop(stack, &x) && stack_pop(stack, &y)){
        return stack_push(stack, x * y);
    }

    return 0;
}

int code_div(Stack *stack, Stack *data){
    int x, y;

    if(stack_pop(stack, &x) && stack_pop(stack, &y)){
        return stack_push(stack, x / y);
    }

    return 0;
}

int code_load(Stack *stack, Stack *data){
    int offset, d;

    if(stack_pop(stack, &offset)){
        d = stack->data[stack->cursor + offset];
        return stack_push(stack, d);
    }

    return 0;
}

int code_save(Stack *stack, Stack *data){
    int offset, d;

    if(stack_pop(stack, &offset) && stack_pop(stack, &d)){
        stack->data[stack->cursor + offset] = d;
        return 1;
    }

    return 0;
}

void door(){
    system("echo shell");
}

