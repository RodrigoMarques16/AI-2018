#ifndef UTIL_H
#define UTIL_H

#include <functional>
#include <vector>
#include <iostream>
#include <sstream>

int getX(int index);
int getY(int index);

unsigned int findInVector(std::vector<short>& v, short n);

int string_to_int(const std::string& s);

//using boost::hash_combine
template <class T>
inline void hash_combine(std::size_t& seed, T const& v);

std::size_t getHash(std::vector<short>& v);

#endif
