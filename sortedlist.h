/*
 * Nama File	: sortedlist.h
 * Deskripsi	: ADT sorted linked list huffman tree
 * Author/NIM	: Nadia Melyani / 181524022
 				  Zara Veda Mahendra / 181524031
 * Tanggal/Ver	: 11/06/2019 ver.0
 * Compiler		: TDM-GCC 4.9.2
**/

#ifndef sortedlist_h
#define sortedlist_h 

#include <stdlib.h>
#include <stdio.h>
#include "boolean.h"
#include "huffmancode.h"

typedef struct elmt_list_t *addr_sorted;
typedef struct elmt_list_t {
	addr_huffman info;
	addr_sorted next;
} elmt_list;

typedef struct {
	addr_sorted front;
} sorted_list;

/*************** Constructor ***************/
sorted_list CreateEmptyList();
sorted_list CreateSortedList(addr_huffman value);
addr_sorted AllocateElmt(addr_huffman value);

/********* Sorted List Operations *********/
void InsertSorted(sorted_list *the_list, addr_huffman value);
addr_sorted SearchNode(sorted_list L, double prob);
addr_sorted SearchNodeBefore(sorted_list L, addr_sorted node);
bool IsFirstElmt(sorted_list L, addr_sorted node);

/*************** Destructor ***************/
addr_sorted DeallocateElmt(addr_sorted *N);
addr_sorted DeleteNode(sorted_list *L, double prob);
void DeleteList(sorted_list *L);


#endif
