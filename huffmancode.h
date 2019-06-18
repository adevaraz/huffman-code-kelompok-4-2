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
#include "codelist.h"
#include "stack.h"
#include "boolean.h"
#include "sortedlist.h"

typedef char infotype;

typedef struct huffmanNode *addr_huffman;
typedef struct huffmanNode {
	infotype symbol;
	addr_huffman parent;
	addr_huffman left_c;
	addr_huffman right_c;
	double probability;
} huffman_node;

struct elmt_list_t;

typedef struct {
	addr_huffman tree;
} huffman_tree;

/*************** Constructor ***************/
huffman_tree CreateEmptyTree();
huffman_tree CreateTree(addr_huffman node);
addr_huffman Allocate(infotype value, double prob);

/*************** Validate ***************/
boolean IsLeftChild(addr_huffman node);
boolean IsRightChild(addr_huffman N);
boolean IsLeaf(addr_huffman node);

/********** Huffman Operations **********/
void Insertion(huffman_tree *tree, infotype value, infotype probability);
void InsertRight(addr_huffman parent, addr_huffman child);
void InsertLeft(addr_huffman parent, addr_huffman child);
huffman_tree GenerateHuffmanTree(sorted_list *nodes_list);
IntList GenerateCode(addr_huffman node);
ListCode CreateHuffmanCode(huffman_tree the_tree);

/*************** Destructor ***************/
addr_huffman Dealloc(addr_huffman *N);

/***************  Display  ***************/
void PrintTree(addr_huffman T);
int Level(addr_huffman node);
void Indent(int n);

#endif
