#ifndef RGB_CLUSTERING_LIMITS_H
#define RGB_CLUSTERING_LIMITS_H

#include <list>

#include "Types.h"

struct Limits
{
    ElementPtrT min_r;
    ElementPtrT min_g;
    ElementPtrT min_b;

    ElementPtrT max_r;
    ElementPtrT max_g;
    ElementPtrT max_b;

    void update(ElementPtrT el);
    void update(ClusterPtrT cluster);

    std::list<ElementPtrT> all() const;
};


#endif //RGB_CLUSTERING_LIMITS_H
