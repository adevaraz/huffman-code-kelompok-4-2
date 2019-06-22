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
#include <assert.h>

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
  DelAllInt(&(L->First->code));
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
      First(*L)=L->First->next;
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
	 	  printf("\n[ %c ] ",Symbol(P));
	 	  PrintInfoInt(Code(P));
		  P=Next(P);
		  i++;
	    } while(P!=Nil); 
	 }
}

/******************************************************/
/***   		PROSES TERHADAP ListCode		    ***/
/******************************************************/
void DelAllCode(ListCode *L)
{ /* Delete semua elemen ListCode, dan alamat elemen di-dealokasi */
	
	assert(L != NULL);
   symboltype X;
   
   while(L->First != NULL) {
	  DelVFirstCode(L,&X);
   } /* kosong */
}

void DelCodeList(addr_code node) {
	addr_code pdel = node;
	addr_code phelp;
	
	while(pdel != NULL) {
		free(pdel);
		pdel = pdel->next;
		pdel->next = NULL;
	}
}
