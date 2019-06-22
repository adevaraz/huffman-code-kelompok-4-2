/* File :  list1.c   					*/
/* Desk :  body list  berkait dgn representasi fisik    */
/*         pointer; 					*/
/* 	   Representasi addr_string dgn pointer 		*/
/*	   infotype adalah integer			*/
/* Oleh :  ANI RAHMANI / 23501007 	  		*/
/* Tgl  :  25/10/01					*/	 

/* body dari List1.h   */

/***********************************************************************/

/**
 * Dimodifikasi oleh : Zara Veda Mahendra / 181524031
 * Tgl : 09/06/2019
 **/

#include "boolean.h"
#include "strlist.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* ** Prototype   **  */
/* ** Test List Kosong **  */
boolean ListEmpty(List  L)                        
{  /*  Mengirim true jika List kosong  */

   	return(First(L)==Nil);	
}

/* Pembuatan  List Kosong  */
void CreateList(List *L)
{  /* I.S  :  Sembarang    		*/
   /* F.S  :  Terbentuk  List kosong  	*/
   First(*L)=Nil;
}

/**
 * Membuat array menjadi kosong seperti saat pertama
 * di deklarasikan
 **/
void ClearArray(char *arr, int max_i) {
	int i;
	for(i = max_i; i >= 0; i--){
		arr[i] = '\0';
	}
}

 void clearstdin() {
    /* taken from https://stackoverflow.com/a/7898516  */
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

/* ********  MANAJEMEN MEMORY  ********* */
addr_string Alokasi(infotype  X[])
{/* Mengirimkan  addr_string  hasil alokasi    sebuah elemen */
 /* Jika alokasi  berhasil, maka  addr_string tidak nil, dan misalnya  */
 /* menghasilkan   P,  maka info(P)=X,  Next(P)=Nil;               */
 /* Jika alokasi  gagal,  mengirimkan  Nil 			   */
   addr_string P;
   P=(addr_string)malloc(sizeof(ElmtList));
   if(P!=Nil) { /* Berhasil  */
//    	Info(P)=X;
		strcpy(Info(P), X);
		Next(P)=Nil;
   }
   return P;	   
}

boolean InitStr(List *sentence, int *spaces, int *len) {
	char text[100], temp[26];
	int i, j;
	boolean stop, unique;
	CreateList(sentence);
	unique = false;
	printf("\nEnter the sentence : ");
	clearstdin();
	gets(text);
	
	(*len) = strlen(text);
	for(i = 0; i < (*len) ; i++) {
		text[i] = tolower(text[i]);
	}
	
	i = 1;
	while(i < (*len) && !unique) {
		if(text[0] != text[i]) {
			unique = true;
		}
		i++;
	}
	
	if(unique) {
		ClearArray(temp, 26);
		CreateList(sentence);
		for(i = 0; i < (*len); i++) {
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
						*spaces += 1;
					}
				}
			}
			InsVLast(sentence, temp);
		}
	}
	
	return unique;
}

void Dealokasi(addr_string *P)
{ /* I.S  : P terdefinisi      				*/
  /* F.S  : P dikembalikan ke  sistem 			*/
  /*   	    Melakukan dealokasi, pengembalian addr_string P */
    Next(*P)=Nil; 	
    free(*P);
}

/*   ** PENCARIAN SEBUAH ELEMEN LIST **   */
addr_string Search1(List L, infotype  X[])
{  /* Mencari apakah  ada elemen list dengan info(P)=X   */
   /* Jika ada, mengirimkan  addr_string dgn info(P)=X       */
   /* Jika  tidak ada, mengirimkan Nil 			 */
   /* Skema dengan boolean. Berlaku untuk List kosong  	 */
   addr_string  P=First(L); 
   boolean found=false;
   
   while((P!=Nil)&&(!found))  { 
	   if(strcmp(Info(P), X) == 0) {
		{	found=true;
		   	}
	   }   
        else {
	         P=Next(P);   
	   }		   
   } /*P=Nil or  found  */
   return P;
}	   


addr_string Search2(List L, infotype  X[])
{  /* Mencari apakah  ada elemen list dengan info(P)=X   */
   /* Jika ada, mengirimkan  addr_string dgn info(P)=X       */
   /* Jika  tidak ada, mengirimkan Nil 			 */
   /* Skema tanpa boolean. Tdk berlaku u/ List kosong  	 */
   addr_string  P; 
   if(First(L)!=Nil){
   	return Nil;
   } else {
   	P=First(L);
   	while((Next(P)!=Nil) && (strcmp(Info(P), X) != 0)) {
	      P=Next(P);   
   	} /* Next(P)==Nil or Info(P)==X */
   	if(Info(P)==X)  {
   	    return P;	
   	}else {
   	    return Nil;
	  }
   }
   return P;
}	   
   

boolean FSearch(List L, addr_string P)
{ /* Mencari apakah ada elemen List yang beralamat P  */
  /* Mengirimkan true jika ada, false jika tidak ada  */
  /* List Tidak mungkin kosong  */

  addr_string PTemp=First(L);
  boolean found=false;
  
  while((PTemp!=Nil)&&(!found)){
    if(PTemp==P) {
		found=true;
    }	     
    else
    { 
		PTemp=Next(PTemp);     
    }
      
  } /* PTemp==Nil or found / ketemu */
  return found;
}

addr_string SearchPrec(List L, infotype X[])
{ /* Mengirimkan addr_string elemen sebelum elemen yang nilainya=X */
  /* Mencari apakah ada elemen List dengan info(P)=X	       */
  /* Jika ada, mengirimkan addr_string Prec, dengan Next(Prec)=P   */
  /* dan Info(P)=X; Jika tidak ada mengirimkan Nil	       */
  /* Jika P adalah  elemen pertama, maka Prec=Nil	       */
  addr_string Prec;	
  addr_string P;
  
  if(Next(P)==Nil)  { /* List hanya berisi 1 elemen */
    Prec=Nil;
  } else { 
	  P=First(L);
	  while((Next(P)!=Nil) && (strcmp(Info(P), X) != 0)) {
	      	Prec=P;
            P=Next(P);		 	      
  	   }  /* Next(P)==Nil or Info(P)==X */
  
  	   if(Info(P)==X){ /* Ketemu Info (P)== X */
  	        return Prec;
  	   } else {
  	        return Nil;  /* tidak ada X di List */
  	   }
     } /* else */
}

/* ** PRIMITIF BERDASARKAN NILAI ** */

/* ** Penambahan Elemen ** */
void InsVFirst(List *L, infotype X[])
{  /* I.S  : L mungkin kosong          */
   /* F.S  : Melakukan alokasi sebuah elemen dan             */
   /*        menambahkan elemen pertama dengan nilai X jika  */
   /*        Alokasi berhasil 				     */
   addr_string P=Alokasi(X);
   if(P!=Nil) { /* Alokasi Berhasil */
      InsertFirst(&(*L),P);
    }
}

void InsVLast(List *L, infotype X[])
{ /* I.S  : L mungkin kosong          */
  /* F.S  : Melakukan alokasi sebuah elemen dan                */
  /*        menambahkan elemen list di akhir; elemen terakhir  */
  /*        yang baru bernilai X jika alokasi berhasil,        */	
  /*	    Jika alokasi gagal: I.S = F.S		       */
      	
     addr_string P=Alokasi(X);
     if(P!=Nil)
     {  InsertLast(&(*L),P);
        }
}

/* *** Penghapusan Elemen  ***  */

void DelVFirst(List *L, infotype X[])
{ /* I.S    : List tidak kosong  		                 */
  /* F.S    : Elemen pertama List dihapus, nilai info disimpan   */
  /*	      pada X dan alamat elemen pertama  di-dealokasi 	 */
  /* Kamus */
  addr_string  P;
  
  DelFirst(&(*L),&P); /* Hapus elemem pertama, blm didealokasi */
  strcpy(X, Info(P));
//  *X=Info(P); 		/* info dari First disimpan di X       */
  Dealokasi(&P);	  
}

void DelVLast(List *L, infotype X[])
{  /* I.S    : List tidak kosong  		                 */
   /* F.S    : Elemen terakhir list dihapus, nilai info disimpan */
   /*	      pada X dan alamat elemen terakhir di-dealokasi 	 */
   addr_string P;
   DelLast(&(*L),&P); 
   strcpy(X, Info(P));
        /* Hapus Elemen Terakhir, addr_codenya disimpan di P, */
        /* Belum diDealokasi, masih bisa dibaca isinya      */
//   *X=Info(P);	/* Info dari addr_string P, ditampung  */ 
   Dealokasi(&P);
}
	

/* *******  PRIMITIF BERDASARKAN ALAMAT ********	*/
/* Penambahan Elemen Berdasarkan Alamat 		*/

void InsertFirst(List *L, addr_string P)
{ /* I.S   : Sembarang, P sudah dialokasi		*/
  /* F.S   : Menambahkan elemen ber-addr_string P, sebagai  */
  /*         elemen pertama				*/
    Next(P)=First(*L);
    First(*L)=P;
}

void InsertAfter(List *L, addr_string P, addr_string Prec)
{ /* I.S   : Prec pastilah elemen  dan bukan elemen terakhir  */
  /*         P sudah dialokasi 					  */
  /* F.S   : Insert P sebagai elemen sesudah elemen beralamat Prec*/
	Next(P)=Next(Prec);
	Next(Prec)=P;
}

void InsertLast(List  *L, addr_string P)
{ /* I.S   : Sembarang, P sudah dialokasi			*/
  /* F.S   : P ditambahkan  sebagai elemen terakhir yang baru	*/

      addr_string Last;
      if(ListEmpty(*L)) { /* Jika kosong, Insert elemen pertama */
	   InsertFirst(&(*L),P);     
      }
      else { /* tdk kosong */
	    Last=First(*L);  
            while(Next(Last)!=Nil)  { /* menuju ke last */
	          Last=Next(Last);
	    	} /* Next(Last)==Nil */
	  
	  Next(Last)=P;	  
      }
}

/* ****** PENGHAPUSAN SEBUAH ELEMEN	*********   */
void DelFirst (List *L, addr_string *P)
{ /* I.S   : List tidak kosong 	*/
  /* F.S   : P adalah alamat elemen pertama list sebelum penghapusan */
  /*         Elemen List berkurang satu (mungkin menjadi kosong)     */
  /* First elemen yang baru adalah suksesor elemen pertama yang lama */
          
      *P=First(*L);
      First(*L)=Next(First(*L));
      Next(*P)=Nil;
    
 }

void DelP(List *L, infotype X[])
{ /* I.S   : Sembarang  */
  /* F.S   : Jika ada elemen  list beraddr_code P,dengan info (P)=X    */
  /*         Maka P dihapus dari List dan di-dealokasi		     */
  /*	     Jika tidak ada elemen List dengan info(P)=X, maka list  */
  /*         tetap. List mungkin menjadi kosomg karena penghapusan   */
    addr_string  P=First(*L);

    while((Next(P)!=Nil) && (strcmp(Info(P), X) != 0)){
          P=Next(P);
    } /*Next(P)=Nil or Info(P)= X */
    
    if(strcmp(Info(P), X) == 0) {
       Dealokasi(&P);
    }
}

void DelLast(List *L, addr_string *P)
{ /* I.S   : List tidak kosong  */
  /* F.S   : P adalah alamat elemen terakhir list sebelum penghapusan */
  /*	     Elemen list berkurang 1 (mungkin menjadi kosong)	      */
  /*         Last elemen baru adalah predessesor elemen pertama yang  */
  /*         lama, jika  ada					      */
  
  /* Kamus */     	
  addr_string Last,PrecLast;
  
  Last=First(*L);
  /* dari catatan di kelas */	
  if(Next(Last)==Nil)  { /* hanya 1 elemen */
	  DelFirst(&(*L),&(Last));
	}	  
  else { /* Lebih dr 1 elemen */
	  PrecLast=Nil;
	  while(Next(Last)!=Nil){   /* Maju sampai elemen terakhir */
		  PrecLast=Last;     
		  Last=Next(Last);
	  } /* Next(Last)=Nil */
	  *P=Last;
	  Next(PrecLast)=Nil;
	}
}

/* *************PROSES SEMUA ELEMEN ****************   */
void PrintInfo(List L)
{ /* I.S   : List mungkin kosong 	*/
  /* F.S   : Jika list tidak kosong, semua info yang disimpan pada */
  /*         elemen list di-print			  	   */
  /*         Jika list kosong, hanya menuliskan "List Kosong"	   */
  int i;	
  addr_string P=First(L);
  if( P==Nil) { 
  	  printf("List Kosong !\n");
  } else { /* List tidak kosong */
	    do { 
	 	  printf("[ %s ] ",Info(P));
		  P=Next(P);
		  i++;
	    } while(P!=Nil); 
	 }
  printf("\n");
}

/******************************************************/
/***   		PROSES TERHADAP LIST		    ***/
/******************************************************/
void DelAll(List *L)
{ /* Delete semua elemen list, dan alamat elemen di-dealokasi */
   infotype X;
   while(!ListEmpty(*L)) {
	  DelVFirst(&(*L),&X);
   }
}
