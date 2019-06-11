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
		/* Loop for comparing new element to element list*/
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

/**
 * Menghapus keberadaan node di memori
 **/
addr_sorted DeallocateElmt(addr_sorted *N) {
	(*N)->info = NULL;
	(*N)->next = NULL;
	
	free(*N);
}

/**
 * Menghapus salah satu node berdasarkan probabilitas
 * yang dimilikinya dan probabilitas yang diminta
 **/
void DeleteNode(sorted_list *L, double prob) {
	addr_sorted node = SearchNode(*L, prob);
	addr_sorted pbefore = SearchNodeBefore(*L, node);
	
	pbefore->next = node->next;
	DeallocateElmt(&node);
}

/**
 * Menghapus seluruh node yang berada dalam list
 **/
void DeleteList(sorted_list *L) {
	addr_sorted pdel;
	
	while((*L).front != NULL) {
		pdel = (*L).front;
		(*L).front = (*L).front->next;
		DeallocateElmt(&pdel);
	}
}

/**
 * Mendapatkan alamat dari sebuah node yang dicari
 * berdasarkan probabilitas
 **/
addr_sorted SearchNode(sorted_list L, double prob) {
	addr_sorted psearch = L.front;
	bool found = false;
	
	while(psearch != NULL && !found) {
		if(psearch->info->probability == prob) {
			found = true;
		} else {
			psearch = psearch->next;
		}
	}
	
	return psearch;
}

/**
 * Mendapatkan alamat dari node sebelum node yang lain
 * untuk mengakses "before" dari sebuah node
 **/
addr_sorted SearchNodeBefore(sorted_list L, addr_sorted node) {
	addr_sorted psearch = L.front;
	bool found = false;
	
	while(psearch->next != NULL && !found) {
		if(psearch->next == node) {
			found = true;
		} else {
			psearch = psearch->next;
		}
	}
	
	return psearch;
}

#endif
