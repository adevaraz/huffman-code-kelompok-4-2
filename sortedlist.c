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
#include "boolean.h"
#include "sortedlist.h"

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
