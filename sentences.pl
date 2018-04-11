:- use_rendering(svgtree, [list(false)]).

head([H|_], H). 
 
sentence(frase(NP)) --> np(NP, max, _, _).
sentence(frase(NP, VP)) --> np(NP, max, Num, _), vp(VP, Num).

np(sujeito(N), Cap, Num, Gender) --> n(N, Cap, Num, Gender).
np(sujeito(det(Det), nome(N)), Cap, Num, Gender) --> det(Det, Cap, Num, Gender), n(N, min, Num, Gender).

vp(verbo(V), Num) --> v(V, Num).
vp(frase_verbal(verbo(V), complemento(C,NP)), Num) --> v(V, Num), comp(C, Num2, Gender), np(NP, min, Num2, Gender).
vp(frase_verbal(complemento(C,NP), verbo(V)), Num) --> comp(C, Num2, Gender), np(NP, min, Num2, Gender), v(V, Num).

% Determinantes ------------------------------------------------------------

det(X, A, B, C, D, E) :- det(A, B, C, D, E), head(D, X).

det(min, sing, fem) --> [a];[uma].
det(min, plur, fem) --> [as];[umas].
det(min, sing, masc) --> [o];[um].
det(min, plur, masc) --> [os];[uns].
det(max, sing, fem) --> ['A'];['Uma'].
det(max, plur, fem) --> ['As'];['Umas'].
det(max, sing, masc) --> ['O'];['Um'].
det(max, plur, masc) --> ['Os'];['Uns'].

% Complementos -------------------------------------------------------------

comp(X, A, B, C, D) :- comp(A, B, C, D), head(C, X).
comp(_,_) --> [com];[para].
comp(sing, masc) --> [pelo];[ao];[no].
comp(sing, fem) --> [pela];[a];[na].
comp(plur, masc) --> [pelos];[aos];[nos].
comp(plur, fem) --> [pelas];[as];[nas].

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

% Verbos -------------------------------------------------------------------
v(X, A, B, C) :- v(A, B, C), head(B,X).
v(sing) --> [bateu];[corre];[correu].
v(plur) --> [bateram];[correram];[corriam].
