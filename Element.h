#ifndef RGB_CLUSTERING_ELEMENT_H
#define RGB_CLUSTERING_ELEMENT_H

#include <cmath>

class Cluster;

using CoordT = unsigned char;

struct Element
{
    CoordT _r, _g, _b;
    int _cluster_id;
    Cluster *_cluster;

    Element(CoordT r, CoordT g, CoordT b, int cluster_id = 0);

    double dist(const Element& rhs) const;
};


#endif //RGB_CLUSTERING_ELEMENT_H
