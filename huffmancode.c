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
#include "intlist.h"

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
boolean IsLeftChild(addr_huffman node) {
	return (node == node->parent->left_c);
}

/**
 * Memeriksa apakah node yang bersangkutan 
 * merupakan anak kanan dari parent atau bukan
 **/
boolean IsRightChild(addr_huffman N) {
	addr_huffman parent;
	parent = N->parent;
	return (parent->right_c == N);
}

/**
 * Memeriksa apakah node merupakan leaf atau bukan. 
 * Mengembalikan nilai .true. jika node merupakan leaf.
 * Mengembalikan nilai .false. jika bukan.
 **/
boolean IsLeaf(addr_huffman node) {
	return (node->left_c == NULL && node->right_c);
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

/**
 * Input berupa code huffman.
 * Mengembalikan simbol/karakter yang telah di konversi dari code huffman.
 **/
infotype ConvertToSymbol(huffman_tree the_tree, char code[]) {
	
}

/**
 * Input kalimat.
 * Mengembalikan kalimat dalam bentuk code huffman.
 **/
void ConvertToHuffmanCode() {
	
}

/**
 * Menyimpan code huffman di sebuah list.
 * Huffman tree dimungkinkan tidak kosong.
 * Terbentuk sebuah list yang berisi simbol dan code huffmannya.
 **/
void CreateHuffmanCode(huffman_tree the_tree, ListCode *huffman_code) {
	addr_huffman checked_node = the_tree.tree;
	ListCode the_code_list;
	IntList code;
	boolean formal = true;
	
	while(checked_node != NULL) {
		if(IsLeaf(checked_node)) {
			code = GenerateCode(checked_node);
			InsVLastCode(&the_code_list, checked_node->symbol, code);
			if(checked_node == checked_node->parent->right_c) {
				if(checked_node->parent->parent->right_c != NULL) {
					/* Its grandparents still have right child */
					checked_node = checked_node->parent->parent->right_c;
				} else {
					/* It is the last node */
					checked_node = NULL;
				}
			} else {
				checked_node = checked_node->parent;
				formal = false;
			}
		} else {
			if(checked_node->left_c != NULL && formal) {
				checked_node = checked_node->left_c;
			} else {
				if(checked_node->right_c != NULL) {
					checked_node = checked_node->right_c;
					formal = true;
				}
			}
		}
	}
}

/**
 * Membentuk code huffman dari sebuah symbol.
 * Huffman tree dimungkinkan tidak kosong.
 * Terbentuk sebuah code untuk suatu simbol.
 **/
IntList GenerateCode(addr_huffman node) {
	addr_huffman parent = node->parent;
	stack code_stack;
	IntList number_list;
	
	CreateListInt(&number_list);
	
	while(parent != NULL) {
		if(node == parent->left_c) {
			Push(&code_stack, 0);
		} else {
			Push(&code_stack, 1);
		}
		
		parent = parent->parent;
	}
	
	/* Stored reversed code in list */
	while(code_stack.top != NULL) {
		InsVLastInt(&number_list, Pop(&code_stack));
	}
	
	return number_list;
}

//addr_huffman SearchLeaf(addr_huffman node) {
//	if(node == NULL) {
//		return;
//	} else {
//		if(IsLeaf(node)) {
//			return node;
//		} else {
//			/* Go to its children */
//			SearchLeaf(node->left_c);
//			SearchLeaf(node->right_c);
//		}
//	}
//}

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

