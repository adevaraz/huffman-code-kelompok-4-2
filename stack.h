/*
 * Nama File	: stack.h
 * Deskripsi	: ADT stack
 * Author/NIM	: Nadia Melyani / 181524022
 				  Zara Veda Mahendra / 181524031
 * Tanggal/Ver	: 09/06/2019 ver.0
 * Compiler		: TDM-GCC 4.9.2
**/

#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>

typedef int vartype;
typedef struct ElmtStack *addr_stack;
typedef struct ElmtStack {
	vartype info;
	addr_stack next;
} elmt_stack;

typedef struct {
	addr_stack top;
} stack;

/*************** Constructor ***************/
addr_stack CreateStack(stack *S);
addr_stack Alloc(vartype info);

/*************** Destructor ***************/
addr_stack Deallocate(addr_stack *S);
void DeleteStack(stack *S);

/************ Stack Operations ************/
void Push(stack *S, vartype info);
vartype Pop(stack *S);

#endif
