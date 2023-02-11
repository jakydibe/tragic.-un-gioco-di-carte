#ifndef GAMELIB_H //per evitare errori dato che includo piu' volte
#define GAMELIB_H

enum tipo {creatura,rimuovi_creatura,infliggi_danno,guarisci_danno};
enum classe {tenebre, vita, luce};


struct Carta {
    enum tipo tipo_carta;
    int punti_vita;
    struct Carta* p_prox_carta;
};

struct Mago {
    char nome[256];
    int punti_vita;
    enum classe classe_mago;
    struct Carta* mazzo;
    struct Carta* mano[6];
    struct Carta* campo[4];
    int bool_pesca;
    int bool_attacca;
    int bool_giocacarta;
};


void imposta_gioco(void);
void combatti();
void termina_gioco();
void printa_benvenuto();
void printa_regolamento();
void riprendi_partita();
void pulisci_tutto();

#endif
