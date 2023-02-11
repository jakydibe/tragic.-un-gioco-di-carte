# Tragic: Un gioco di carte
Template progetto finale Programmazione Procedurale con Laboratorio a.a. 2021/2022.

Aggiungere a questo README eventuali estensioni al progetto assegnato, e scelte progettuali da comunicare.

Fondamentalmente il gioco rispetta abbastanza fedelmente la trama originale del progetto, tuttavia la gestione dei turni e' regolata da tre campi aggiunti
alla struct Mago cosi' da fare in modo che giustamente un mago non ripeta piu' azioni equivalenti nello  stesso turno di gioco.

La piu' grande aggiunta al progetto consiste nella possibilita' di salvare una partita e riprendere quando si vuole grazie alla scrittura dei dati di gioco
su ben 4 file di testo (per semplificare il tutto e rendere piu' ordinati i file) con la funzione salva_gioco()  alla funzione riprendi_gioco() che permette di leggere tutti i file di testo e infine grazie a imposta_gioco_ripresa() che permette di ricreare tutte le strutture dati (con i dati della precedente partita) necessarie per il gioco.

In piu' ho aggiunto una funzione che stampa a terminale le regole basilari del gioco e una funzione chiamata pulisci_tutto() che viene invocata ogni volta che si termina il gioco o ogni volta che si vuole re-impostare il gioco ed essa serve a deallocare tutto cio' che e' stato precedentemente allocato in memoria dinamica cosi' da evitare qualsivoglia memory leak o altri errori


Nome:JACOPO

Cognome:DI BENEDETTO

Matricola:344276
