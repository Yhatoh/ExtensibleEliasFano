#include <vector>

#include "extensibleEliasFanoTuplesVector.hpp"
#include "extensibleEliasFano.hpp"
#include "linearSearch.hpp"

using namespace std;

#ifndef SCHEME4
#define SCHEME4

template<class T>
class Scheme4 {
	private:
    // se usa para saber la posicion del 1 que comenzo la run de 1's actual
    uint32_t bufferRunStart;
    // se usa para recordar la ultima posicion ingresada
    uint32_t bufferNumber;
    // se usa para saber si el primer numero del conjunto es 1 o no
		char firstNum;
		void *G;
		void *R;
		void *V;
	public:
		Scheme4(uint32_t bufferSiz, char type);
		uint32_t append(uint32_t number);
		uint32_t size();
    uint32_t getLast();
		//uint32_t print();
};

/*

Constructor

uint32_t bufferSize, corresponde al tamaño del buffer a usar en la 
                     estructura extesibleEliasFano
char type,           corresponde al tipo de estructura se usa si tuples
                     vector o red black tree

*/
template<class T>
Scheme4<T>::Scheme4(uint32_t bufferSize, char type){
	//this->buffer = 0;
  this->bufferRunStart = 0;
  this->bufferNumber = 0;
  this->firstNum = '0';
  if(type == 'T'){
    this->G = new ExtensibleEliasFanoTuplesVector(bufferSize, linearSearch);
    this->R = new ExtensibleEliasFanoTuplesVector(bufferSize, linearSearch);
    this->V = new ExtensibleEliasFanoTuplesVector(bufferSize, linearSearch);
  } else {
    this->G = new ExtensibleEliasFano<RedBlackTree>(bufferSize);
    this->R = new ExtensibleEliasFano<RedBlackTree>(bufferSize);
    this->V = new ExtensibleEliasFano<RedBlackTree>(bufferSize);
  }
}

/*

Append,              recibe la posición del 1 en el vector de bits
                     para ingresarlo al esquema

uint32_t pos,        la posición del 1 en el vector de bits

*/
template<class T>
uint32_t Scheme4<T>::append(uint32_t number){
  if(this->bufferNumber) {
    //not first number
    if(number - 1 > this->bufferNumber) {
      uint32_t cantZeros = number - this->bufferNumber - 1;
      while(cantZeros-- > 1) {
        static_cast< T* >(this->G)->pushBit(0);
      }
      static_cast< T* >(this->G)->pushBit(1);
      if(this->bufferRunStart == this->bufferNumber) {
        static_cast< T* >(this->V)->pushBit(0);
      } else {
        uint32_t o = this->bufferNumber - this->bufferRunStart;      
        while(o-- > 1) {
          static_cast< T* >(this->R)->pushBit(0);
        }
        static_cast< T* >(this->R)->pushBit(1);
        static_cast< T* >(this->V)->pushBit(1);
      }
      this->bufferRunStart = number;
    }
  } else {
    //first number
    if(number - 1 == this->bufferNumber) {
      this->firstNum = '1';
    } else {
      uint32_t cantZeros = number - 1;
      while(cantZeros-- > 1){
        static_cast< T* >(this->G)->pushBit(0);
      }
      static_cast< T* >(this->G)->pushBit(1);
    }
    this->bufferRunStart = number;
  }

  this->bufferNumber = number;

  return 1;
}

/*

Size

retorna el tamaño total del esquema, siendo este la suma de los
tamaños de G, R, V, bufferRunStart, bufferNumber y firstNum

*/
template<class T>
uint32_t Scheme4<T>::size(){
	return static_cast< T* >(this->G)->size() + static_cast< T* >(this->R)->size() + static_cast< T* >(this->V)->size() + sizeof(this->bufferRunStart) + sizeof(this->bufferNumber) + sizeof(this->firstNum);
}
#endif