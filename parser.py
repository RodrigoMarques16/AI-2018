from pyswip import *

def main():
    prolog = Prolog()
    prolog.consult("parser.pl")

    print("Portuguese Grammatical Parser")
    print("Instructions: ")
    print(" - Surround capital words with ''")
    print(" - Seperate each word with commas")
    print(" - eg: 'A',menina,bateu,a,porta")
    print("Enter 'exit' to exit the program")

    while True:
        phrase = raw_input("Enter a phrase: ")
        if phrase == "exit":
            break
        else:
            phrase = "sentence(Tree, [" + phrase + "], [])"
            print(phrase)
            for soln in prolog.query(phrase):
                print(soln)
    print("Exiting parser")

main()
