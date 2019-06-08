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
#include "huffmancode.h"

addr_huffman Dealloc(addr_huffman *N) {
	(*N)->parent = NULL;
	(*N)->left_c = NULL;
	(*N)->right_c = NULL;
	free(*N);
}
/**
 * Menghapus keberadaan node di memori
**/

bool IsRightChild(addr_huffman N) {
	addr_huffman parent;
	parent = N->parent;
	return (parent->right_c == N);
}
/**
 * Mengecek apakah node yang bersangkutan 
 * merupakan anak kanan dari parent atau bukan
**/

void PrintTab(int level) {
	int i;
	for(i = 0; i < level; i++) {
		printf("  ");
	}
}
/**
 * Menampilkan sebuah jarak sesuai dengan level
 * tertentu
**/

void DisplayHuffmanTree(huffman_tree T) {
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
/**
 * Menampilkan pohon Huffman yang sudah terbentuk
**/

