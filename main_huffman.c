#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "boolean.h"
#include "huffmancode.h"
#include "sortedlist.h"
#include "strlist.h"
#include "codelist.h"

#define INIT_TREE 1
#define PRINT_TREE 2
#define CODE_LIST 3
#define CONVERT_SENTENCE 4
#define CONVERT_CODE 5
#define DELETE_TREE 6
#define EXIT 7

#define INIT_BY_SENTENCE 1
#define INIT_BY_W_P 2

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main() {
	int len = 0;
	int spaces = 0;
	int choice = 0;
	int init_choice = 0;
	boolean end = false;
	sorted_list node_list = CreateEmptyList();
	huffman_tree the_tree = CreateEmptyTree();
	List sentence;
	ListCode codes;
	
	CreateListCode(&codes);
	
	while(!end) {
		system("cls");
		choice = Menu();
	
		switch(choice) {
			case INIT_TREE :
				system("cls");
				init_choice = InitMenu();
			
				switch(init_choice) {
					case 1 :
						InitStr(&sentence, &spaces, &len);
						GenerateSortedList(sentence, &node_list, (double) (len - spaces));
						the_tree = GenerateHuffmanTree(&node_list);
						codes = CreateHuffmanCode(the_tree);
						printf("\n");
						ConvertToHuffmanCode(codes, sentence);
						break;
					
					case 2 :
						
						break;
				}
				
				init_choice = 0;
			break;
		
			case PRINT_TREE :
				system("cls");
				
				printf("[  H U F F M A N  T R E E  ]\n\n");
				if(the_tree.tree != NULL) {
					PrintTree(the_tree.tree);	
				} else {
					printf("The Huffman Tree is empty!\n");
				}
				break;
			
			case CODE_LIST :
				system("cls");
				
				printf("[  T H E  C O D E S  ]\n\n");
				PrintInfoCode(codes);
				break;
				
			case CONVERT_SENTENCE :
				system("cls");
				if(the_tree.tree != NULL) {
					DelAll(&sentence);
				
					printf("[  C O N V E R T  S E N T E N C E  ]\n\n");
				
					printf("Conversion Result : ");
				} else {
					printf("The Huffman Tree is empty!\n");
				}
				break;
				
			case CONVERT_CODE :
				system("cls");
				
				printf("[  C O N V E R T  C O D E  ]\n\n");
				printf("Available codes : \n");
				PrintInfoCode(codes);
				
				printf("Conversion Result : ");
				break;
			
			case DELETE_TREE :
				system("cls");
				
				if(the_tree.tree != NULL) {
					printf("Deleting..");
					getch();
					printf("The Huffman Tree is now empty\n");	
				} else {
					printf("The Huffman Tree is empty\n");
				}
				
				break;
			
			case EXIT : 
				system("cls");
				printf("Exiting system..\n");
				end = true;
				break;
				
			default :
				printf("\nPlease enter the right number!\n");
				break;
		}
		getch();
		choice = 0;
	}
	
//	printf("Spaces : %d\n", spaces);
//	printf("Str List : ");
//	PrintInfo(sentence);
//	
//	
//	
//	printf("\nSorted List :\n");
//	PrintSorted(node_list);
//	
//	
//	
//	
//	CreateListCode(&codes);
//	printf("\n\nCodes : ");
//	printf("\n");
//	
//	PrintInfoCode(codes);
	
	printf("\nyahooo!");
	getch();
	return 0;
}


