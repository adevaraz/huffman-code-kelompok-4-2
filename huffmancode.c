/*
 * Nama File	: huffmancode.c
 * Deskripsi	: implementasi dari ADT huffman code (huffmancode.h)
 * Author/NIM	: Nadia Melyani / 181524022
 				  Zara Veda Mahendra / 181524031
 * Tanggal/Ver	: 07/06/2019 ver.0
 * Compiler		: TDM-GCC 4.9.2
**/

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdbool.h>
#include "huffmancode.h"
#include "sortedlist.h"
#include "codelist.h"
#include "stack.h"

/*************** Constructor ***************/
/**
 * Membuat tree baru yang kosong.
 * Mengembalikan sebuah tree dengan dengan root == NULL.
 **/
huffman_tree CreateEmptyTree() {
	huffman_tree T;
	
	T.tree = NULL;
	
	return T;
}

/**
 * Membuat tree baru yang sudah berisi satu Node sebagai root.
 * Mengembalikan sebuah tree dengan dengan root == node.
 **/
huffman_tree CreateTree(addr_huffman node) {
	huffman_tree T = CreateEmptyTree();
	
	T.tree = node;
	
	return T;
}

/**
 * Mengalokasikan node baru.
 * Mengembalikan sebuah node dengan node.symbol = value,
 * node.probability = prob dan node.left_c == node.right_c == node.parent == NULL.
 * Jika alokasi gagal, modul mengembalikan NULL.
 **/
addr_huffman Allocate(infotype value, double prob) {
	addr_huffman n_node = (addr_huffman) malloc(sizeof(huffman_node));
	
	if(n_node != NULL) {
		n_node->symbol = value;
		n_node->probability = prob;
		n_node->left_c = NULL;
		n_node->right_c = NULL;
		n_node->parent = NULL;
	}
	
	return n_node;
}

/*************** Validate ***************/
/**
 * Memeriksa apakah suatu node merupakan left_child dari
 * parentnya atau bukan.
 * Mengembalikan nilai .true. jika node merupakan left_child
 * dari parentnya;
 * Mengembalikan nilai .false. jika node bukan left_child
 * dari parentnya.
 **/
bool IsLeftChild(addr_huffman node) {
	return (node == node->parent->left_c);
}

/**
 * Mengecek apakah node yang bersangkutan 
 * merupakan anak kanan dari parent atau bukan
 **/
bool IsRightChild(addr_huffman N) {
	addr_huffman parent;
	parent = N->parent;
	return (parent->right_c == N);
}

/********** Huffman Operations **********/
/**
 * Anak kanan dari suatu node == NULL.
 * right_c dari suatu node == child.
 **/
void InsertRight(addr_huffman parent, addr_huffman child) {
	parent->right_c = child;
}

/**
 * Anak kanan dari suatu node == NULL.
 * right_c dari suatu node == child.
 **/
void InsertLeft(addr_huffman parent, addr_huffman child) {
	parent->left_c = child;
}

/**
 * Huffman tree masih kosong.
 * Mengembalikan huffman tree yang tidak kosong.
 **/
huffman_tree GenerateHuffmanTree(sorted_list *nodes_list) {
	addr_huffman firstnode, secondnode; //The nodes that will be merged
	addr_huffman mergednode, sorted_elmt;;
	struct elmt_list_t *temp;
	double sum;
	huffman_tree the_tree;
	
	while(nodes_list->front->next != NULL) {
		firstnode = GetFirstElmt((*nodes_list));
//		firstnode = sorted_elmt;
		temp = DeleteNode(&(*nodes_list), firstnode->probability);
		secondnode = GetFirstElmt((*nodes_list));
//		secondnode = sorted_elmt->info; 
		temp = DeleteNode(&(*nodes_list), secondnode->probability);
		
		sum =  firstnode->probability + secondnode->probability;
		mergednode = Allocate((infotype) sum, sum);
		InsertLeft(mergednode, firstnode);
		InsertRight(mergednode, secondnode);
		
		InsertSorted(&(*nodes_list), mergednode);
		
		firstnode = NULL;
		secondnode = NULL;
	}
	
	the_tree = CreateTree(mergednode);
	
	return the_tree;
}

//infotype ConvertToSymbol(huffman_tree the_tree, char[] code) {
//	
//}

void SetHuffmanCode(huffman_tree the_tree, ListCode *huffman_code) {
	
}

addr_huffman SearchHuffmanNode(huffman_tree the_tree, infotype keyword) {
	addr_huffman psearch = the_tree.tree;
	
	return psearch;
}

/*************** Destructor ***************/
/**
 * Menghapus keberadaan node di memori
 **/
addr_huffman Dealloc(addr_huffman *N) {
	(*N)->parent = NULL;
	(*N)->left_c = NULL;
	(*N)->right_c = NULL;
	free(*N);
}

/*************** Display ***************/

/**
 * Menampilkan sebuah jarak sesuai dengan level
 * tertentu
**/
void PrintTab(int level) {
	int i;
	for(i = 0; i < level; i++) {
		printf("  ");
	}
}

/**
 * Menampilkan pohon Huffman yang sudah terbentuk
**/
void PrintTree(huffman_tree T) {
	addr_huffman psearch;
	bool formal;
	int level;
	
	psearch = T.tree;
	formal = true;
	level = 0;
	printf("%c", psearch->symbol);
	while(psearch != NULL) {
		if(psearch->left_c != NULL && formal) {
			psearch = psearch->left_c;
			level = level + 1;
			PrintTab(level);
			printf("%c", psearch->symbol);
			formal = true;
		} else {
			if(psearch->right_c != NULL) {
				psearch = psearch->right_c;
				level = level + 1;
				PrintTab(level);
				printf("%c", psearch->symbol);
				formal = true;
			} else {
				psearch = psearch->parent;
				level = level - 1;
				formal = false;
			}
		}
	}
}

