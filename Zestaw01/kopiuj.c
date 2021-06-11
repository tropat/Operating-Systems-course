#include <stdio.h>
#include <stdlib.h> //exit()
#include <sys/types.h> //open()
#include <sys/stat.h> //
#include <fcntl.h> //
#include <unistd.h> //read(),write()

int main(int argc, const char* argv[]) {
    if(argc!=3) {
        printf("\nNieprawidłowa liczba argumentow przy probie uruchomienia programu!\n\nProsze wpisac:\n %s nazwa_pliku_zrodlowego nazwa_pliku_docelowego\n\n", argv[0]);
        exit(1);
    }
    
    int fr=open(argv[1],O_RDONLY); // OTWARCIE PLIKU ZRODLOWEGO
    if(fr==-1) {
        perror(argv[1]);
        exit(1);
    }

    int fw=open(argv[2],O_WRONLY|O_CREAT,0644); // OTWARCIE PLIKU DOCELOWEGO LUB UTWORZENIE NOWEGO O PRAWACH DOSTEPU -rw-r--r--
    if(fw==-1) {
        perror(argv[2]);
        exit(1);
    }
    
    int size=1024; // ILOSC BAJTOW W BUFORZE (DO POBRANIA Z PLIKU)

    char *bufor = (char*)malloc(size); // BUFOR
    if(!bufor) {
        perror("bufor error");
        exit(1);
    }

    int wczytane, zapisane; // LICZBA WCZYTANYCH BAJTOW DO BUFORA I LICZBA ZAPISANYCH DO PLIKU DOCELOWEGO

// WCZYTANIE PLIKU DO BUFORA (PARTIAMI PO 'SIZE') I PRZEPISANIE DO PLIKU DOCELOWEGO
    do {
        wczytane=read(fr,bufor,size);
        if(wczytane==-1) {
            perror("read error");
            exit(1);
        }

        zapisane=write(fw,bufor,wczytane);
        if(zapisane==-1) {
            perror("write error");
            exit(1);
        }
    } while(wczytane>0);

    // SPRZATANIE //
    
    close(fr); // PLIK ZRODLOWY
    close(fw); // PLIK DOCELOWY
    free(bufor); // BUFOR
}