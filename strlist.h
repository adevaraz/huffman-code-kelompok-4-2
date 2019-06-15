/* File :  list1.h   					*/
/* Desk :  deklarasi list  berkait dgn representasi     */
/* 	   fisik pointer; 				*/
/* 	   Representasi addr_string dgn pointer 		*/
/* Oleh :  ANI RAHMANI / 23501007 	  		*/
/* Tgl  :  25/10/01					*/	 

/* List :  */

/***********************************************************************/

/**
 * Dimodifikasi oleh : Zara Veda Mahendra / 181524031
 * Tgl : 09/06/2019
 **/

#ifndef STRLIST_H
#define STRLIST_H 

#include "boolean.h"
#include <stdlib.h>

#define Nil  NULL				//definisikan Nil dengan NULL (addr_string yg tidak punya adress)
#define Info(P) (P)->info		//P : sebuah addr_string
#define Next(P) (P)->next
#define First(L) ((L).First)	//L : list
#define MAX_WORD 26

typedef char infotype; //type definition, diubah di sini jika infotypenya berubah                               
typedef struct tElmtlist *addr_string;
typedef struct  tElmtlist   {
	infotype info[MAX_WORD];
	addr_string next;
} ElmtList;

/* Definisi  List                   */
/* List Kosong  :  First(L) = Nil   */
/* Setiap elemen dengan addr_string P dapat diacu Info(P),Next(P)       */
/* Elemen terakhir  List :jika addr_codenya Last, maka next(Last)=Nil */

typedef struct {
	addr_string First;
} List;

/* ** Prototype   **  */
/* ** Test List Kosong **  */
boolean ListEmpty(List  L);                        
/*  Mengirim true jika List kosong  */

/* Pembuatan  List Kosong  */
void CreateList(List *L);
/* I.S  :  Sembarang    		*/
/* F.S  :  Terbentuk  List kosong  	*/

/* Manajeman  memory  			*/
addr_string Alokasi(infotype  X[]);
 /* Mengirimkan  addr_string  hasil alokasi    sebuah elemen */
 /* Jika alokasi  berhasil, maka  addr_string tidak nil, dan misalnya  */
 /* menghasilkan   P,  maka info(P)=X,  Nest(P)=Nil;               */
 /* Jika alokasi  gagal,  mengirimkan  Nil 			   */

void Dealokasi(addr_string *P);
/* I.S  :   P  terdefinisi         	*/
/* F.S  :   P dikembalikan ke  sistem 	*/
/*   	    Melakukan  dealokasi, pengembalian addr_string  P */


/*   ** PENCARIAN SEBUAH ELEMEN LIST **   */

addr_string Search1(List L, infotype  X[]);
/* Mencari apakah  ada elemen list dengan info(P)=X      */
/* Jika ada, mengirimkan  addr_string elemen tersebut	 */
/* Jika  tidak ada, mengirimkan Nil 			 */

boolean FSearch(List L, addr_string P);
/* Mencari apakah  ada elemen List yang  beralamat   P   */
/* Mengirimkan true jika ada, false jika tidak ada  	 */


addr_string SearchPrec(List L, infotype X[]);
/* mencari apakah ada elemen List  yang beralamat P 	     */
/* Mnegirimkan addr_string elemen sebelum elemen yang nilainya X */
/* Mencari apakah ada elemen List dengan info(P)=X	     */
/* Jika ada, mengirimkan addr_string Prec, dengan Next(Prec)=P   */

/* ** PRIMITIF BERDASARKAN NILAI ** */

/* ** Penambahan Elemen ** */
void InsVFirst(List *L, infotype X[]);
/* I.S  : L mungkin kosong          */
/* F.S  : Melakukan alokasi sebuah elemen dan                */
/*        menambahkan elemen pertama dengan nilai X jika     */
/*        Alokasi berhasil 				     */

void InsVLast(List *L, infotype X[]);
/* I.S  : L mungkin kosong          */
/* F.S  : Melakukan alokasi sebuah elemen dan                */
/*        menambahkan elemen list di akhir; elemen terakhir  */
/*        yang baru bernilai X jika alokasi berhasil, 	     */	
/*	  Jika alokasi gagal: I.S = F.S			     */

/* *** Penghapusan Elemen  ***  */
	  

void DelVFirst(List *L, infotype X[]);
  /* I.S    : List tidak kosong  		                 */
  /* F.S    : Elemen pertama List dihapus, nilai info disimpan   */
  /*	      pada X dan alamat elemen pertama  di-dealokasi 	 */


void DelVLast(List *L, infotype X[]);
  /* I.S    : List tidak kosong  		                 */
  /* F.S    : Elemen terakhir list dihapus, nilai info disimpan  */
  /*	      pada X dan alamat elemen terakhir di-dealokasi 	 */

/* *******  PRIMITIF BERDASARKAN ALAMAT ********	*/
/* Penambahan Elemen Berdasarkan Alamat 		*/

void InsertFirst(List *L, addr_string P);
/* I.S   : Sembarang, P sudah dialokasi			*/
/* F.S   : Menambahkan elemen ber-addr_string P, sebagai    */
/*         elemen pertama				*/

void InsertAfter(List *L, addr_string P, addr_string Prec);
/* I.S   : Prec pastilah elemen list dan bukan elemen terakhir  */
/*         P sudah dialokasi 					*/
/* F.S   : Insert P sebagai elemen sesudah elemen beralamat Prec*/

void InsertLast(List  *L, addr_string P);
/* I.S   : Sembarang, P sudah dialokasi				*/
/* F.S   : P ditambahkan  sebagai elemen terakhir yang baru	*/

/* ****** PENGHAPUSAN SEBUAH ELEMEN	*********   */
void DelFirst (List *L, addr_string *P);
/* I.S   : List tidak kosong 	*/
/* F.S   : P adalah alamat elemen pertama list sebelum penghapusan */
/*         Elemen List berkurang satu (mungkin menjadi kosong)     */
/* First elemen yang baru adalah suksesor elemen pertama yang lama */

void DelP(List *L, infotype X[]);
/* I.S   : Sembarang  */
/* F.S   : Jika ada elemen  list beraddr_code P,dengan info (P)=X    */
/*         Maka P dihapus dari List dan di-dealokasi		   */
/*	   Jika tidak ada elemen List dengan info(P)=X, maka list  */
/*         tetap. List mungkin menjadi kosomg karena penghapusan   */

void DelLast(List *L, addr_string *P);
/* I.S   : List tidak kosong  */
/* F.S   : P adalah alamat elemen terakhir list sebelum penghapusan */
/*	   Elemen list berkurang 1 (mungkin menjadi kosong)	    */
/*         Last elemen baru adalah predessesor elemen pertama yang  */
/*         jika tidak ada					    */

void DelAfter(List *L, addr_string *Pdel, addr_string Prec);
/* I.S   : List tidak kosong, Prec adalah anggota List		*/
/* F.S   : Menghapus Next(Prec) :				*/
/*         Pdel adalah alamat elemen List yang dihapus		*/

/* *************PROSES SEMUA ELEMEN ****************   */
void PrintInfo(List L);
/* I.S   : List mungkin kosong 	*/
/* F.S   : Jika list tidak kosong, semua info yang disimpan pada */
/*         elemen list di-print					 */
/*         Jika list kosong, hanya menuliskan "List Kosong"	 */

int NbElmt(List L);
/* Mengirimkan banyaknya elemen list, mengirimkan Nol jika kosong */

infotype Max(List L);
/* Mengirimkan nilai info(P) yang maksimum */

addr_string AdrMax(List L);
/* mengirimkan addr_string P, dengan info (P) yang maksimum */

infotype Min(List L);
/* mengirimkan nilai info(P), yang minumum    */

addr_string AdrMin(List L);
/* mengirimkan addr_string P, dengan info(P) yang minimum */

float Average(List L);
/* mengirimkan nilai rata-rata info(P)	*/

/******************************************************/
/***   		PROSES TERHADAP LIST		    ***/
/******************************************************/
void DelAll(List *L);
/* Delete semua elemen list, dan alamat elemen di-dealokasi */

void InversList(List *L);
/* I.S   : sembarang  			*/
/* F.S   : elemen list  dibalik		*/
/*	   elemen terakhir menjadi elemen pertama, dst    */
/*	   Membalik elemen list, tanpa alokasi/dealokasi  */

List FInversList(List L);
/* mengirimkan list baru, hasil invers dari L 	*/

void CopyList(List L1, List *L2);
/* I.S   : L1 sembarang 				*/
/* F.S   : L1 dan L2 menunjuk ke list yang sama 	*/
/*         tidak ada alokasi/dealokasi yang elemen	*/

List FCopyList(List L);
/* Mengirimkan list yang merupakan salinan L  		*/

void CpAlokList(List Lin, List  *Lout);
/* I.S   : Lin sembarang				    */
/* F.S   : Jika semua alokasi berhasil, maka Lout berisi    */
/*         hasil copy Lin. Jika ada alokasi yang  gagal     */
/*         maka Lout=Nil, dan semua elemen yang terlanjur   */
/*	   dialokasi, didealokasi dengan melakukan alokasi  */
/*	   elemen. Lout adalah List kosong, jika ada alokasi*/
/*	   elemen yang gagal				    */

void konkat(List L1, List L2, List *L3);
/* I.S   : L1 dan L2 sembarang				      */
/* F.S   : L1 dan L2 tetap, L3 adalah hasil konkatenasi L1 &  */
/*	   L2. Jika semua alokasi berhasil, maka L3  adalah   */
/*	   hasil konkatenasi. Jika ada alokasi yang gagal,    */	
/*	   semua elemen yang sudah dialokasi, di-dealokasi dan*/
/*	   L3=Nil					      */

void konkat1(List *L1, List *L2, List *L3);
/* I.S  : L1 dan L2 sembarang				*/
/* F.S  : L1 dan L2 kosong,  L3 adalah hasil konkatenasi*/
/*	  L1 & L2, 					*/
/* Konkatenasi 2 buah list : L1 dan L2 menghasilkan L3  */
/* yang baru (dengan elemen list L1 dan L2). Dan L1 dan */
/* L2 menjadi List kosong. Tidak ada alokasi/dealokasi  */

void PecahList(List *L1, List *L2, List L);
/* I.S  : L mungkin kosong  */
/* F.S  : Berdasarkan L, dibentuk 2 buah list L1 dan L2     */
/*        L tidak berubah. Untuk membentuk L1 dan L2 harus  */
/*	  alokasi. L1 berisi separuh elemen  L dan L2 berisi*/
/*	  sisa elemen L. Jika elemen L ganjil, maka separuh */
/* 	  adalah NbElmt(L)div 2				    */

#endif
