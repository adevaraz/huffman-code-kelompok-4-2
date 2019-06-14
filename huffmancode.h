/*
 * Nama File	: huffmancode.h
 * Deskripsi	: ADT huffman code
 * Author/NIM	: Nadia Melyani / 181524022
 				  Zara Veda Mahendra / 181524031
 * Tanggal/Ver	: 07/06/2019 ver.0
 * Compiler		: TDM-GCC 4.9.2
**/

#ifndef HUFFMANCODE_H

#define HUFFMANCODE_H

#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>
#include "huffmancode.h"
#include "codelist.h"
#include "stack.h"
#include "boolean.h"
#include "sortedlist.h"

typedef char infotype;

typedef struct huffmanNode *addr_huffman;
typedef struct huffmanNode  {
	infotype symbol;
	addr_huffman parent;
	addr_huffman left_c;
	addr_huffman right_c;
	double probability;
} huffman_node;

typedef struct {
	addr_huffman tree;
} huffman_tree;

typedef struct elmt_list_t *addr_sorted;
typedef struct elmt_list_t elmt_list;
struct elmt_list_t {
	addr_huffman info;
	addr_sorted next;
};

/*************** Constructor ***************/
huffman_tree CreateEmptyTree();
huffman_tree CreateTree(addr_huffman node);
addr_huffman Allocate(infotype value, double prob);

/*************** Validate ***************/
bool IsLeftChild(addr_huffman node);
bool IsRightChild(addr_huffman N);

/********** Huffman Operations **********/
void Insertion(huffman_tree *tree, infotype value, infotype probability);
void InsertRight(addr_huffman parent, addr_huffman child);
void InsertLeft(addr_huffman parent, addr_huffman child);
huffman_tree GenerateHuffmanTree(sorted_list *nodes_list);
void SetHuffmanCode(huffman_tree the_tree, ListCode *huffman_code);
addr_huffman SearchHuffmanNode(huffman_tree the_tree, infotype keyword);

/*************** Destructor ***************/
addr_huffman Dealloc(addr_huffman *N);

/***************  Display  ***************/
void PrintTab(int level);
void PrintTree(huffman_tree T);

#endif
