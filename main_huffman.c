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
#define BACK 3

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main() {
	int len = 0;
	int spaces = 0;
	int choice = 0;
	int init_choice = 0;
	boolean end = false;
	sorted_list node_list;
	huffman_tree the_tree;
	List sentence;
	ListCode codes;
	
	while(!end) {
		system("cls");
		choice = Menu();
	
		switch(choice) {
			case INIT_TREE :
				system("cls");
				init_choice = InitMenu();
			
				switch(init_choice) {
					case INIT_BY_SENTENCE :
						InitStr(&sentence, &spaces, &len);
						GenerateSortedList(sentence, &node_list, (double) (len - spaces));
						codes = CreateHuffmanCode(the_tree);
						printf("\n");
						ConvertToHuffmanCode(codes, sentence);
						break;
					
					case INIT_BY_W_P :
						
						break;
					
					case BACK :
						break;
			}
			break;
		
			case PRINT_TREE :
				system("cls");
				
				printf("[\t\tH U F F M A N  T R E E\t\t]\n\n");
				PrintTree(the_tree.tree);
				getch();
				break;
			
			case CODE_LIST :
				system("cls");
				
				printf("[\t\tT H E  C O D E S\t\t]\n\n");
				PrintInfoCode(codes);
				getch();
				break;
				
			case CONVERT_SENTENCE :
				system("cls");
				DelAll(&sentence);
				
				printf("[\t\tC O N V E R T  S E N T E N C E\t\t]\n\n");
				
				printf("Conversion Result : ");
				getch();
				break;
				
			case CONVERT_CODE :
				system("cls");
				
				printf("[\t\tC O N V E R T  C O D E\t\t]\n\n");
				printf("Available codes : \n");
				PrintInfoCode(codes);
				
				printf("Conversion Result : ");
				getch();
				break;
			
			case DELETE_TREE :
				system("cls");
				
				printf("Deleting..");
				getch();
				printf("The tree is empty\n");
				getch();
				break;
			
			case EXIT : 
				system("cls");
				printf("Exiting system..\n");
				end = true;
				break;
		}
	}
	
	printf("Spaces : %d\n", spaces);
	printf("Str List : ");
	PrintInfo(sentence);
	
	
	
	printf("\nSorted List :\n");
	PrintSorted(node_list);
	
	the_tree = GenerateHuffmanTree(&node_list);
	
	
	
	CreateListCode(&codes);
	printf("\n\nCodes : ");
	printf("\n");
	
	PrintInfoCode(codes);
	
	printf("\nyahooo!");
	getch();
	return 0;
}


