/* File :  ListCode1.h   					*/
/* Desk :  deklarasi ListCode  berkait dgn representasi     */
/* 	   fisik pointer; 				*/
/* 	   Representasi addr_code dgn pointer 		*/
/* Oleh :  ANI RAHMANI / 23501007 	  		*/
/* Tgl  :  25/10/01					*/	 

/* ListCode :  */

/***********************************************************************/

/**
 * Dimodifikasi oleh : Zara Veda Mahendra / 181524031
 * Tgl : 09/06/2019
 **/

#ifndef CODELIST_H
#define CODELIST_H

#include "boolean.h"
#include "intlist.h"
#include <stdlib.h>

#define Nil  NULL				//definisikan Nil dengan NULL (addr_code yg tidak punya adress)
#define Symbol(P) (P)->symbol		//P : sebuah addr_code
#define Code(P) (P)->code
#define Next(P) (P)->next
#define First(L) ((L).First)	//L : ListCode

typedef char symboltype;					//type definition, diubah di sini jika infotypenya berubah                               
typedef struct tElmtListCode *addr_code;
typedef struct  tElmtListCode   {
	symboltype symbol;
	IntList code;
	addr_code next;
} ElmtListCode;

/* Definisi  ListCode                   */
/* ListCode Kosong  :  First(L) = Nil   */
/* Setiap elemen dengan addr_code P dapat diacu Symbol(P),Next(P)       */
/* Elemen terakhir  ListCode :jika addr_codenya Last, maka next(Last)=Nil */

typedef struct {
	addr_code First;
} ListCode;

/* ** Prototype   **  */
/* ** Test ListCode Kosong **  */
boolean ListEmptyCode(ListCode  L);                        
/*  Mengirim true jika ListCode kosong  */

/* Pembuatan  ListCode Kosong  */
void CreateListCode(ListCode *L);
/* I.S  :  Sembarang    		*/
/* F.S  :  Terbentuk  ListCode kosong  	*/

/* Manajeman  memory  			*/
addr_code AlokasiCode(symboltype  X, IntList code);
 /* Mengirimkan  addr_code  hasil alokasi    sebuah elemen */
 /* Jika alokasi  berhasil, maka  addr_code tidak nil, dan misalnya  */
 /* menghasilkan   P,  maka info(P)=X,  Nest(P)=Nil;               */
 /* Jika alokasi  gagal,  mengirimkan  Nil 			   */

void DealokasiCode(addr_code *P);
/* I.S  :   P  terdefinisi         	*/
/* F.S  :   P dikembalikan ke  sistem 	*/
/*   	    Melakukan  dealokasi, pengembalian addr_code  P */


/*   ** PENCARIAN SEBUAH ELEMEN ListCode **   */

addr_code Search1Code(ListCode L, symboltype  X);
/* Mencari apakah  ada elemen ListCode dengan info(P)=X      */
/* Jika ada, mengirimkan  addr_code elemen tersebut	 */
/* Jika  tidak ada, mengirimkan Nil 			 */

boolean FSearchCode(ListCode L, addr_code P);
/* Mencari apakah  ada elemen ListCode yang  beralamat   P   */
/* Mengirimkan true jika ada, false jika tidak ada  	 */


addr_code SearchPrecCode(ListCode L, symboltype X);
/* mencari apakah ada elemen ListCode  yang beralamat P 	     */
/* Mnegirimkan addr_code elemen sebelum elemen yang nilainya X */
/* Mencari apakah ada elemen ListCode dengan info(P)=X	     */
/* Jika ada, mengirimkan addr_code Prec, dengan Next(Prec)=P   */

/* ** PRIMITIF BERDASARKAN NILAI ** */

/* ** Penambahan Elemen ** */
void InsVFirstCode(ListCode *L, symboltype X, IntList code);
/* I.S  : L mungkin kosong          */
/* F.S  : Melakukan alokasi sebuah elemen dan                */
/*        menambahkan elemen pertama dengan nilai X jika     */
/*        Alokasi berhasil 				     */

void InsVLastCode(ListCode *L, symboltype X, IntList code);
/* I.S  : L mungkin kosong          */
/* F.S  : Melakukan alokasi sebuah elemen dan                */
/*        menambahkan elemen ListCode di akhir; elemen terakhir  */
/*        yang baru bernilai X jika alokasi berhasil, 	     */	
/*	  Jika alokasi gagal: I.S = F.S			     */

/* *** Penghapusan Elemen  ***  */
	  

void DelVFirstCode(ListCode *L, symboltype *X);
  /* I.S    : ListCode tidak kosong  		                 */
  /* F.S    : Elemen pertama ListCode dihapus, nilai info disimpan   */
  /*	      pada X dan alamat elemen pertama  di-dealokasi 	 */


void DelVLastCode(ListCode *L, symboltype *X);
  /* I.S    : ListCode tidak kosong  		                 */
  /* F.S    : Elemen terakhir ListCode dihapus, nilai info disimpan  */
  /*	      pada X dan alamat elemen terakhir di-dealokasi 	 */

/* *******  PRIMITIF BERDASARKAN ALAMAT ********	*/
/* Penambahan Elemen Berdasarkan Alamat 		*/

void InsertFirstCode(ListCode *L, addr_code P);
/* I.S   : Sembarang, P sudah dialokasi			*/
/* F.S   : Menambahkan elemen ber-addr_code P, sebagai    */
/*         elemen pertama				*/

void InsertAfterCode(ListCode *L, addr_code P, addr_code Prec);
/* I.S   : Prec pastilah elemen ListCode dan bukan elemen terakhir  */
/*         P sudah dialokasi 					*/
/* F.S   : Insert P sebagai elemen sesudah elemen beralamat Prec*/

void InsertLastCode(ListCode  *L, addr_code P);
/* I.S   : Sembarang, P sudah dialokasi				*/
/* F.S   : P ditambahkan  sebagai elemen terakhir yang baru	*/

/* ****** PENGHAPUSAN SEBUAH ELEMEN	*********   */
void DelFirstCode (ListCode *L, addr_code *P);
/* I.S   : ListCode tidak kosong 	*/
/* F.S   : P adalah alamat elemen pertama ListCode sebelum penghapusan */
/*         Elemen ListCode berkurang satu (mungkin menjadi kosong)     */
/* First elemen yang baru adalah suksesor elemen pertama yang lama */

void DelPCode(ListCode *L, symboltype X);
/* I.S   : Sembarang  */
/* F.S   : Jika ada elemen  ListCode beraddr_code P,dengan info (P)=X    */
/*         Maka P dihapus dari ListCode dan di-dealokasi		   */
/*	   Jika tidak ada elemen ListCode dengan info(P)=X, maka ListCode  */
/*         tetap. ListCode mungkin menjadi kosomg karena penghapusan   */

void DelLastCode(ListCode *L, addr_code *P);
/* I.S   : ListCode tidak kosong  */
/* F.S   : P adalah alamat elemen terakhir ListCode sebelum penghapusan */
/*	   Elemen ListCode berkurang 1 (mungkin menjadi kosong)	    */
/*         Last elemen baru adalah predessesor elemen pertama yang  */
/*         jika tidak ada					    */

void DelAfterCode(ListCode *L, addr_code *Pdel, addr_code Prec);
/* I.S   : ListCode tidak kosong, Prec adalah anggota ListCode		*/
/* F.S   : Menghapus Next(Prec) :				*/
/*         Pdel adalah alamat elemen ListCode yang dihapus		*/

/* *************PROSES SEMUA ELEMEN ****************   */
void PrintInfoCode(ListCode L);
/* I.S   : ListCode mungkin kosong 	*/
/* F.S   : Jika ListCode tidak kosong, semua info yang disimpan pada */
/*         elemen ListCode di-print					 */
/*         Jika ListCode kosong, hanya menuliskan "ListCode Kosong"	 */

int NbElmtCode(ListCode L);
/* Mengirimkan banyaknya elemen ListCode, mengirimkan Nol jika kosong */

/******************************************************/
/***   		PROSES TERHADAP ListCode		    ***/
/******************************************************/
void DelAllCode(ListCode *L);
/* Delete semua elemen ListCode, dan alamat elemen di-dealokasi */

void InversListCode(ListCode *L);
/* I.S   : sembarang  			*/
/* F.S   : elemen ListCode  dibalik		*/
/*	   elemen terakhir menjadi elemen pertama, dst    */
/*	   Membalik elemen ListCode, tanpa alokasi/dealokasi  */

ListCode FInversListCode(ListCode L);
/* mengirimkan ListCode baru, hasil invers dari L 	*/

void CopyListCode(ListCode L1, ListCode *L2);
/* I.S   : L1 sembarang 				*/
/* F.S   : L1 dan L2 menunjuk ke ListCode yang sama 	*/
/*         tidak ada alokasi/dealokasi yang elemen	*/

ListCode FCopyListCode(ListCode L);
/* Mengirimkan ListCode yang merupakan salinan L  		*/

void CpAlokListCode(ListCode Lin, ListCode  *Lout);
/* I.S   : Lin sembarang				    */
/* F.S   : Jika semua alokasi berhasil, maka Lout berisi    */
/*         hasil copy Lin. Jika ada alokasi yang  gagal     */
/*         maka Lout=Nil, dan semua elemen yang terlanjur   */
/*	   dialokasi, didealokasi dengan melakukan alokasi  */
/*	   elemen. Lout adalah ListCode kosong, jika ada alokasi*/
/*	   elemen yang gagal				    */

void konkatCode(ListCode L1, ListCode L2, ListCode *L3);
/* I.S   : L1 dan L2 sembarang				      */
/* F.S   : L1 dan L2 tetap, L3 adalah hasil konkatenasi L1 &  */
/*	   L2. Jika semua alokasi berhasil, maka L3  adalah   */
/*	   hasil konkatenasi. Jika ada alokasi yang gagal,    */	
/*	   semua elemen yang sudah dialokasi, di-dealokasi dan*/
/*	   L3=Nil					      */

void konkat1Code(ListCode *L1, ListCode *L2, ListCode *L3);
/* I.S  : L1 dan L2 sembarang				*/
/* F.S  : L1 dan L2 kosong,  L3 adalah hasil konkatenasi*/
/*	  L1 & L2, 					*/
/* Konkatenasi 2 buah ListCode : L1 dan L2 menghasilkan L3  */
/* yang baru (dengan elemen ListCode L1 dan L2). Dan L1 dan */
/* L2 menjadi ListCode kosong. Tidak ada alokasi/dealokasi  */

void PecahListCode(ListCode *L1, ListCode *L2, ListCode L);
/* I.S  : L mungkin kosong  */
/* F.S  : Berdasarkan L, dibentuk 2 buah ListCode L1 dan L2     */
/*        L tidak berubah. Untuk membentuk L1 dan L2 harus  */
/*	  alokasi. L1 berisi separuh elemen  L dan L2 berisi*/
/*	  sisa elemen L. Jika elemen L ganjil, maka separuh */
/* 	  adalah NbElmt(L)div 2				    */

#endif
