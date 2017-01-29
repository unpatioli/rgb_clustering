#include "Limits.h"

#include "Element.h"
#include "Cluster.h"

void Limits::update(Element *el)
{
    if (el->_r < min_r->_r) {
        min_r = el;
    } else if (el->_r > max_r->_r) {
        max_r = el;
    }
    if (el->_g < min_g->_g) {
        min_g = el;
    } else if (el->_g > max_g->_g) {
        max_g = el;
    }
    if (el->_b < min_b->_b) {
        min_b = el;
    } else if (el->_b > max_b->_b) {
        max_b = el;
    }
}

void Limits::update(const Cluster *cluster)
{
    auto new_limits = cluster->get_limits();

    auto new_min_r = new_limits->min_r;
    auto new_min_g = new_limits->min_g;
    auto new_min_b = new_limits->min_b;

    auto new_max_r = new_limits->max_r;
    auto new_max_g = new_limits->max_g;
    auto new_max_b = new_limits->max_b;

    if (new_min_r->_r < min_r->_r) {
        min_r = new_min_r;
    } else if (new_max_r->_r > max_r->_r) {
        max_r = new_max_r;
    }
    if (new_min_g->_g < min_g->_g) {
        min_g =new_min_g;
    } else if (new_max_g->_g > max_g->_g) {
        max_g = new_max_g;
    }
    if (new_min_b->_b < min_b->_b) {
        min_b = new_min_b;
    } else if (new_max_b->_b > max_b->_b) {
        max_b = new_max_b;
    }
}

std::list<Element*> Limits::all() const
{
    std::list<Element*> res;
    res.push_back(min_r);
    res.push_back(min_g);
    res.push_back(min_b);

    res.push_back(max_r);
    res.push_back(max_g);
    res.push_back(max_b);

    return res;
}
