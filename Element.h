#ifndef RGB_CLUSTERING_ELEMENT_H
#define RGB_CLUSTERING_ELEMENT_H

#include <cmath>
#include <memory>

#include "Types.h"

struct Element
{
    const CoordT _r, _g, _b;
    int _cluster_id;
    ClusterPtrT _cluster;

    Element(CoordT r, CoordT g, CoordT b, int cluster_id = 0);
    Element(const Element&) = delete;
    Element& operator= (const Element&) = delete;

    DistT dist(const Element& rhs) const;
};


#endif //RGB_CLUSTERING_ELEMENT_H
