:- op(50, xfy, :).
:- op(60, xfy, /).

% In which days of the week there is a direct flight from Place1 to Place2?
question1(Place1, Place2, List) :- 
    findall(Day, flight(Place1, Place2, Day, _,_,_), L), sort(L,List).

% What are the available flights from Place1 to Place2 on a certain day?
question2(Place1, Place2, Day, List) :-
    findall(Flight_num:Dep_time, flight(Place1, Place2, Day, Flight_num, Dep_time, _:_), List).

%question3(S, C1, C2, C3, Begin, End, List).

% Retrieves the DepartureTime from a Route
depTime(_-_:_:DepartureTime, DepartureTime).

% Is true if there are at least 40 minutes between Time1 and Time2
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

% Gets all flights originating from Place1
allFlights(Place1, Day, L) :- 
    findall(Place1-Place2:Day:Flight_num:Dep_time, flight(Place1, Place2, Day, Flight_num, Dep_time, _:_), L).

route(Place1, Place2, Day, Route) :-  route_r(Place1, Place2, Day, Route, [Place1]).

route_r(Place1, Place2, Day, [Place1-Place2:Flight_num:DEPTIME], _) :- 
    flight(Place1, Place2, Day, Flight_num, DEPTIME, _).



/*
route(Place1,Place2,Day,Route) :- 
    flight(Place1, Place2, Day, Flight_num, Dep_time,_),
    Route = [Place1-Place2:Flight_num:Dep_time],
    !.

route(Place1,Place2,Day,Route) :- 
    flight(Place1, Intermed, Day, Flight_num, Dep_time,_),
    route(Intermed, Place2, Day, Route),
	Route = [Intermed-Place2:Flight_num:Dep_time].
*/
/* * * * * * * * * * * * * * * * * * * * 
 * * * UTILITIES * * * * * * * * * * * *
 * * * * * * * * * * * * * * * * * * * */

head([H|_], H). 

delta(A,B,C) :- 
    C is B-A.

toMin(H:M, Minutes) :- 
    Minutes is H * 60 + M. 

find(Day, Daylist) :-
    Daylist=alldays;
    Day=alldays;
    member(Day, Daylist).

inBoth(Day, List1, List2) :-
    member(Day, List1),
    member(Day, List2).

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
[ 9:10/10:00/az458/alldays,
12:20/13:10/ba511/alldays]).

timetable(milan,zurich,
[ 9:25/10:15/sr621/alldays,
12:45/13:35/sr623/alldays]).

timetable(zurich,ljubljana,
[13:30/14:40/yu323/[tu,th]]).

timetable(zurich,london,
[ 9:00/9:40/ba613/[mo,tu,we,th,fr,sa],
16:10/16:55/sr806/[mo,tu,we,th,fr,su]]).

timetable(zurich,milan,
[ 7:55/8:45/sr620/alldays]).