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
#define INIT_BY_C_P 2
#define BACK 3

#define CODE_EXIST true
#define CODE_NOT_EXIST false

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main() {
	boolean end = false;
	boolean exist;
	int choice = 0;
	int init_choice = 0;
	
	int len = 0;
	int spaces = 0;
	
	char to_be_converted[100];
	
	sorted_list node_list = CreateEmptyList();
	huffman_tree the_tree = CreateEmptyTree();
	List sentence;
	ListCode codes;
	
	char *converted_code;
	
	CreateListCode(&codes);
	
	while(!end) {
		ClearArray(to_be_converted);
		system("cls");
		Menu();
		scanf(" %d", &choice);
		switch(choice) {
			case INIT_TREE :
				system("cls");
				if(the_tree.tree == NULL) {
					InitMenu();
					scanf(" %d", &init_choice);
					switch(init_choice) {
						case INIT_BY_SENTENCE :
							system("cls");
							
							printf("[  I N I T  B Y  S E N T E N C E  ]\n\n");
							InitStr(&sentence, &spaces, &len);
							GenerateSortedList(sentence, &node_list, (double) (len - spaces));
							
							the_tree = GenerateHuffmanTree(&node_list);
							
							codes = CreateHuffmanCode(the_tree);
							
							printf("\nThe Codes :\n");
							PrintInfoCode(codes);
							printf("Conversion Result : ");
							ConvertToHuffmanCode(codes, sentence);
							break;
					
						case INIT_BY_C_P :
							printf("[  I N I T  B Y  C H A R A C T E R  ]\n\n");
							InitFromProb(&node_list);
							
							the_tree = GenerateHuffmanTree(&node_list);
							
							codes = CreateHuffmanCode(the_tree);
							
							printf("\nThe Codes :\n");
							PrintInfoCode(codes);	
							break;
						
						case BACK :
							printf("\nBack to menu...\n");
							break;
					}
				
					init_choice = 0;
				} else {
					printf("\nThe tree has been initialized before..\n");
					printf("\nBack to menu..\n");
				}
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
					
					ConvertToHuffmanCode();
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
				
				printf("Enter the codes : ");
				scanf(" %s", to_be_converted);
				
				exist = ConvertToSymbol(the_tree, to_be_converted, &converted_code);
				switch(exist) {
					case CODE_EXIST :
						printf("\nConversion Result : ");
						printf("%s", &converted_code);
						break;
					
					case CODE_NOT_EXIST :
						printf("The code can't be converted");
						break;
				}
				break;
			
			case DELETE_TREE :
				system("cls");
				
				if(the_tree.tree != NULL) {
					DeleteHuffmanTree(the_tree.tree);
					the_tree.tree = NULL;
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
	}
	
	InitFromProb(&node_list, 'a', 0.18);
	InitFromProb(&node_list, 'e', 0.04);
	InitFromProb(&node_list, 'k', 0.3);
	InitFromProb(&node_list, 'l', 0.03);
	InitFromProb(&node_list, 'n', 0.2);
	InitFromProb(&node_list, 'b', 0.1);
	InitFromProb(&node_list, 'y', 0.15);
	//GenerateSortedList(sentence, &node_list, (double) (len - spaces));
	
	printf("\nSorted List :\n");
	PrintSorted(node_list);
	
	the_tree = GenerateHuffmanTree(&node_list);
	
	printf("\nHuffman Tree : ");
	PrintTree(the_tree.tree);
	
	CreateListCode(&codes);
	printf("\n\nCodes : ");
	printf("\n");
	codes = CreateHuffmanCode(the_tree);
	PrintInfoCode(codes);
	
	printf("\n");
//	ConvertToHuffmanCode(codes, sentence);
	
	printf("\nyahooo!");
	getch();
	return 0;
}


