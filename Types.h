#ifndef RGB_CLUSTERING_TYPES_H
#define RGB_CLUSTERING_TYPES_H

#include <memory>

using CoordT = unsigned char;
using DistT = float;

class Element;
class Cluster;

using ElementPtrT = std::shared_ptr<Element>;
using ClusterPtrT = std::shared_ptr<Cluster>;

#endif //RGB_CLUSTERING_TYPES_H
