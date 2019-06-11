/*
 * Nama File	: stack.c
 * Deskripsi	: Implementasi dari stack.h
 * Author/NIM	: Nadia Melyani / 181524022
 				  Zara Veda Mahendra / 181524031
 * Tanggal/Ver	: 09/06/2019 ver.0
 * Compiler		: TDM-GCC 4.9.2
**/

#include "stack.h"

/*************** Constructor ***************/
/**
 * Membuat stack yang kosong
 **/
addr_stack CreateStack(stack *S) {
	(*S).top = NULL;
}

/**
 * Mengalokasikan tempat di memori untuk sebuah node baru
 **/
addr_stack Alloc(vartype info) {
	addr_stack new_node = (addr_stack)malloc(sizeof(elmt_stack));
	new_node->info = info;
	new_node->next = NULL;
}

/*************** Destructor ***************/
/**
 * Menghapus keberadaan node di memori
 **/
addr_stack Deallocate(addr_stack *S) {
	(*S)->next = NULL;
	free(*S);
}

/************ Stack Operations ************/
/**
 * Menambahkan isi stack
 **/
void Push(stack *S, vartype info) {
	addr_stack node = Alloc(info);
	node->next = (*S).top;
	(*S).top = node;
}

/**
 * Mengambil isi stack
 **/
vartype Pop(stack *S) {
	vartype pop;
	addr_stack phelp;
	pop = (*S).top->info;
	phelp = (*S).top;
	(*S).top = (*S).top->next;
	Deallocate(&phelp);
	
	return pop;
}

/**
 * Menghapus semua isi stack
 **/
void DeleteStack(stack *S) {
	addr_stack pdel;
	pdel = (*S).top;
	while((*S).top != NULL) {
		pdel = (*S).top;
		(*S).top= (*S).top->next;
		Deallocate(&pdel);
	}
}
