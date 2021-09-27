#include "Node.h"

bool operator<(Node& n1, Node& n2){
    return n1.totalFrequency<n2.totalFrequency;
}
