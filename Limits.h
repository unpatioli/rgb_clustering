#ifndef RGB_CLUSTERING_LIMITS_H
#define RGB_CLUSTERING_LIMITS_H

#include <list>

class Element;
class Cluster;

struct Limits
{
    Element *min_r;
    Element *min_g;
    Element *min_b;

    Element *max_r;
    Element *max_g;
    Element *max_b;

    void update(Element *el);
    void update(const Cluster *cluster);

    std::list<Element*> all() const;
};


#endif //RGB_CLUSTERING_LIMITS_H
