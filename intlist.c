/* File :  list1.c   					*/
/* Desk :  body list  berkait dgn representasi fisik    */
/*         pointer; 					*/
/* 	   Representasi addr_int dgn pointer 		*/
/*	   type adalah integer			*/
/* Oleh :  ANI RAHMANI / 23501007 	  		*/
/* Tgl  :  25/10/01					*/	 

/* body dari List1.h   */

#include "boolean.h"
#include "intlist.h"
#include <stdlib.h>
#include <stdio.h>

/* ** Prototype   **  */
/* ** Test IntList Kosong **  */
boolean ListEmpty(IntList  L)                        
{  /*  Mengirim true jika IntList kosong  */

   	return(First(L)==Nil);	
}

/* Pembuatan  IntList Kosong  */
void CreateList(IntList *L)
{  /* I.S  :  Sembarang    		*/
   /* F.S  :  Terbentuk  IntList kosong  	*/
   First(*L)=Nil;
}

/* ********  MANAJEMEN MEMORY  ********* */
addr_int Alokasi(type  X)
{/* Mengirimkan  addr_int  hasil alokasi    sebuah elemen */
 /* Jika alokasi  berhasil, maka  addr_int tidak nil, dan misalnya  */
 /* menghasilkan   P,  maka info(P)=X,  Next(P)=Nil;               */
 /* Jika alokasi  gagal,  mengirimkan  Nil 			   */
   addr_int P;
   P=(addr_int)malloc(sizeof(ElmtList));
   if(P!=Nil) { /* Berhasil  */
    	Info(P)=X;
		Next(P)=Nil;
   }
   return P;	   
}

void Dealokasi(addr_int *P)
{ /* I.S  : P terdefinisi      				*/
  /* F.S  : P dikembalikan ke  sistem 			*/
  /*   	    Melakukan dealokasi, pengembalian addr_int P */
    Next(*P)=Nil; 	
    free(*P);
}

/*   ** PENCARIAN SEBUAH ELEMEN LIST **   */
addr_int Search1(IntList L, type  X)
{  /* Mencari apakah  ada elemen list dengan info(P)=X   */
   /* Jika ada, mengirimkan  addr_int dgn info(P)=X       */
   /* Jika  tidak ada, mengirimkan Nil 			 */
   /* Skema dengan boolean. Berlaku untuk IntList kosong  	 */
   addr_int  P=First(L); 
   boolean found=false;
   
   while((P!=Nil)&&(!found))  { 
	   if(Info(P)==X) {
		{  found=true;
		   }
	   }   
           else {
	         P=Next(P);   
	   }		   
   } /*P=Nil or  found  */
   return P;
}	   


addr_int Search2(IntList L, type  X)
{  /* Mencari apakah  ada elemen list dengan info(P)=X   */
   /* Jika ada, mengirimkan  addr_int dgn info(P)=X       */
   /* Jika  tidak ada, mengirimkan Nil 			 */
   /* Skema tanpa boolean. Tdk berlaku u/ IntList kosong  	 */
   addr_int  P; 
   if(First(L)!=Nil){
   	return Nil;
   } else {
   	P=First(L);
   	while((Next(P)!=Nil)&&(Info(P)!=X)) {
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
   

boolean FSearch(IntList L, addr_int P)
{ /* Mencari apakah ada elemen IntList yang beralamat P  */
  /* Mengirimkan true jika ada, false jika tidak ada  */
  /* IntList Tidak mungkin kosong  */

  addr_int PTemp=First(L);
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

addr_int SearchPrec(IntList L, type X)
{ /* Mengirimkan addr_int elemen sebelum elemen yang nilainya=X */
  /* Mencari apakah ada elemen IntList dengan info(P)=X	       */
  /* Jika ada, mengirimkan addr_int Prec, dengan Next(Prec)=P   */
  /* dan Info(P)=X; Jika tidak ada mengirimkan Nil	       */
  /* Jika P adalah  elemen pertama, maka Prec=Nil	       */
  addr_int Prec;	
  addr_int P;
  
  if(Next(P)==Nil)  { /* IntList hanya berisi 1 elemen */
    Prec=Nil;
  } else { 
	  P=First(L);
	  while((Next(P)!=Nil) &&(Info(P)!=X)) {
	      Prec=P;
              P=Next(P);		 	      
  	   }  /* Next(P)==Nil or Info(P)==X */
  
  	   if(Info(P)==X){ /* Ketemu Info (P)== X */
  	        return Prec;
  	   } else {
  	        return Nil;  /* tidak ada X di IntList */
  	   }
     } /* else */
}

/* ** PRIMITIF BERDASARKAN NILAI ** */

/* ** Penambahan Elemen ** */
void InsVFirst(IntList *L, type X)
{  /* I.S  : L mungkin kosong          */
   /* F.S  : Melakukan alokasi sebuah elemen dan             */
   /*        menambahkan elemen pertama dengan nilai X jika  */
   /*        Alokasi berhasil 				     */
   addr_int P=Alokasi(X);
   if(P!=Nil) { /* Alokasi Berhasil */
      InsertFirst(&(*L),P);
    }
}

void InsVLast(IntList *L, type X)
{ /* I.S  : L mungkin kosong          */
  /* F.S  : Melakukan alokasi sebuah elemen dan                */
  /*        menambahkan elemen list di akhir; elemen terakhir  */
  /*        yang baru bernilai X jika alokasi berhasil,        */	
  /*	    Jika alokasi gagal: I.S = F.S		       */
      	
     addr_int P=Alokasi(X);
     if(P!=Nil)
     {  InsertLast(&(*L),P);
         }
}

/* *** Penghapusan Elemen  ***  */

void DelVFirst(IntList *L, type *X)
{ /* I.S    : IntList tidak kosong  		                 */
  /* F.S    : Elemen pertama IntList dihapus, nilai info disimpan   */
  /*	      pada X dan alamat elemen pertama  di-dealokasi 	 */
  /* Kamus */
  addr_int  P;
  
  DelFirst(&(*L),&P); /* Hapus elemem pertama, blm didealokasi */
  *X=Info(P); 		/* info dari First disimpan di X       */
  Dealokasi(&P);	  
}

void DelVLast(IntList *L, type *X)
{  /* I.S    : IntList tidak kosong  		                 */
   /* F.S    : Elemen terakhir list dihapus, nilai info disimpan */
   /*	      pada X dan alamat elemen terakhir di-dealokasi 	 */
   addr_int P;
   DelLast(&(*L),&P); 
        /* Hapus Elemen Terakhir, addressnya disimpan di P, */
        /* Belum diDealokasi, masih bisa dibaca isinya      */
   *X=Info(P);	/* Info dari addr_int P, ditampung  */ 
   Dealokasi(&P);
}
	

/* *******  PRIMITIF BERDASARKAN ALAMAT ********	*/
/* Penambahan Elemen Berdasarkan Alamat 		*/

void InsertFirst(IntList *L, addr_int P)
{ /* I.S   : Sembarang, P sudah dialokasi		*/
  /* F.S   : Menambahkan elemen ber-addr_int P, sebagai  */
  /*         elemen pertama				*/
    Next(P)=First(*L);
    First(*L)=P;
}

void InsertAfter(IntList *L, addr_int P, addr_int Prec)
{ /* I.S   : Prec pastilah elemen  dan bukan elemen terakhir  */
  /*         P sudah dialokasi 					  */
  /* F.S   : Insert P sebagai elemen sesudah elemen beralamat Prec*/
	Next(P)=Next(Prec);
	Next(Prec)=P;
}

void InsertLast(IntList  *L, addr_int P)
{ /* I.S   : Sembarang, P sudah dialokasi			*/
  /* F.S   : P ditambahkan  sebagai elemen terakhir yang baru	*/

      addr_int Last;
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
void DelFirst (IntList *L, addr_int *P)
{ /* I.S   : IntList tidak kosong 	*/
  /* F.S   : P adalah alamat elemen pertama list sebelum penghapusan */
  /*         Elemen IntList berkurang satu (mungkin menjadi kosong)     */
  /* First elemen yang baru adalah suksesor elemen pertama yang lama */
          
      *P=First(*L);
      First(*L)=Next(First(*L));
      Next(*P)=Nil;
    
 }

void DelP(IntList *L, type X)
{ /* I.S   : Sembarang  */
  /* F.S   : Jika ada elemen  list beraddress P,dengan info (P)=X    */
  /*         Maka P dihapus dari IntList dan di-dealokasi		     */
  /*	     Jika tidak ada elemen IntList dengan info(P)=X, maka list  */
  /*         tetap. IntList mungkin menjadi kosomg karena penghapusan   */
    addr_int  P=First(*L);

    while((Next(P)!=Nil) && (Info(P)!=X)){
          P=Next(P);
    } /*Next(P)=Nil or Info(P)= X */
    
    if(Info(P)==X) {
       Dealokasi(&P);
    }
}

void DelLast(IntList *L, addr_int *P)
{ /* I.S   : IntList tidak kosong  */
  /* F.S   : P adalah alamat elemen terakhir list sebelum penghapusan */
  /*	     Elemen list berkurang 1 (mungkin menjadi kosong)	      */
  /*         Last elemen baru adalah predessesor elemen pertama yang  */
  /*         lama, jika  ada					      */
  
  /* Kamus */     	
  addr_int Last,PrecLast;
  
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


void DelAfter(IntList *L, addr_int *Pdel, addr_int Prec)
{  /* I.S   : IntList tidak kosong, Prec adalah anggota IntList	*/
   /* F.S   : Menghapus Next(Prec) :				*/
   /*         Pdel adalah alamat elemen IntList yang dihapus	*/
	*Pdel=Next(Prec);
	Next(Prec)=Next(*Pdel);
}


/* *************PROSES SEMUA ELEMEN ****************   */
void PrintInfo(IntList L)
{ /* I.S   : IntList mungkin kosong 	*/
  /* F.S   : Jika list tidak kosong, semua info yang disimpan pada */
  /*         elemen list di-print			  	   */
  /*         Jika list kosong, hanya menuliskan "IntList Kosong"	   */
  int i;	
  addr_int P=First(L);
  if( P==Nil) { 
  	  printf("IntList Kosong !\n");
  } else { /* IntList tidak kosong */
	    printf("[ ");
	    do { 
	 	  printf("%d ",Info(P));
		  P=Next(P);
		  i++;
	    } while(P!=Nil); 
	    printf("]");
	 }
  printf("\n");
}

int NbElmt(IntList L)
{ /* Mengirimkan banyaknya elemen list, mengirimkan Nol jika kosong */
  addr_int P;
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

type Max(IntList L)
{  /* Mengirimkan nilai info(P) yang maksimum */

   addr_int P;	
   type MMax;
   if(!ListEmpty(L))
   {      P=First(L);
	  MMax=Info(P);
	  while(Next(P)!=Nil) { 
	 	P=Next(P);
		if(Info(P)>MMax) {
		   MMax=Info(P);	
		}	
	  } /* Next(P)==Nil */
   }
  return MMax;	  
}

addr_int AdrMax(IntList L)
{  /* mengirimkan addr_int P, dengan info (P) yang maksimum */

   addr_int PMax,P;
   type Max;
   if(!ListEmpty(L)){
	   P=First(L);
	   Max=Info(P);
	   while(Next(P) != Nil) { 
		   P=Next(P);
		   if(Info(P)>Max) {
			   Max = Info(P);
			   PMax=P;
		   }
	   } /* Next(P)==Nil */
   }
   return PMax;
}


type Min(IntList L)
{ /* mengirimkan nilai info(P), yang minimum    */

   addr_int P;	
   type MMin;
   if(!ListEmpty(L))
   {      P=First(L);
	  MMin=Info(P);
	  while(Next(P)!=Nil) { 
	 	   P=Next(P);
		   if(Info(P)<MMin) {
		        MMin=Info(P);	
		   }	
	  } /* Next(P)==Nil */
    } 
    return MMin;	  
}
	

addr_int AdrMin(IntList L)
{ /* mengirimkan addr_int P, dengan info(P) yang minimum */
	
   addr_int PMin,P;
   type Min;
   if(!ListEmpty(L)){
	   P=First(L);
	   Min=Info(P);
	   while(Next(P) != Nil) { 
	      P=Next(P);
	      if(Info(P)<Min) {
			   Min = Info(P);
			   PMin=P;
		   }
  	   }
   }
   return PMin;
}

float Average(IntList L)
{  /* mengirimkan nilai rata-rata info(P)	*/
	addr_int P;
	type NbEl,Count;
	float avg;
	
	if(!ListEmpty(L)) { /* Tidak kosong */
		P=First(L);
		Count=Info(P);
		NbEl=1;
		while(Next(P)!=Nil) 
		{  P=Next(P);
		   Count=Count+Info(P);  		    
		   NbEl++;
		} /*Next(P) == Nil */
		avg= (float)Count/(float)NbEl;
	}
       return avg;		
}

/******************************************************/
/***   		PROSES TERHADAP LIST		    ***/
/******************************************************/
void DelAll(IntList *L)
{ /* Delete semua elemen list, dan alamat elemen di-dealokasi */
   type X;
   while(!ListEmpty(*L)) {
	  DelVFirst(&(*L),&X);
   } /* kosong */
}

void InversList(IntList *L)
{ /* I.S   : sembarang  			*/
  /* F.S   : elemen list  dibalik		*/
  /*	   elemen terakhir menjadi elemen pertama, dst    */
  /*	   Membalik elemen list, tanpa alokasi/dealokasi  */

	/* Kamus */
	IntList LTemp;
	addr_int P;

	/* Algoritma */
	CreateList(&LTemp);
	while(First(*L)!=Nil){
		DelFirst(&(*L),&P);
		Next(P)=Nil;
		InsertFirst(&LTemp,P);
	}
	First(*L)=First(LTemp);
}

IntList FInversList(IntList L)
{ /* mengirimkan list baru (LB), hasil invers dari L 	*/
  /* dengan Alokasi 					*/
	
  /* IntList L tidak kosong ; min 1 elemen				*/	
	
  /* Kamus */	
   IntList LB;
   addr_int P,PB;
   type X;
  
  /* Algoritma */ 
	P=First(L);
	CreateList(&LB);
	do {    X=Info(P);
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

void CopyList(IntList L1, IntList *L2)
{ /* I.S   : L1 sembarang 				*/
  /* F.S   : L1 dan L2 menunjuk ke list yang sama 	*/
  /*         tidak ada alokasi/dealokasi 		*/
   *L2=L1;	
}


IntList FCopyList(IntList L)
{ /* Mengirimkan list yang merupakan salinan L  	*/
}

void CpAlokList(IntList Lin, IntList  *Lout)
{ /* I.S   : Lin sembarang				    */
  /* F.S   : Jika semua alokasi berhasil, maka Lout berisi  */
  /*         hasil copy Lin. Jika ada alokasi yang  gagal   */
  /*         maka Lout=Nil, dan semua elemen yang terlanjur */
  /*	   dialokasi, didealokasi dengan melakukan alokasi  */
  /*	   elemen. Lout adalah IntList kosong, jika ada alokasi*/
  /*	   elemen yang gagal				    */
    	
	/* Kamus */
	addr_int P,Pout;
	type X;
	
	/* ALgoritma */
	if(!ListEmpty(Lin)) { /* tidak kosong */
	   
		CreateList(&(*Lout));
		P=First(Lin);
		do 
		{  X=Info(P);
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


void konkat(IntList L1, IntList L2, IntList *L3)
{ /* I.S   : L1 dan L2 sembarang			      */
/* F.S   : L1 dan L2 tetap, L3 adalah hasil konkatenasi L1 &  */
/*	   L2. Jika semua alokasi berhasil, maka L3  adalah   */
/*	   hasil konkatenasi. Jika ada alokasi yang gagal,    */	
/*	   semua elemen yang sudah dialokasi, di-dealokasi dan*/
/*	   L3=Nil					      */
/*		
/*      L1, dan L2 tidak kosong */

	/* Kamus */	
	addr_int P1,P2,P3;
        type X1,X2;
	
	/* Algoritma */
	CreateList(&(*L3));
	
	/* Mengisi L3 dengan L1 */
	P1=First(L1);
	do 
	{ /* L1 minimal 1 elemen */
		X1=Info(P1);
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
		X2=Info(P2);
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

void konkat1(IntList *L1, IntList *L2, IntList *L3)
{ /* I.S  : L1 dan L2 sembarang	; 			  */
  /* F.S  : L1 dan L2 kosong,  L3 adalah hasil konkatenasi*/
  /*	  L1 & L2, 					  */
  /* Konkatenasi 2 buah list : L1 dan L2 menghasilkan L3  */
  /* yang baru (dengan elemen list L1 dan L2 menjadi      */
  /* IntList kosong. Tidak ada alokasi/dealokasi  		  */

	
  addr_int P1,P2,P3;
  type X1,X2,X3;

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

void PecahList(IntList *L1, IntList *L2, IntList L)
{ /* I.S  : L mungkin kosong  */
  /* F.S  : Berdasarkan L, dibentuk 2 buah list L1 dan L2     */
  /*        L tidak berubah. Untuk membentuk L1 dan L2 harus  */
  /*	  alokasi. L1 berisi separuh elemen  L dan L2 berisi  */
  /*	  sisa elemen L. Jika elemen L ganjil, maka separuh   */
  /* 	  adalah NbElmt(L)div 2				      */
 
  /* Kamus */	
  addr_int P,P1,P2;
  type X1,X2;

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
		   {  X1=Info(P);
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
		   {  X2=Info(P);
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
