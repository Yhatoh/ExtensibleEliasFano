/*#include <vector>
#include <tuple>

#include <sdsl/bit_vectors.hpp>

using namespace std;
using namespace sdsl;

class TuplesVector {
  private:
    vector<tuple<uint32_t, uint32_t, sd_vector<>>*> tuplesVector;
    tuple<uint32_t, uint32_t, sd_vector<>>*(*predecessorFunction)(vector<tuple<uint32_t, uint32_t, sd_vector<>>*>&, uint32_t);
  public:
    TuplesVector(tuple<uint32_t, uint32_t, sd_vector<>>*(*predecessorFunction)(vector<tuple<uint32_t, uint32_t, sd_vector<>>*>&, uint32_t));
    ~TuplesVector();
    void push(tuple<uint32_t, uint32_t, sd_vector<>> *element, uint32_t bufferSize);
    tuple<uint32_t, uint32_t, sd_vector<>>* getPredecessor(uint32_t value, uint32_t bufferSize);
    uint32_t eefsize();
};
*/