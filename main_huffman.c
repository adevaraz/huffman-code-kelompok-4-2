#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "boolean.h"
#include "huffmancode.h"
#include "sortedlist.h"
#include "strlist.h"
#include "codelist.h"

#define CODE_EXIST true
#define CODE_NOT_EXIST false

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main() {
	char text[100] = { "ananda bayu" }, temp[26];
	char *converted_code;
	int i, j, len, spaces = 0;
	sorted_list node_list;
	huffman_tree the_tree;
	List sentence;
	boolean stop;
	ListCode codes;
	
	len = strlen(text);
	for(i = 0; i < len ; i++) {
		text[i] = tolower(text[i]);
	}
	
	CreateList(&sentence);
	for(i = 0; i < len; i++) {
		stop = false;
		j = 0;
		while(!stop) {
			if(text[i] != ' ' && text[i] != '\0') {
				temp[j] = text[i];
				i++;
				j++;
			} else {
				stop = true;
				if(text[i] == ' ') {
					spaces += 1;
				}
			}
		}
		InsVLast(&sentence, temp);
		ClearArray(temp);
	}
	
	printf("Spaces : %d\n", spaces);
	printf("Str List : ");
	PrintInfo(sentence);
	
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
	PrintTreeCoba(the_tree.tree);
	
	CreateListCode(&codes);
	printf("\n\nCodes : ");
	printf("\n");
	codes = CreateHuffmanCode(the_tree);
	PrintInfoCode(codes);
	
	switch(ConvertToSymbol(the_tree, "00010111", &converted_code)) {
		case CODE_EXIST :
			printf("%s", &converted_code);
			break;
		case CODE_NOT_EXIST :
			printf("The code can't be converted");
			break;
	}
	
	printf("\n");
//	ConvertToHuffmanCode(codes, sentence);
	
	printf("\nyahooo!");
	getch();
	return 0;
}
