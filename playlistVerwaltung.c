/*Es wird hier eine Playlist für Songs verwalten.
*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

enum{ STRLEN = 100 };
enum{ PLLEN = 100 };

typedef struct {
  char interpret[STRLEN], title[STRLEN];
	unsigned int jahr, minuten, sekunden;
  
} Song;


/* Diese Funktion gibt einen zufaelligen Index
   zwischen 0 und laenge-1 zurueck */
int zufallsIndex( int laenge ) {
  return (int) rand()%laenge;
}

/* Diese Funktion lädt eine Playlist falls schon vorhanden*/
int laden( Song *playlist ) {
  
  FILE* fin = NULL;
  int n = 0;
  
  if ( ( fin = fopen( "playlist.dat", "rb" ) ) != NULL ) {
    while ( fread( &(playlist[n]), sizeof(Song), 1, fin ) > 0 && n < PLLEN )
      n++;
    printf("\nDatensaetze geladen!\n\n");
    fclose( fin );
  } else {
    printf("\nDerzeit sind keine Datensaetze gespeichert!\n\n");
  }
  
  return n;
}

/* Diese Funktion speichert neue Songs*/
void speichern( Song *playlist, int laenge ) {
  
  FILE* fout = NULL;
  
  if ( ( fout = fopen( "playlist.dat", "wb" ) ) != NULL ) {
    fwrite( playlist, sizeof(Song), laenge, fout );
    printf("\nDatensaetze gespeichert!\n\n");
    fclose( fout );
  } else {
    printf("\nSpeichern fehlgeschlagen\n\n");
  }
	}

 /*Diese Funktion liest alle Attribute eines Songs
   aus der Kommandozeile und gibt einen struct vom Typ Song zurueck */
Song einlesen( void ) {
  Song s;
	printf("Interpret bitte eingeben: \n");
fgets(s.interpret,STRLEN,stdin);
s.interpret[strlen(s.interpret)-1]='\0';
	printf("Title bitte eingeben: \n");
fgets(s.title,STRLEN,stdin);
s.title[strlen(s.title)-1]='\0';
printf("Jahr bitte eingeben: \n");
scanf("%u", &s.jahr);
	
  do         
  {
  printf("Minuten bitte eingeben: \n");
  scanf("%u",&s.minuten);
  if(s.minuten >= 60)
    printf("Geben sie eine Zahl zwischen 0 und 59 ein");

  } while (s.minuten >= 60);

  do    
  {
    printf("Sekunden bitte eingeben: \n");
    scanf("%u",&s.sekunden); 
    if(s.sekunden >= 60)
      printf("Geben sie eine Zahl zwischen 0 und 59 ein");

  } while (s.sekunden >= 60); 
	
	
	return s;
 }


/* Diese Funktion gibt alle Attribute eines Songs aus */
 void ausgeben( Song song, int i ) {
	 
	 printf("%.2d: %s - %s, %u, %u:%u\n", i+1, song.interpret, song.title, song.jahr, song.minuten, song.sekunden);
  
 }


/* Diese Funktion loescht ein Song aus der Playlist*/
int loeschen( Song *playlist, int pos, int laenge ) {
 
	if(pos>laenge-1){     //falls gesuchte Position glößer als Laenge des Arrays
		printf("Fehlermeldung! Eingegebene Position ist ungültig."); //gib Felher aus
      return laenge;	
	}
	playlist[pos]=playlist[laenge-1];  //gewünsche Position aus Array entfernen
	laenge--;
	
	return laenge;	
  
 }

/* Diese Funktion mischt alle Songs einer Playlist*/
 void shuffle( Song *playlist, int laenge ) {
  
  int i,x,y;
  Song tmp;      
  for(i=0;i<laenge-1;i++){
    x= zufallsIndex(laenge);
    y= zufallsIndex(laenge);
    tmp= playlist[x];
     playlist[x]=playlist[y];
     playlist[y]= tmp;
}}


/* Diese Funktion sucht ein Song je nach einem eingegebenen Jahr */
 int jahrSuchen( Song *playlist, int jahr, int laenge ) {
  
int i,j=0;
  for(i=0;i<laenge;i++)
  if(playlist[i].jahr==jahr){
      ausgeben(playlist[i],i);
      j++;}
	 
      return j;
  
}

/* Diese Funktion sucht ein Song je nach einem eingegebenen Singer */int interpretSuchen( Song *playlist, char *interpret, int laenge ) {
  
	
int i,y=0,j;
  for(i=0;i<laenge;i++){
    for(j=0;j<strlen(interpret);){
  if(playlist[i].interpret[j]==interpret[j])
    j++;
  
    else
        j= 101;}
    if(j==strlen(interpret)){
    ausgeben(playlist[i],i);
      y++;}
  }


      return y;
  
 }

/* Hier begint die main-Funktion */
int main( void ) {
  
 Song playlist[PLLEN];
	
 int laenge = 0, fertig = 0;
  char eingabe;
	int pos;
  char muster[PLLEN];
  srand(time(NULL));
  
  while ( !fertig ) {
    
    printf("\nl: laden\n");
    printf("s: speichern\n");
    printf("e: einlesen\n");
    printf("d: loeschen\n");
    printf("a: ausgeben\n");
    printf("m: mischen\n");
    printf("j: jahr suchen\n");
    printf("i: interpret suchen\n");
    printf("b: beenden\n\n");
    printf("Eingabe: ");
    
    scanf(" %c", &eingabe );
    getchar();
  

        
    switch( eingabe ) {
      case 'l': laenge = laden( playlist ); break;
      case 's': speichern( playlist, laenge ); break;
      case 'b': fertig = 1; break;
	  case 'e': playlist[laenge]= einlesen();
		          laenge=laenge+1;
		             break;
	 
	  case 'a': 
            
         for(pos=0; pos<laenge; pos++)   // Song der Playlist komplett ausgeben
	          {
				ausgeben(playlist[pos], pos);
	          }
          printf("\n");
		  break;
    case 'd': 
            
         printf("An welcher Position muss den Song gelöscht werden?\n");
	                   scanf("%d", &pos);
         laenge=loeschen(playlist,pos,laenge);
         printf("\n");
         break;
		
     case 'm': 
            
        shuffle(playlist, laenge); // Alle Songs der Playlist werden gemischt
		break;
		
     case 'j':

        printf("Gesuchtes Jahr eingeben:\n");
        scanf("%d",&pos);        // gewünsches Jahr in Playlist eingeben
        printf("%d wurde(n) gefunden\n\n", jahrSuchen(playlist,pos,laenge)); // alle Songs des gewünschen Jahres sortieren
        printf("\n");
	    break;

     case'i':
            
        printf("Interpret eingeben:\n");
        fgets(muster,PLLEN,stdin);// gewünscher Interpret in Playlist eingeben
        muster[strlen(muster)-1]='\0';
	    printf("%d wurde(n) gefunden!\n\n",interpretSuchen(playlist,muster,laenge));  // alle Songs des gewünschen Interprets aus Playlist sortieren
        printf("\n");
	    break;		
		
     default: printf("Funktion nicht verfuebar!\n\n");
    }
    
  }
  
  return 0;
}
        