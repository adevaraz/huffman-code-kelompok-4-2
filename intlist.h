/* File :  list1.h   					*/
/* Desk :  deklarasi list  berkait dgn representasi     */
/* 	   fisik pointer; 				*/
/* 	   Representasi addr_int dgn pointer 		*/
/* Oleh :  ANI RAHMANI / 23501007 	  		*/
/* Tgl  :  25/10/01					*/	 

/* IntList :  */

/**
 * Modifikasi oleh : Zara Veda Mahendra / 181524031
 * Tgl : 15 Juni 2019
 **/

#ifndef INTLIST_H
#define INTLIST_H 

#include "boolean.h"
#include <stdlib.h>

#define Nil  NULL				
#define CodeInfo(P) (P)->info		
#define Next(P) (P)->next
#define First(L) ((L).First)	

typedef int type;                              
typedef struct tElmtListInt *addr_int;
typedef struct  tElmtListInt   {
	type info;
	addr_int next;
	}ElmtIntList;

/* Definisi  IntList                   */
/* IntList Kosong  :  First(L) = Nil   */
/* Setiap elemen dengan addr_int P dapat diacu CodeInfo(P),Next(P)       */
/* Elemen terakhir  IntList :jika addressnya Last, maka next(Last)=Nil */

typedef struct {
	addr_int First;
	}IntList;

/* ** Prototype   **  */
/* ** Test IntList Kosong **  */
boolean ListIntEmpty(IntList  L);                        
/*  Mengirim true jika IntList kosong  */

/* Pembuatan  IntList Kosong  */
void CreateListInt(IntList *L);
/* I.S  :  Sembarang    		*/
/* F.S  :  Terbentuk  IntList kosong  	*/

/* Manajeman  memory  			*/
addr_int AlokasiInt(type  X);
 /* Mengirimkan  addr_int  hasil alokasi    sebuah elemen */
 /* Jika alokasi  berhasil, maka  addr_int tidak nil, dan misalnya  */
 /* menghasilkan   P,  maka info(P)=X,  Nest(P)=Nil;               */
 /* Jika alokasi  gagal,  mengirimkan  Nil 			   */

void DealokasiInt(addr_int *P);
/* I.S  :   P  terdefinisi         	*/
/* F.S  :   P dikembalikan ke  sistem 	*/
/*   	    Melakukan  dealokasi, pengembalian addr_int  P */


/*   ** PENCARIAN SEBUAH ELEMEN LIST **   */

addr_int Search1Int(IntList L, type  X);
/* Mencari apakah  ada elemen list dengan info(P)=X      */
/* Jika ada, mengirimkan  addr_int elemen tersebut	 */
/* Jika  tidak ada, mengirimkan Nil 			 */

boolean FSearchInt(IntList L, addr_int P);
/* Mencari apakah  ada elemen IntList yang  beralamat   P   */
/* Mengirimkan true jika ada, false jika tidak ada  	 */


addr_int SearchPrecInt(IntList L, type X);
/* mencari apakah ada elemen IntList  yang beralamat P 	     */
/* Mnegirimkan addr_int elemen sebelum elemen yang nilainya X */
/* Mencari apakah ada elemen IntList dengan info(P)=X	     */
/* Jika ada, mengirimkan addr_int Prec, dengan Next(Prec)=P   */

/* ** PRIMITIF BERDASARKAN NILAI ** */

/* ** Penambahan Elemen ** */
void InsVFirstInt(IntList *L, type X);
/* I.S  : L mungkin kosong          */
/* F.S  : Melakukan alokasi sebuah elemen dan                */
/*        menambahkan elemen pertama dengan nilai X jika     */
/*        Alokasi berhasil 				     */

void InsVLastInt(IntList *L, type X);
/* I.S  : L mungkin kosong          */
/* F.S  : Melakukan alokasi sebuah elemen dan                */
/*        menambahkan elemen list di akhir; elemen terakhir  */
/*        yang baru bernilai X jika alokasi berhasil, 	     */	
/*	  Jika alokasi gagal: I.S = F.S			     */

/* *** Penghapusan Elemen  ***  */
	  

void DelVFirstInt(IntList *L, type *X);
  /* I.S    : IntList tidak kosong  		                 */
  /* F.S    : Elemen pertama IntList dihapus, nilai info disimpan   */
  /*	      pada X dan alamat elemen pertama  di-dealokasi 	 */


void DelVLastInt(IntList *L, type *X);
  /* I.S    : IntList tidak kosong  		                 */
  /* F.S    : Elemen terakhir list dihapus, nilai info disimpan  */
  /*	      pada X dan alamat elemen terakhir di-dealokasi 	 */

/* *******  PRIMITIF BERDASARKAN ALAMAT ********	*/
/* Penambahan Elemen Berdasarkan Alamat 		*/

void InsertFirstInt(IntList *L, addr_int P);
/* I.S   : Sembarang, P sudah dialokasi			*/
/* F.S   : Menambahkan elemen ber-addr_int P, sebagai    */
/*         elemen pertama				*/

void InsertAfterInt(IntList *L, addr_int P, addr_int Prec);
/* I.S   : Prec pastilah elemen list dan bukan elemen terakhir  */
/*         P sudah dialokasi 					*/
/* F.S   : Insert P sebagai elemen sesudah elemen beralamat Prec*/

void InsertLastInt(IntList  *L, addr_int P);
/* I.S   : Sembarang, P sudah dialokasi				*/
/* F.S   : P ditambahkan  sebagai elemen terakhir yang baru	*/

/* ****** PENGHAPUSAN SEBUAH ELEMEN	*********   */
void DelFirstInt(IntList *L, addr_int *P);
/* I.S   : IntList tidak kosong 	*/
/* F.S   : P adalah alamat elemen pertama list sebelum penghapusan */
/*         Elemen IntList berkurang satu (mungkin menjadi kosong)     */
/* First elemen yang baru adalah suksesor elemen pertama yang lama */

void DelPInt(IntList *L, type X);
/* I.S   : Sembarang  */
/* F.S   : Jika ada elemen  list beraddress P,dengan info (P)=X    */
/*         Maka P dihapus dari IntList dan di-dealokasi		   */
/*	   Jika tidak ada elemen IntList dengan info(P)=X, maka list  */
/*         tetap. IntList mungkin menjadi kosomg karena penghapusan   */

void DelLastInt(IntList *L, addr_int *P);
/* I.S   : IntList tidak kosong  */
/* F.S   : P adalah alamat elemen terakhir list sebelum penghapusan */
/*	   Elemen list berkurang 1 (mungkin menjadi kosong)	    */
/*         Last elemen baru adalah predessesor elemen pertama yang  */
/*         jika tidak ada					    */

void DelAfterInt(IntList *L, addr_int *Pdel, addr_int Prec);
/* I.S   : IntList tidak kosong, Prec adalah anggota IntList		*/
/* F.S   : Menghapus Next(Prec) :				*/
/*         Pdel adalah alamat elemen IntList yang dihapus		*/

/* *************PROSES SEMUA ELEMEN ****************   */
void PrintInfoInt(IntList L);
/* I.S   : IntList mungkin kosong 	*/
/* F.S   : Jika list tidak kosong, semua info yang disimpan pada */
/*         elemen list di-print					 */
/*         Jika list kosong, hanya menuliskan "IntList Kosong"	 */

/******************************************************/
/***   		PROSES TERHADAP LIST		    ***/
/******************************************************/
void DelAllInt(IntList *L);
/* Delete semua elemen list, dan alamat elemen di-dealokasi */


#endif
