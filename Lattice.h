#ifndef RGB_CLUSTERING_LATTICE_H
#define RGB_CLUSTERING_LATTICE_H

#include <unordered_map>
#include <vector>

#include "Types.h"

using BucketT = std::vector<ElementPtrT>;

using bLatticeT = std::unordered_map<CoordT, BucketT>;
using gLatticeT = std::unordered_map<CoordT, bLatticeT>;
using rLatticeT = std::unordered_map<CoordT, gLatticeT>;

using LatticeT = rLatticeT;

#endif //RGB_CLUSTERING_LATTICE_H
