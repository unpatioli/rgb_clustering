#include "Cluster.h"

#include "Element.h"

Cluster::Cluster(int id, ElementPtrT first_el) : _id(id)
{
    _limits.min_r = first_el;
    _limits.min_g = first_el;
    _limits.min_b = first_el;

    _limits.max_r = first_el;
    _limits.max_g = first_el;
    _limits.max_b = first_el;
}

ClusterPtrT Cluster::create(int id, ElementPtrT first_el)
{
    auto cluster = ClusterPtrT(new Cluster(id, first_el));
    cluster->add_element(first_el);
    return cluster;
}

void Cluster::add_element(ElementPtrT el)
{
    el->_cluster_id = _id;
    el->_cluster = shared_from_this();
    _els.push_back(el);
    _limits.update(el);
}

void Cluster::add_element(ClusterPtrT cluster)
{
    for (auto el : cluster->_els) {
        el->_cluster_id = _id;
        el->_cluster = shared_from_this();
    }
    _limits.update(cluster);
    _els.splice(_els.end(), cluster->_els);
}

Limits Cluster::get_limits() const
{
    return _limits;
}

const size_t Cluster::size() const
{
    return _els.size();
}

const int Cluster::id() const
{
    return _id;
}

