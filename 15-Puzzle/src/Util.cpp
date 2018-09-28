#include "Util.h"
#include <cctype>

// Lookup tables to convert a point in a 1D vector to (x,y) coordinates
int matrix_x[16] = { 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3 }; 
int matrix_y[16] = { 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3 };

int getX(int index) {
  if (index > 0 && index <= 16)
    return matrix_x[index];
  return -1;
}

int getY(int index) {
  if (index > 0 && index <= 16)
    return matrix_y[index];
  return -1;
}

unsigned int findInVector(std::vector<short>& v,short n){
  unsigned int i = 0;
  for(auto& it :v){
    if (it == n) 
      return i;
    i++;
  }
  return 20;
}

int string_to_int(const std::string& s){
  for(auto& it: s)
    if (!isdigit(it))
      throw "Enter a number when limiting depth";
  std::stringstream ss(s);
  int x = 0;
  ss >> x;
  return x;
}


//using boost::hash_combine
template <class T>
inline void hash_combine(std::size_t& seed, T const& v) {
    seed ^= std::hash<T>()(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

std::size_t getHash(std::vector<short>& v){
  std::size_t seed = 0;
  for(unsigned int i = 1; i < v.size(); i++){
    hash_combine(seed, v[i]);
  }
  return seed;
}
