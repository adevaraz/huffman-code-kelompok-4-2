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

/************ Huffman Operations ************/

huffman_tree SortProbability(huffman_tree *the_tree);

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

bool IsEmpty(huffman_tree T) {
	return T.tree == NULL;
}

void GenerateTreeNadia(huffman_tree *T, sorted_list *L) {
	addr_huffman firstnode, secondnode;
	addr_huffman mergednode;
	double sum;
	
	firstnode = DeleteSmallestElmt(&(*L));
	secondnode = DeleteSmallestElmt(&(*L));
	sum = firstnode->probability + secondnode->probability;
	mergednode = Allocate((infotype) sum, sum);
	InsertSorted(&(*L), mergednode);

}




