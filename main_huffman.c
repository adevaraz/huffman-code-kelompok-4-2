#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "boolean.h"
#include "huffmancode.h"
#include "sortedlist.h"
#include "strlist.h"
#include "codelist.h"
#include "stack.h"

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
	boolean unique;
	boolean number;
	int choice = 0;
	int init_choice = 0;

	int len = 0;
	int spaces = 0;
	int n = 0;
	int i = 0;

	char to_be_converted[100];

	sorted_list node_list = CreateEmptyList();
	huffman_tree the_tree = CreateEmptyTree();
	List sentence, n_sentence;
	ListCode codes;

	char *converted_code;
	IntList converted_sent;

	CreateListCode(&codes);

	while(!end) {
		ClearArray(to_be_converted, 100);
		system("cls");
		Menu();
		fflush(stdin);
		scanf("%d", &choice);

		switch(choice) {
			case INIT_TREE :
				system("cls");
				if(the_tree.tree == NULL) {
					InitMenu();
					clearstdin();
					scanf("%d", &init_choice);

					switch(init_choice) {
						case INIT_BY_SENTENCE :
							system("cls");
							printf("====================\n");
							printf("INIT BY SENTENCE\n");
							printf("====================\n\n");
							unique = InitStr(&sentence, &spaces, &len);
							if(unique) {
								printf("\nProcessing..\n");
								GenerateSortedList(sentence, &node_list, (double) len - spaces);
								
								the_tree = GenerateHuffmanTree(&node_list);

								codes.First = CreateHuffmanCode(the_tree);

								printf("\nThe Codes :\n");
								PrintInfoCode(codes);
								exist  = ConvertToHuffmanCode(codes, sentence, &converted_sent);

								switch(exist) {
									case CODE_EXIST :
										printf("\nConversion Result : ");
										PrintInfoInt(converted_sent);
									break;

									case CODE_NOT_EXIST :
										printf("\nThe sentence cannot be converted\n");
									break;
								}
							} else {
								printf("\nPlease enter different sentence..\n");
							}
						break;

						case INIT_BY_C_P :
							system("cls");
							printf("===================================\n");
							printf("INIT BY CHARACTER AND PROBABILITY\n");
							printf("===================================\n\n");
							n = InitFromProb(&node_list);
							
							if(n != 1) {
								printf("\nProcessing..\n");
								the_tree = GenerateHuffmanTree(&node_list);

								codes.First = CreateHuffmanCode(the_tree);
	
								printf("\nThe Codes :\n");
								PrintInfoCode(codes);
							} else {
								printf("\nPlease enter more than one character..");
							} 
						break;

						case BACK :
							printf("\nBack to menu...\n");
						break;
						
						default :
							printf("\nPlease enter the right number!\n");
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

				printf("====================\n");
				printf("PRINT TREE\n");
				printf("====================\n\n");
				if(the_tree.tree != NULL) {
					PrintTree(the_tree.tree);
				} else {
					printf("The Huffman Tree is empty!\n");
				}
			break;

			case CODE_LIST :
				system("cls");

				printf("====================\n");
				printf("CODE LIST\n");
				printf("====================\n");
				PrintInfoCode(codes);
			break;

			case CONVERT_SENTENCE :
				system("cls");
				if(the_tree.tree != NULL) {

					printf("=========================\n");
					printf("CONVERT SENTENCE TO CODE\n");
					printf("=========================\n\n");

					printf("Available character : ");
					PrintInfoCode(codes);

					InitStr(&n_sentence, &spaces, &len);

					exist = ConvertToHuffmanCode(codes, n_sentence, &converted_sent);

					switch(exist) {
						case CODE_EXIST :
							printf("\nConversion Result : ");
							PrintInfoInt(converted_sent);
						break;

						case CODE_NOT_EXIST :
							printf("\nThe sentence cannot be converted\n");
						break;
					}
				} else {
					printf("The Huffman Tree is empty!\n");
				}
			break;

			case CONVERT_CODE :
				system("cls");

				converted_code = NULL;
				printf("=========================\n");
				printf("CONVERT CODE TO SYMBOL\n");
				printf("=========================\n\n");
				printf("Available codes : ");
				PrintInfoCode(codes);

				do{
					printf("\nEnter the codes : ");
					fflush(stdin);
					scanf(" %s", to_be_converted);
					i = 0;
					number = false;
					while(i < strlen(to_be_converted) - 1) {
						if(to_be_converted[i] == '0' || to_be_converted[i] == '1') {
							number = true;
						} else {
							printf("\nThe codes must be 0 or 1\n");
							break;
						}
						i++;
					}					
				}while(!number);


				exist = ConvertToSymbol(the_tree, to_be_converted, &converted_code);
				switch(exist) {
					case CODE_EXIST :
						printf("\nConversion Result : ");
						printf("%s", &converted_code);
						break;

					case CODE_NOT_EXIST :
						printf("\nThe code cannot be converted\n");
						break;
				}
			break;

			case DELETE_TREE :
				system("cls");

				if(the_tree.tree != NULL) {
					printf("Deleting..\n");
					DeleteHuffmanTree(the_tree.tree);
					DeleteList(&node_list);
					the_tree.tree = NULL;
					getch();
					printf("\nThe Huffman Tree is now empty\n");
				} else {
					printf("\nThe Huffman Tree is empty\n");
				}

			break;

			case EXIT :
				system("cls");
				printf("Exiting system..");
				end = true;
			break;

			default :
				printf("\nPlease enter the right number!\n");
			break;
		}
		printf("\n\nPress any key to continue..\n");
		getch();
	}

	return 0;
}
