#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "gamelib.h"
#include "string.h"


static void imposta_mazzo(struct Mago*,struct Carta*,int);
static void stampa_campo(struct Mago*);
static void stampa_mano(struct Mago*);
static void passa(struct Mago*, int);
static void pesca(struct Mago*);
static void gioca_carta(struct Mago*,struct Mago*);
static void mano_campo(struct Mago*,int);
static void attacca(struct Mago*, struct Mago*);
static void stampa_punti_vita_maghi (struct Mago , struct Mago);
static void salva_partita();
static void imposta_gioco_ripresa();
void riprendi_partita();
void pulisci_tutto();


//ROBE GLOBALI
static int contatore_turni = 0; //un var globale che e' il turno in cui si sta giocando
static int turno = 0;//un numero che puo' essere 1 o 2 e indica il mago che svolge il turno
struct Mago mago1;
struct Mago mago2;
unsigned int numero_carte = 0; //queste 3 variabili numero_carte sono globali perche' mi sarebbe servito per riprendere il gioco salvato in .txt
unsigned int numero_carte1 = 0;
unsigned int numero_carte2 = 0;

void printa_benvenuto() {
    printf("\n\n\n");

    printf("\t\t\t ▄▄▄▄   ▓█████  ███▄    █ ██▒   █▓▓█████  ███▄    █  █    ██ ▄▄▄█████▓ ▒█████      ██▓ ███▄    █ \n");
    printf("\t\t\t▓█████▄ ▓█   ▀  ██ ▀█   █▓██░   █▒▓█   ▀  ██ ▀█   █  ██  ▓██▒▓  ██▒ ▓▒▒██▒  ██▒   ▓██▒ ██ ▀█   █ \n");
    printf("\t\t\t▒██▒ ▄██▒███   ▓██  ▀█ ██▒▓██  █▒░▒███   ▓██  ▀█ ██▒▓██  ▒██░▒ ▓██░ ▒░▒██░  ██▒   ▒██▒▓██  ▀█ ██▒\n");
    printf("\t\t\t▒██░█▀  ▒▓█  ▄ ▓██▒  ▐▌██▒ ▒██ █░░▒▓█  ▄ ▓██▒  ▐▌██▒▓▓█  ░██░░ ▓██▓ ░ ▒██   ██░   ░██░▓██▒  ▐▌██▒\n");
    printf("\t\t\t░▓█  ▀█▓░▒████▒▒██░   ▓██░  ▒▀█░  ░▒████▒▒██░   ▓██░▒▒█████▓   ▒██▒ ░ ░ ████▓▒░   ░██░▒██░   ▓██░\n");
    printf("\t\t\t░▒▓███▀▒░░ ▒░ ░░ ▒░   ▒ ▒   ░ ▐░  ░░ ▒░ ░░ ▒░   ▒ ▒ ░▒▓▒ ▒ ▒   ▒ ░░   ░ ▒░▒░▒░    ░▓  ░ ▒░   ▒ ▒ \n");
    printf("\t\t\t▒░▒   ░  ░ ░  ░░ ░░   ░ ▒░  ░ ░░   ░ ░  ░░ ░░   ░ ▒░░░▒░ ░ ░     ░      ░ ▒ ▒░     ▒ ░░ ░░   ░ ▒░\n");
    printf("\t\t\t░    ░    ░      ░   ░ ░     ░░     ░      ░   ░ ░  ░░░ ░ ░   ░      ░ ░ ░ ▒      ▒ ░   ░   ░ ░ \n");
    printf("\t\t\t░         ░  ░         ░      ░     ░  ░         ░    ░                  ░ ░      ░           ░ \n");
    printf("\t\t\t     ░                       ░                                                                 \n");

    printf("\n\n\n\n\n");

    printf("\t\t\t\t\t     s                                            .              \n");
    printf("\t\t\t\t\t    :8                                           @88>            \n");
    printf("\t\t\t\t\t   .88       .u    .                              8P             \n");
    printf("\t\t\t\t\t  :888ooo  .d88B :@8c        u          uL        .          .   \n");
    printf("\t\t\t\t\t-*8888888 ='8888f8888r    us888u.   .ue888Nc..  .@88u   .udR88N  \n");
    printf("\t\t\t\t\t  8888      4888>'88'  .@88 '8888' d88E`'888E` ''888E` <888'888k \n");
    printf("\t\t\t\t\t  8888      4888> '    9888  9888  888E  888E    888E  9888 'Y'  \n");
    printf("\t\t\t\t\t  8888      4888>      9888  9888  888E  888E    888E  9888      \n");
    printf("\t\t\t\t\t .8888Lu=  .d888L .+   9888  9888  888E  888E    888E  9888      \n");
    printf("\t\t\t\t\t ^C888*    ^'8888*''    9888  9888  888& .888E    888&  ?8888u../ \n");
    printf("\t\t\t\t\t   'Y'        'Y'      '888*'''888' *888' 888&    R888'  '8888P'  \n");
    printf("\t\t\t\t\t                        ^Y'   ^Y'   `''   '888E    ''      'P'    \n");
    printf("\t\t\t\t\t                                   .dWi   `88E                   \n");
    printf("\t\t\t\t\t                                   4888~  J8O                    \n");
    printf("\t\t\t\t\t                                    ^''===*''`                     \n");


    printf("\n\nUN SEMPLICE GIUOCO DI CARTE\n\n\n");


    printf("\n\n\n\n\n\n\n\n");
}


void imposta_gioco(void) {//imposta le caratteristiche della partita
    mago1.punti_vita = 20;
    mago2.punti_vita = 20;

    for(int i = 0; i < 4; i++) { //metto i puntatori dei campi a NULL
        mago1.campo[i] = NULL;
        mago2.campo[i] = NULL;
    }
    //INIZIALIZZAZIONE STRUCT MAGO CON NOMI E CLASSE MAGO

    printf("\nper piacere giocatore numero 1 inserisci il nome del tuo mago----> ");
    fgets(mago1.nome,256,stdin);
    printf("il nome del mago 1 e': %s\n", mago1.nome);
    printf("\nper piacere giocatore numero 2 inserisci il nome del tuo mago----> ");
    fgets(mago2.nome,256,stdin);//prendo input mago2
    printf("il nome del mago2 e': %s\n", mago2.nome);

        int temp_classe_mago = 0;
    do {
        printf("\n");
        printf("ora mago numero 1 scegli la classe del tuo combattente tra le seguenti; digita : -1 per classe TENEBRE\n");
        printf("                                                                                 -2 per classe VITA\n");
        printf("                                                                                 -3 per classe LUCE\n");
        scanf("%d",&temp_classe_mago);
        scanf("%*[^\n]");
        scanf("%*c");


        if (temp_classe_mago < 1 || temp_classe_mago > 3) {
            printf("Per piacere digita un numero valido (1-3)....\n\n");
            continue;
        }
        else {
            break;
        }
    }while(1);

    mago1.classe_mago = temp_classe_mago;
    printf("quindi hai scelto la classe: %d\n", mago1.classe_mago);

    do {
        printf("\n");
        printf("ora mago numero 2 scegli la classe del tuo combattente tra le seguenti; digita : -1 per classe TENEBRE\n");
        printf("                                                                                 -2 per classe VITA\n");
        printf("                                                                                 -3 per classe LUCE\n");
        scanf("%d",&temp_classe_mago);
        scanf("%*[^\n]");
        scanf("%*c");

        if (temp_classe_mago < 1 || temp_classe_mago > 3) {
            printf("Per piacere digita un numero valido (1-3)....\n\n");
            continue;
        }
        else {
            break;
        }
    }while(1);

    mago2.classe_mago = temp_classe_mago;
    printf("quindi hai scelto la classe: %d\n", mago2.classe_mago);

    //CREO I DUE MAZZI OVVERO LE DUE LISTE DINAMICHE
    do{//PRENDO INPUT NUMERO_CARTE
        printf("\ngiocatori, decidete il numero di carte di cui sara' composto il vostro mazzo: almeno 3 carte (e massimo 420)\n");
        scanf("%d",&numero_carte);
        scanf("%*[^\n]");
        scanf("%*c");
    }while(numero_carte < 3 || numero_carte > 420);
    numero_carte1 = numero_carte;
    numero_carte2 = numero_carte;

    //CREAZIONE DEL MAZZO TRAMITE LISTA DINAMICA
    mago1.mazzo = (struct Carta*)malloc(sizeof(struct Carta));//assegno al puntatore mazzo un indirizzo mallocato
    mago1.mazzo->p_prox_carta = NULL;
    struct Carta* p_temp1;
    struct Carta* p_nuovo1;
    p_temp1 = mago1.mazzo;

    for (int i = 0; i < numero_carte -1;i++){//numero carte -1 perche' ho gia' allocato il primo(mago1.mazzo))
        p_nuovo1 = (struct Carta*)malloc(sizeof(struct Carta));//alloco ogni volta un nuovo
        p_nuovo1->p_prox_carta = NULL;

        p_temp1->p_prox_carta = p_nuovo1;//il puntatore temp puntera' all' elemento appena allocato cosi che quando sara' uguale al puntatore di quell' elemento, colleghera' il nodo vecchio al nodo nuovo
        p_temp1 = p_nuovo1;
    }
    imposta_mazzo(&mago1,mago1.mazzo,numero_carte);//imposto il mazzo 1
    printf("Mazzo 1 impostato correttamente\n");

    // CREO LISTA DINAMICA PER MAZZO DEL MAGO 2
    mago2.mazzo = (struct Carta*)malloc(numero_carte*sizeof(struct Carta));
    mago2.mazzo->p_prox_carta = NULL;
    struct Carta* p_temp2;
    struct Carta* p_nuovo2;
    p_temp2 = mago2.mazzo;

    for (int i = 0; i < numero_carte -1;i++){//numero carte -1 perche' ho gia' allocato il primo(mago1.mazzo))
        p_nuovo2 = (struct Carta*)malloc(sizeof(struct Carta));

        p_nuovo2->p_prox_carta = NULL;

        p_temp2->p_prox_carta = p_nuovo2;//il puntatore temp puntera' all' elemento appena allocato cosi che quando sara' uguale al puntatore di quell' elemento, colleghera' il nodo vecchio al nodo nuovo
        p_temp2 = p_nuovo2;
    }
    imposta_mazzo(&mago2,mago2.mazzo,numero_carte);
    printf("Mazzo 2 impostato correttamente\n\n\n");

    //creo 5 carte per la mano di ciascun mago

    for(size_t i = 0; i < 6; i++) {//qui si sta creando la MANO
        mago1.mano[i] = (struct Carta*)malloc(sizeof(struct Carta));//alloco le carte senno' sarebbe solo un array di puntatori
        mago2.mano[i] = (struct Carta*)malloc(sizeof(struct Carta));
        int rand_tipo1 = rand() % 100;//random per il tipo di carta della mano del mago 1
        int rand_tipo2 = rand() % 100;//random per il tipo di carta della mano del mago 2
        int rand_vita1 = (rand() % 2) + 1;//random per i punti vita della carta della mano del mago 1
        int rand_vita2 = (rand() % 2) + 1;//random per i punti vita della carta della mano del mago 2
        mago1.mano[i]->punti_vita = rand_vita1;
        mago2.mano[i]->punti_vita = rand_vita2;

        //IMPOSTO CARTE MANO DEL GIOCATORE 1
        if(rand_tipo1 < 40) {
            mago1.mano[i]->tipo_carta = creatura;
            if(mago1.classe_mago == vita) {
                mago1.mano[i]->punti_vita += mago1.mano[i]->punti_vita/2;
            }
        }
        else if (rand_tipo1 >= 40 && rand_tipo1 < 65) {
            mago1.mano[i]->tipo_carta = rimuovi_creatura;
        }
        else if(rand_tipo1 >= 65 && rand_tipo1 < 85) {
            mago1.mano[i]->tipo_carta = infliggi_danno;
            if(mago1.classe_mago == vita) {
                mago1.mano[i]->punti_vita *= 2;
            }
        }
        else {
            mago1.mano[i]->tipo_carta = guarisci_danno;
            if(mago1.classe_mago == vita) {
                mago1.mano[i]->punti_vita *= (7/2);
            }
        }

        //IMPOSTO CARTE MANO DEL GIOCATORE 2
        if(rand_tipo2 < 40) {
            mago2.mano[i]->tipo_carta = creatura;
            if(mago2.classe_mago == vita) {
                mago2.mano[i]->punti_vita += mago2.mano[i]->punti_vita/2;
            }
        }
        else if (rand_tipo2 >= 40 && rand_tipo2 < 65) {
            mago2.mano[i]->tipo_carta = rimuovi_creatura;
        }
        else if(rand_tipo2 >= 65 && rand_tipo2 < 85) {
            mago2.mano[i]->tipo_carta = infliggi_danno;
            if(mago2.classe_mago == vita) {
                mago2.mano[i]->punti_vita *= 2;
            }
        }
        else {
            mago2.mano[i]->tipo_carta = guarisci_danno;
            if(mago2.classe_mago == vita) {
                mago2.mano[i]->punti_vita *= (7/2);
            }
        }
    }
}

static void imposta_mazzo(struct Mago* mago,struct Carta* p_primo, int numero_carte) {//per ragioni di pulizia le caratteristiche delle carte del mazzo le imposto in una funzione differente da imposta_gioco()
    int contatore = 0;//per tenere conto di quanti loop fare
    struct Carta* p_temp = p_primo;
    int rand_vita;
    int rand_tipo;
    if(p_primo != NULL) {
        while(p_temp->p_prox_carta != NULL) {//itero per tutta la lista dinamica
            //IMPOSTO I PUNTI VITA
            if(contatore <= numero_carte/4) {
                rand_vita = (rand() %2) + 1;
            }
            else if(contatore > numero_carte/4 && contatore <= numero_carte/2) {
                rand_vita = (rand() %4) + 1;
            }
            else if(contatore > numero_carte/2 && contatore <= numero_carte*3/4) {
                rand_vita = (rand() %6) + 1;
            }
            else  {
                rand_vita = (rand() %8) + 1;
            }
            p_temp->punti_vita = rand_vita;
            //IMPOSTO IL TIPO DELLA CARTA
            rand_tipo = rand() % 99;
            if(rand_tipo < 40) {
                p_temp->tipo_carta = creatura;
                if(mago->classe_mago == vita) {
                    p_temp->punti_vita += p_temp->punti_vita/2;
                }
            }
            else if (rand_tipo >= 40 && rand_tipo < 65) {
                p_temp->tipo_carta = rimuovi_creatura;
            }
            else if(rand_tipo >= 65 && rand_tipo < 85) {
                p_temp->tipo_carta = infliggi_danno;
                if(mago->classe_mago == tenebre) {
                    p_temp->punti_vita *= 2;
                }
            }
            else {
                p_temp->tipo_carta = guarisci_danno;
                if(mago->classe_mago == luce) {
                    p_temp->punti_vita *= (7/2);
                }
            }
            p_temp = p_temp->p_prox_carta;
            contatore++;
        }

    }
    for(int i = 0; i < 4; i++) {//inizializzo i puntatori del campo a NULL per evitare inconvenienti
        mago->campo[i] = NULL;
    }
}


void combatti(void) {//struct dei due maghi e puntatori ai mazzi
    int rand_inizio = (rand() % 2) + 1;//numero random tra 1 e 2 per decidere chi inizia
    //inizializzo i booleani delle struct mago per gestire bene i turni ed evitare che si ripeta piu' volte un' azione
    mago1.bool_pesca = 1;
    mago1.bool_attacca = 1;
    mago1.bool_giocacarta = 1;

    mago2.bool_pesca = 1;
    mago2.bool_attacca = 1;
    mago2.bool_giocacarta = 1;

    turno = rand_inizio;//inizio il turno in maniera casuale

    if(turno == 1) {
        printf("iniziera' il mago numero 1!!\n");
    }
    else {
        printf("iniziera' il mago numero 2!!\n");
    }
    while(1) {

        system("clear");//pulisco il terminale senno' e' un macello e non si capisce nulla

        if(mago1.punti_vita <= 0) {//controllo se la partita potrebbe essersi gia' conclusa
            printf("LA PARTITA SI E' CONCLUSA PERCHE' %s HA ESAURITO TUTTI I PUNTI VITA\n\n",mago1.nome);
            printf("\n\n\n\n\n\n\n");
            printf("------------------------------------------------------------------------------------------------------------\n");
            printf("------------------------------------------------------------------------------------------------------------\n");
            printf("                    IL VINCITORE QUINDI E' %s\n",mago2.nome);
            printf("------------------------------------------------------------------------------------------------------------\n");
            printf("------------------------------------------------------------------------------------------------------------\n");

            termina_gioco(); //DEALLOCO TUTTO
        }
        else if (mago2.punti_vita <= 0) {
            printf("LA PARTITA SI E' CONCLUSA PERCHE' %s HA ESAURITO TUTTI I PUNTI VITA\n\n",mago2.nome);
            printf("\n\n\n\n\n\n\n");
            printf("------------------------------------------------------------------------------------------------------------\n");
            printf("------------------------------------------------------------------------------------------------------------\n");
            printf("                    IL VINCITORE QUINDI E' %s\n",mago1.nome);
            printf("------------------------------------------------------------------------------------------------------------\n");
            printf("------------------------------------------------------------------------------------------------------------\n");

            termina_gioco();
        }
        else if(mago1.mazzo == NULL || mago2.mazzo == NULL) {
            printf("LA PARTITA SI E' CONCLUSA PERCHE' UN GIOCATORE HA ESAURITO LE CARTE DEL MAZZO\n\n");
            if(mago1.punti_vita > mago2.punti_vita) {
                printf("\n\n\n\n\n\n\n");
                printf("------------------------------------------------------------------------------------------------------------\n");
                printf("------------------------------------------------------------------------------------------------------------\n");
                printf("                    IL VINCITORE QUINDI E' %s\n",mago1.nome);
                printf("------------------------------------------------------------------------------------------------------------\n");
                printf("------------------------------------------------------------------------------------------------------------\n");
                termina_gioco();
            }
            else if(mago2.punti_vita > mago1.punti_vita) {
                printf("\n\n\n\n\n\n\n");
                printf("------------------------------------------------------------------------------------------------------------\n");
                printf("------------------------------------------------------------------------------------------------------------\n");
                printf("                    IL VINCITORE QUINDI E' %s\n",mago2.nome);
                printf("------------------------------------------------------------------------------------------------------------\n");
                printf("------------------------------------------------------------------------------------------------------------\n");
                termina_gioco();
            }
            else if(mago1.punti_vita == mago2.punti_vita) {
                printf("\n\n\n\\n\n\n\n\n\n\n");
                printf("*********************************************************************************************************\n");
                printf("*********************************************************************************************************\n");
                printf("SEMBREREBBE UN VERO E PROPRIO PAREGGIO QUESTA PARTITA; RITENTATE LA PROSSIMA VOLTA....\n");
                printf("*********************************************************************************************************\n");
                printf("*********************************************************************************************************\n");

                termina_gioco();
            }
        }

        stampa_punti_vita_maghi(mago1,mago2);

        printf("             *******************************************               \n");
        printf("             *************MANO DEL MAGO 1***************               \n");
        printf("             *******************************************               \n\n\n");
        stampa_mano(&mago1);

        printf("             *******************************************               \n");
        printf("             *************CAMPO DEL MAGO 1***************               \n");
        printf("             *******************************************               \n\n\n");
        stampa_campo(&mago1);
        printf("\n\n\n$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n\n\n");

        printf("             *******************************************               \n");
        printf("             *************MANO DEL MAGO 2***************               \n");
        printf("             *******************************************               \n\n\n");
        stampa_mano(&mago2);

        printf("             *******************************************               \n");
        printf("             *************CAMPO DEL MAGO 2***************               \n");
        printf("             *******************************************               \n\n\n");
        stampa_campo(&mago2);
        printf("\n\n\n$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n\n\n");



        //QUI INIZIA IL VERO GIOCO
        int scelta = 0;
        //CONTROLLO SE I BOOLEANI SONO A POSTO, SENNO' FACCIO PASSARE IL TURNO A FORZA PERCHE' SI SONO COMPIUTE TUTTE LE AZIONI
        if(mago1.bool_pesca == 0 && mago1.bool_attacca == 0 && mago1.bool_giocacarta == 0) {//metto passa per cambiare turno
            passa(&mago1,contatore_turni);
        }
        if(mago2.bool_pesca == 0 && mago2.bool_attacca == 0 && mago2.bool_giocacarta == 0) {//metto passa per cambiare turno
            passa(&mago2,contatore_turni);
        }
        do {
            printf("\n\n\n\n^^^^^^^^^^^^^^^^^^^^^^^^SCORRERE IN ALTO PER VISUALIZZARE TUTTI I DATI^^^^^^^^^^^^^^^^^^^^^^^\n\n\n\n");
            printf("\n\nsiamo al turno numero %d\n\n", contatore_turni + 1);
            printf("Bene mago numero %d ,  e' il tuo turno decidi se(digita il numero) : -1 pescare una carta\n",turno);
            printf("                                                                    -2 giocare una carta\n");
            printf("                                                                    -3 attaccare\n");
            printf("                                                                    -4 passa il turno\n");
            printf("                                                                    -5 per salvare la partita\n");
            printf("                                                                    -6 per uscire dal gioco(i dati andranno persi e chiuderai il gioco..)\n");
            scanf("%d",&scelta);
            scanf("%*[^\n]");
            scanf("%*c");

            if(scelta < 1 || scelta > 6) {
                printf("Per piacere digita un numero valido(1-6)...\n\n");
                continue;
            }
            else {
                break;
            }
        }while(1);

        switch(scelta) {//semplice menu di scelta che chiama le varie funzioni
            case 1:
                if(turno == 1 ){
                    if(mago1.bool_pesca == 1) {
                        pesca(&mago1);
                        numero_carte1--;
                        mago1.bool_pesca = 0;
                        printf("\nCARTA PESCATA CORRETTAMENTE DIGITARE QUALSIASI TASTO PER CONTINUARE....");
                        scanf("%*[^\n]"); //TUTTI QUESTI SCANF SERVONO PER FAR LEGGERE ALL' UTENTE L' AZIONE CHE SI E' ESEGUITA PRIMA CHE IL TERMINALE VENGA PULITO DA SYSTEM("CLEAR");
                    }
                    else {
                        printf("mi dispiace ma hai gia' eseguito questa azione nel tuo turno\n");
                    }
                }
                else if(turno == 2){
                    if(mago2.bool_pesca == 1) {
                        pesca(&mago2);
                        numero_carte2--;
                        mago2.bool_pesca = 0;
                        printf("\nCARTA PESCATA CORRETTAMENTE DIGITARE QUALSIASI TASTO PER CONTINUARE....");
                        scanf("%*[^\n]");
                    }
                    else {
                        printf("mi dispiace ma hai gia' eseguito questa azione nel tuo turno\n");
                    }
                }
                else {
                    printf("errore gestione turni...\n");
                }
                break;
            case 2:
                if(turno == 1){
                    if(mago1.bool_giocacarta == 1) {
                        gioca_carta(&mago1,&mago2);
                        mago1.bool_giocacarta = 0;
                        printf("\nCARTA GIOCATA CORRETTAMENTE DIGITARE QUALSIASI TASTO PER CONTINUARE....");
                        scanf("%*[^\n]");
                    }
                    else {
                        printf("mi dispiace ma hai gia' eseguito questa azione nel tuo turno\n");
                    }
                }
                else if(turno == 2) {
                    if(mago2.bool_giocacarta == 1) {
                        gioca_carta(&mago2,&mago1);
                        mago2.bool_giocacarta = 0;
                        printf("\nCARTA GIOCATA CORRETTAMENTE DIGITARE QUALSIASI TASTO PER CONTINUARE....");
                        scanf("%*[^\n]");
                    }
                    else {
                        printf("mi dispiace ma hai gia' eseguito questa azione nel tuo turno\n");
                    }
                }
                else {
                    printf("errore gestione turni...\n");
                }
                break;
            case 3:
                if(turno == 1){
                    if(mago1.bool_attacca == 1) {
                        attacca(&mago1,&mago2);
                        mago1.bool_attacca = 0;
                        printf("\nATTACCO ESEGUITO CORRETTAMENTE DIGITARE QUALSIASI TASTO PER CONTINUARE....");
                        scanf("%*[^\n]");
                    }
                    else {
                        printf("mi dispiace ma hai gia' eseguito questa azione nel tuo turno\n");
                    }
                }
                else if(turno == 2){
                    if(mago2.bool_attacca == 1) {
                        attacca(&mago2,&mago1);
                        mago2.bool_attacca = 0;
                        printf("\nATTACCO ESEGUITO CORRETTAMENTE DIGITARE QUALSIASI TASTO PER CONTINUARE....");
                        scanf("%*[^\n]");
                    }
                    else {
                        printf("mi dispiace ma hai gia' eseguito questa azione nel tuo turno\n");
                    }
                }
                else {
                    printf("errore gestione turni...\n");
                }
                break;
            case 4:
                if(turno == 1){
                    passa(&mago1,contatore_turni);
                    printf("\nTURNO PASSATO CORRETTAMENTE DIGITARE QUALSIASI TASTO PER CONTINUARE....");
                    scanf("%*[^\n]");
                }
                else if (turno == 2){
                    passa(&mago2,contatore_turni);
                    printf("\nTURNO PASSATO CORRETTAMENTE DIGITARE QUALSIASI TASTO PER CONTINUARE....");
                    scanf("%*[^\n]");
                }
                else {
                    printf("errore gestione turni...\n");
                }
                break;
            case 5:
                salva_partita();
                printf("Partita salvata CORRETTAMENTE....\n");
                printf("PREMI QUALSIASI TASTO PER CONTINUARE....");
                scanf("%*[^\n]");
                break;
            case 6:
                termina_gioco();
                break;
            default:
                printf("per piacere digita un numero valido (1-4)\n");
        }
    }
}


static void passa(struct Mago* mago, int contatoreturni) {//questa funzione fa cambiare il turno al giocatore e ri imposta ad 1 i booleani per compiere le azioni
    printf("\nBene bene il tuo turno e' completato!!, ora e' il turno di %s\n", mago->nome);
    if (turno == 1){//cambia il turno qui
        turno = 2;
    }
    else if(turno == 2) {
        turno = 1;
    }
    else {
        printf("errore gestione turni...\n");
    }
    mago->bool_pesca = 1;//riimposta i booleani ad 1 cosi' che al prossimo turno i maghi potranno nuovamente svolgere azioni
    mago->bool_attacca = 1;
    mago->bool_giocacarta = 1;
    contatore_turni++;//aumenta il contatore dei turni
}


static void stampa_mano(struct Mago* mago) {//questa funzione deve solamente stampare la mano
    printf("bene; nella tua mano ci sono le seguenti carte\n\n\n");
    char str_tipo_carta[256];
    for(int i = 0; i < 6 ; i++) {
        if(mago->mano[i] == NULL) {
            printf("POSIZIONE CARTA VUOTA\n\n");
            continue;
        }
        else {
            switch(mago->mano[i]->tipo_carta) {//errore che non riconosce il tipo carta
                case 0:
                    strcpy(str_tipo_carta,"CREATURA");
                    break;
                case 1:
                    strcpy(str_tipo_carta,"RIMUOVI CREATURA");
                    break;
                case 2:
                    strcpy(str_tipo_carta,"INFLIGGI DANNO");
                    break;
                case 3:
                    strcpy(str_tipo_carta,"GUARISCI DANNO");
                    break;
                default:
                    printf("errore riconoscimento tipo carta\n\n");
            }
            printf("TIPOLOGIA DELLA CARTA: %s\n", str_tipo_carta);
            if(mago->mano[i]->tipo_carta == creatura) {
                printf("PUNTI VITA DELLA CREATURA: %d\n", mago->mano[i]->punti_vita);
            }
            else if(mago->mano[i]->tipo_carta == rimuovi_creatura) {
                printf("CREATURE CHE QUESTA CARTA PUO' ELIMINARE: 1\n");
            }
            else if(mago->mano[i]->tipo_carta == infliggi_danno) {
                printf("DANNO CHE INFLIGGE CARTA INFLIGGI DANNO: %d\n", mago->mano[i]->punti_vita);
            }
            else if (mago->mano[i]->tipo_carta == guarisci_danno){
                printf("DANNO CHE GUARISCE LA CARTA GUARISCI DANNO: %d\n",mago->mano[i]->punti_vita);
            }
            else {
                printf("errore tipo carta\n\n");
            }
            printf("CARTA POSIZIONE NUMERO: %d\n\n",i+1);
        }
    }
    printf("\n\n\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~                            ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n\n\n");
}


static void stampa_campo(struct Mago* mago) {//questa funzione deve solamente stampare le carte dentro al campo(estremamente simile a stampa_mano)
    printf("bene; nel tuo campo ci sono le seguenti carte\n\n\n");
    char str_tipo_carta[256];

    for(int i = 0; i < 4 ; i++) {
        if(mago->campo[i] == NULL) {
            printf("POSIZIONE CARTA VUOTA\n\n");
            continue;
        }
        else {
            switch(mago->campo[i]->tipo_carta) {
                case 0:
                    strcpy(str_tipo_carta,"CREATURA");
                    break;
                case 1:
                    strcpy(str_tipo_carta,"RIMUOVI CREATURA");
                    break;
                case 2:
                    strcpy(str_tipo_carta,"INFLIGGI DANNO");
                    break;
                case 3:
                    strcpy(str_tipo_carta,"GUARISCI DANNO");
                    break;
                default:
                    printf("errore riconoscimento tipo carta\n\n");
            }
            printf("TIPOLOGIA DELLA CARTA: %s \n", str_tipo_carta);
            if(mago->campo[i]->tipo_carta == creatura) {
                printf("PUNTI VITA DELLA CREATURA: %d\n", mago->campo[i]->punti_vita);
            }
            else if(mago->campo[i]->tipo_carta == rimuovi_creatura) {
                printf("PUNTI VITA DELLA CARTA RIMUOVI CREATURA: %d\n", mago->campo[i]->punti_vita);
            }
            else if(mago->campo[i]->tipo_carta == infliggi_danno) {
                printf("DANNO CHE INFLIGGE CARTA INFLIGGI DANNO: %d\n", mago->campo[i]->punti_vita);
            }
            else if(mago->campo[i]->tipo_carta == guarisci_danno){
                printf("DANNO CHE GUARISCE LA CARTA GUARISCI DANNO: %d\n",mago->campo[i]->punti_vita);
            }
            else {
                printf("errore tipo carta....\n\n");
            }
            printf("CARTA POSIZIONE NUMERO: %d\n\n\n",i+1);
        }
    }
}


static void pesca (struct Mago* mago) {//pesca il primo elemento della lista dinamica e lo mette nella prima posizione vuota della mano che trova
    struct Carta* p_temp = mago->mazzo;
    for(int i = 0; i < 6; i++) {
        if(mago->mano[i] == NULL) { //SE C'E' POSTO LIBERO PESCA DIRETTAMENTE
            mago->mano[i] = p_temp;
            mago->mazzo = mago->mazzo->p_prox_carta;
            break;
        }
        else { //SE NON C'E' POSTO LIBERO ELIMINA UNA CARTA A SCELTA
            if (i == 5) {//cosi' da non fermarsi prima che si incontri una posizione vuota
                int carta_da_eliminare = 0;
                do {
                    printf("mi dispiace ma la tua mano e' piena, scegli quale carta scartare per fare spazio alla nuova(digita il numero):-->  ");
                    scanf("%d", &carta_da_eliminare);//faccio scegliere la carta da eliminare per far spazio alla nuova carta
                    scanf("%*[^\n]");
                    scanf("%*c");

                    carta_da_eliminare -= 1;

                    if(carta_da_eliminare < 0 || carta_da_eliminare > 5) {
                        printf("Per piacere digita un numero valido (1-6) ...\n\n");
                        continue;
                    }
                    else {
                        break;
                    }
                }while(1);

                mago->mano[carta_da_eliminare] = p_temp;
                mago->mazzo = mago->mazzo->p_prox_carta;
            }
            else {
                continue;
            }
        }
    }
}


static void gioca_carta(struct Mago* mago_attacco, struct Mago* mago_difesa) {//struct dei due maghi
    int bool_campo_non_nullo = 0;//bool per vedere se il campo e' vuoto
    int carta_giocata = 0;//numero della carta da giocare
    int carta_attaccata = 0;//numero della carta da attaccare

    for(int i = 0; i < 4; i++) {
        if(mago_difesa->campo[i] != NULL) {//checka se il campo e' vuoto o no
            bool_campo_non_nullo = 1;
        }
    }

    do {
        printf("Attaccante!; scegli quale carta giocare (ricordati che devi digitare il numero) ------> ");
        scanf("%d", &carta_giocata);
        scanf("%*[^\n]");
        scanf("%*c");

        carta_giocata -= 1;
        if(carta_giocata < 0 || carta_giocata > 5 || mago_attacco->mano[carta_giocata] == NULL) {
            printf("Per piacere digita un numero valido (1-6) e di una carta realmente presente nel tuo mazzo...\n\n");
            continue;
        }
        else {
            break;
        }
    }while(1);

    if(mago_attacco->mano[carta_giocata]->tipo_carta == rimuovi_creatura) { // rimuovi creatura nemica che ovviamente si puo scegliere
        if(bool_campo_non_nullo == 1) {
            do {
                printf("scegli la creatura nemica da rimuovere-----> ");
                scanf("%d", &carta_attaccata);
                scanf("%*[^\n]");
                scanf("%*c");

                carta_attaccata -= 1;
                printf("\n\n");

                if(carta_attaccata < 0 || carta_attaccata > 3 || mago_difesa->campo[carta_attaccata] == NULL) {
                    printf("Per piacere digita un numero valido (1-4) e una carta realmente presente nel campo avversario...\n\n");
                    continue;
                }
                else {
                    break;
                }
            }while(1);
            free(mago_difesa->campo[carta_attaccata]); // dealloco memoria
            mago_difesa->campo[carta_attaccata] = NULL;
            free(mago_attacco->mano[carta_giocata]);
            mago_attacco->mano[carta_giocata] = NULL;
            printf("\nCREATURA NEMICA ELIMINATA CON SUCCESSO!!\n");
        }
        else {
            printf("Mi dispiace ma il nemico non ha creature sul campo!!\n");
        }
    }

    else if(mago_attacco->mano[carta_giocata]->tipo_carta == infliggi_danno) {// infliggi danno o al mago o ad una creatura nel campo
        int scelta_mago_o_creatura = 0;

        do {
            printf("scegli se attaccare una creatura nel campo(digita 1) oppure attaccare direttamente il mago avversario -----> ");
            scanf("%d", &scelta_mago_o_creatura);
            scanf("%*[^\n]");
            scanf("%*c");

            printf("n\n");
            if(scelta_mago_o_creatura != 1 && scelta_mago_o_creatura != 2) {
                printf("Per piacere digita un numero valido(1-2)...\n\n");
                continue;
            }
            else {
                break;
            }
        }while(1);


        if(scelta_mago_o_creatura == 2) {//attacca direttamente il mago
            printf("\n\nPV MAGO ATTACCATO %d - %d = %d\n",mago_difesa->punti_vita,mago_attacco->mano[carta_giocata]->punti_vita,mago_difesa->punti_vita - mago_attacco->mano[carta_giocata]->punti_vita);
            mago_difesa->punti_vita -= mago_attacco->mano[carta_giocata]->punti_vita; //tolgo al mago avversario il numero di punti vita della carta che ho giocato
            free(mago_attacco->mano[carta_giocata]);
            mago_attacco->mano[carta_giocata] = NULL;
        }
        else if(scelta_mago_o_creatura == 1) {
            int scelta_creatura_infliggi_danno = 0;
            if(bool_campo_non_nullo == 1) {

                do {
                    printf("Scegli la creatura da attaccare dal campo del nemico ----> ");
                    scanf("%d", &scelta_creatura_infliggi_danno);
                    scanf("%*[^\n]");
                    scanf("%*c");

                    scelta_creatura_infliggi_danno -= 1;
                    printf("\n\n");

                    if(scelta_creatura_infliggi_danno < 0 || scelta_creatura_infliggi_danno > 3 || mago_difesa->campo[scelta_creatura_infliggi_danno] == NULL) {
                        printf("Per piacere digita un numero valido (1-4) e di una carta che realmente e' presente nel campo...\n\n");
                        continue;
                    }
                    else {
                        break;
                    }
                }while(1);

                printf("\n\nCREATURA NEMICA PV: %d - %d = %d\n",mago_difesa->campo[scelta_creatura_infliggi_danno]->punti_vita,mago_attacco->mano[carta_giocata]->punti_vita, mago_difesa->campo[scelta_creatura_infliggi_danno]->punti_vita - mago_attacco->mano[carta_giocata]->punti_vita);
                mago_difesa->campo[scelta_creatura_infliggi_danno]->punti_vita -= mago_attacco->mano[carta_giocata]->punti_vita;//tolgo alla creatura del nemico i punti vita della carta giocata
                free(mago_attacco->mano[carta_giocata]);
                if(mago_difesa->campo[scelta_creatura_infliggi_danno]->punti_vita <= 0) {
                    free(mago_difesa->campo[scelta_creatura_infliggi_danno]);
                    mago_difesa->campo[scelta_creatura_infliggi_danno] = NULL;
                }
            }
            else {
                printf("Mi dispiace ma sul campo nemico non e' presente alcuna creatura\n\n");
            }
        }
        else {
            printf("digita un numero valido per piacere\n\n");
        }
    }
    else if(mago_attacco->mano[carta_giocata]->tipo_carta == guarisci_danno) {
        int curare_se_o_creatura = 0;
        do {
            printf("Scegli se curare te stesso(digita 1) oppure curare una tua creatura(digita 2) ---> ");
            scanf("%d", &curare_se_o_creatura);
            scanf("%*[^\n]");
            scanf("%*c");

            printf("\n\n");

            if(curare_se_o_creatura != 1 && curare_se_o_creatura != 2) {
                printf("Per piacere digita un numero valido (1-2)...\n\n");
                continue;
            }
            else {
                break;
            }
        }while(1);

        if(curare_se_o_creatura == 1) {
            printf("\n\nPV TUOI: %d + %d = %d\n",mago_attacco->punti_vita,mago_attacco->mano[carta_giocata]->punti_vita,mago_attacco->punti_vita + mago_attacco->mano[carta_giocata]->punti_vita);
            mago_attacco->punti_vita += mago_attacco->mano[carta_giocata]->punti_vita;
            free(mago_attacco->mano[carta_giocata]);
            mago_attacco->mano[carta_giocata] = NULL;
        }
        else if(curare_se_o_creatura == 2) {
            int scelta_creatura_guarisci_danno = 0;
            if(bool_campo_non_nullo == 1) {
                do {
                    printf("scegli quale tua creatura curare ----> ");
                    scanf("%d", &scelta_creatura_guarisci_danno);
                    scanf("%*[^\n]");
                    scanf("%*c");

                    scelta_creatura_guarisci_danno -= 1;
                    printf("\n\n");
                    if (scelta_creatura_guarisci_danno < 0 || scelta_creatura_guarisci_danno > 3 || mago_attacco->campo[scelta_creatura_guarisci_danno] == NULL) {
                        printf("Per piacere digita un numero valido (1-4) e di una creatura realmente presente nel campo...\n\n");
                        continue;
                    }
                    else {
                        break;
                    }
                }while(1);

                printf("\n\nPV CREATURA: %d + %d = %d\n",mago_attacco->campo[scelta_creatura_guarisci_danno]->punti_vita,mago_attacco->mano[carta_giocata]->punti_vita, mago_attacco->campo[scelta_creatura_guarisci_danno]->punti_vita + mago_attacco->mano[carta_giocata]->punti_vita);
                mago_attacco->campo[scelta_creatura_guarisci_danno]->punti_vita += mago_attacco->mano[carta_giocata]->punti_vita;
                free(mago_attacco->mano[carta_giocata]);
                mago_attacco->mano[carta_giocata] = NULL;
            }
            else {
                printf("Mi dispiace ma non hai alcuna creatura schierata sul campo\n\n");
            }
        }
    }
    else if(mago_attacco->mano[carta_giocata]->tipo_carta == creatura) {
        mano_campo(mago_attacco, carta_giocata);
    }
    else {
        printf("Errore riconoscimento tipo carta...\n\n");
    }

    printf("\n\n");



}


static void mano_campo(struct Mago* mago, int carta_mano) {//struct mago e numero della carta della mano da spostare nel campo
    if(mago->mano[carta_mano]->tipo_carta == creatura) {
        for(int i = 0; i < 4; i++) {
            if(mago->campo[i] == NULL) {
                mago->campo[i] = mago->mano[carta_mano];//assegno al primo posto vuoto nel campo il puntatore alla carta creatura della mano che volevo giocare
                printf("\n\nCREATURA POSIZIONATA CORRETTAMENTE IN CAMPO...\n");
                mago->mano[carta_mano] = NULL;
                break;
            }
            else {
                if (i == 3) { // faccio questo solo se tutti e tre i posti nel campo sono gia' occupati
                    int carta_campo_eliminare = 0;
                    do {
                        scanf("%d", &carta_campo_eliminare);
                        scanf("%*[^\n]");
                        scanf("%*c");

                        printf("\n\n");
                        carta_campo_eliminare -= 1;
                        printf("scegli che carta eliminare dal campo:---> ");

                        if(carta_campo_eliminare < 0 || carta_campo_eliminare > 3) {
                            printf("Per piacere digita un numero valido (1-4)...\n\n");
                            continue;
                        }
                        else {
                            break;
                        }
                    }while(1);

                    mago->campo[carta_campo_eliminare] = mago->mano[carta_mano];
                    mago->mano[carta_mano] = NULL;
                    printf("\n\nCREATURA POSIZIONATA CORRETTAMENTE IN CAMPO...\n");
                    break;
                }
                else {
                    continue;
                }
            }
        }
    }
    else {
        printf("errore chiamata mano_campo: tipo carta incompatibile con azione richiesta...\n\n");
    }
}


static void attacca(struct Mago* mago_attacco, struct Mago* mago_difesa) {//si utilizza la creatura gia' schierata in campo per attaccare creature o maghi
    int bool_campo_attacco_non_nullo = 0;//booleani per
    int bool_campo_difesa_non_nullo = 0;//
    for (int i = 0; i < 4; i++) { //CONTROLLA CHE I CAMPI DEI DUE MAGHI NON SIANO VUOTI
        if (mago_attacco->campo[i] != NULL) {
            bool_campo_attacco_non_nullo = 1;
        }
        if(mago_difesa->campo[i] != NULL) {
            bool_campo_difesa_non_nullo = 1;
        }
    }
    if (bool_campo_attacco_non_nullo == 1) {
        printf("Bene, hai scelto di attaccare utilizzando una delle creature schierate sul tuo campo!!\n\n");
        int scelta_mago_o_creatura = 0;
        int scelta_creatura_attacco = 0;
        int scelta_creatura_difesa = 0;

        do {
            printf("Ora scegli se attaccare una creatura (Premi 1) oppure attaccare direttamente il mago avversario(Premi 2)\n\n");
            scanf("%d",&scelta_mago_o_creatura);
            scanf("%*[^\n]");
            scanf("%*c");

            if(scelta_mago_o_creatura != 1 && scelta_mago_o_creatura != 2) {
                printf("Per piacere digita un numero valido (1-2)...\n\n");
                continue;
            }
            else {
                break;
            }
        }while(1);

        if (scelta_mago_o_creatura == 1) {
            if(bool_campo_difesa_non_nullo == 0) {
                int scelta = 0;

                do {
                    printf("Mi dispiace ma attualmente non c'e' alcuna creatura nel campo nemico\n");
                    printf("desideri comunque proseguire e attaccare direttamente il mago avversario(Premi 1) oppure desideri tornare indietro(Premi 2)\n\n");
                    scanf("%d",&scelta);
                    scanf("%*[^\n]");
                    scanf("%*c");
                    if(scelta != 1 && scelta != 2) {
                        printf("Per piacere digita un numero valido (1-2)...\n\n");
                        continue;
                    }
                    else {
                        break;
                    }
                }while(1);

                if(scelta == 1) {
                    do {
                        printf("OK scegli quale creatura utilizzare: (digita il suo numero di posizione)\n\n");
                        scanf("%d",&scelta_creatura_attacco);
                        scanf("%*[^\n]");
                        scanf("%*c");

                        scelta_creatura_attacco -= 1;

                        if(scelta_creatura_attacco < 0 || scelta_creatura_attacco > 3 || mago_attacco->campo[scelta_creatura_attacco] == NULL) {
                            printf("**********Per piacere digita un numero valido (1-4) e di una carta realmente presente nel campo...********\n\n");
                            continue;
                        }
                        else {
                            break;
                        }
                    }while(1);

                    mago_difesa->punti_vita -= mago_attacco->campo[scelta_creatura_attacco]->punti_vita;
                    return;
                }
                if (scelta == 2) {
                    return;
                }
            }
            else {//se invece ci sono creature nel CAMPO
                do {
                    printf("Tutto a posto: sia te che il tuo nemico avete creature schierate sul campo");
                    printf("Quindi hai scelto di attaccare utilizzando una tua creatura\n\n");
                    printf("Ora scegli la creatura con cui attaccare(Digita il suo numero di posizione)\n\n");
                    scanf("%d",&scelta_creatura_attacco);
                    scanf("%*[^\n]");
                    scanf("%*c");

                    scelta_creatura_attacco -= 1;

                    if (scelta_creatura_attacco < 0 || scelta_creatura_attacco > 3 || mago_attacco->campo[scelta_creatura_attacco] == NULL) {
                        printf("Per piacere digita un numero valido (1-4) e di una creatura realmente presente nel campo...\n\n");
                        continue;
                    }
                    else {
                        break;
                    }
                }while(1);

                do{
                    printf("\n\nora invece scegli la creatura da attaccare(digita il suo numero di posizione)\n\n");
                    scanf("%d",&scelta_creatura_difesa);
                    scanf("%*[^\n]");
                    scanf("%*c");

                    scelta_creatura_difesa -= 1;

                    if(scelta_creatura_difesa < 0 || scelta_creatura_difesa > 3 || mago_difesa->campo[scelta_creatura_difesa] == NULL) {
                        printf("Per piacere digita un numero valido (1-4) e di una creatura realmente presente nel campo...\n\n");
                        continue;
                    }
                    else {
                        break;
                    }
                }while(1);

                int vita_vecchia = mago_difesa->campo[scelta_creatura_difesa]->punti_vita;//PER NON PERDERE IL VALORE DELLA VITA
                mago_difesa->campo[scelta_creatura_difesa]->punti_vita -= mago_attacco->campo[scelta_creatura_attacco]->punti_vita;
                if(mago_difesa->campo[scelta_creatura_difesa]->punti_vita <= 0) {
                    printf("Mi dispiace %s ma la tua creatura e' stata eliminata!\n", mago_difesa->nome);
                    mago_difesa->campo[scelta_creatura_difesa] = NULL;
                    free(mago_difesa->campo[scelta_creatura_difesa]);
                }
                else {
                    printf("CREATURA NUMERO %d %d - %d = %d PUNTI VITA ATTUALI\n\n",scelta_creatura_difesa, vita_vecchia, mago_attacco->campo[scelta_creatura_attacco]->punti_vita,mago_difesa->campo[scelta_creatura_difesa]->punti_vita);
                    return;
                }

            }
        }
        else {
            do {
                printf("Quindi %s hai scelto di attaccare direttamente l' avversario!!\n\n", mago_attacco->nome);
                printf("Bene, ora scegli che creatura utilizzare(digita suo numero di posizione)\n\n");
                scanf("%d", &scelta_creatura_attacco);
                scanf("%*[^\n]");
                scanf("%*c");

                scelta_creatura_attacco -= 1;

                if(scelta_creatura_attacco < 0 || scelta_creatura_attacco > 3 || mago_attacco->campo[scelta_creatura_attacco] == NULL) {
                    printf("Per piacere digita un numero valido (1-4) e di una creatura realmente presente nel campo...\n\n");
                    continue;
                }
                else {
                    break;
                }
            }while(1);

            int vita_vecchia = mago_difesa->punti_vita;
            mago_difesa->punti_vita -= mago_attacco->campo[scelta_creatura_attacco]->punti_vita;
            if(mago_difesa->punti_vita > 0) {
                printf("MAGO IN DIFESA %d - %d = %d PUNTI VITA ATTUALI\n\n",vita_vecchia,mago_attacco->campo[scelta_creatura_attacco]->punti_vita,mago_difesa->punti_vita);
                return;
            }
        }
    }
    else {
        printf("Mi dispiace ma al momento non e' presente alcuna creatura nel tuo campo, percio' non potrai attaccare");
        return;
    }

}


static void stampa_punti_vita_maghi (struct Mago mago1, struct Mago mago2) {//semplicemente stampo i punti vita dei maghi
    printf("********************************************\n");
    printf("*********PUNTI VITA MAGO 1: %d *************\n",mago1.punti_vita);
    printf("********************************************\n");

    printf("\n\n\n_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-\n\n\n");

    printf("********************************************\n");
    printf("*********PUNTI VITA MAGO 2: %d *************\n",mago2.punti_vita);
    printf("********************************************\n");
    printf("\n\n\n\n");
}


void termina_gioco(void) {
    printf(" ██████╗ ██████╗  █████╗ ███████╗██╗███████╗    ██████╗ ███████╗██████╗      █████╗ ██╗   ██╗███████╗██████╗      ██████╗ ██╗ ██████╗  ██████╗ █████╗ ████████╗ ██████╗   \n");
    printf("██╔════╝ ██╔══██╗██╔══██╗╚══███╔╝██║██╔════╝    ██╔══██╗██╔════╝██╔══██╗    ██╔══██╗██║   ██║██╔════╝██╔══██╗    ██╔════╝ ██║██╔═══██╗██╔════╝██╔══██╗╚══██╔══╝██╔═══██╗   \n");
    printf("██║  ███╗██████╔╝███████║  ███╔╝ ██║█████╗      ██████╔╝█████╗  ██████╔╝    ███████║██║   ██║█████╗  ██████╔╝    ██║  ███╗██║██║   ██║██║     ███████║   ██║   ██║   ██║    \n");
    printf("██║   ██║██╔══██╗██╔══██║ ███╔╝  ██║██╔══╝      ██╔═══╝ ██╔══╝  ██╔══██╗    ██╔══██║╚██╗ ██╔╝██╔══╝  ██╔══██╗    ██║   ██║██║██║   ██║██║     ██╔══██║   ██║   ██║   ██║    \n");
    printf("╚██████╔╝██║  ██║██║  ██║███████╗██║███████╗    ██║     ███████╗██║  ██║    ██║  ██║ ╚████╔╝ ███████╗██║  ██║    ╚██████╔╝██║╚██████╔╝╚██████╗██║  ██║   ██║   ╚██████╔╝    \n");
    printf(" ╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═╝╚══════╝╚═╝╚══════╝    ╚═╝     ╚══════╝╚═╝  ╚═╝    ╚═╝  ╚═╝  ╚═══╝  ╚══════╝╚═╝  ╚═╝     ╚═════╝ ╚═╝ ╚═════╝  ╚═════╝╚═╝  ╚═╝   ╚═╝    ╚═════╝     \n");

    printf("\n\n\n\n\n\n\n");


    printf("                                 █████╗     ████████╗██████╗  █████╗  ██████╗ ██╗ ██████╗  \n");
    printf("                                ██╔══██╗    ╚══██╔══╝██╔══██╗██╔══██╗██╔════╝ ██║██╔════╝   \n");
    printf("                                ███████║       ██║   ██████╔╝███████║██║  ███╗██║██║        \n");
    printf("                                ██╔══██║       ██║   ██╔══██╗██╔══██║██║   ██║██║██║         \n");
    printf("                                ██║  ██║       ██║   ██║  ██║██║  ██║╚██████╔╝██║╚██████╗     \n");
    printf("                                ╚═╝  ╚═╝       ╚═╝   ╚═╝  ╚═╝╚═╝  ╚═╝ ╚═════╝ ╚═╝ ╚═════╝      \n");

    pulisci_tutto();
    exit(0);
//printa un saluto, dealloca tutto ed esce dal gioco
}


void printa_regolamento(void) { //STAMPA IL REGOLAMENTO DEL GIOCO
    printf("Le regole di TRAGIC sono semplici. Voi siete due maghi che devono sfidarsi nelle lande desolate  a suon di incantesimi e creature.\n\n");
    printf("Inizialmente vi sara' semplicemente richiesto di impostare il gioco in base alle vostre preferenze.\n\n");
    printf("Per quanto riguarda la scelta delle classi dei maghi : se scegli VITA le tue creature avranno i 3/2 della vita che senno' avrebbero, \n");
    printf("se invece scegli TENEBRA le tue carte INFLIGGI DANNO infliggeranno il doppio del danno che senno' infiggerebbero, se scegli LUCE le tue \n");
    printf("carte guarisci danno guariranno i 7/2 dei danni che altrimenti guarirebbero.\n\n");
    printf("Detto cio' ci sono 4 tipologie di carte: le carte CREATURA, che si devono schierare in campo e possono attaccare altre creature o \n");
    printf("direttamente il mago avversario, le carte INFLIGGI DANNO infliggono danno alle creature nemiche o al mago avversario, \n");
    printf("le carte RIMUOVI CREATURA rimuovono una creatura a scelta dal campo nemico e infine le carte GUARISCI DANNO rifocillare di punti vita \n");
    printf("le creature o i maghi stessi\n\n\n\n\n");
    printf("Spero di essere stato il piu' chiaro possibile e vi auguro un buon divertimento!!!\n\n");//semplicemente stampa il regolamento
}


static void salva_partita() { //SALVA I DATI DEL GIOCO IN 4 DIFFERENTI FILE .TXT
    printf("Bene hai deciso di salvare la tua partita in memoria!!\n\n");

    //salvo i dati generali
    FILE* file_dati_generali = fopen("dati_generali.txt","w+"); //APRI I FILE IN SCRITTURA
    if(file_dati_generali == NULL) {
        printf("Errore aprendo il file....\n");
        exit(1);
    }
    else {
        fprintf(file_dati_generali,"TURNO NUMERO %d\n",contatore_turni);//SCRIVO I VARI DATI
        fprintf(file_dati_generali,"TURNO %d\n",turno);
        fprintf(file_dati_generali,"CARTE MAGO 1 %d\n",numero_carte1);
        fprintf(file_dati_generali,"CARTE MAGO 2 %d",numero_carte2);
        //chiudo i file
        fclose(file_dati_generali);
    }

    //creo e salvo i dati dei maghi
    FILE* file_dati_maghi = fopen("dati_maghi.txt", "w+");
    if (file_dati_maghi == NULL){
        printf("Errore aprendo il file...\n");
        exit(1);
    }
    else {
        //PRINTO DATI MAGO 1
        fprintf(file_dati_maghi,"MAGO1:\n");
        fprintf(file_dati_maghi,"PUNTI_VITA: %d\n",mago1.punti_vita);
        fprintf(file_dati_maghi,"CLASSE: %d\n",mago1.classe_mago);
        fprintf(file_dati_maghi,"NOME: %s",mago1.nome);
        fprintf(file_dati_maghi,"bool_pesca %d\n",mago1.bool_pesca);
        fprintf(file_dati_maghi,"bool_attacca %d\n",mago1.bool_attacca);
        fprintf(file_dati_maghi,"bool_giocacarta %d\n\n\n",mago1.bool_giocacarta);

        //PRINTO DATI MAGO 2
        fprintf(file_dati_maghi,"MAGO2:\n");
        fprintf(file_dati_maghi,"PUNTI_VITA: %d\n",mago2.punti_vita);
        fprintf(file_dati_maghi,"CLASSE: %d\n",mago2.classe_mago);
        fprintf(file_dati_maghi,"NOME: %s",mago2.nome);
        fprintf(file_dati_maghi,"bool_pesca %d\n",mago2.bool_pesca);
        fprintf(file_dati_maghi,"bool_attacca %d\n",mago2.bool_attacca);
        fprintf(file_dati_maghi,"bool_giocacarta %d",mago2.bool_giocacarta);

        fclose(file_dati_maghi);

    }//prova a salvare la partita

    //SALVO DATI DELLE CARTE NELLA MANO: PRIMO PARAMETRO NUMERO DEL AMGO, 2 PUNTI VITA, 3 TIPO DI CARTA
    FILE* file_dati_mano = fopen("dati_mano.txt","w+");
    if(file_dati_mano == NULL) {
        printf("Errore aprendo il file.....\n");
        exit(1);
    }
    else {
        //prima stampo per la mano del mago 1 e quindi stampo 1 come primo char
        for (int i = 0; i < 6; i++) {
            fprintf(file_dati_mano,"1 ");//NUMERO MAGO
            if(mago1.mano[i] != NULL) {
                fprintf(file_dati_mano,"%d ",mago1.mano[i]->punti_vita);
                fprintf(file_dati_mano,"%d\n",mago1.mano[i]->tipo_carta);
            }
            else {
                fprintf(file_dati_mano,"-\n");
            }
        }
        //stampo dati mago 2
        for (int i = 0; i < 6; i++) {
            fprintf(file_dati_mano,"2 ");//NUMERO MAGO
            if(mago2.mano[i] != NULL) {
                if(i < 5) { // PER NON METTERE \n NELL' ULTIMA RIGA CONTROLLO (PERCHE' SENNO' IN LETTURA DEL FILE DA ERRORE PERCHE' LEGGEVA PURE QUELLA)
                    fprintf(file_dati_mano,"%d ",mago1.mano[i]->punti_vita);
                    fprintf(file_dati_mano,"%d\n",mago1.mano[i]->tipo_carta);
                }
                else {
                    fprintf(file_dati_mano,"%d ",mago1.mano[i]->punti_vita);
                    fprintf(file_dati_mano,"%d",mago1.mano[i]->tipo_carta);
                }
            }
            else {
                fprintf(file_dati_mano,"-\n");
            }
        }
        fclose(file_dati_mano);
    }

    //SALVO DATI DELLE CARTA NEL CAMPO
    FILE* file_dati_campo = fopen("dati_campo.txt","w+");
    if(file_dati_campo == NULL) {
        printf("Errore aprendo il file.....\n");
        exit(1);
    }
    else {
        //prima stampo per la mano del mago 1 e quindi stampo 1 come primo char
        for (int i = 0; i < 4; i++) {
            fprintf(file_dati_campo,"1 ");//NUMERO MAGO
            if(mago1.campo[i] != NULL) {
                fprintf(file_dati_campo,"%d ",mago1.campo[i]->punti_vita);
                fprintf(file_dati_campo,"%d\n",mago1.campo[i]->tipo_carta);
            }
            else {
                fprintf(file_dati_campo,"-\n");
            }
        }
        //stampo dati mago 2
        for (int i = 0; i < 4; i++) {
            fprintf(file_dati_campo,"2 ");//NUMERO MAGO
            if(mago2.campo[i] != NULL) {
                if(i < 3) {
                    fprintf(file_dati_mano,"%d ",mago2.campo[i]->punti_vita);
                    fprintf(file_dati_mano,"%d\n",mago2.campo[i]->tipo_carta);
                }
                else {
                    fprintf(file_dati_mano,"%d ",mago2.campo[i]->punti_vita);
                    fprintf(file_dati_mano,"%d",mago2.campo[i]->tipo_carta);
                }
            }
            else {
                if(i < 3) {
                    fprintf(file_dati_campo,"-\n");
                }
                else {
                    fprintf(file_dati_campo,"-");
                }
            }
        }
        fclose(file_dati_campo);
    }
}


void riprendi_partita() {//LEGGO I 4 .TXT CREATI SALVANDO IL GIOCO PER RIPRENDERE UNA PARTITA IN SOSPESO
    //MI RIPRENDO I DATI GENERALI
    FILE* file_dati_generali = fopen("dati_generali.txt","r");//APRO IL FILE IN LETTURA
    if(file_dati_generali != NULL) {//CONTROLLO CHE SI SIA APERTO CORRETTAMENTE IL FILE
        printf("\n\n\n\n\n                            ******************Caricamento dati******************");
        int contatore = 0;
        char linea_letta[256];
        while(!feof(file_dati_generali)){//LEGGO FINO ALLA FINE DEL FILE
            fgets(linea_letta,256,file_dati_generali);
            //riprendo il numero di turni
            if(contatore == 0) {
                char sub_stringa_dati[4];
                for(int i = 0; i < 3; i++) {
                    sub_stringa_dati[3 -i] = linea_letta[strlen(linea_letta) - 2 -i];
                }
                for(int i =0; i < strlen(sub_stringa_dati); i++) {
                    if(sub_stringa_dati[i] < 48 || sub_stringa_dati[i] > 57) {//CONTROLLO IL CHAR SIA UN NUMERO
                        sub_stringa_dati[i] = '0';
                    }
                }
                contatore_turni = atoi(sub_stringa_dati);
            }
            //riprendo di chi e' il turno
            else if(contatore == 1) {
                if(linea_letta[strlen(linea_letta) -2] <= 57 && linea_letta[strlen(linea_letta) -2] >= 48) { //-2 perche' c'e' '\n' e '/0'
                    if(linea_letta[strlen(linea_letta) -2 ] == '1') {
                        turno = 1;
                    }
                    else if (linea_letta[strlen(linea_letta) - 2 ] == '2') {
                        turno = 2;
                    }
                }
            }
            //riprendo numero carte mago 1
            else if(contatore == 2) {
                char sub_stringa_dati[4];
                for(int i = 0; i < 3; i++) {
                    sub_stringa_dati[3 -i] = linea_letta[strlen(linea_letta) - 2 -i];
                }
                for(int i =0; i < strlen(sub_stringa_dati); i++) {
                    if(sub_stringa_dati[i] < 48 || sub_stringa_dati[i] > 57) {
                        sub_stringa_dati[i] = '0';
                    }
                }
                numero_carte1 = atoi(sub_stringa_dati);
            }
            else if(contatore == 3) {
                char sub_stringa_dati[4];
                for(int i = 0; i < 3; i++) {
                    sub_stringa_dati[3 -i] = linea_letta[strlen(linea_letta) - 1 -i];//stavolta -1 e basta perche' non c'e' il \n
                }
                for(int i =0; i < strlen(sub_stringa_dati); i++) {
                    if(sub_stringa_dati[i] < 48 || sub_stringa_dati[i] > 57) {
                        sub_stringa_dati[i] = '0';
                    }
                }
                numero_carte2 = atoi(sub_stringa_dati);
            }
            contatore++;
        }
        fclose(file_dati_generali);
        printf("\n\n\t\t\t\t\tDATI GENERALI CARICATI.... turno numero: %d  tocca a: %d numero carte mago 1: %d numero carte mago 2  %d\n\n",contatore_turni,turno,numero_carte1,numero_carte2);
    }
    else {
        printf("Mi dispiace ma qui non c'e' alcuna partita in sospeso....\n\n");
    }

    //MI RIPRENDO IL FILE MAGHI
    FILE* file_dati_maghi = fopen("dati_maghi.txt","r");
    if(file_dati_maghi != NULL) {
        printf("                            ******************Caricamento dati******************");
        int contatore = 0;
        char linea_letta[256];
        while(!feof(file_dati_maghi)){
            fgets(linea_letta,256,file_dati_maghi);
            if(contatore == 1) {
                char sub_stringa_dati[4];
                for(int i = 0; i < 3; i++) {
                    sub_stringa_dati[3 -i] = linea_letta[strlen(linea_letta) - 2 -i];
                }
                for(int i =0; i < strlen(sub_stringa_dati); i++) {
                    if(sub_stringa_dati[i] < 48 || sub_stringa_dati[i] > 57) {
                        sub_stringa_dati[i] = '0';
                    }
                }
                mago1.punti_vita = atoi(sub_stringa_dati);
            }
            else if(contatore == 2) {
                mago1.classe_mago = atoi(&linea_letta[strlen(linea_letta) - 2]);
            }
            else if(contatore == 3) {
                char sub_stringa_dati[249];
                for(int i = 0; i < strlen(linea_letta); i++) {
                    sub_stringa_dati[i] = linea_letta[i + 6];
                }
                strcpy(mago1.nome,sub_stringa_dati);
            }
            else if(contatore == 4) {
                mago1.bool_pesca = atoi(&linea_letta[strlen(linea_letta) -2]);
            }
            else if(contatore == 5) {
                mago1.bool_attacca = atoi(&linea_letta[strlen(linea_letta) -2]);
            }
            else if(contatore == 6) {
                mago1.bool_giocacarta = atoi(&linea_letta[strlen(linea_letta) -2]);
            }
            //PER IL MAGO 2
            else if(contatore == 10) {
                char sub_stringa_dati[4];
                for(int i = 0; i < 3; i++) {
                    sub_stringa_dati[3 -i] = linea_letta[strlen(linea_letta) - 2 -i];
                }
                for(int i =0; i < 4; i++) {
                    if(sub_stringa_dati[i] < 48 || sub_stringa_dati[i] > 57) {
                        sub_stringa_dati[i] = '0';
                    }
                }
                mago2.punti_vita = atoi(sub_stringa_dati);
            }
            else if(contatore == 11) {
                mago2.classe_mago = atoi(&linea_letta[strlen(linea_letta) - 2]);
            }
            else if(contatore == 12) {
                char sub_stringa_dati[249];
                for(int i = 0; i < strlen(linea_letta); i++) {
                    sub_stringa_dati[i] = linea_letta[i + 6];
                }
                strcpy(mago2.nome,sub_stringa_dati);
            }
            else if(contatore == 13) {
                mago2.bool_pesca = atoi(&linea_letta[strlen(linea_letta) -2]);
            }
            else if(contatore == 14) {
                mago2.bool_attacca = atoi(&linea_letta[strlen(linea_letta) -2]);
            }
            else if(contatore == 15) {
                mago2.bool_giocacarta = atoi(&linea_letta[strlen(linea_letta) -2]);
            }
            contatore++;
        }
        printf("\n\n\nDATI MAGHI CARICATI....\n\n MAGO1 PV: %d MAGO1 CLASSE: %d MAGO1 NOME: %s MAGO1 b_pesca: %d MAGO1 b_attacco: %d MAGO1 b_giocacarta: %d\n\n\n MAGO2 PV: %d MAGO2 CLASSE: %d MAGO2 NOME: %s MAGO2 b_pesca: %d MAGO2 b_attacco: %d MAGO2 b_giocacarta: %d\n\n",mago1.punti_vita,mago1.classe_mago,mago1.nome,mago1.bool_pesca,mago1.bool_attacca,mago1.bool_giocacarta,mago2.punti_vita,mago2.classe_mago,mago2.nome,mago2.bool_pesca,mago2.bool_attacca,mago2.bool_giocacarta);
        fclose(file_dati_maghi);
    }
    else {
        printf("Mi dispiace ma qui non c'e' alcuna partita in sospeso....\n\n");
    }

    imposta_gioco_ripresa();
    //MI PRENDO I DATI DELLA MANO

    FILE* file_dati_mano = fopen("dati_mano.txt","r");
    if(file_dati_mano != NULL) {
        int contatore = 0;
        //MALLOCO 6 CARTE PER LA MANO

        char linea_letta[256];
        while(!feof(file_dati_mano)){
            fgets(linea_letta,256,file_dati_mano);
            if(linea_letta[0] == '1') {
                char pv[4];
                char* p_inizio = NULL;
                char* p_fine;
                //UNA PAZZIA CON PUNTATORI PER LEGGERE UNA CERTA STRINGA COMPREA TRA 2 SPAZI COSI' I PUNTI VITA POSSONO ESSERE ANCHE DI PIU' DI UNA CIFRA
                //assegno i punti vita
                if(linea_letta[2] != '-') { //controllo che non sia una posizione vuota
                    for (int i = 0; i < strlen(linea_letta); i++) {
                        if(linea_letta[i] == ' ') {
                            if(p_inizio == NULL) {
                                p_inizio = &linea_letta[i];//ASSEGNO IL PRIMO P AL PRIMO SPAZIO
                            }
                            else {
                                p_fine = &linea_letta[i];//ASSEGNO IL SECONDO P AL SECONDO SPAZIO
                            }
                        }
                    }
                    int i = 0;
                    while((p_inizio + 1 + i) != p_fine) {//ITERO FINCHE IL PRIMO PUNTATORE != SECONDO
                        pv[i] = *(p_inizio + 1 + i);
                        i++;
                    }
                    mago1.mano[contatore]->punti_vita = atoi(pv);
                    //assegno il tipo della carta
                    mago1.mano[contatore]->tipo_carta = atoi(&linea_letta[strlen(linea_letta) - 2]);
                }
                else {
                    mago1.mano[contatore] = NULL;
                }
            }
            else if(linea_letta[0] == '2') {
                char pv[4];
                char* p_inizio = NULL;
                char* p_fine;
                //assegno i punti vita
                if(linea_letta[2] != '-') { //controllo che non sia una posizione vuota
                    for (int i = 0; i < strlen(linea_letta); i++) {
                        if(linea_letta[i] == ' ') {
                            if(p_inizio == NULL) {
                                p_inizio = &linea_letta[i];
                            }
                            else {
                                p_fine = &linea_letta[i];
                                break;
                            }
                        }
                    }
                    int i = 0;
                    while((p_inizio + 1 + i) != p_fine) {
                        pv[i] = *(p_inizio + 1 + i);
                        i++;
                    }
                    mago2.mano[contatore - 6]->punti_vita = atoi(pv);
                    //assegno il tipo della carta
                    mago2.mano[contatore - 6]->tipo_carta = atoi(&linea_letta[strlen(linea_letta) - 2]);
                }
                else {
                    mago2.mano[contatore - 6] = NULL;
                }
            }
            else {
                printf("Errore valore impossibile nella lettura del file........\n\n");
            }
            contatore++;
        }
        printf("\n\n\nDATI DELLE MANI CARICATI CORRETTAMENTE!!!.....\n\n\n");
        fclose(file_dati_mano);
    }
    else {
        printf("Mi dispiace ma qui non c'e' alcuna partita in sospeso....\n\n");
    }

    //MI PRENDO I DATI DEL CAMPO
    FILE* file_dati_campo = fopen("dati_campo.txt","r");
    if(file_dati_campo != NULL) {
        printf("                            ******************Caricamento dati******************\n\n\n");
        int contatore = 0;
        char linea_letta[256];
        while(!feof(file_dati_campo)){
            fgets(linea_letta,256,file_dati_campo);
            if(linea_letta[0] == '1') {
                char pv[4];
                char* p_inizio = NULL;
                char* p_fine;
                //assegno i punti vita
                if(linea_letta[2] != '-') { //controllo che non sia una posizione vuota
                    mago1.campo[contatore] = (struct Carta*)malloc(sizeof(struct Carta));//COSTRETTO A MALLOCARE QUI POICHE' IN IMPOSTA_GIOCO_RIPRESA() MALLOCO SOLO MAZZO E MANO E PERCIO' EVENTUALI CARTE DEL MAZZO VANNO ALLOCATE
                    for (int i = 0; i < strlen(linea_letta); i++) {
                        if(linea_letta[i] == ' ') {
                            if(p_inizio == NULL) {
                                p_inizio = &linea_letta[i];
                            }
                            else {
                                p_fine = &linea_letta[i];
                            }
                        }
                    }
                    int i = 0;
                    while((p_inizio + 1 + i) != p_fine) {
                        pv[i] = *(p_inizio + 1 + i);
                        i++;
                    }
                    mago1.campo[contatore]->punti_vita = atoi(pv);
                    //assegno il tipo della carta
                    mago1.campo[contatore]->tipo_carta = atoi(&linea_letta[strlen(linea_letta) - 2]);
                }
                else {
                    mago1.campo[contatore] = NULL;
                }
            }
            //aggiusto il mago 2
            else if(linea_letta[0] == '2') {
                char pv[4];
                char* p_inizio = NULL;
                char* p_fine;
                //assegno i punti vita
                if(linea_letta[2] != '-') { //controllo che non sia una posizione vuota
                    mago2.campo[contatore - 4] = (struct Carta*)malloc(sizeof(struct Carta));
                    for (int i = 0; i < strlen(linea_letta); i++) {
                        if(linea_letta[i] == ' ') {
                            if(p_inizio == NULL) {
                                p_inizio = &linea_letta[i];
                            }
                            else {
                                p_fine = &linea_letta[i];
                            }
                        }
                    }
                    int i = 0;
                    while((p_inizio + 1 + i) != p_fine) {
                        pv[i] = *(p_inizio + 1 + i);
                        i++;
                    }
                    mago2.campo[contatore - 4]->punti_vita = atoi(pv);
                    //assegno il tipo della carta
                    mago2.campo[contatore - 4]->tipo_carta = atoi(&linea_letta[strlen(linea_letta) - 2]);
                }
                else {
                    mago2.campo[contatore - 4] = NULL;
                }
            }
            else {
                printf("Errore valore impossibile nella lettura del file........\n\n");
            }
            contatore++;
        }
        printf("\n\n\nDATI DEI CAMPI CARICATI CORRETTAMENTE!!!.....\n\n\n");
        printf("\n\n\n\t\t\t\t\t\t*******_______PREMERE COMBATTI PER RIPRENDERE LA PARTITA AVVIATA_______*******\n\n\n\n\n\n\n\n");
        fclose(file_dati_campo);
    }
    else {
        printf("Mi dispiace ma qui non c'e' alcuna partita in sospeso....\n\n");
    }
}


void imposta_gioco_ripresa () {//e' un imposta gioco in miniatura diciamo per ricreare il mazzo e allocare le carte della mano
    //CREAZIONE DEL MAZZO TRAMITE LISTA DINAMICA
    mago1.mazzo = (struct Carta*)malloc(sizeof(struct Carta));//assegno al puntatore mazzo un indirizzo mallocato
    mago1.mazzo->p_prox_carta = NULL;
    struct Carta* p_temp1;
    struct Carta* p_nuovo1;
    p_temp1 = mago1.mazzo;

    for (int i = 0; i < numero_carte1 -1;i++){//numero carte -1 perche' ho gia' allocato il primo(mago1.mazzo))
        p_nuovo1 = (struct Carta*)malloc(sizeof(struct Carta));//alloco ogni volta un nuovo
        p_nuovo1->p_prox_carta = NULL;

        p_temp1->p_prox_carta = p_nuovo1;//il puntatore temp puntera' all' elemento appena allocato cosi che quando sara' uguale al puntatore di quell' elemento, colleghera' il nodo vecchio al nodo nuovo
        p_temp1 = p_nuovo1;
    }
    imposta_mazzo(&mago1,mago1.mazzo,numero_carte1);//imposto il mazzo 1
    printf("\nMazzo 1 impostato correttamente....\n");


    mago2.mazzo = (struct Carta*)malloc(numero_carte*sizeof(struct Carta));
    mago2.mazzo->p_prox_carta = NULL;
    struct Carta* p_temp2;
    struct Carta* p_nuovo2;
    p_temp2 = mago2.mazzo;

    for (int i = 0; i < numero_carte2 -1;i++){//numero carte -1 perche' ho gia' allocato il primo(mago1.mazzo))
        p_nuovo2 = (struct Carta*)malloc(sizeof(struct Carta));

        p_nuovo2->p_prox_carta = NULL;

        p_temp2->p_prox_carta = p_nuovo2;//il puntatore temp puntera' all' elemento appena allocato cosi che quando sara' uguale al puntatore di quell' elemento, colleghera' il nodo vecchio al nodo nuovo
        p_temp2 = p_nuovo2;
    }
    imposta_mazzo(&mago2,mago2.mazzo,numero_carte2);
    printf("\nMazzo 2 impostato correttamente....\n");

    //creo 6 carte per la mano di ciascun mago

    for(size_t i = 0; i < 6; i++) {//qui si sta creando la MANO
        mago2.mano[i] = (struct Carta*)malloc(sizeof(struct Carta));
        mago1.mano[i] = (struct Carta*)malloc(sizeof(struct Carta));//alloco le carte senno' sarebbe solo un array di puntatori
    }
    printf("\nmano creata regolarmente.......\n\n");
}

void pulisci_tutto() {//funzione per deallocare ed evitare eventuali memory leaks
    for(int i = 0; i < 6; i++) {//dealloco qualsiasi cosa sia allocata nella mano o nel campo
        if(i < 4) {//per evitare di fare un for diverso semlicemente mento un if
            if(mago1.campo[1] != NULL) {
                free(mago1.campo[i]);
                mago1.campo[i] = NULL;//per evitare dangling pointers
            }
            if(mago2.campo[i] != NULL) {
                free(mago2.campo[i]);
                mago2.campo[i] = NULL;//per evitare dangling pointers

            }
        }
        if(mago1.mano[i] != NULL) {
            free(mago1.mano[i]);
            mago1.campo[i] = NULL;//per evitare dangling pointers
        }
        if(mago2.mano[i] != NULL) {
            free(mago2.mano[i]);
            mago2.campo[i] = NULL;//per evitare dangling pointers
        }
    }

    while(mago1.mazzo != NULL) {//dealloco tutto il mazzo
        struct Carta* p_dealloca = mago1.mazzo;
        mago1.mazzo = mago1.mazzo->p_prox_carta;
        free(p_dealloca);
    }
    while(mago2.mazzo != NULL) {
        struct Carta* p_dealloca = mago2.mazzo;
        mago2.mazzo = mago2.mazzo->p_prox_carta;
        free(p_dealloca);
    }
    printf("\n\n\n\n\n\n\n\n||||||--------TUTTO DEALLOCATO CORRETTAMENTE--------||||||\n\n\n\n\n\n\n\n\n\n\n\n");
}
