#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <vector>

#include <sdsl/bit_vectors.hpp>

#include "../include/avlMap.h"
#include "../include/binarySearch.hpp"
#include "../include/btree_map.h"
#include "../include/extensibleEliasFano.hpp"
#include "../include/ExtensibleEliasFanoTuplesVector.hpp"
#include "../include/interpolationSearch.hpp"
#include "../include/linearSearch.hpp"
#include "../include/scheme2.hpp"
#include "../include/scheme4.hpp"
#include "../include/tuplesVector.hpp"
#include "../include/vEB.h"
#include "../include/x-fast-map.h"
#include "../include/y-fast.h"

using namespace std;
using namespace sdsl;

int main(int argc, char *argv[]) {

  std::ios::sync_with_stdio(false);
  vector<uint32_t> bufferSizes = {1024, 2048, 4096};
  
  uint32_t ret = 0;

  vector< uint32_t > numbers;
  string line;
  getline(std::cin, line);
  getline(std::cin, line);
  uint32_t n = 0;
  while(n < line.length()){
    if(line[n++] == '1') numbers.push_back(n);
  }
  n = numbers.size();

  for(uint32_t i = 0; i < 3; i++){

    Scheme2<ExtensibleEliasFanoTuplesVector> *s2Tuples = new Scheme2<ExtensibleEliasFanoTuplesVector>(bufferSizes[i], 'T');
    Scheme2<ExtensibleEliasFano<RedBlackTree>> *s2RedBlack = new Scheme2<ExtensibleEliasFano<RedBlackTree>>(bufferSizes[i], 'R');

    Scheme4<ExtensibleEliasFanoTuplesVector> *s4Tuples = new Scheme4<ExtensibleEliasFanoTuplesVector>(bufferSizes[i], 'T');
    Scheme4<ExtensibleEliasFano<RedBlackTree>> *s4RedBlack = new Scheme4<ExtensibleEliasFano<RedBlackTree>>(bufferSizes[i], 'R');

    for(uint32_t i = 0; i < n; i++){
      ret = s2Tuples->append(numbers[i]);
    }
    cout << ret << " Memory Used Scheme 2 using tuples vector with buffer size " << bufferSizes[i] << ": " << ((double) s2Tuples->size() * 8.0 )/((double)n) << "\n";

    for(uint32_t i = 0; i < n; i++){
      ret = s2RedBlack->append(numbers[i]);
    }
    cout << ret << " Memory Used Scheme 2 using red black tree with buffer size " << bufferSizes[i] << ": " << ((double) s2RedBlack->size() * 8.0 )/((double)n) << "\n";

    for(uint32_t i = 0; i < n; i++){
      ret = s4Tuples->append(numbers[i]);
    }
    cout << ret << " Memory Used Scheme 4 using tuples vector with buffer size " << bufferSizes[i] << ": " << ((double) s4Tuples->size() * 8.0 )/((double)n) <<  "\n";

    for(uint32_t i = 0; i < n; i++){
      ret = s4RedBlack->append(numbers[i]);
    }
    cout << ret << " Memory Used Scheme 4 using red black tree with buffer size " << bufferSizes[i] << ": " << ((double) s4RedBlack->size() * 8.0 )/((double)n) <<  "\n";
  }

  bit_vector b = bit_vector(line.length(), 0);
  for(uint32_t i = 0; i < line.length(); i++){
    //cout << i << "\n";
    if(line[i] == '1') b[i] = 1;
  }

  ret = 1;
  sd_vector<> sdb(b);
  cout << ret << " Memory Used sdb " << ((double)size_in_bytes(sdb) * 8.0) / ((double)n) << "\n";
  return 0;
}