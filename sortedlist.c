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
	addr_sorted n_node = AllocateElmt(&(*value));
	addr_sorted prec_node = the_list->front;

	if(the_list->front == NULL) {
		the_list->front = n_node;
	} else {
		if(n_node->info->probability >= the_list->front->info->probability) {

			while(prec_node->next != NULL) {
					/* Loop for comparing new element to element list*/
				if(n_node->info->probability >= prec_node->next->info->probability) {
					prec_node = prec_node->next;
				} else {
					break;
				}
			}

			n_node->next = prec_node->next;
			prec_node->next = n_node;
		} else {
			/* Insertion as front list */
			n_node->next = the_list->front;
			the_list->front = n_node;
		}
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
addr_sorted DeleteNode(sorted_list *L, infotype value) {
	addr_sorted pdel = SearchNode(*L, value);
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
addr_sorted SearchNode(sorted_list L, infotype value) {
	addr_sorted psearch = L.front;
	bool found = false;

	while(psearch != NULL && !found) {
		if(psearch->info->symbol == value) {
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

/**
 * Menghitung probabilitas yaitu banyaknya frekuensi
 * dibagi dengan total huruf
 **/
double CountProbability(double freq, double count) {
	return (freq/count);
}

/**
 * Membuat List yang sudah terurut dan berisi huruf-huruf beserta
 * peluang munculnya huruf tersebut, dari sebuah kalimat yang ada
 **/
void GenerateSortedList(List string_l, sorted_list *sorted_l, double total) {
	addr_string phelp = string_l.First;
	addr_sorted psearch, pdel;
	addr_sorted n_sorted = (addr_sorted) malloc(sizeof(elmt_list));
	addr_huffman n_node;
	char word[MAX_WORD];
	int i;
	bool found = false;
	double prob;
	
	psearch = sorted_l->front;
	*sorted_l = CreateEmptyList();
	prob = CountProbability(1, total);
	psearch = (*sorted_l).front;
	while(phelp != NULL) {
		ClearArray(word, MAX_WORD);
		strcpy(word, phelp->info);
		for(i = 0; i < strlen(word); i++) {
			psearch = sorted_l->front;
			found = false;
			if(sorted_l->front == NULL) {
				n_node = Allocate(word[i], prob);
				*sorted_l = CreateSortedList(n_node);
			} else {
				while(psearch != NULL && !found) {
					if(word[i] == psearch->info->symbol) {
						psearch->info->probability += prob;
						CopyElmt(&pdel, psearch);
						DeleteNode(sorted_l, psearch->info->symbol);
						InsertSorted(sorted_l, pdel->info);
						found = true;
						free(pdel);
					} else {
						psearch = psearch->next;
					}
				}
				if(!found) {
					n_node = Allocate(word[i], 0.0);
					n_node->probability = prob;
					InsertSorted(sorted_l, n_node);
					
				}				
			}
		}
		phelp = phelp->next;
	}
}

/**
 * Membuat list terurut melalui probabilitas
 * yang sudah ada
 **/
int InitFromProb(sorted_list *L) {
	addr_huffman n_node;
	infotype info;
	double prob;
	int i, n;
	
	do{
		printf("\nHow many character do you want to enter? : ");
		fflush(stdin);
		scanf(" %d", &n);
		if(n < 1){
			printf("\nPlease enter the right number.\n");
		} else {
			break;
		}		
	}while(true);

	
	if(n != 1) {
		for(i = 0; i < n; i++) {
			printf("\nEnter character [%d] : ", i+1);
			scanf(" %c", &info);
			printf("Enter probability [%d] : ", i+1);
			scanf(" %lf", &prob);
			n_node = Allocate(info, prob);
			InsertSorted(&(*L), n_node);
			n_node = NULL;
		}
	}
	
	return n;
}

/**
 * Menampilkan list yang terurut ke layar
 **/
void PrintSorted(sorted_list the_list) {
	addr_sorted phelp = the_list.front;
	
	while(phelp != NULL) {
		printf("[ %c ]", phelp->info->symbol);
		printf(" %g\n", phelp->info->probability);
		
		phelp = phelp->next;
	}
}

/**
 * Membuat salinan dari sebuah node
 **/
void CopyElmt(addr_sorted *dest, addr_sorted source) {
	*dest = AllocateElmt(source->info);
}
