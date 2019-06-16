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
#include <string.h>
#include "strlist.h"
#include "boolean.h"

typedef char infotype;

struct huffmanNode;
typedef struct elmt_list_t *addr_sorted;
typedef struct elmt_list_t {
	struct huffmanNode *info;
	addr_sorted next;
} elmt_list;

typedef struct sorted_list {
	addr_sorted front;
} sorted_list;

/*************** Constructor ***************/
sorted_list CreateEmptyList();
sorted_list CreateSortedList(struct huffmanNode *value);
addr_sorted AllocateElmt(struct huffmanNode *value);

/********* Sorted List Operations *********/
void InsertSorted(sorted_list *the_list, struct huffmanNode *value);
addr_sorted SearchNode(sorted_list L, infotype value);
addr_sorted SearchNodeBefore(sorted_list L, addr_sorted node);
boolean IsFirstElmt(sorted_list L, addr_sorted node);
struct huffmanNode* GetFirstElmt(sorted_list L);
void GenerateSortedList(List string_l, sorted_list *sorted_l, double total);
double CountProbability(double freq, double count);
void ClearArray(char *arr);
void CopyElmt(addr_sorted *dest, addr_sorted source);

/*************** Destructor ***************/
addr_sorted DeallocateElmt(addr_sorted *N);
addr_sorted DeleteNode(sorted_list *L, infotype value);
void DeleteList(sorted_list *L);

/*************** Display ***************/
void PrintSorted(sorted_list the_list);

#endif
