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
boolean ListIntEmpty(IntList  L)                        
{  /*  Mengirim true jika IntList kosong  */

   	return(First(L)==Nil);	
}

/* Pembuatan  IntList Kosong  */
void CreateListInt(IntList *L)
{  /* I.S  :  Sembarang    		*/
   /* F.S  :  Terbentuk  IntList kosong  	*/
   First(*L)=Nil;
}

/* ********  MANAJEMEN MEMORY  ********* */
addr_int AlokasiInt(type  X)
{/* Mengirimkan  addr_int  hasil alokasi    sebuah elemen */
 /* Jika alokasi  berhasil, maka  addr_int tidak nil, dan misalnya  */
 /* menghasilkan   P,  maka info(P)=X,  Next(P)=Nil;               */
 /* Jika alokasi  gagal,  mengirimkan  Nil 			   */
   addr_int P;
   P=(addr_int)malloc(sizeof(ElmtIntList));
   if(P!=Nil) { /* Berhasil  */
    	CodeInfo(P)=X;
		Next(P)=Nil;
   }
   return P;	   
}

void DealokasiInt(addr_int *P)
{ /* I.S  : P terdefinisi      				*/
  /* F.S  : P dikembalikan ke  sistem 			*/
  /*   	    Melakukan dealokasi, pengembalian addr_int P */
    Next(*P)=Nil; 	
    free(*P);
}

/*   ** PENCARIAN SEBUAH ELEMEN LIST **   */
addr_int Search1Int(IntList L, type  X)
{  /* Mencari apakah  ada elemen list dengan info(P)=X   */
   /* Jika ada, mengirimkan  addr_int dgn info(P)=X       */
   /* Jika  tidak ada, mengirimkan Nil 			 */
   /* Skema dengan boolean. Berlaku untuk IntList kosong  	 */
   addr_int  P=First(L); 
   boolean found=false;
   
   while((P!=Nil)&&(!found))  { 
	   if(CodeInfo(P)==X) {
		{  found=true;
		   }
	   }   
           else {
	         P=Next(P);   
	   }		   
   } /*P=Nil or  found  */
   return P;
}	   


addr_int Search2Int(IntList L, type  X)
{  /* Mencari apakah  ada elemen list dengan info(P)=X   */
   /* Jika ada, mengirimkan  addr_int dgn info(P)=X       */
   /* Jika  tidak ada, mengirimkan Nil 			 */
   /* Skema tanpa boolean. Tdk berlaku u/ IntList kosong  	 */
   addr_int  P; 
   if(First(L)!=Nil){
   	return Nil;
   } else {
   	P=First(L);
   	while((Next(P)!=Nil)&&(CodeInfo(P)!=X)) {
	      P=Next(P);   
   	} /* Next(P)==Nil or CodeInfo(P)==X */
   	if(CodeInfo(P)==X)  {
   	    return P;	
   	}else {
   	    return Nil;
	  }
   }
   return P;
}	   
   

boolean FSearchInt(IntList L, addr_int P)
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

addr_int SearchPrecInt(IntList L, type X)
{ /* Mengirimkan addr_int elemen sebelum elemen yang nilainya=X */
  /* Mencari apakah ada elemen IntList dengan info(P)=X	       */
  /* Jika ada, mengirimkan addr_int Prec, dengan Next(Prec)=P   */
  /* dan CodeInfo(P)=X; Jika tidak ada mengirimkan Nil	       */
  /* Jika P adalah  elemen pertama, maka Prec=Nil	       */
  addr_int Prec;	
  addr_int P;
  
  if(Next(P)==Nil)  { /* IntList hanya berisi 1 elemen */
    Prec=Nil;
  } else { 
	  P=First(L);
	  while((Next(P)!=Nil) &&(CodeInfo(P)!=X)) {
	      Prec=P;
              P=Next(P);		 	      
  	   }  /* Next(P)==Nil or CodeInfo(P)==X */
  
  	   if(CodeInfo(P)==X){ /* Ketemu CodeInfo (P)== X */
  	        return Prec;
  	   } else {
  	        return Nil;  /* tidak ada X di IntList */
  	   }
     } /* else */
}

/* ** PRIMITIF BERDASARKAN NILAI ** */

/* ** Penambahan Elemen ** */
void InsVFirstInt(IntList *L, type X)
{  /* I.S  : L mungkin kosong          */
   /* F.S  : Melakukan alokasi sebuah elemen dan             */
   /*        menambahkan elemen pertama dengan nilai X jika  */
   /*        AlokasiInt berhasil 				     */
   addr_int P=AlokasiInt(X);
   if(P!=Nil) { /* AlokasiInt Berhasil */
      InsertFirstInt(&(*L),P);
    }
}

void InsVLastInt(IntList *L, type X)
{ /* I.S  : L mungkin kosong          */
  /* F.S  : Melakukan alokasi sebuah elemen dan                */
  /*        menambahkan elemen list di akhir; elemen terakhir  */
  /*        yang baru bernilai X jika alokasi berhasil,        */	
  /*	    Jika alokasi gagal: I.S = F.S		       */
      	
     addr_int P=AlokasiInt(X);
     if(P!=Nil)
     {  InsertLastInt(&(*L),P);
         }
}

/* *** Penghapusan Elemen  ***  */

void DelVFirstInt(IntList *L, type *X)
{ /* I.S    : IntList tidak kosong  		                 */
  /* F.S    : Elemen pertama IntList dihapus, nilai info disimpan   */
  /*	      pada X dan alamat elemen pertama  di-dealokasi 	 */
  /* Kamus */
  addr_int  P;
  
  DelFirstInt(&(*L),&P); /* Hapus elemem pertama, blm didealokasi */
  *X=CodeInfo(P); 		/* info dari First disimpan di X       */
  DealokasiInt(&P);	  
}

void DelVLastInt(IntList *L, type *X)
{  /* I.S    : IntList tidak kosong  		                 */
   /* F.S    : Elemen terakhir list dihapus, nilai info disimpan */
   /*	      pada X dan alamat elemen terakhir di-dealokasi 	 */
   addr_int P;
   DelLastInt(&(*L),&P); 
        /* Hapus Elemen Terakhir, addressnya disimpan di P, */
        /* Belum diDealokasi, masih bisa dibaca isinya      */
   *X=CodeInfo(P);	/* CodeInfo dari addr_int P, ditampung  */ 
   DealokasiInt(&P);
}
	

/* *******  PRIMITIF BERDASARKAN ALAMAT ********	*/
/* Penambahan Elemen Berdasarkan Alamat 		*/

void InsertFirstInt(IntList *L, addr_int P)
{ /* I.S   : Sembarang, P sudah dialokasi		*/
  /* F.S   : Menambahkan elemen ber-addr_int P, sebagai  */
  /*         elemen pertama				*/
    Next(P)=First(*L);
    First(*L)=P;
}

void InsertLastInt(IntList  *L, addr_int P)
{ /* I.S   : Sembarang, P sudah dialokasi			*/
  /* F.S   : P ditambahkan  sebagai elemen terakhir yang baru	*/

      addr_int Last;
      if(ListIntEmpty(*L)) { /* Jika kosong, Insert elemen pertama */
	   InsertFirstInt(&(*L),P);     
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
void DelFirstInt (IntList *L, addr_int *P)
{ /* I.S   : IntList tidak kosong 	*/
  /* F.S   : P adalah alamat elemen pertama list sebelum penghapusan */
  /*         Elemen IntList berkurang satu (mungkin menjadi kosong)     */
  /* First elemen yang baru adalah suksesor elemen pertama yang lama */
          
      *P=First(*L);
      First(*L)=Next(First(*L));
      Next(*P)=Nil;
    
 }

void DelPInt(IntList *L, type X)
{ /* I.S   : Sembarang  */
  /* F.S   : Jika ada elemen  list beraddress P,dengan info (P)=X    */
  /*         Maka P dihapus dari IntList dan di-dealokasi		     */
  /*	     Jika tidak ada elemen IntList dengan info(P)=X, maka list  */
  /*         tetap. IntList mungkin menjadi kosomg karena penghapusan   */
    addr_int  P=First(*L);

    while((Next(P)!=Nil) && (CodeInfo(P)!=X)){
          P=Next(P);
    } /*Next(P)=Nil or CodeInfo(P)= X */
    
    if(CodeInfo(P)==X) {
       DealokasiInt(&P);
    }
}

void DelLastInt(IntList *L, addr_int *P)
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
	  DelFirstInt(&(*L),&(Last));
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
void PrintInfoInt(IntList L)
{ /* I.S   : IntList mungkin kosong 	*/
  /* F.S   : Jika list tidak kosong, semua info yang disimpan pada */
  /*         elemen list di-print			  	   */
  /*         Jika list kosong, hanya menuliskan "IntList Kosong"	   */
  int i;	
  addr_int P=First(L);
  if( P==Nil) { 
  	  printf("IntList Kosong !\n");
  } else { /* IntList tidak kosong */
	    do { 
	 	  printf("%d", CodeInfo(P));
		  P=Next(P);
		  i++;
	    } while(P!=Nil); 
	 }
}

/******************************************************/
/***   		PROSES TERHADAP LIST		    ***/
/******************************************************/
void DelAllInt(IntList *L)
{ /* Delete semua elemen list, dan alamat elemen di-dealokasi */
   type X;
   while(!ListIntEmpty(*L)) {
	  DelVFirstInt(&(*L),&X);
   } /* kosong */
}
