
Linguaggi di Programmazione 2019-2020
Progetto Lisp gennaio 2020 E1P

Daniele Scalco 844762, Daniel Scalena 844608

Il progetto nfa.lisp si occupa della creazione di un automa non deterministico
che permette il riconoscimento di linguaggi descritti attraverso espressioni reoglari

Le funzioni principali sono:

1) (is-regexp RE)
   is-regexp si occupa di controllare che l'espressione passata in input ripetti le regole date dal testo.
   Grazie alla ricorsione è capace di controllare ogni sotto-espressione regolare contenuta all'interno di RE.
   La funzione is-regexp restituisce il valore booleano T in caso RE sia un'espressione regolare accettata,
   NIL in caso contrario;

2) (nfa-regexp-comp RE)
   nfa-regexp-comp si occupa della vera e propria creazione dell'automa non deterministico. Se RE non
   è un'espressione regolare che soddisfa is-regexp, la funzione ritorna il valore NIL senza generare
   errori. Nello specifico utilizza diverse funzioni con prefisso apply che svolgono il lavoro di creazione 
   delle transizioni più nel dettaglio. Esse sono:
       - (apply-atom RE init final): crea delle transizioni da init a final in caso RE sia un atomo
       - (apply-seq RE init final): crea delle transizioni in sequenza e controlla ricorsivamente le
              sotto-espressioni regolari
       - (apply-or RE init final): crea delle transizioni alternative e controlla ricorsivamente le
              sotto-espressioni regolari
       - (apply-star RE init final): crea delle transizioni seguendo la chiusura di Kleene e controlla
              ricorsivamente le sotto-espressioni regolari
       - (apply-plus RE init final): crea delle transizioni seguendo la chiusura di Kleene senza includere
              nell'alfabeto il simbolo epsilon e controlla ricorsivamente le sotto-espressioni regolari

3) (nfa-test FA Input)
   nfa-test si occupa controllare che l'input rispetti l'espressione regolare che genere l'automa FA.
   Prima di tutto controlla che FA rispetti lo standard di automa generato da nfa-regexp-comp.
   Lo standard in questione è definito come segue:
      (list stato-iniziale stato-finale (transizione-1) (transizione-2) ... (transizione-n))
      Nello specifico le transizioni sono così strutturate: (list stato-1 simbolo stato-2)
   Se l'automa risulta non valido nfa-test restituisce una stringa di errore sullo STDERR,
   restituisce invece il valore booleano T nel caso la stringa in Input sia consumata completamente
   dall'automa FA e la computazione si trovi in uno stato di accettazione, NIL in caso contrario.
   
   Dopo aver effettuato tutti i controlli necessari nfa-test passa la computazione a check che si occupa
   di consumare l'Input e verificare tutti i passaggi computazionali.


Nota:
Se viene inserita un'espressione regolare complessa che genera quindi
un automa di grandi dimensioni la funzione nfa-test potrebbe
richiedere del tempo extra per elaborare tutto l'input (questione
comunque di pochi secondi). In ogni caso, secondo i nostri test, il
risultato risulta sempre essere corretto.
Questo problema in realtà potrebbe essere anche dovuto alla scarsa
potenza della virtual machine sul quale lispwork è stato eseguito

Grazie per l'attenzione!
