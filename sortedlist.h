/*
 * Nama File	: sortedlist.h
 * Deskripsi	: ADT sorted linked list huffman tree
 * Author/NIM	: Nadia Melyani / 181524022
 				  Zara Veda Mahendra / 181524031
 * Tanggal/Ver	: 11/06/2019 ver.0
 * Compiler		: TDM-GCC 4.9.2
**/

#ifndef SORTEDLIST_H

#define SORTEDLIST_H

#include <stdlib.h>
#include <stdio.h>
#include "boolean.h"
#include "huffmancode.h"

typedef char infotype;

typedef struct huffmanNode *addr_huffman;
typedef struct huffmanNode huffman_node;
//struct huffmanNode  {
//	infotype symbol;
//	addr_huffman parent;
//	addr_huffman left_c;
//	addr_huffman right_c;
//	double probability;
//};

typedef struct elmt_list_t *addr_sorted;
typedef struct elmt_list_t {
	addr_huffman info;
	addr_sorted next;
} elmt_list;

typedef struct sorted_list {
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
