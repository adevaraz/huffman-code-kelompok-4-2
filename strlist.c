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


void DelAfter(List *L, addr_string *Pdel, addr_string Prec)
{  /* I.S   : List tidak kosong, Prec adalah anggota List	*/
   /* F.S   : Menghapus Next(Prec) :				*/
   /*         Pdel adalah alamat elemen List yang dihapus	*/
	*Pdel=Next(Prec);
	Next(Prec)=Next(*Pdel);
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

int NbElmt(List L)
{ /* Mengirimkan banyaknya elemen list, mengirimkan Nol jika kosong */
  addr_string P;
  int NbEl=0;
  if(ListEmpty(L)){
 	return 0;
  } else { /* Tidak kosong */
	      P=First(L);
       	      do {
		    NbEl++;  
		    P=Next(P);  
	      }while(P!=Nil);
  	}
       return NbEl;		      
}

/******************************************************/
/***   		PROSES TERHADAP LIST		    ***/
/******************************************************/
void DelAll(List *L)
{ /* Delete semua elemen list, dan alamat elemen di-dealokasi */
   infotype X;
   while(!ListEmpty(*L)) {
	  DelVFirst(&(*L),&X);
   } /* kosong */
}

void InversList(List *L)
{ /* I.S   : sembarang  			*/
  /* F.S   : elemen list  dibalik		*/
  /*	   elemen terakhir menjadi elemen pertama, dst    */
  /*	   Membalik elemen list, tanpa alokasi/dealokasi  */

	/* Kamus */
	List LTemp;
	addr_string P;

	/* Algoritma */
	CreateList(&LTemp);
	while(First(*L)!=Nil){
		DelFirst(&(*L),&P);
		Next(P)=Nil;
		InsertFirst(&LTemp,P);
	}
	First(*L)=First(LTemp);
}

List FInversList(List L)
{ /* mengirimkan list baru (LB), hasil invers dari L 	*/
  /* dengan Alokasi 					*/
	
  /* List L tidak kosong ; min 1 elemen				*/	
	
  /* Kamus */	
   List LB;
   addr_string P,PB;
   infotype X[MAX_WORD];
  
  /* Algoritma */ 
	P=First(L);
	CreateList(&LB);
	do {
		strcpy(X, Info(P));
//	    X=Info(P);
		PB=Alokasi(X);	
		if(PB!=Nil) { /* berhasil alokasi */
		    InsertLast(&LB,PB);
		    P=Next(P);
		} else { /* alokasi gagal */
			    DelAll(&LB);
			    First(LB)=Nil;
			}
	} while (P!= Nil);
   return LB;	
}

void CopyList(List L1, List *L2)
{ /* I.S   : L1 sembarang 				*/
  /* F.S   : L1 dan L2 menunjuk ke list yang sama 	*/
  /*         tidak ada alokasi/dealokasi 		*/
   *L2=L1;	
}


List FCopyList(List L)
{ /* Mengirimkan list yang merupakan salinan L  	*/
}

void CpAlokList(List Lin, List  *Lout)
{ /* I.S   : Lin sembarang				    */
  /* F.S   : Jika semua alokasi berhasil, maka Lout berisi  */
  /*         hasil copy Lin. Jika ada alokasi yang  gagal   */
  /*         maka Lout=Nil, dan semua elemen yang terlanjur */
  /*	   dialokasi, didealokasi dengan melakukan alokasi  */
  /*	   elemen. Lout adalah List kosong, jika ada alokasi*/
  /*	   elemen yang gagal				    */
    	
	/* Kamus */
	addr_string P,Pout;
	infotype X[MAX_WORD];
	
	/* ALgoritma */
	if(!ListEmpty(Lin)) { /* tidak kosong */
	   
		CreateList(&(*Lout));
		P=First(Lin);
		do 
		{  
		   strcpy(X, Info(P));
//		   X=Info(P);
		   Pout=Alokasi(X);
		   if(Pout!=Nil) {  /* Alokasi berhasil */
			InsertLast(&(*Lout),Pout);
			P=Next(P);
		   } else { /* Alokasi Pout gagal */
			     DelAll(&(*Lout));
			     First(*Lout)=Nil;
			     break;  
		          }
	        } while	(Next(P) != Nil);   
	}  
}


void konkat(List L1, List L2, List *L3)
{ /* I.S   : L1 dan L2 sembarang			      */
/* F.S   : L1 dan L2 tetap, L3 adalah hasil konkatenasi L1 &  */
/*	   L2. Jika semua alokasi berhasil, maka L3  adalah   */
/*	   hasil konkatenasi. Jika ada alokasi yang gagal,    */	
/*	   semua elemen yang sudah dialokasi, di-dealokasi dan*/
/*	   L3=Nil					      */
/*		
/*      L1, dan L2 tidak kosong */

	/* Kamus */	
	addr_string P1,P2,P3;
    infotype X1[MAX_WORD],X2[MAX_WORD];
	
	/* Algoritma */
	CreateList(&(*L3));
	
	/* Mengisi L3 dengan L1 */
	P1=First(L1);
	do 
	{ /* L1 minimal 1 elemen */
		strcpy(X1, Info(P1));
//		X1=Info(P1);
		P3=Alokasi(X1);
		if(P3!=Nil) { /* Alokasi L3 berhasil */
			InsertLast(&(*L3),P3);
			P1=Next(P1);
		} else { /* Alokasi gagal ; L3 di-dealokasi semua */
			    DelAll(&(*L3));
			    First(*L3)=Nil;
			    break;
			}
	} while(Next(P1) != Nil);

	/* Mengisi L3 dengan L2 */
	P2=First(L2);
	do
	{ /* L2 minimal 1 elemen */
		strcpy(X2, Info(P2));
//		X2=Info(P2);
		P3=Alokasi(X2);
		if(P3!=Nil){
			InsertLast(&(*L3),P3);
			P2=Next(P2);
		} else { /* Alokasi L3 gagal */
			DelAll(&(*L3));
			First(*L3)=Nil;
			break;
		}
	}while (Next(P2)!=Nil);	
}

void konkat1(List *L1, List *L2, List *L3)
{ /* I.S  : L1 dan L2 sembarang	; 			  */
  /* F.S  : L1 dan L2 kosong,  L3 adalah hasil konkatenasi*/
  /*	  L1 & L2, 					  */
  /* Konkatenasi 2 buah list : L1 dan L2 menghasilkan L3  */
  /* yang baru (dengan elemen list L1 dan L2 menjadi      */
  /* List kosong. Tidak ada alokasi/dealokasi  		  */

	
  addr_string P1,P2,P3;
  infotype X1[MAX_WORD], X2[MAX_WORD], X3[MAX_WORD];

   CreateList(&(*L3));

   while (First(*L1)!=Nil)  /* L1 belum kosong */
   {   DelFirst(&(*L1),&P1);
       InsertLast(&(*L3),P1);	   
   } /* First(L1) == Nil ; Kosong */

   while (First(*L2)!=Nil)  /* L2 belum kosong */
   {   DelFirst(&(*L2),&P2);
       InsertLast(&(*L3),P2);	   
   } /* First (L2) == Nil ; kosong */
	
}

void PecahList(List *L1, List *L2, List L)
{ /* I.S  : L mungkin kosong  */
  /* F.S  : Berdasarkan L, dibentuk 2 buah list L1 dan L2     */
  /*        L tidak berubah. Untuk membentuk L1 dan L2 harus  */
  /*	  alokasi. L1 berisi separuh elemen  L dan L2 berisi  */
  /*	  sisa elemen L. Jika elemen L ganjil, maka separuh   */
  /* 	  adalah NbElmt(L)div 2				      */
 
  /* Kamus */	
  addr_string P,P1,P2;
  infotype X1[MAX_WORD], X2[MAX_WORD];

  int Nb,tengah;
  
  /* ALgoritma */
  if(!ListEmpty(L)) {           /* tidak kosong ; minimal 1 elemen    */
	  CreateList(&(*L1));
	  
	  if(NbElmt(L)==1) {  /* Hanya L1 yang dapat diisi 1 elm, dari L */
		  First(*L1)=First(L);
	  } else /* L1 beirisi > 1 elemen */
	  	{  tengah = NbElmt(L) / 2;
		   P=First(L);
		   Nb=1;
		   
		   do /* mengisi L1 */
		   {  
		      strcpy(X1, Info(P));
//		      X1=Info(P);
		      P1=Alokasi(X1);
	   	      if(P1!=Nil){
			  InsertLast(&(*L1),P1);      
			  P=Next(P);
			  Nb++;
		      } else { /* alokasi gagal; semua di-dealokasi */
			  DelAll(&(*L1));
			  First(*L1)=Nil;
		    	  break;	  
		      	}	
		   } while(Nb<=tengah);

		   do  /* Mengisi L2 */ 
		   {  
		      strcpy(X2, Info(P));
//		      X2=Info(P);
	       	      P2=Alokasi(X2);
	   	      if(P2!=Nil) {
			      InsertLast(&(*L2),P2);
			      P=Next(P);
		      } else {
			      DelAll(&(*L2));
			      First(*L2)=Nil;
			      break;
		      }		      
		   } while(Next(P)!=Nil);
		} /* End ; L > 1 elemen */	  
  } else { /* First(L) == Nil */
		printf("List tidak dapat dipecah ! Kosong !\n");
	  }
}
