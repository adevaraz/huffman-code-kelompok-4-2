/*
 * Nama File	: sortedlist.c
 * Deskripsi	: implementasi dari ADT sorted linked list huffman tree (sortedlist.h)
 * Author/NIM	: Nadia Melyani / 181524022
 				  Zara Veda Mahendra / 181524031
 * Tanggal/Ver	: 11/06/2019 ver.0
 * Compiler		: TDM-GCC 4.9.2
**/

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
sorted_list CreateSortedList(struct huffmanNode* value) {
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
addr_sorted AllocateElmt(struct huffmanNode* value) {
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
void InsertSorted(sorted_list *the_list, struct huffmanNode* value) {
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
 * List tidak kosong.
 * Mengembalikan element pertama dari sebuah list.
 **/
struct huffmanNode* GetFirstElmt(sorted_list L) {
	return L.front->info;
}

/**
 * Menghapus salah satu node berdasarkan probabilitas
 * yang dimilikinya dan probabilitas yang diminta
 **/
addr_sorted DeleteNode(sorted_list *L, double prob) {
	addr_sorted pdel = SearchNode(*L, prob);
	if(!IsFirstElmt(*L, pdel)) {
		addr_sorted pbefore = SearchNodeBefore(*L, pdel);
		pbefore->next = pdel->next;
	} else {
		L->front = pdel->next;
	}
	
	addr_sorted node = pdel;
	DeallocateElmt(&pdel);
	
	return node;
}

/**
 * Mengecek apakah sebuah node merupakan elemen pertama 
 * atau bukan
 **/
boolean IsFirstElmt(sorted_list L, addr_sorted node) {
	return (L.front == node);
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
