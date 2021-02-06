
Linguaggi di Programmazione 2019-2020
Progetto Prolog gennaio 2020 E1P

Daniele Scalco 844762, Daniel Scalena 844608

Il progetto nfa.pl si occupa della creazione di un automa non deterministico
che permette il riconoscimento di linguaggi descritti attraverso espressioni reoglari

Le funzioni principali sono:

1) is_regexp/1
   is_regexp si occupa di controllare se l'espressione regolare data in input risulta
   essere sintatticamente corretta restituendo true, in caso contrario false.
   Nello specifico is_regexp/1 fa uso di list_of_regexp/1 che si occupa di chiamare
   ricorsivamente ogni sotto-espressione regolare data in input

2) nfa_regexp_comp/2
   nfa-regexp_comp riceve come primo argomento l'Id dell'automa da creare e come
   secondo argomento l'espressione regolare da associare all'automa stesso. I primi controlli
   sono effettuati su FA_Id che non deve essere un termine già utilizzato per altri automi
   precedentemente creati. Dopo aver controllato che RE sia un'espressione regolare valida
   grazie all'ausilio di is_regexp/1, nfa_regexp_comp/2 chiama la sua funzione omonima
   nfa_regexp_comp/4 passando 4 argomenti: i primi due sono sempre FA_Id ed RE, i restanti
   due sono lo stato iniziale e finale entro il quale l'automa deve essere creato.

3) nfa_test/2
   nfa_test si occupa di verificare che la lista passata in input come secondo argomento
   sia consumata dall'automa passato come primo argomento

4) nfa_list/1 and nfa_clear/1
   nfa_list si occupa di stampare l'automa composto dai delta registrati nella base di dati prolog
   nfa_clear si occupa di pulire la base di dati prolog da qualsiasi automa creato precedentemente
