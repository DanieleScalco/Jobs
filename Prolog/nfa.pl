%%%% -*- Mode: Prolog -*-

%%%% nfa.pl
%%%% Daniele Scalco 844762, Daniel Scalena 844608



%%% is_regexp/1
%%% is_regexp(RE) vero se RE è un'espressione regolare

is_regexp(epsilon).
is_regexp(RE) :-
    atomic(RE),
    !.
is_regexp(RE) :-
    RE =.. [seq | Ls],
    !,
    list_of_regexp(Ls).
is_regexp(RE) :-
    RE =.. [or | Ls],
    !,
    list_of_regexp(Ls).
is_regexp(RE) :-
    RE =.. [star | Ls],
    !,
    length(Ls, 1),
    list_of_regexp(Ls).
is_regexp(RE) :-
    RE =.. [plus | Ls],
    !,
    length(Ls, 1),
    list_of_regexp(Ls).
is_regexp(RE) :-
    !,
    compound(RE),
    RE =.. X,
    length(X, 2).



%%% list_of_regexp/1
%%% list_of_regexp(Xs) true se Xs è una lista di espresssioni
%%% regolari

list_of_regexp([]).
list_of_regexp([X | Xs]) :-
    is_regexp(X),
    list_of_regexp(Xs).



%%% nfa_regexp_comp/3
%%% nfa_regexp_comp(FA_Id, RE) vero quando RE è un'espressione regolare
%%% compilabile in un automa e FA_Id è un termine Prolog che identifica
%%% l'automa

nfa_regexp_comp(FA_Id, _) :-
    nonvar(FA_Id),
    current_predicate(initial/2),
    initial(FA_Id, _),
    !,
    write("Automa gia' esistente").
nfa_regexp_comp(FA_Id, RE) :-
    nonvar(FA_Id),
    is_regexp(RE),
    gensym(q, Init),
    assert(initial(FA_Id, Init)),
    nfa_regexp_comp(FA_Id, RE, Init, Final),
    assert(final(FA_Id, Final)).




%%% nfa_regexp_comp/4
%%% nfa_regexp_comp(FA_Id, RE, Init, Final) predicato di supporto a
%%% regexp, fa la stessa cosa ma Init è lo stato iniziale dell'automa e
%%% Final lo stato finale

nfa_regexp_comp(FA_Id, RE, Init, Final) :-
    atomic(RE),
    var(Init),
    !,
    gensym(q, Init),
    gensym(q, Final),
    assert(nfa_delta(FA_Id, Init, RE, Final)).
nfa_regexp_comp(FA_Id, RE, Init, Final) :-
    atomic(RE),
    nonvar(Init),
    !,
    gensym(q, Final),
    assert(nfa_delta(FA_Id, Init, RE, Final)).
nfa_regexp_comp(FA_Id, RE, Init, Final) :-
    RE =.. [seq, X | Xs],
    !,
    ricorsivo_seq(FA_Id, [X | Xs], Init, Final).
nfa_regexp_comp(FA_Id, RE, Init, Final) :-
    RE =.. [or, X | Xs],
    !,
    gensym(q, Final),
    ricorsivo_or(FA_Id, [X | Xs], Init, Final).
nfa_regexp_comp(FA_Id, RE, Init, Final) :-
    RE =.. [star, X],
    atomic(X),
    !,
    gensym(q, Final),
    assert(nfa_delta(FA_Id, Init, epsilon, Final)),
    nfa_regexp_comp(FA_Id, X, Init1, Final1),
    assert(nfa_delta(FA_Id, Init, epsilon, Init1)),
    assert(nfa_delta(FA_Id, Final1, epsilon, Init1)),
    assert(nfa_delta(FA_Id, Final1, epsilon, Final)).
nfa_regexp_comp(FA_Id, RE, Init, Final) :-
    RE =.. [star, X],
    !,
    gensym(q, Final),
    assert(nfa_delta(FA_Id, Init, epsilon, Final)),
    nfa_regexp_comp(FA_Id, X, Init, Final1),
    assert(nfa_delta(FA_Id, Final1, epsilon, Init)),
    assert(nfa_delta(FA_Id, Final1, epsilon, Final)).
nfa_regexp_comp(FA_Id, RE, Init, Final) :-
    RE =.. [plus, X],
    atomic(X),
    !,
    gensym(q, Final),
    nfa_regexp_comp(FA_Id, X, Init1, Final1),
    assert(nfa_delta(FA_Id, Init, epsilon, Init1)),
    assert(nfa_delta(FA_Id, Final1, epsilon, Init1)),
    assert(nfa_delta(FA_Id, Final1, epsilon, Final)).
nfa_regexp_comp(FA_Id, RE, Init, Final) :-
    RE =.. [plus, X],
    !,
    gensym(q, Final),
    nfa_regexp_comp(FA_Id, X, Init, Final1),
    assert(nfa_delta(FA_Id, Final1, epsilon, Init)),
    assert(nfa_delta(FA_Id, Final1, epsilon, Final)).
nfa_regexp_comp(FA_Id, RE, Init, Final) :-
    compound(RE),
    RE =.. X,
    length(X, 2),
    !,
    gensym(q, Final),
    assert(nfa_delta(FA_Id, Init, RE, Final)).



%%% ricorsivo_seq/4
%%% ricorsivo_seq(FA_Id, Xs, Init, Final) richiama ricorsivamente
%%% nfa_regexp_comp su tutti gli elementi della lista Xs creando
%%% applicando l'algoritmo di Thompson al seq

ricorsivo_seq(_, [], Final, Final) :-
    !.
ricorsivo_seq(FA_Id, [X | Xs], Init, Final) :-
    atomic(X),
    !,
    nfa_regexp_comp(FA_Id, X, Init1, Final1),
    assert(nfa_delta(FA_Id, Init, epsilon, Init1)),
    ricorsivo_seq(FA_Id, Xs, Final1, Final).
ricorsivo_seq(FA_Id, [X | Xs], Init, Final) :-
    !,
    nfa_regexp_comp(FA_Id, X, Init, Final1),
    ricorsivo_seq(FA_Id, Xs, Final1, Final).


%%% ricorsivo_or/4
%%% ricorsivo_or(FA_Id, Xs, Init, Final) richiama ricorsivamente
%%% nfa_regexp_comp su tutti gli elementi della lista Xs applicando
%%% l'algoritmo di Thompson all'or

ricorsivo_or(_, [], _, _) :-
    !.
ricorsivo_or(FA_Id, [X | Xs], Init, Final) :-
    atomic(X),
    !,
    nfa_regexp_comp(FA_Id, X, Init1, Final1),
    assert(nfa_delta(FA_Id, Init, epsilon, Init1)),
    assert(nfa_delta(FA_Id, Final1, epsilon, Final)),
    ricorsivo_or(FA_Id, Xs, Init, Final).
ricorsivo_or(FA_Id, [X | Xs], Init, Final) :-
    !,
    nfa_regexp_comp(FA_Id, X, Init, Final1),
    assert(nfa_delta(FA_Id, Final1, epsilon, Final)),
    ricorsivo_or(FA_Id, Xs, Init, Final).


%%% nfa_test/2
%%% nfa_test(FA_Id, Input) testa se la stringa rappresentata dalla lista
%%% Input sia accettata dall'automa FA_Id

nfa_test(FA_Id, I) :-
    initial(FA_Id, S),
    nfa_test(FA_Id, I, S).
nfa_test(FA_Id, [], S) :-
    final(FA_Id, S),
    !.
nfa_test(FA_Id, [I | Is], S) :-
    nfa_delta(FA_Id, S, I, S1),
    nfa_test(FA_Id, Is, S1).
nfa_test(FA_Id, I, S) :-
    nfa_delta(FA_Id, S, epsilon, S1),
    nfa_test(FA_Id, I, S1).


%%% nfa_list/0
%%% nfa_list() mostra tutti gli automi presenti nella base di dati

nfa_list() :-
    nfa_list(_),
    fail.



%%% nfa_list(FA_Id)/1
%%% nfa_list(FA_Id) mostra l'automa FA_Id

nfa_list(FA_Id) :-
    listing(initial(FA_Id, _)),
    listing(final(FA_Id, _)),
    listing(nfa_delta(FA_Id, _, _, _)).



%%% nfa_clear/0
%%% nfa_clear() elimina dalla base di dati tutti gli automi

nfa_clear():-
    nfa_clear(_),
    fail.



%%% nfa_clear/1
%%% nfa_clear(FA_Id) elimina dalla base di dati l'automa FA_Id

nfa_clear(FA_Id) :-
    retract(initial(FA_Id, _)),
    retract(final(FA_Id, _)),
    retract(nfa_delta(FA_Id, _, _, _)),
    fail.



%%%% end of file -- nfa.pl
