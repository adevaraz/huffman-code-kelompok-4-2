/*
 * Nama File	: sortedlist.c
 * Deskripsi	: implementasi dari ADT sorted linked list huffman tree (sortedlist.h)
 * Author/NIM	: Nadia Melyani / 181524022
 				  Zara Veda Mahendra / 181524031
 * Tanggal/Ver	: 11/06/2019 ver.0
 * Compiler		: TDM-GCC 4.9.2
**/

#ifndef sortedlist_c
#define sortedlist_c 

#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include "boolean.h"
#include "sortedlist.h"
#include "huffmancode.h"


/*************** Constructor ***************/
/**
 * Membuat list baru yang kosong.
 * Mengembalikan sebuah list dengan dengan front == NULL.
 **/
sorted_list CreateEmptyList() {
	sorted_list n_list;
	
	n_list.front = NULL;
	
	return n_list;
}

/**
 * Membuat list baru yang sudah berisi satu element sebagai front.
 * Mengembalikan sebuah list dengan dengan front == node.
 **/
sorted_list CreateSortedList(addr_huffman value) {
	sorted_list n_list = CreateEmptyList();
	addr_sorted n_node = AllocateElmt(value);
	
	n_list.front = n_node;
	
	return n_list;
}

/**
 * Mengalokasikan node baru.
 * Mengembalikan sebuah node dengan node.info == value dan node.next == NULL.
 * Jika alokasi gagal, modul mengembalikan NULL.
 **/
addr_sorted AllocateElmt(addr_huffman value) {
	addr_sorted n_node = (addr_sorted) malloc(sizeof(elmt_list));
	
	if(n_node != NULL) {
		n_node->info = value;
		n_node->next = NULL;
	}
	
	return n_node;
}

/********* Sorted List Operations *********/
/**
 * List sudah memiliki minimal 1 element.
 * Menambahkan element ke list dengan terurut secara ascending.
 **/
void InsertSorted(sorted_list *the_list, addr_huffman value) {
	addr_sorted n_node = AllocateElmt(value);
	addr_sorted prec_node = the_list->front;
	
	if(n_node->info->probability >= the_list->front->info->probability) {
		while(n_node->info->probability >= prec_node->next->info->probability && prec_node->next != NULL) {
			prec_node = prec_node->next;
		}
		
		n_node->next = prec_node->next;
		prec_node->next = n_node->next;
	} else {
		/* Insertion as front list */
		n_node->next = the_list->front;
		the_list->front = n_node;
	}
}

#endif
