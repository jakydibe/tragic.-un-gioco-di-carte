#include "gamelib.h"
#include "stdio.h"
#include "stdlib.h"
#include "time.h"


int main() {

    int controlla_gioco_impostato = 0;//per evitare di cliccare combatti() prima di aver impostato il gioco
    time_t t;
    srand((unsigned) time(&t));
    int scelta = 0;

    int contatore_imposta_gioco = 0;

    printa_benvenuto();
    do{
        printf("FAI LA TUA SCELTA, PREMI : - 1 per impostare il gioco\n");
        printf("\n                           - 2 per combattere(prima devi impostare il gioco)\n");
        printf("\n                           - 3 per visualizzare il regolamento\n");
        printf("\n                           - 4 per riprendere una partita interrotta\n");
        printf("\n                           - 5 per terminare il gioco\n\n\n");

        scanf("%d",&scelta);
        scanf("%*[^\n]");
        scanf("%*c");
        switch(scelta) {
            case 1:
            if(contatore_imposta_gioco == 0) {
                imposta_gioco();
                controlla_gioco_impostato = 1;
                break;
            }
            else {
                pulisci_tutto();
                imposta_gioco();
                controlla_gioco_impostato = 1;
                break;
            }

            case 2:
                if(controlla_gioco_impostato == 0) {
                    printf("Per piacere prima di combattere imposta il gioco...\n\n");
                }
                else {
                    combatti();
                }
                break;
            case 3:
                printa_regolamento();
                break;
            case 4:
                riprendi_partita();
                controlla_gioco_impostato = 1;
                break;
            case 5:
                termina_gioco();
                break;
            default:
                printf("Per piacere digita fai una scelta possibile, ovvero digita un numero tra 1 e 3\n");
        }
        contatore_imposta_gioco++; //incremento un contatore cosi' che se si riprova a riimpostare il gioco almeno dealloco tutto cio' che ho allocato precedentemente
    }while(1);
    return 0;
}
