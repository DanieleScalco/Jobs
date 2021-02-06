;;;; -*- Mode: Lisp -*-

;;;; nfa.lisp
;;;; Daniele Scalco 844762, Daniel Scalena 844608


;;;; is-regexp chiama is-regexp-42 che a sua volta controlla che RE sia un
;;;; espressione regolare
(defun is-regexp (RE)
  (check-all-true (is-regexp-42 RE)))


;;;; is-regexp-42 controlla che l'RE sia valida e rispetti tutti i requisiti
;;;; indicati scendendo ricorsivamente nei vari casi
(defun is-regexp-42 (RE)
  (cond ((atom RE) T)
        ((eql 'seq (car RE)) (mapcar 'is-regexp-42 (rest RE)))
        ((eql 'or (car RE)) (mapcar 'is-regexp-42 (rest RE)))
        ((and (eql 'star (car RE))
              (<= (list-length (rest RE)) 1))
         (mapcar 'is-regexp-42 (rest RE)))
        ((and (eql 'plus (car RE))
              (<= (list-length (rest RE)) 1))
         (mapcar 'is-regexp-42 (rest RE)))
        ((and (listp RE)
              (not (equal (car RE) 'star))
              (not (equal (car RE) 'plus)))
         (mapcar 'is-regexp-42 RE))
        (T 'false)))


;;;; check-all-true controlla che la lista restituita da is-regexp-42 contenga
;;;; tutte sottoespressioni regolari valide
(defun check-all-true (result)
  (cond ((null result) t)
        ((and (atom result)
              (equal result 'false)) nil)
        ((and (atom result)
              (not (equal result 'false))) t)
        ((and (eql (list-length result) 1)
              (atom (car result)))
         (if (equal (car result) 'false) nil (car result)))
        (t (and (check-all-true (car result))
                (check-all-true (rest result))))))

  
;;;; nfa-regexp-comp chiama is-regexp per controllare che RE sia un
;;;; espressione regolare valida e procede a richiamare le varie apply per la
;;;; creazione dell'automa non deterministico con epsilon-mosse
;;;; La rappresentazione dell'automa è affidata a una struttura dati di tipo
;;;; list che contiene come primi due elementi lo stato iniziale e finale dell
;;;; automa e successivamente i vari delta creati ricorsivamente
(defun nfa-regexp-comp (RE)
  (if (is-regexp RE)
      (let ((automa (list (gensym) (gensym))))
        (cond ((atom  RE) (append automa 
                                  (apply-atom  RE
                                               (first automa)
                                               (second automa))))
              ((eql 'seq (car RE)) (append automa 
                                           (apply-seq (rest RE)
                                                      (first automa)
                                                      (second automa)
                                                      nil)))
              ((eql 'or (car RE)) (append automa
                                          (apply-or (rest RE)
                                                    (first automa)
                                                    (second automa))))
              ((eql 'star (car RE)) (append automa
                                            (apply-star (rest RE)
                                                        (first automa)
                                                        (second automa))))
              ((eql 'plus (car RE)) (append automa
                                            (apply-plus (rest RE)
                                                        (first automa)
                                                        (second automa))))
              ((listp RE) (append automa
                                  (apply-atom RE ;;;
                                              (first automa)
                                              (second automa)))) 
              (T nil)))
    nil))


;;;; apply-atom crea i delta nel caso RE sia un atomo
(defun apply-atom (RE init final)
  (let ((init-atom (gensym))
        (final-atom (gensym)))
    (append (list (list init 'epsilon init-atom))
            (list (list init-atom RE final-atom))
            (list (list final-atom 'epsilon final)))))


;;;; apply-seq crea i delta nel caso RE sia una sequenza inoltre controlla
;;;; eventuali sottoespressioni regolari e richiama gli appropriati apply
(defun apply-seq (RE init final init-conn)
  (let ((nuovo-stato1 (gensym))
        (nuovo-stato2 (gensym))
        (nuovo-stato3 (gensym)))
    (cond ((null RE)
           (list (list init 'epsilon final)))
          ((listp (car RE))
           (cond ((and (equal (car (car RE)) 'seq)
                       (null init-conn))
                  (append (list (list init 'epsilon nuovo-stato1))
                          (apply-seq (rest (car RE))
                                     nuovo-stato1
                                     nuovo-stato2
                                     nil)
                          (list (list nuovo-stato2 'epsilon nuovo-stato3))
                          (apply-seq (rest RE)
                                     nuovo-stato3
                                     final
                                     t)))
                 ((equal (car (car RE)) 'seq)   
                  (append (apply-seq (rest (car RE))
                                     init
                                     nuovo-stato2
                                     init-conn)
                          (list (list nuovo-stato2 'epsilon nuovo-stato3))
                          (apply-seq (rest RE)
                                     nuovo-stato3
                                     final
                                     init-conn)))
                 ((and (equal (car (car RE)) 'or)
                       (null init-conn))
                  (append (list (list init 'epsilon nuovo-stato1))
                          (apply-or (rest (car RE))
                                    nuovo-stato1
                                    nuovo-stato2)
                          (list (list nuovo-stato2 'epsilon nuovo-stato3))
                          (apply-seq (rest RE)
                                     nuovo-stato3
                                     final
                                     t)))
                 ((equal (car (car RE)) 'or)
                  (append (apply-or (rest (car RE))
                                    init
                                    nuovo-stato2)
                          (list (list nuovo-stato2 'epsilon nuovo-stato3))
                          (apply-seq (rest RE)
                                     nuovo-stato3
                                     final
                                     init-conn)))
                 ((equal (car (car RE)) 'star)
                  (append (apply-star (rest (car RE))
                                      init
                                      nuovo-stato2)
                          (list (list nuovo-stato2 'epsilon nuovo-stato3))
                          (apply-seq (rest RE)
                                     nuovo-stato3
                                     final
                                     init-conn)))
                 ((equal (car (car RE)) 'plus)
                  (append (apply-plus (rest (car RE))
                                      init
                                      nuovo-stato2)
                          (list (list nuovo-stato2 'epsilon nuovo-stato3))
                          (apply-seq (rest RE)
                                     nuovo-stato3
                                     final
                                     init-conn)))
                 ((not (equal RE ())) (append (apply-atom (car RE)
                                                          init
                                                          nuovo-stato1)
                                              (apply-seq (rest RE)
                                                         nuovo-stato1
                                                         final
                                                         init-conn)))))
          ((and (atom (car RE))
                (null init-conn))
           (append (list (list init 'epsilon nuovo-stato1))
                   (apply-atom (car RE)
                               nuovo-stato1
                               nuovo-stato2)
                   (apply-seq (rest RE)
                              nuovo-stato2
                              final
                              t)))
          ((atom (car RE))
           (append (apply-atom (car RE)
                               init
                               nuovo-stato1)
                   (apply-seq (rest RE)
                              nuovo-stato1
                              final
                              init-conn))))))


;;;; apply-or crea i delta nel caso RE sia un'alternativa (or) inoltre controlla
;;;; eventuali sottoespressioni regolari e richiama gli appropriati apply
(defun apply-or (RE init final)
  (let ((nuovo-stato1 (gensym))
        (nuovo-stato2 (gensym)))
    (cond ((listp (car RE))
           (cond ((equal (car (car RE)) 'seq)   
                  (append (list (list init 'epsilon nuovo-stato1))
                          (list (list nuovo-stato2 'epsilon final))
                          (apply-seq (rest (car RE))
                                     nuovo-stato1
                                     nuovo-stato2
                                     nil)
                          (apply-or (rest RE)
                                    init
                                    final)))
                 ((equal (car (car RE)) 'or)
                  (append (list (list init 'epsilon nuovo-stato1))
                          (list (list nuovo-stato2 'epsilon final))
                          (apply-or (rest (car RE))
                                    nuovo-stato1
                                    nuovo-stato2)
                          (apply-or (rest RE)
                                    init
                                    final)))
                 ((equal (car (car RE)) 'star)
                  (append (list (list init 'epsilon nuovo-stato1))
                          (list (list nuovo-stato2 'epsilon final))
                          (apply-star (rest (car RE))
                                      nuovo-stato1
                                      nuovo-stato2)
                          (apply-or (rest RE)
                                    init
                                    final)))
                 ((equal (car (car RE)) 'plus)
                  (append (list (list init 'epsilon nuovo-stato1))
                          (list (list nuovo-stato2 'epsilon final))
                          (apply-plus (rest (car RE))
                                    nuovo-stato1
                                    nuovo-stato2)
                          (apply-or (rest RE)
                                    init
                                    final)))
                 ((not (equal RE ())) (append (apply-atom (car RE)
                                                          init
                                                          final)
                                              (apply-or (rest RE)
                                                        init
                                                        final)))))
          ((atom (car RE))
           (append (apply-atom (car RE)
                               init
                               final)
                   (apply-or (rest RE)
                             init
                             final))))))


;;;; apply-star crea i delta nel caso RE sia una chiusura di Kleene inoltre controlla
;;;; eventuali sottoespressioni regolari e richiama gli appropriati apply
(defun apply-star (RE init final)
  (cond ((listp (car RE))
         (cond ((equal (car (car RE)) 'seq)   
                (append (list (list init 'epsilon final))
                        (list (list final 'epsilon init))
                        (apply-seq (rest (car RE)) init  final nil)))
               ((equal (car (car RE)) 'or)
                (append (list (list init 'epsilon final))
                        (list (list final 'epsilon init))
                        (apply-or (rest (car RE)) init final)))
               ((equal (car (car RE)) 'star)
                (append (list (list init 'epsilon final))
                        (list (list final 'epsilon init))
                        (apply-star (rest (car RE)) init final)))
               ((equal (car (car RE)) 'plus)
                (append (list (list init 'epsilon final))
                        (list (list final 'epsilon init))
                        (apply-plus (rest (car RE)) init final)))
               (t (append (list (list init 'epsilon final))
                          (list (list final 'epsilon init))
                          (apply-atom (car RE) init final)))))
        ((atom (car RE))
         (append (list (list init 'epsilon final))
                 (list (list final 'epsilon init))
                 (apply-atom (car RE) init final)))))


;;;; apply-plus crea i delta nel caso RE sia una chiusura di Kleene senza il
;;;; simbolo epsilon, inoltre controlla eventuali sottoespressioni regolari e
;;;; richiama gli appropriati apply
(defun apply-plus (RE init final)
  (cond ((listp (car RE))
         (cond ((equal (car (car RE)) 'seq)   
                (append (list (list final 'epsilon init))
                        (apply-seq (rest (car RE)) init  final nil)))
               ((equal (car (car RE)) 'or)
                (append (list (list final 'epsilon init))
                        (apply-or (rest (car RE)) init final)))
               ((equal (car (car RE)) 'star)
                (append (list (list final 'epsilon init))
                        (apply-star (rest (car RE)) init final)))
               ((equal (car (car RE)) 'plus)
                (append (list (list final 'epsilon init))
                        (apply-plus (rest (car RE)) init final)))
               (t (append (list (list final 'epsilon init))
                          (apply-atom (car RE) init final)))))
        ((atom (car RE))
         (append (list (list final 'epsilon init))
                 (apply-atom (car RE) init final)))))


;;;; nfa-test prende come argomenti l'automa generato da nfa-regexp-comp che e
;;;; vene controllato nella sua struttua e una lista input che  contiene le
;;;; sequenze di simboli da computare
(defun nfa-test (FA input)
  (if (is-automa FA)
      (check (rest (rest FA)) input (list (first FA)) (second FA))
    (error "FA non è un automa valido")))


;;;; is-automa si occupa di controllare l'automa FA in input rispetti gli
;;;; standard prima citati e utilizzati da nfa-regexp-comp
(defun is-automa (FA)
  (if (and (listp FA)
           (not (null FA))
           (atom (first FA))
           (atom (second FA))
           (check-all-delta (rest (rest FA))))
      t
    nil))


;;;; check-all-delta controlla che ogni delta dell'automa rispetti lo standard
;;;; (nome_stato1 simbolo nome_stato2)
(defun check-all-delta (FA)
  (cond ((and (listp (first FA))
              (equal (list-length (first FA)) 3)
              (is-regexp (second (first FA))))
         (check-all-delta (rest FA)))
        ((equal FA ()) t)
        (t nil)))


;;;; check calcola tutte le computazioni possibili scorrendo l'input
;;;; utilizzando le funzioni aggiorna-epsilon e aggiorna-simbolo
(defun check (FA input ultimi-stati stato-finale)
  (cond ((equal input ())
         (check-state (aggiorna-epsilon ultimi-stati
                                        FA
                                        FA
                                        1)
                      stato-finale))
        (t (check FA
                  (rest input)
                  (mapcar (lambda (x)
                            (aggiorna-simbolo x (first input) FA))
                          (riduci (aggiorna-epsilon ultimi-stati
                                                    FA
                                                    FA
                                                    1)))
                  stato-finale))))


;;;; check-state controlla che tra tutti gli stati raggiunti nelle varie
;;;; computazioni ce ne sia uno di accettazione
(defun check-state (stati stato-finale)
  (cond ((equal stati ())
         nil)
        ((equal (car stati) stato-finale) t)
        (t (check-state (rest stati) stato-finale))))


;;;; aggiorna-epsilon si occupa di scorrere tutte le epsilon-transizioni nell
;;;; automa
(defun aggiorna-epsilon (stati FA FA-attuali n-giri)
  (let ((prima-delta (first FA-attuali)))
    (cond ((not (equal FA-attuali ()))
           (cond ((and (find (first prima-delta) stati)
                       (equal (second prima-delta) 'epsilon))
                  (append (list (third prima-delta))
                          stati
                          (aggiorna-epsilon
                           (append stati
                                   (list (third prima-delta)))
                           FA
                           (rest FA-attuali)
                           n-giri)))
                 (t (aggiorna-epsilon stati
                                      FA
                                      (rest FA-attuali)
                                      n-giri))))
          ((and (equal 0 n-giri)
                (equal FA-attuali ()))
           stati)
          (t (aggiorna-epsilon stati FA FA (- n-giri 1))))))


;;;; aggiorna-simbolo si occupa di scorrere le transizioni delta che contengono
;;;; dei simboli appartenenti all'alfabeto
(defun aggiorna-simbolo (stato simbolo FA)
  (let ((prima-delta (first FA)))
    (if (not (equal FA ()))
        (cond ((and (equal (first prima-delta) stato)
                    (equal (second prima-delta) simbolo))
               (third prima-delta))
              (t (aggiorna-simbolo stato simbolo (rest FA))))
      (list 'fail)))) 


;;;; riduci elimina dalla lista eventuali doppioni e le computazioni fallite
(defun riduci (lista)
  (cond ((<= (list-length lista) 1) lista)
        ((find (first lista) (rest lista))
         (riduci (rest lista)))
        ((equal (first lista) '(fail))
         (riduci (rest lista)))
        (t (append (list (first lista))
                   (riduci (rest lista))))))



;;;; end of file -- nfa.lisp








