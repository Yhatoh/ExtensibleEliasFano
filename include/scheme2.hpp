#include <vector>

#include "extensibleEliasFanoTuplesVector.hpp"
#include "redBlackTree.hpp"
#include "extensibleEliasFano.hpp"
#include "linearSearch.hpp"

using namespace std;

#ifndef SCHEME2
#define SCHEME2

template<class T>
class Scheme2 {
  private:
    // se usa para recordar la ultima posicion ingresada
    uint32_t lastPos;
    // se usa para saber si el primer numero del conjunto es 1 o no
    char fistPos;
    void *G;
    void *L;
  public:
    Scheme2(uint32_t bufferSize, char type);
    uint32_t append(uint32_t pos);
    uint32_t size();
};

/*

Constructor

uint32_t bufferSize, corresponde al tamaño del buffer a usar en la 
                     estructura extesibleEliasFano
char type,           corresponde al tipo de estructura se usa si tuples
                     vector o red black tree

*/
template<class T>
Scheme2<T>::Scheme2(uint32_t bufferSize, char type){
  this->lastPos = 0;
  this->fistPos = '0';
  if(type == 'T'){
    this->G = new ExtensibleEliasFanoTuplesVector(bufferSize, linearSearch);
    this->L = new ExtensibleEliasFanoTuplesVector(bufferSize, linearSearch);
  } else {
    this->G = new ExtensibleEliasFano<RedBlackTree>(bufferSize);
    this->L = new ExtensibleEliasFano<RedBlackTree>(bufferSize);
  }
}

/*

Append,              recibe la posición del 1 en el vector de bits
                     para ingresarlo al esquema

uint32_t pos,        la posición del 1 en el vector de bits

*/
template<class T>
uint32_t Scheme2<T>::append(uint32_t pos){
  if(this->lastPos) {
    //not first element
    if(pos - 1 == this->lastPos) {
      //is a consecutive pos
      static_cast< T* >(this->L)->pushBit(0);
    } else {
      //is not a consecutive pos
      static_cast< T* >(this->L)->pushBit(1);
      uint32_t cantZeros = pos - this->lastPos - 1;
      while(cantZeros-- > 1){
        static_cast< T* >(this->G)->pushBit(0);
      }
      static_cast< T* >(this->G)->pushBit(1);
    }
  } else {
    //first element 
    if(pos - 1 == this->lastPos) {
      //is 1
      this->fistPos = '1';
    } else {
      //is not 1
      uint32_t cantZeros = pos - 1;
      while(cantZeros-- > 1){
        static_cast< T* >(this->G)->pushBit(0);
      }
      static_cast< T* >(this->G)->pushBit(1);
    }
  }
  this->lastPos = pos;

  return 1;
}

/*

Size

retorna el tamaño total del esquema, siendo este la suma de los
tamaños de G, L, buffer y fistPos

*/
template<class T>
uint32_t Scheme2<T>::size(){
  return static_cast< T* >(this->G)->size() + static_cast< T* >(this->L)->size() + sizeof(this->lastPos) + sizeof(this->fistPos);
}
#endif