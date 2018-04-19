%:- use_rendering(svgtree, [list(false)]).

head([H|_], H).

sentence(frase(NP)) --> np(NP, max, _, _).
sentence(frase(NP, VP)) --> np(NP, max, Num, _), vp(VP, Num).

np(sujeito(N), Cap, Num, Gender) --> n(N, Cap, Num, Gender).
np(sujeito(det(Det), nome(N)), Cap, Num, Gender) --> det(Det, Cap, Num, Gender), n(N, min, Num, Gender).

vp(verbo(V), Num) --> v(V, Num).
vp(predicado(verbo(V), complemento(C)), Num) --> v(V, Num), comp(C, _, _).
vp(predicado(complemento(C), verbo(V)), Num) --> comp(C, _, _), v(V, Num).

comp(complemento(prep(P), nome(N)), Num, Gender) --> prep(P, Num, Gender), n(N, min, Num, Gender).
comp(complemento(prep(P), det(Det), nome(N)), Num, Gender) 
	--> prep_s(P), det(Det, min, Num, Gender), n(N, min, Num, Gender).


% Determinantes ------------------------------------------------------------

det(X, A, B, C, D, E) :- det(A, B, C, D, E), head(D, X).

det(min, sing, fem)  --> [a];[uma].
det(min, plur, fem)  --> [as];[umas].
det(min, sing, masc) --> [o];[um].
det(min, plur, masc) --> [os];[uns].
det(max, sing, fem)  --> ['A'];['Uma'].
det(max, plur, fem)  --> ['As'];['Umas'].
det(max, sing, masc) --> ['O'];['Um'].
det(max, plur, masc) --> ['Os'];['Uns'].

% Preposições --------------------------------------------------------------

prep_s(X, A, B) :- prep_s(A, B), head(A, X).
prep_s --> [com];[para].

prep(X, A, B, C, D) :- prep(A, B, C, D), head(C, X).

prep(sing, masc) --> [pelo];[ao];[no].
prep(sing, fem)  --> [pela];[a];[na].
prep(plur, masc) --> [pelos];[aos];[nos].
prep(plur, fem)  --> [pelas];[as];[nas].

% Verbos -------------------------------------------------------------------

v(X, A, B, C) :- v(A, B, C), head(B,X).

v(sing) --> [bateu];[corre];[correu].
v(plur) --> [bateram];[correram];[corriam].

% Nomes --------------------------------------------------------------------

n(X, A, B, C, D, E) :- n(A, B, C, D, E), head(D, X).

n(min, sing, fem) -->
    [menina];[vida];[floresta];[mae];
    [cidade];[noticia];[porta];[lagrima].

n(max, sing, fem)  -->
    ['Menina'];['Vida'];['Floresta'];['Mae'];
    ['Cidade'];['Noticia'];['Porta'];['Lagrima'].

n(min, plur, fem) -->
    [meninas];[vidas];[florestas];[maes];
    [cidades];[noticias];[portas];[lagrimas].

n(max, plur, fem)  -->
    ['Meninas'];['Vidas'];['Florestas'];['Maes'];
    ['Cidades'];['Noticias'];['Portas'];['Lagrimas'].

n(min, sing, masc) -->
    [menino];[tempo];[cacador];[lobo];
    [pai];[rosto];[rio];[mar];
    [cachorro];[tambor];[sino];[vento];
    [martelo].

n(max, sing, masc) -->
    ['Menino'];['Tempo'];['Cacador'];['Lobo'];
    ['Pai'];['Rosto'];['Rio'];['Mar'];
    ['Cachorro'];['Tambor'];['Sino'];['Vento'];
    ['Martelo'].

n(min, plur, masc) -->
    [meninos];[tempos];[cacadores];[lobos];
    [pais];[rostos];[rios];[mares];
    [cachorros];[tambores];[sinos];[ventos];
    [martelos].

n(max, plur, masc) -->
    ['Meninos'];['Tempos'];['Cacadores'];['Lobos'];
    ['Pais'];['Rostos'];['Rios'];['Mares'];
    ['Cachorros'];['Tambores'];['Sinos'];['Ventos'];
    ['Martelos'].
