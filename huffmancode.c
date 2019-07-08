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

#define COMPRESSED_FILE "compressed_file.txt"

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
addr_code CreateHuffmanCode(huffman_tree the_tree) {
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
	
	return the_code_list.First;
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
boolean ConvertToHuffmanCode(ListCode the_codes, List sentence, IntList *output) {
	addr_code phelp;
	addr_int pinsert;
	addr_string pword;
	int i, len;
	boolean same = true;
	
	CreateListInt(output);
	pword = sentence.First;
	
	//Loop for checking whether the word can be converted or no
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
				pinsert = phelp->code.First;
				
				while(pinsert != NULL) {
					InsVLastInt(output, pinsert->info);
					pinsert = pinsert->next;
				}
				
				free(pinsert);
				i++;
			}
		}
		
		pword = pword->next;
	}
	
	return same;
}

/**
 * Huffman tree tidak kosong.
 * Menghapus huffman tree menjadi kosong.
 **/
void DeleteHuffmanTree(addr_huffman the_node) {
	
	if(the_node != NULL) {
		DeleteHuffmanTree(the_node->left_c);
		DeleteHuffmanTree(the_node->right_c);
		Dealloc(&the_node);
	}
}

/********** Compressing Operation ***********/

/**
 * File masih dalam bentuk text.
 * Hasil kompresi melalui Huffman Code disimpan ke file dalam bentuk simbol-simbol ASCII.
 **/
void CompressFile() {
	char text[100], src_file[100], temp[26], compressed[100];
	char *compressed_text;
	int space = 0;
	int len = 0;
	int i, j, binaryLength, symbolCount;
	addr_int phelp;
	List list_txt;
	boolean unique, exist;
	FILE *fsrc, *fdest;
	huffman_tree the_tree;
	sorted_list node_list;
	ListCode the_codes;
	IntList converted_text;
	
	the_tree = CreateEmptyTree();
	node_list = CreateEmptyList();
	ClearArray(text, 100);
	ClearArray(src_file, 100);
	CreateList(&list_txt);
	
	printf("\nEnter the file name : ");
	fflush(stdin);
	scanf(" %s", src_file);
	
	fsrc = fopen(src_file, "r");
	
	if(fsrc != NULL) {
		while(fread(&text, (sizeof(char)) * 100 , 1, fsrc) != 0) {
			if(feof(fsrc)) {
				break;
			}
		}	
		
		ToLowerSentence(text);
		unique = IsUnique(text);
				
		if(unique) {
			printf("\nProcessing..\n");
			
			ClearArray(temp, 26);
			len = strlen(text);
			for(i = 0; i < len; i++) {
				boolean stop = false;
				j = 0;
				while(!stop) {
					if(text[i] != ' ' && text[i] != '\0') {
						temp[j] = text[i];
						i++;
						j++;
					} else {
						stop = true;
						if(text[i] == ' ') {
							temp[j] = text[i];
//							space += 1;
						}
					}
				}
				InsVLast(&list_txt, temp);
				ClearArray(temp, 26);
			}
				
			GenerateSortedList(list_txt, &node_list, (double) len);
			the_tree = GenerateHuffmanTree(&node_list);		
			the_codes.First = CreateHuffmanCode(the_tree);
			PrintTree(the_tree.tree);
			exist = ConvertToHuffmanCode(the_codes, list_txt, &converted_text);
			
			if(exist) {
				fdest = fopen(COMPRESSED_FILE, "w+");
				
				phelp = converted_text.First;
				ClearArray(compressed, 100);
				i = 0;
				while(phelp != NULL) {
					itoa(phelp->info, &compressed[i], 10);
					phelp = phelp->next;
					i++;
				}
			    binaryLength = strlen(compressed);
			    symbolCount = binaryLength / 8 + 1;
			    compressed_text = malloc(symbolCount + 1);
				binaryToText(compressed, binaryLength, compressed_text, symbolCount);
				fprintf(fdest, compressed_text);
				printf("Conversion completed.\n");
				fclose(fdest);
			} else {
				printf("Compression failed.");
			}
		}
	} else {
		printf("The file doesn't exist!");
	}
	free(compressed_text);
	fclose(fsrc);
}

unsigned long binaryToDecimal(char *binary, int length) {
    int i;
    int len = length - 1;
    unsigned long decimal = 0;
    unsigned long weight = 1;
    binary += len;
    weight = 1;
    for(i = 0; i < len; i++, binary--) {
        if(*binary == '1') {
            decimal += weight;
            weight *= 2;
        }
    }
    
	return decimal;
}

void binaryToText(char *binary, int binaryLength, char *text, int symbolCount) {
    int i;
    for(i = 0; i < binaryLength; i+=8, binary += 8) {
        char *byte = binary;
        byte[8] = '\0';
        *text++ = binaryToDecimal(byte, 8);
    }
    text -= symbolCount;
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
		if(IsLeaf(T)) {
			printf("[ %c ] %g ", phelp->symbol, phelp->probability);
		} else {
			printf("[ %g ]", phelp->probability);
		}
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
void Menu() {
	printf("====================\n");
	printf("MENU\n");
	printf("====================\n\n");
	printf("1 - Init huffman tree\n");
	printf("2 - Print huffman tree\n");
	printf("3 - Code list\n");
	printf("4 - Convert sentence to huffman code\n");
	printf("5 - Convert code to symbol\n");
	printf("6 - Delete huffman tree\n");
	printf("7 - Compress file\n");
	printf("8 - Exit\n");
	printf("Choose a number : ");
 }
 
void InitMenu() {
	printf("====================\n");
	printf("INIT MENU\n");
	printf("====================\n\n");
	printf("1 - Init by sentence\n");
	printf("2 - Init by character and probability\n");
	printf("3 - Back\n");
	printf("Choose a number : ");
 }
 
 
