/* File :  ListCode1.c   					*/
/* Desk :  body ListCode  berkait dgn representasi fisik    */
/*         pointer; 					*/
/* 	   Representasi addr_code dgn pointer 		*/
/*	   symboltype adalah integer			*/
/* Oleh :  ANI RAHMANI / 23501007 	  		*/
/* Tgl  :  25/10/01					*/	 

/* body dari ListCode1.h   */

/***********************************************************************/

/**
 * Dimodifikasi oleh : Zara Veda Mahendra / 181524031
 * Tgl : 09/06/2019
 **/
 
#include "boolean.h"
#include "codelist.h"
#include "intlist.h"
#include <stdlib.h>
#include <stdio.h>

/* ** Prototype   **  */
/* ** Test ListCode Kosong **  */
boolean ListEmptyCode(ListCode  L)                        
{  /*  Mengirim true jika ListCode kosong  */

   	return(First(L)==Nil);	
}

/* Pembuatan  ListCode Kosong  */
void CreateListCode(ListCode *L)
{  /* I.S  :  Sembarang    		*/
   /* F.S  :  Terbentuk  ListCode kosong  	*/
   First(*L)=Nil;
}

/* ********  MANAJEMEN MEMORY  ********* */
addr_code AlokasiCode(symboltype  X, IntList code)
{/* Mengirimkan  addr_code  hasil alokasi    sebuah elemen */
 /* Jika alokasi  berhasil, maka  addr_code tidak nil, dan misalnya  */
 /* menghasilkan   P,  maka info(P)=X,  Next(P)=Nil;               */
 /* Jika alokasi  gagal,  mengirimkan  Nil 			   */
   addr_code P;
   P=(addr_code)malloc(sizeof(ElmtListCode));
   if(P!=Nil) { /* Berhasil  */
    	Symbol(P)=X;
    	Code(P) = code;
		Next(P)=Nil;
   }
   return P;	   
}

void DealokasiCode(addr_code *P)
{ /* I.S  : P terdefinisi      				*/
  /* F.S  : P dikembalikan ke  sistem 			*/
  /*   	    Melakukan dealokasi, pengembalian addr_code P */
    Next(*P)=Nil; 	
    free(*P);
}

/*   ** PENCARIAN SEBUAH ELEMEN ListCode **   */
addr_code Search1Code(ListCode L, symboltype  X)
{  /* Mencari apakah  ada elemen ListCode dengan info(P)=X   */
   /* Jika ada, mengirimkan  addr_code dgn info(P)=X       */
   /* Jika  tidak ada, mengirimkan Nil 			 */
   /* Skema dengan boolean. Berlaku untuk ListCode kosong  	 */
   addr_code  P=First(L); 
   boolean found=false;
   
   while((P!=Nil)&&(!found))  { 
	   if(Symbol(P)==X) {
		{	found=true;
		   	}
	   }   
        else {
	         P=Next(P);   
	   }		   
   } /*P=Nil or  found  */
   return P;
}	   


addr_code Search2Code(ListCode L, symboltype  X)
{  /* Mencari apakah  ada elemen ListCode dengan info(P)=X   */
   /* Jika ada, mengirimkan  addr_code dgn info(P)=X       */
   /* Jika  tidak ada, mengirimkan Nil 			 */
   /* Skema tanpa boolean. Tdk berlaku u/ ListCode kosong  	 */
   addr_code  P; 
   if(First(L)!=Nil){
   	return Nil;
   } else {
   	P=First(L);
   	while((Next(P)!=Nil)&&(Symbol(P)!=X)) {
	      P=Next(P);   
   	} /* Next(P)==Nil or Symbol(P)==X */
   	if(Symbol(P)==X)  {
   	    return P;	
   	}else {
   	    return Nil;
	  }
   }
   return P;
}	   
   

boolean FSearchCode(ListCode L, addr_code P)
{ /* Mencari apakah ada elemen ListCode yang beralamat P  */
  /* Mengirimkan true jika ada, false jika tidak ada  */
  /* ListCode Tidak mungkin kosong  */

  addr_code PTemp=First(L);
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

addr_code SearchPrecCode(ListCode L, symboltype X)
{ /* Mengirimkan addr_code elemen sebelum elemen yang nilainya=X */
  /* Mencari apakah ada elemen ListCode dengan info(P)=X	       */
  /* Jika ada, mengirimkan addr_code Prec, dengan Next(Prec)=P   */
  /* dan Symbol(P)=X; Jika tidak ada mengirimkan Nil	       */
  /* Jika P adalah  elemen pertama, maka Prec=Nil	       */
  addr_code Prec;	
  addr_code P;
  
  if(Next(P)==Nil)  { /* ListCode hanya berisi 1 elemen */
    Prec=Nil;
  } else { 
	  P=First(L);
	  while((Next(P)!=Nil) &&(Symbol(P)!=X)) {
	      Prec=P;
              P=Next(P);		 	      
  	   }  /* Next(P)==Nil or Symbol(P)==X */
  
  	   if(Symbol(P)==X){ /* Ketemu Symbol (P)== X */
  	        return Prec;
  	   } else {
  	        return Nil;  /* tidak ada X di ListCode */
  	   }
     } /* else */
}

/* ** PRIMITIF BERDASARKAN NILAI ** */

/* ** Penambahan Elemen ** */
void InsVFirstCode(ListCode *L, symboltype X, IntList code)
{  /* I.S  : L mungkin kosong          */
   /* F.S  : Melakukan alokasi sebuah elemen dan             */
   /*        menambahkan elemen pertama dengan nilai X jika  */
   /*        AlokasiCode berhasil 				     */
   addr_code P = AlokasiCode(X, code);
   if(P!=Nil) { /* AlokasiCode Berhasil */
      InsertFirstCode(&(*L),P);
    }
}

void InsVLastCode(ListCode *L, symboltype X, IntList code)
{ /* I.S  : L mungkin kosong          */
  /* F.S  : Melakukan alokasi sebuah elemen dan                */
  /*        menambahkan elemen ListCode di akhir; elemen terakhir  */
  /*        yang baru bernilai X jika alokasi berhasil,        */	
  /*	    Jika alokasi gagal: I.S = F.S		       */
      	
     addr_code P=AlokasiCode(X, code);
     if(P!=Nil)
     {  InsertLastCode(&(*L),P);
        }
}

/* *** Penghapusan Elemen  ***  */

void DelVFirstCode(ListCode *L, symboltype *X)
{ /* I.S    : ListCode tidak kosong  		                 */
  /* F.S    : Elemen pertama ListCode dihapus, nilai info disimpan   */
  /*	      pada X dan alamat elemen pertama  di-dealokasi 	 */
  /* Kamus */
  addr_code  P;
  
  DelFirstCode(&(*L),&P); /* Hapus elemem pertama, blm didealokasi */
  *X=Symbol(P); 		/* info dari First disimpan di X       */
  DealokasiCode(&P);	  
}

void DelVLastCode(ListCode *L, symboltype *X)
{  /* I.S    : ListCode tidak kosong  		                 */
   /* F.S    : Elemen terakhir ListCode dihapus, nilai info disimpan */
   /*	      pada X dan alamat elemen terakhir di-dealokasi 	 */
   addr_code P;
   DelLast(&(*L),&P); 
        /* Hapus Elemen Terakhir, addr_codenya disimpan di P, */
        /* Belum diDealokasi, masih bisa dibaca isinya      */
   *X=Symbol(P);	/* Symbol dari addr_code P, ditampung  */ 
   DealokasiCode(&P);
}
	

/* *******  PRIMITIF BERDASARKAN ALAMAT ********	*/
/* Penambahan Elemen Berdasarkan Alamat 		*/

void InsertFirstCode(ListCode *L, addr_code P)
{ /* I.S   : Sembarang, P sudah dialokasi		*/
  /* F.S   : Menambahkan elemen ber-addr_code P, sebagai  */
  /*         elemen pertama				*/
    Next(P)=First(*L);
    First(*L)=P;
}

void InsertAfterCode(ListCode *L, addr_code P, addr_code Prec)
{ /* I.S   : Prec pastilah elemen  dan bukan elemen terakhir  */
  /*         P sudah dialokasi 					  */
  /* F.S   : Insert P sebagai elemen sesudah elemen beralamat Prec*/
	Next(P)=Next(Prec);
	Next(Prec)=P;
}

void InsertLastCode(ListCode  *L, addr_code P)
{ /* I.S   : Sembarang, P sudah dialokasi			*/
  /* F.S   : P ditambahkan  sebagai elemen terakhir yang baru	*/

      addr_code Last;
      if(ListEmptyCode(*L)) { /* Jika kosong, Insert elemen pertama */
	   InsertFirstCode(&(*L),P);     
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
void DelFirstCode(ListCode *L, addr_code *P)
{ /* I.S   : ListCode tidak kosong 	*/
  /* F.S   : P adalah alamat elemen pertama ListCode sebelum penghapusan */
  /*         Elemen ListCode berkurang satu (mungkin menjadi kosong)     */
  /* First elemen yang baru adalah suksesor elemen pertama yang lama */
          
      *P=First(*L);
      First(*L)=Next(First(*L));
      Next(*P)=Nil;
    
 }

void DelPCode(ListCode *L, symboltype X)
{ /* I.S   : Sembarang  */
  /* F.S   : Jika ada elemen  ListCode beraddr_code P,dengan info (P)=X    */
  /*         Maka P dihapus dari ListCode dan di-dealokasi		     */
  /*	     Jika tidak ada elemen ListCode dengan info(P)=X, maka ListCode  */
  /*         tetap. ListCode mungkin menjadi kosomg karena penghapusan   */
    addr_code  P=First(*L);

    while((Next(P)!=Nil) && (Symbol(P)!=X)){
          P=Next(P);
    } /*Next(P)=Nil or Symbol(P)= X */
    
    if(Symbol(P)==X) {
       DealokasiCode(&P);
    }
}

void DelLastCode(ListCode *L, addr_code *P)
{ /* I.S   : ListCode tidak kosong  */
  /* F.S   : P adalah alamat elemen terakhir ListCode sebelum penghapusan */
  /*	     Elemen ListCode berkurang 1 (mungkin menjadi kosong)	      */
  /*         Last elemen baru adalah predessesor elemen pertama yang  */
  /*         lama, jika  ada					      */
  
  /* Kamus */     	
  addr_code Last,PrecLast;
  
  Last=First(*L);
  /* dari catatan di kelas */	
  if(Next(Last)==Nil)  { /* hanya 1 elemen */
	  DelFirstCode(&(*L),&(Last));
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


void DelAfterCode(ListCode *L, addr_code *Pdel, addr_code Prec)
{  /* I.S   : ListCode tidak kosong, Prec adalah anggota ListCode	*/
   /* F.S   : Menghapus Next(Prec) :				*/
   /*         Pdel adalah alamat elemen ListCode yang dihapus	*/
	*Pdel=Next(Prec);
	Next(Prec)=Next(*Pdel);
}


/* *************PROSES SEMUA ELEMEN ****************   */
void PrintInfoCode(ListCode L)
{ /* I.S   : ListCode mungkin kosong 	*/
  /* F.S   : Jika ListCode tidak kosong, semua info yang disimpan pada */
  /*         elemen ListCode di-print			  	   */
  /*         Jika ListCode kosong, hanya menuliskan "ListCode Kosong"	   */
  int i;	
  addr_code P=First(L);
  if( P==Nil) { 
  	  printf("ListCode Kosong !\n");
  } else { /* ListCode tidak kosong */
	    do { 
	 	  printf("[ %c ] ",Symbol(P));
	 	  PrintInfoInt(Code(P));
	 	  printf("\n");
		  P=Next(P);
		  i++;
	    } while(P!=Nil); 
	 }
  printf("\n");
}

int NbElmtCode(ListCode L)
{ /* Mengirimkan banyaknya elemen ListCode, mengirimkan Nol jika kosong */
  addr_code P;
  int NbEl=0;
  if(ListEmptyCode(L)){
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
/***   		PROSES TERHADAP ListCode		    ***/
/******************************************************/
void DelAllCode(ListCode *L)
{ /* Delete semua elemen ListCode, dan alamat elemen di-dealokasi */
   symboltype X;
   while(!ListEmptyCode(*L)) {
	  DelVFirst(&(*L),&X);
   } /* kosong */
}

void InversListCode(ListCode *L)
{ /* I.S   : sembarang  			*/
  /* F.S   : elemen ListCode  dibalik		*/
  /*	   elemen terakhir menjadi elemen pertama, dst    */
  /*	   Membalik elemen ListCode, tanpa alokasi/dealokasi  */

	/* Kamus */
	ListCode LTemp;
	addr_code P;

	/* Algoritma */
	CreateListCode(&LTemp);
	while(First(*L)!=Nil){
		DelFirstCode(&(*L),&P);
		Next(P)=Nil;
		InsertFirstCode(&LTemp,P);
	}
	First(*L)=First(LTemp);
}

ListCode FInversListCode(ListCode L)
{ /* mengirimkan ListCode baru (LB), hasil invers dari L 	*/
  /* dengan AlokasiCode 					*/
	
  /* ListCode L tidak kosong ; min 1 elemen				*/	
	
  /* Kamus */	
   ListCode LB;
   addr_code P,PB;
   symboltype X;
   IntList C;
  
  /* Algoritma */ 
	P=First(L);
	CreateListCode(&LB);
	do {    X=Symbol(P);
	    C = Code(P);
		PB=AlokasiCode(X, C);	
		if(PB!=Nil) { /* berhasil alokasi */
		    InsertLastCode(&LB,PB);
		    P=Next(P);
		} else { /* alokasi gagal */
			    DelAllCode(&LB);
			    First(LB)=Nil;
			}
	} while (P!= Nil);
   return LB;	
}

void CopyListCode(ListCode L1, ListCode *L2)
{ /* I.S   : L1 sembarang 				*/
  /* F.S   : L1 dan L2 menunjuk ke ListCode yang sama 	*/
  /*         tidak ada alokasi/dealokasi 		*/
   *L2=L1;	
}


ListCode FCopyListCode(ListCode L)
{ /* Mengirimkan ListCode yang merupakan salinan L  	*/
}

void CpAlokListCode(ListCode Lin, ListCode  *Lout)
{ /* I.S   : Lin sembarang				    */
  /* F.S   : Jika semua alokasi berhasil, maka Lout berisi  */
  /*         hasil copy Lin. Jika ada alokasi yang  gagal   */
  /*         maka Lout=Nil, dan semua elemen yang terlanjur */
  /*	   dialokasi, didealokasi dengan melakukan alokasi  */
  /*	   elemen. Lout adalah ListCode kosong, jika ada alokasi*/
  /*	   elemen yang gagal				    */
    	
	/* Kamus */
	addr_code P,Pout;
	symboltype X;
	IntList C;
	
	/* ALgoritma */
	if(!ListEmptyCode(Lin)) { /* tidak kosong */
	   
		CreateListCode(&(*Lout));
		P=First(Lin);
		do 
		{  X=Symbol(P);
		   C = Code(P);
		   Pout = AlokasiCode(X, C);
		   if(Pout!=Nil) {  /* AlokasiCode berhasil */
			InsertLastCode(&(*Lout),Pout);
			P=Next(P);
		   } else { /* AlokasiCode Pout gagal */
			     DelAllCode(&(*Lout));
			     First(*Lout)=Nil;
			     break;  
		          }
	        } while	(Next(P) != Nil);   
	}  
}


void konkatCode(ListCode L1, ListCode L2, ListCode *L3)
{ /* I.S   : L1 dan L2 sembarang			      */
/* F.S   : L1 dan L2 tetap, L3 adalah hasil konkatenasi L1 &  */
/*	   L2. Jika semua alokasi berhasil, maka L3  adalah   */
/*	   hasil konkatenasi. Jika ada alokasi yang gagal,    */	
/*	   semua elemen yang sudah dialokasi, di-dealokasi dan*/
/*	   L3=Nil					      */
/*		
/*      L1, dan L2 tidak kosong */

	/* Kamus */	
	addr_code P1,P2,P3;
    symboltype X1,X2;
    IntList C1, C2;
	
	/* Algoritma */
	CreateListCode(&(*L3));
	
	/* Mengisi L3 dengan L1 */
	P1=First(L1);
	do 
	{ /* L1 minimal 1 elemen */
		X1=Symbol(P1);
		C1 = Code(P1);
		P3=AlokasiCode(X1, C1);
		if(P3!=Nil) { /* AlokasiCode L3 berhasil */
			InsertLastCode(&(*L3),P3);
			P1=Next(P1);
		} else { /* AlokasiCode gagal ; L3 di-dealokasi semua */
			    DelAllCode(&(*L3));
			    First(*L3)=Nil;
			    break;
			}
	} while(Next(P1) != Nil);

	/* Mengisi L3 dengan L2 */
	P2=First(L2);
	do
	{ /* L2 minimal 1 elemen */
		X2=Symbol(P2);
		C2 = Code(P2);
		P3=AlokasiCode(X2, C2);
		if(P3!=Nil){
			InsertLastCode(&(*L3),P3);
			P2=Next(P2);
		} else { /* AlokasiCode L3 gagal */
			DelAllCode(&(*L3));
			First(*L3)=Nil;
			break;
		}
	}while (Next(P2)!=Nil);	
}

void konkat1Code(ListCode *L1, ListCode *L2, ListCode *L3)
{ /* I.S  : L1 dan L2 sembarang	; 			  */
  /* F.S  : L1 dan L2 kosong,  L3 adalah hasil konkatenasi*/
  /*	  L1 & L2, 					  */
  /* Konkatenasi 2 buah ListCode : L1 dan L2 menghasilkan L3  */
  /* yang baru (dengan elemen ListCode L1 dan L2 menjadi      */
  /* ListCode kosong. Tidak ada alokasi/dealokasi  		  */

	
  addr_code P1,P2,P3;
  symboltype X1,X2,X3;

   CreateListCode(&(*L3));

   while (First(*L1)!=Nil)  /* L1 belum kosong */
   {   DelFirstCode(&(*L1),&P1);
       InsertLastCode(&(*L3),P1);	   
   } /* First(L1) == Nil ; Kosong */

   while (First(*L2)!=Nil)  /* L2 belum kosong */
   {   DelFirstCode(&(*L2),&P2);
       InsertLastCode(&(*L3),P2);	   
   } /* First (L2) == Nil ; kosong */
	
}

void PecahListCode(ListCode *L1, ListCode *L2, ListCode L)
{ /* I.S  : L mungkin kosong  */
  /* F.S  : Berdasarkan L, dibentuk 2 buah ListCode L1 dan L2     */
  /*        L tidak berubah. Untuk membentuk L1 dan L2 harus  */
  /*	  alokasi. L1 berisi separuh elemen  L dan L2 berisi  */
  /*	  sisa elemen L. Jika elemen L ganjil, maka separuh   */
  /* 	  adalah NbElmtCode(L)div 2				      */
 
  /* Kamus */	
  addr_code P,P1,P2;
  symboltype X1,X2;
  IntList C1, C2;

  int Nb,tengah;
  
  /* ALgoritma */
  if(!ListEmptyCode(L)) {           /* tidak kosong ; minimal 1 elemen    */
	  CreateListCode(&(*L1));
	  
	  if(NbElmtCode(L) == 1) {  /* Hanya L1 yang dapat diisi 1 elm, dari L */
		  First(*L1)=First(L);
	  } else /* L1 beirisi > 1 elemen */
	  	{  tengah = NbElmtCode(L) / 2;
		   P=First(L);
		   Nb=1;
		   
		   do /* mengisi L1 */
		   {  X1=Symbol(P);
		   	  C1 = Code(P);
		      P1=AlokasiCode(X1, C1);
	   	      if(P1!=Nil){
			  InsertLastCode(&(*L1),P1);      
			  P=Next(P);
			  Nb++;
		      } else { /* alokasi gagal; semua di-dealokasi */
			  DelAllCode(&(*L1));
			  First(*L1)=Nil;
		    	  break;	  
		      	}	
		   } while(Nb<=tengah);

		   do  /* Mengisi L2 */ 
		   {  X2=Symbol(P);
		      C2 = Code(P);
	       	      P2=AlokasiCode(X2, C2);
	   	      if(P2!=Nil) {
			      InsertLastCode(&(*L2),P2);
			      P=Next(P);
		      } else {
			      DelAllCode(&(*L2));
			      First(*L2)=Nil;
			      break;
		      }		      
		   } while(Next(P)!=Nil);
		} /* End ; L > 1 elemen */	  
  } else { /* First(L) == Nil */
		printf("List tidak dapat dipecah ! Kosong !\n");
	  }
}
