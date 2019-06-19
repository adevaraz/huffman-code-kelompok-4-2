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
	return (node->left_c == NULL && node->right_c == NULL);
}

/********** Huffman Operations **********/
/**
 * Anak kanan dari suatu node == NULL.
 * right_c dari suatu node == child.
 **/
void InsertRight(addr_huffman parent, addr_huffman child) {
	parent->right_c = child;
	child->parent = parent;
}

/**
 * Anak kanan dari suatu node == NULL.
 * right_c dari suatu node == child.
 **/
void InsertLeft(addr_huffman parent, addr_huffman child) {
	parent->left_c = child;
	child->parent = parent;
}

/**
 * Huffman tree masih kosong.
 * Mengembalikan huffman tree yang tidak kosong.
 **/
huffman_tree GenerateHuffmanTree(sorted_list *nodes_list) {
	addr_huffman firstnode, secondnode; //The nodes that will be merged
	addr_huffman mergednode;
	struct elmt_list_t *temp;
	double sum;
	addr_sorted phelp = nodes_list->front;
	huffman_tree the_tree;
	
	while(nodes_list->front->next != NULL) {
		firstnode = GetFirstElmt((*nodes_list));
		temp = DeleteNode(&(*nodes_list), firstnode->symbol);
		secondnode = GetFirstElmt((*nodes_list));
		temp = DeleteNode(&(*nodes_list), secondnode->symbol);
		
		sum =  firstnode->probability + secondnode->probability;
		mergednode = Allocate((char) sum, sum);
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
 * Menyimpan code huffman di sebuah list.
 * Huffman tree dimungkinkan tidak kosong.
 * Terbentuk sebuah list yang berisi simbol dan code huffmannya.
 **/
ListCode CreateHuffmanCode(huffman_tree the_tree) {
	addr_huffman checked_node = the_tree.tree, phelp;
	ListCode the_code_list;
	IntList code;
	boolean formal = true;
	
	CreateListInt(&code);
	CreateListCode(&the_code_list);
	
	while(checked_node != NULL) {
		if(IsLeaf(checked_node)) {
			code = GenerateCode(checked_node);
			InsVLastCode(&the_code_list, checked_node->symbol, code);
			if(checked_node == checked_node->parent->right_c) {
				phelp = checked_node;
				
				/* Loop for checking whether it is last node or no */
				while(phelp->parent != NULL) {
					if(phelp == phelp->parent->right_c) {
						phelp = phelp->parent;
					} else {
						break;
					}
				}
				
				checked_node = phelp->parent;
			} else {
				checked_node = checked_node->parent;
			}
			
			formal = false;
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
	
	return the_code_list;
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
	
	CreateStack(&code_stack);
	CreateListInt(&number_list);
	
	while(parent != NULL) {
		if(node == parent->left_c) {
			Push(&code_stack, 0);
		} else {
			Push(&code_stack, 1);
		}
		
		node = parent;
		parent = parent->parent;
	}
	
	/* Stored reversed code in list */
	while(code_stack.top != NULL) {
		InsVLastInt(&number_list, Pop(&code_stack));
	}
	
	return number_list;
}

/**
 * Input berupa code huffman.
 * Menampilkan simbol/karakter yang telah di konversi dari code huffman.
 **/
bool ConvertToSymbol(huffman_tree the_tree, char code[], char* output) {
	addr_huffman phelp;
	bool exist;
	int i, j;
	j = 0;
	i = 0;
	exist = true;
	phelp = the_tree.tree;
	while(i < strlen(code)) {
		while(phelp != NULL && exist) {
			if(code[i] == '0' || code [i] == '1') {
				if(code[i] == '0') {
					phelp = phelp->left_c;	
				} else {
					phelp = phelp->right_c;
				}
				if (IsLeaf(phelp)) {
					output[j] = phelp->symbol;
					phelp = NULL;
					j++;	
				}		
			} else {
				exist = false;
			}
			i++;
		}
		phelp = the_tree.tree;
	}
	return exist;
}

/**
 * Input kalimat.
 * Menampilkan kalimat dalam bentuk code huffman.
 **/
boolean ConvertToHuffmanCode(ListCode the_codes, List sentence) {
	addr_code phelp;
	addr_string pword;
	int i, len;
	boolean same = true;
	
	pword = sentence.First;
	
	while(pword != NULL && same) {
		len = strlen(pword->info);
		i = 0;
		while(i < len && same) {
			phelp = the_codes.First;
			same = false;
			while(phelp != NULL && !same) {
				if(phelp->symbol == pword->info[i]) {
					same = true;
				} else {
					phelp = phelp->next;
				}
			}
			
			if(same) {
				PrintInfoInt(phelp->code);
				i++;
			}
		}
		
		pword = pword->next;
	}
	
	return same;
}

void DeleteHuffmanTree(addr_huffman the_node) {
	
	if(the_node != NULL) {
		DeleteHuffmanTree(the_node->left_c);
		DeleteHuffmanTree(the_node->right_c);
		Dealloc(&the_node);
	}
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
 * Menampilkan pohon Huffman yang sudah terbentuk
**/
void PrintTree(addr_huffman T) {
	addr_huffman phelp = T;
	int level;
	
	if(phelp != NULL) {
		level = Level(phelp);
		Indent(level);
		printf("[ %c ] %g ", phelp->symbol, phelp->probability);
		PrintTree(phelp->left_c);
		PrintTree(phelp->right_c);
	}
}

/**
 * Mencari level dari suatu node
 **/
int Level(addr_huffman node) {
	int level = 0;
	
	while(node->parent != NULL) {
		level += 1;
		node = node->parent;
	}
	
	return level;
}

/**
 * Menampilkan space sesuai dengan level
 */
void Indent(int n) {
	int i = 0;
	
	printf("\n");
	while(i < n) {
		printf("\t");
		i++;
	}
}

/**
 * Menampilkan menu.
 */
int Menu() {
	int choice;
	
	printf("[  M E N U  ]\n\n");
	printf("1 - Init Huffman Tree\n");
	printf("2 - Print Huffman Tree\n");
	printf("3 - List of codes\n");
	printf("4 - Convert new sentence from exist Huffman Tree\n");
	printf("5 - Convert code to symbol\n");
	printf("6 - Delete Huffman Tree\n");
	printf("7 - Exit\n");
	printf("Choose a number : ");
	scanf(" %d", &choice);
	return choice;
 }
 
 int InitMenu() {
	int choice;
 	
	printf("[  I N I T  M E N U  ]\n\n");
	printf("1 - Init by sentence\n");
	printf("2 - Init by word and its probability\n");
	printf("3 - Back\n");
	printf("Choose a number : ");
	scanf(" %d", &choice);
	
	return choice;
 }
