#ifndef RGB_CLUSTERING_CLUSTER_H
#define RGB_CLUSTERING_CLUSTER_H

#include <list>

#include "Limits.h"

class Element;

class Cluster
{
private:
    int _id;
    std::list<Element *> _els;

    Limits _limits;

public:
    Cluster(int id, Element *first_el);

    void add_element(Element *el);
    void add_element(Cluster *cluster);

    const Limits* get_limits() const;
    const size_t size() const;
    const int id() const;
};


#endif //RGB_CLUSTERING_CLUSTER_H
