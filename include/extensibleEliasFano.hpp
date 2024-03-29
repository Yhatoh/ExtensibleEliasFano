#include <tuple>
#include <vector>
#include <algorithm>

#include <sdsl/bit_vectors.hpp>

using namespace std;
using namespace sdsl;

#ifndef EXTENSIBLEELIASFANO
#define EXTENSIBLEELIASFANO

template <class T>
class ExtensibleEliasFano {
  private:
    vector<uint32_t> buffer;
    uint32_t bufferFill = 0;
    uint32_t count = 0;
    uint32_t blocksCount = 0;
    T *predecessorStructure;
    vector<tuple<uint32_t, uint32_t, sd_vector<>>*> blocks; //#block, key, vector
    char whereIsPredecessor(uint32_t position);

  public:
    ExtensibleEliasFano(uint32_t bufferSize);
    ExtensibleEliasFano(uint32_t bufferSize, uint32_t u_exp);
    ~ExtensibleEliasFano();
    int pushBit(uint32_t bit);
    int select1(uint32_t occurrence, uint32_t &result);
    uint32_t rank1(uint32_t position);
    uint32_t size();
};

template <class T>
ExtensibleEliasFano<T>::ExtensibleEliasFano(uint32_t bufferSize) {
  this->buffer = vector<uint32_t>(bufferSize, 0);
  predecessorStructure = new T();
}

template <class T>
ExtensibleEliasFano<T>::ExtensibleEliasFano(uint32_t bufferSize, uint32_t u_exp) {
  this->buffer = vector<uint32_t>(bufferSize, 0);
  predecessorStructure = new T(u_exp);
}

template <class T>
ExtensibleEliasFano<T>::~ExtensibleEliasFano() {
  for (vector<tuple<uint32_t, uint32_t, sd_vector<>>*>::iterator it = blocks.begin(), end = blocks.end(); it != end; ++it) {
    delete *it;
  }
  delete predecessorStructure;
}

template <class T>
int ExtensibleEliasFano<T>::pushBit(uint32_t bit) {
  if(bit) {
    (this->buffer)[bufferFill] = count;
    ++(this->bufferFill);
    if (this->bufferFill == (this->buffer).capacity()) {
      this->bufferFill = 0;
      uint32_t first = (this->buffer)[0];
      for (vector<uint32_t>::iterator it = (this->buffer).begin(), end = (this->buffer).end(); it != end; ++it) {
        *it -= first;
      }
      tuple<uint32_t, uint32_t, sd_vector<>>* bufferSDVector = new tuple<uint32_t, uint32_t, sd_vector<>>(this->blocksCount, first, sd_vector<>((this->buffer).begin(), (this->buffer).end()));
      blocks.push_back(bufferSDVector);
      this->predecessorStructure->push(bufferSDVector, (this->buffer).capacity());
      ++this->blocksCount;
    }
  }
  ++count;
  return count;
}

template <class T>
char ExtensibleEliasFano<T>::whereIsPredecessor(uint32_t position) {
  if (buffer[0] <= position && bufferFill != 0) {
    return 'b';
  } else {
    if (blocksCount == 0) {
      return 'n';
    } else {
      return 's';
    }
  }
}

template <class T>
int ExtensibleEliasFano<T>::select1(uint32_t occurrence, uint32_t &result) {
  uint32_t block = (occurrence-1)/buffer.size();
  if (block > blocksCount) {
    return 0;
  } else if (block < blocksCount) {
    tuple<uint32_t, uint32_t, sd_vector<>>* containerBlock = blocks[block];
    uint32_t subOccurrence = occurrence - get<0>(*containerBlock) * uint32_t(buffer.size());
    sd_vector<>::select_1_type selectSD(&(get<2>(*containerBlock)));
    result = selectSD(subOccurrence) + get<1>(*containerBlock);
    return 1;
  } else {
    if (occurrence <= blocksCount*buffer.size() + bufferFill) {
      result = buffer[occurrence - blocksCount*buffer.size() - 1];
      return 1;
    }
  }
  return 0;
}

template <class T>
uint32_t ExtensibleEliasFano<T>::rank1(uint32_t position) {
  char predecessorPlace = whereIsPredecessor(position);
  if (predecessorPlace == 'n') {
    return 0;
  } else if (predecessorPlace == 'b') {
    vector<uint32_t>::iterator low = upper_bound(buffer.begin(), buffer.begin() + bufferFill, position);
    return blocksCount * buffer.size() + (low - buffer.begin());
  } else {
    tuple<uint32_t, uint32_t, sd_vector<>>* predecessorBlock = (tuple<uint32_t, uint32_t, sd_vector<>>*)predecessorStructure->getPredecessor(position, (this->buffer).capacity());
    if (predecessorBlock) {
      uint64_t relativePosition = position - get<1>(*predecessorBlock) + 1;
      uint32_t ones = sd_vector<>::rank_1_type(&get<2>(*predecessorBlock))(min(relativePosition, get<2>(*predecessorBlock).size()));
      return get<0>(*predecessorBlock) * buffer.size() + ones;
    } else {
      return 0;
    }
  }
}

template <class T>
uint32_t ExtensibleEliasFano<T>::size() {
  uint32_t returnSize = 0;
  returnSize += sizeof(vector<uint32_t>);
  returnSize += sizeof(uint32_t) * buffer.size();
  returnSize += sizeof(uint32_t) * 3;
  returnSize += predecessorStructure->eefsize();
  returnSize += sizeof(vector<tuple<uint32_t, uint32_t, sd_vector<>>*>);
  returnSize += sizeof(tuple<uint32_t, uint32_t, sd_vector<>>*) * blocks.size();
  returnSize += sizeof(tuple<uint32_t, uint32_t, sd_vector<>>) * blocks.size();
  for (vector<tuple<uint32_t, uint32_t, sd_vector<>>*>::iterator it = blocks.begin(), end = blocks.end(); it != end; ++it) {
    returnSize += size_in_bytes(get<2>(**it));
  }
  return returnSize;
}
#endif