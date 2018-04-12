#include <map>

using namespace std;

/* * * * * * * * * * * * * * * * * * *
 * DETERMINERS * * * * * * * * * * * *
 * * * * * * * * * * * * * * * * * * */

map<string,bool> det_sing_fem = {
};

map<string,bool> det_sing_male = {
};

map<string,bool> det_plur_fem = {
};

map<string,bool> det_plur_male = {
};


/* * * * * * * * * * * * * * * * * * *
 * NOUNS * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * * * * * */

map<string,bool> noun_sing_fem = {
};

map<string,bool> noun_sing_male = {
};

map<string,bool> noun_plur_fem = {
};

map<string,bool> noun_plur_male = {
};

/* * * * * * * * * * * * * * * * * * *
 * VERBS * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * * * * * */

map<string,bool> verb_sing = {
  {"bateu", true},
  {"corre", true},
  {"correu", true}
};

map<string,bool> verb_plur = {
  {"bateram", true},
  {"correm", true},
  {"correram", true}
};

/* * * * * * * * * * * * * * * * * * *
 * COMPLEMENTS * * * * * * * * * * *
 * * * * * * * * * * * * * * * * * * */

map<string,bool> comp = {
};

map<string,bool> comp_sing_male = {
};

map<string,bool> comp_sing_fem = {
};

map<string,bool> comp_plur_male = {
};

map<string,bool> comp_plur_fem = {
};
