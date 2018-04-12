timetable(edinburgh,london,[9:40/10:50/ba4733/[mo,tu,we,th,fr,sa,su],13:40/14:50/ba4773/[mo,tu,we,th,fr,sa,su],19:40/20:50/ba4833/[mo,tu,we,th,fr,su]]).

timetable(london,edinburgh,[9:40/10:50/ba4732/[mo,tu,we,th,fr,sa,su],11:40/12:50/ba4752/[mo,tu,we,th,fr,sa,su],18:40/19:50/ba4822/[mo,tu,we,th,fr]]).

timetable(london,ljubljana,[13:20/16:20/ju201/[fr],13:20/16:20/ju213/[su]]).

timetable(london,zurich,[9:10/11:45/ba614/[mo,tu,we,th,fr,sa,su],14:45/17:20/sr805/[mo,tu,we,th,fr,sa,su]]).

timetable(london,milan,[8:30/11:20/ba510/[mo,tu,we,th,fr,sa,su],11:00/13:50/az459/[mo,tu,we,th,fr,sa,su]]).

timetable(ljubljana,zurich,[11:30/12:40/ju322/[tu,th]]).

timetable(ljubljana,london,[11:10/12:20/yu200/[fr],11:25/12:20/yu212/[su]]).

timetable(milan,london,[9:10/10:00/az458/[mo,tu,we,th,fr,sa,su],12:20/13:10/ba511/[mo,tu,we,th,fr,sa,su]]).

timetable(milan,zurich,[9:25/10:15/sr621/[mo,tu,we,th,fr,sa,su],12:45/13:35/sr623/[mo,tu,we,th,fr,sa,su]]).

timetable(zurich,ljubljana,[13:30/14:40/yu323/[tu,th]]).

timetable(zurich,london,[9:00/9:40/ba613/[mo,tu,we,th,fr,sa],16:10/16:55/sr806/[mo,tu,we,th,fr,su]]).

timetable(zurich,milan,[7:55/8:45/sr620/[mo,tu,we,th,fr,sa,su]]).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

allFlights(Origin, Day, L) :- findall(Origin-Dest:Day:Flight_num:DEPTIME, flight(Origin, Dest, Day, Flight_num, DEPTIME, _:_) , L).

hi(hello). 

%Utilities
dest(_-Place2, Place2).
head([A|_], A). 

transfer(H1:M1, H2:M2) :- X is H1*60 + M1 , Y is H2*60 + M2 , Y - X > 40.

depTime(_-_:_:DepartureTime, DepartureTime).
flightCode(_:Code:_, Code).

route(Place1, Place2, Day, Route) :-  route_(Place1, Place2, Day, Route, [Place1]).


route_(Place1, Place2, Day, [Place1-Place2:Flight_num:DEPTIME], _) :- flight(Place1, Place2, Day, Flight_num, DEPTIME, _).

route_(Place1, Place2, Day, Route, AllPlaces) :- allFlights(Place1, Day, AllFlights),
									  member(X:Day:Flight_num:DEPTIME,AllFlights),
									  dest(X, NewDest),
									  \+ member(Place2, AllPlaces),
									  append(AllPlaces, Place2, NewPlaces),								  
									  route_(NewDest, Place2, Day, NewRoute, NewPlaces),
									  append([X:Flight_num:DEPTIME], NewRoute, Route).							  

									  	
question3(Place1, Place2, Place3, S, [R1,R2,R3,R4]) :- member(X, [Place1, Place2, Place3]),
                                        member(Y, [Place1, Place2, Place3]),
                                        member(Z, [Place1, Place2, Place3]),
                                        X \= Y,
                                        Y \= Z,
                                        X \= Z, 
                                        route(S, X, tu, R1), route(X, Y, we, R2), route(X, Z, th, R3), route(Z, S, fr, R4).
					 
flight(Place1, Place2, Day, Flight_num, H1:M1, H2:M2) :- timetable(Place1, Place2, L), member(H1:M1/H2:M2/Flight_num/DayList, L), member(Day, DayList).




