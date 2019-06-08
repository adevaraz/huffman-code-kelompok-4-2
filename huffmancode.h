/*
 * Nama File	: huffmancode.h
 * Deskripsi	: ADT huffman code
 * Author/NIM	: Nadia Melyani / 181524022
 				  Zara Veda Mahendra / 181524031
 * Tanggal/Ver	: 07/06/2019 ver.0
 * Compiler		: TDM-GCC 4.9.2
**/

#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>

#ifndef huffmancode_h

#define huffmancode_h

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

/*************** Constructor ***************/
huffman_tree CreateEmptyTree();
huffman_tree CreateTree(huffman_tree *the_tree, huffman_node the_root);
addr_huffman Allocate(infotype value);

/*************** Validate ***************/
bool IsLeftChild(huffman_node node);

/************ Huffman Operations ************/
huffman_tree SortProbability(huffman_tree *the_tree);


#endif
