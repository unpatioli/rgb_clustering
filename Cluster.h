#ifndef RGB_CLUSTERING_CLUSTER_H
#define RGB_CLUSTERING_CLUSTER_H

#include <list>

#include "Limits.h"
#include "Types.h"

class Cluster : public std::enable_shared_from_this<Cluster>
{
private:
    int _id;
    std::list<ElementPtrT> _els;

    Limits _limits;

private:
    Cluster(int id, ElementPtrT first_el);
    Cluster(const Cluster&) = delete;
    Cluster& operator= (const Cluster&) = delete;

public:
    static ClusterPtrT create(int id, ElementPtrT first_el);

    void add_element(ElementPtrT el);
    void add_element(ClusterPtrT cluster);

    Limits get_limits() const;
    const size_t size() const;
    const int id() const;
};


#endif //RGB_CLUSTERING_CLUSTER_H
