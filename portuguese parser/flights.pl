:- op(50, xfy, :).
:- op(60, xfy, /).

% In which days of the week there is a direct flight from Place1 to Place2?
question1(Place1, Place2, List) :-
    findall(Day, flight(Place1, Place2, Day, _,_,_), L), sort(L,List).

% What are the available flights from Place1 to Place2 on a certain day?
question2(Place1, Place2, Day, List) :-
    findall(Flight_num:Dep_time, flight(Place1, Place2, Day, Flight_num, Dep_time, _:_), List).

% What order should C1, C2 and C3 be visited, starting and ending at S, with at most 1 flight a day?
question3(S, C1, C2, C3, Day1, List) :-
    member(X, [C1,C2,C3]), X \= S,
    member(Y, [C1,C2,C3]), Y \= S, Y \== X,
    member(Z, [C1,C2,C3]), Z \= S, Z \= X, Z \= Y,
    question3_(S, X, Y, Z, Day1, List), !.

question3_(S, C1, C2, C3, Day1, List) :-
	route(S, C1, Day1, Route1),
    length(Route1, 1),
    nextDay(Day1, Day2),
    route(C1, C2, Day2, Route2),
    length(Route2, 1),
    nextDay(Day2, Day3),
    route(C2, C3, Day3, Route3),
    length(Route3, 1),
    nextDay(Day3, Day4),
    route(C3, S, Day4, Route4),
    length(Route4, 1),
    Temp = [Route1, Route2, Route3, Route4],
    append(Temp, List).

% Retrieves the DepartureTime from a Route
depTime(_-_:_:DepartureTime, DepartureTime).

% Avances day
nextDay(mo, Day) :- Day=tu; Day=we; Day=th; Day=fr; Day=sa; Day=su.
nextDay(tu, Day) :- Day=mo; Day=we; Day=th; Day=fr; Day=sa; Day=su.
nextDay(we, Day) :- Day=mo; Day=tu; Day=th; Day=fr; Day=sa; Day=su.
nextDay(th, Day) :- Day=mo; Day=tu; Day=we; Day=fr; Day=sa; Day=su.
nextDay(fr, Day) :- Day=mo; Day=tu; Day=we; Day=th; Day=sa; Day=su.
nextDay(sa, Day) :- Day=mo; Day=tu; Day=we; Day=th; Day=fr; Day=su.
nextDay(su, Day) :- Day=mo; Day=tu; Day=we; Day=th; Day=fr; Day=sa.

% Is true if there are at least 40 minutes between Time1 and Time2
transfer(-1, _).
transfer(Time1, Time2) :-
    toMin(Time1,M1),
    toMin(Time2,M2),
    delta(M1,M2,Delta),
    Delta >= 40.

% Says if a flight from Place1 to Place2 exists in a certain Day
flight(Place1,Place2,Day,Flight_num,Dep_time,Arr_time) :-
	timetable(Place1,Place2, List),
    member(Dep_time/Arr_time/Flight_num/DayList, List),
    member(Day, DayList).

% Call the recursive route function with an initialized list
route(Place1, Place2, Day, Route) :-
    route_r(Place1, Place2, Day, -1, Route).

% Direct flight
route_r(Place1, Place2, Day, Arrival, [Place1-Place2:Flight_num:Dep_time]) :-
    flight(Place1, Place2, Day, Flight_num, Dep_time, _Arr_time),
    transfer(Arrival, Dep_time).

% Intermediary flight
route_r(Place1, Place2, Day, Arrival, Route) :-
    flight(Place1, Intermed, Day, Flight_num, Dep_time, Arr_time),
    transfer(Arrival, Dep_time),
    route_r(Intermed, Place2, Day, Arr_time, NewRoute),
    append([Place1-Intermed:Flight_num:Dep_time], NewRoute, Route).

delta(A,B,C) :-
    C is B-A.

toMin(H:M, Minutes) :-
    Minutes is H * 60 + M.

/********************/
/***** DATABASE *****/
/********************/
timetable(edinburgh,london,
[ 9:40/10:50/ba4733/[mo,tu,we,th,fr,sa,su],
13:40/14:50/ba4773/[mo,tu,we,th,fr,sa,su],
19:40/20:50/ba4833/[mo,tu,we,th,fr,su]]).

timetable(london,edinburgh,
[ 9:40/10:50/ba4732/[mo,tu,we,th,fr,sa,su],
11:40/12:50/ba4752/[mo,tu,we,th,fr,sa,su],
18:40/19:50/ba4822/[mo,tu,we,th,fr]]).

timetable(london,ljubljana,
[13:20/16:20/ju201/[fr],
13:20/16:20/ju213/[su]]).

timetable(london,zurich,
[ 9:10/11:45/ba614/[mo,tu,we,th,fr,sa,su],
14:45/17:20/sr805/[mo,tu,we,th,fr,sa,su]]).

timetable(london,milan,
[ 8:30/11:20/ba510/[mo,tu,we,th,fr,sa,su],
11:00/13:50/az459/[mo,tu,we,th,fr,sa,su]]).

timetable(ljubljana,zurich,
[11:30/12:40/ju322/[tu,th]]).

timetable(ljubljana,london,
[11:10/12:20/yu200/[fr],
11:25/12:20/yu212/[su]]).

timetable(milan,london,
[ 9:10/10:00/az458/[mo,tu,we,th,fr,sa,su],
12:20/13:10/ba511/[mo,tu,we,th,fr,sa,su]]).

timetable(milan,zurich,
[ 9:25/10:15/sr621/[mo,tu,we,th,fr,sa,su],
12:45/13:35/sr623/[mo,tu,we,th,fr,sa,su]]).

timetable(zurich,ljubljana,
[13:30/14:40/yu323/[tu,th]]).

timetable(zurich,london,
[ 9:00/9:40/ba613/[mo,tu,we,th,fr,sa],
16:10/16:55/sr806/[mo,tu,we,th,fr,su]]).

timetable(zurich,milan,
[ 7:55/8:45/sr620/[mo,tu,we,th,fr,sa,su]]).
