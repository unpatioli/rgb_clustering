#include "Cluster.h"

#include "Element.h"

Cluster::Cluster(int id, Element *first_el) : _id(id)
{
    first_el->_cluster_id = id;
    first_el->_cluster = this;

    _limits.min_r = first_el;
    _limits.min_g = first_el;
    _limits.min_b = first_el;

    _limits.max_r = first_el;
    _limits.max_g = first_el;
    _limits.max_b = first_el;
}

void Cluster::add_element(Element *el)
{
    el->_cluster_id = _id;
    el->_cluster = this;
    _els.push_back(el);
    _limits.update(el);
}

void Cluster::add_element(Cluster *cluster)
{
    for (auto el : cluster->_els) {
        el->_cluster_id = _id;
        el->_cluster = this;
    }
    _limits.update(cluster);
    _els.splice(_els.end(), cluster->_els);
}

const Limits* Cluster::get_limits() const
{
    return &_limits;
}

const size_t Cluster::size() const
{
    return _els.size();
}

const int Cluster::id() const
{
    return _id;
}
