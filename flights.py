from pyswip import *

prolog = Prolog()    #initialize
prolog.consult("flights.pl")

def question1():
    place1 = raw_input("Place1: ")
    place2 = raw_input("Place2: ")
    List = Variable()
    q = Functor("question1",3)
    result = Query(q(place1, place2, List))
    while result.nextSolution():
        for x in List.value:
            print x
    result.closeQuery()

def question2():
    place1 = raw_input("Place1: ")
    place2 = raw_input("Place2: ")
    day    = raw_input("Day: ")
    List = Variable()
    q = Functor("question2",4)
    result = Query(q(place1,place2,day,List))
    while result.nextSolution():
        for x in List.value:
            print x
    result.closeQuery()

def question3():
    s    = raw_input("Starting location: ")
    c1   = raw_input("Choose a city to visit: ")
    c2   = raw_input("Choose a city to visit: ")
    c3   = raw_input("Choose a city to visit: ")
    day1  = raw_input("When does your trip start: ")
    day2  = raw_input("When does your trip end: ")
    List = Variable()
    q    = Functor("question3", 7)
    result = Query(q(s,c1,c2,c3,day1,day2,List))
    while result.nextSolution():
        for x in List.value:
            print x
    result.closeQuery()

questions = {
    "question1": question1,
    "question2": question2,
    "question3": question3
}

def main():
    print("Flight planner - Answers specific questions")
    print("q1: In which days of the week there is a direct flight from Place1 to Place2?")
    print("q2: What are the available flights from Place1 to Place2 on a certain Day?")
    print("q3: What order should C1, C2 and C3 be visited, starting and ending at S, with at most 1 flight a day?")
    print("Enter 'exit' to exit the program")
    while True:
        question = raw_input("Which question? ")
        if question == "exit":
            break
        else:
            questions[question]()
    print("Exiting parser")

main()
