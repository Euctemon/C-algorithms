#include<stdio.h>
#include<stdlib.h>

typedef struct uzel {
    int cislo;
    struct uzel* ptr_dalsi;
} Uzel;

typedef struct spojovy_seznam {
    Uzel* hlava;
    Uzel* konec;
    Uzel* aktualni;
    int velikost;
} Spojovy_seznam;

void inicializace_listu(Spojovy_seznam* seznam);

void pridej_hlavu(Spojovy_seznam* seznam, int hodnota);
void pridej_konec(Spojovy_seznam* seznam, int hodnota);

void odeber_hlavu(Spojovy_seznam* seznam);
void odeber_konec(Spojovy_seznam* seznam);

void odeber_vse(Spojovy_seznam* seznam);
void vypis_vse(Spojovy_seznam* seznam);

void aplikuj_funkci(Spojovy_seznam* seznam, int hodnota);
void vynasob_cislem(Uzel* uzlik, int hodnota);




int main() {
    Spojovy_seznam pokus;
    inicializace_listu(&pokus);


    pridej_konec(&pokus, 20);
    pridej_konec(&pokus, 22);
    pridej_hlavu(&pokus, 12);
    pridej_hlavu(&pokus, 14);
    pridej_konec(&pokus, 20);
    vypis_vse(&pokus);
    printf("velikost seznamu je %d\n", pokus.velikost);
    printf("adresy pameti jsou %p\t%p\t%p\n", pokus.hlava, pokus.aktualni, pokus.konec);

    odeber_konec(&pokus);
    pridej_konec(&pokus, 133);
    odeber_hlavu(&pokus);

    printf("odebrani hlavy\n");
    vypis_vse(&pokus);
    printf("velikost seznamu je %d\n", pokus.velikost);
    printf("adresy pameti jsou %p\t%p\t%p\n", pokus.hlava, pokus.aktualni, pokus.konec);

    pridej_konec(&pokus, 20);
    pridej_konec(&pokus, 23);
    pridej_konec(&pokus, 26);
    pridej_konec(&pokus, 30);
    
    printf("aplikace funkce (+4)\n");
    aplikuj_funkci(&pokus, 4);
    vypis_vse(&pokus);
    
    printf("adresy pameti jsou %p\t%p\t%p\n", pokus.hlava, pokus.aktualni, pokus.konec);
    odeber_vse(&pokus);
    printf("seznam odebran\n");

    printf("adresy pameti jsou %p\t%p\t%p\n", pokus.hlava, pokus.aktualni, pokus.konec);
    printf("velikost seznamu je %d\n", pokus.velikost);

    return 1;
}








void inicializace_listu(Spojovy_seznam* seznam) {
    seznam->hlava = NULL;
    seznam->konec = NULL;
    seznam->aktualni = NULL;
    seznam->velikost = 0;
}

void pridej_hlavu(Spojovy_seznam* seznam, int hodnota) {
    Uzel* uzlik = (Uzel*)malloc(sizeof(Uzel));

    if (uzlik == NULL) {
        printf("Neprobehla alokace");
    }
    else {
        uzlik->cislo = hodnota;

        if (seznam->hlava == NULL) {
            seznam->konec = uzlik;
            uzlik->ptr_dalsi = NULL;
        }
        else {
            uzlik->ptr_dalsi = seznam->hlava;
        }
        seznam->hlava = uzlik;
    }
    seznam->velikost++;
}

void pridej_konec(Spojovy_seznam* seznam, int hodnota) {
    Uzel* uzlik = (Uzel*)malloc(sizeof(Uzel));

    if (uzlik == NULL) {
        printf("Neprobehla alokace");
    }
    else {
        uzlik->cislo = hodnota;
        uzlik->ptr_dalsi = NULL;

        if (seznam->hlava == NULL) {
            seznam->hlava = uzlik;
        }
        else {
            seznam->konec->ptr_dalsi = uzlik;
        }
        seznam->konec = uzlik;
    }
    seznam->velikost++;
}

void odeber_hlavu(Spojovy_seznam* seznam) {
    if (seznam->velikost == 1) {
        free(seznam->hlava);
        inicializace_listu(seznam);
    }

    else if (seznam->hlava != NULL) {
        seznam->aktualni = seznam->hlava->ptr_dalsi;
        free(seznam->hlava);
        seznam->hlava = seznam->aktualni;
        seznam->velikost--;
    }
}

void odeber_konec(Spojovy_seznam* seznam) {
    if (seznam->velikost == 1) {
        free(seznam->hlava);
        inicializace_listu(seznam);
    }
    else if (seznam->hlava != NULL) {
        seznam->aktualni = seznam->hlava;
        while (seznam->aktualni->ptr_dalsi != seznam->konec)
        {
            seznam->aktualni = seznam->aktualni->ptr_dalsi;
        }
        free(seznam->konec);
        seznam->konec = seznam->aktualni;
        seznam->velikost--;
    }
}

void odeber_vse(Spojovy_seznam* seznam) {
    for (int i = 0; i < seznam->velikost; ++i) {
        seznam->aktualni = seznam->hlava->ptr_dalsi;
        free(seznam->hlava);
        seznam->hlava = seznam->aktualni;
    }
    inicializace_listu(seznam);
}

void vypis_vse(Spojovy_seznam* seznam) {
    seznam->aktualni = seznam->hlava;
    for (int i = 0; i < seznam->velikost; ++i) {
        printf("%d\n", seznam->aktualni->cislo);
        seznam->aktualni = seznam->aktualni->ptr_dalsi;
    }
}

void vynasob_cislem(Uzel* uzlik, int hodnota) {
    uzlik->cislo *= hodnota;
}

void aplikuj_funkci(Spojovy_seznam* seznam, int hodnota) {
    seznam->aktualni = seznam->hlava;
    while (seznam->aktualni != NULL) {
        vynasob_cislem(seznam->aktualni, hodnota);
        seznam->aktualni = seznam->aktualni->ptr_dalsi;
    }
}