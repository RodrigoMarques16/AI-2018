
## I.A. - 3º Trabalho ###########################################################################

Rodrigo Marques 201605427

Tiago Melo 201604918

## Requirements #################################################################################

 - SWI-Prolog 7.6.x
 - Python 2.7.x
 - PySWIP 0.2.3 and its requirements (https://github.com/yuce/pyswip)

## Running ######################################################################################


 ### Flight planner #############################
 
 Call with `flights.pl` or `flights.py`
  
  #### Prolog #################################### 
 
  The required queries were implemented as:
     - question1(Place1, Place2, List)
     - question2(Place1, Place2, Day, List)
     - question3(S, C1, C2, C3, Day1, List) 
  Each named as in the assignment description

  #### Python ####################################
  
  The same queries are implemented.

 ### Portuguese Grammatical Parser ##############

 Run with `parser.pl` or `parser.py`

  #### Prolog ####################################
  
  To parse through a sentence use the query sentence/3, for example
     - sentence(Tree, ['A', menina, bateu, a, porta], [])
  
  With Tree being the syntatic tree returned by the query.

  Due to Prolog's nature, words starting with a capital letter must be enclosed in ''.

  #### Python ####################################

  Enter your phrase normally, but with ',' seperating each word.
