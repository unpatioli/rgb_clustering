#include "Element.h"

#include "Cluster.h"

Element::Element(CoordT r, CoordT g, CoordT b, int cluster_id) :
        _r(r), _g(g), _b(b),
        _cluster_id(cluster_id)
{}

DistT Element::dist(const Element& rhs) const
{
    auto res = std::sqrt(std::pow(_r - rhs._r, 2) + std::pow(_g - rhs._g, 2) + std::pow(_b - rhs._b, 2));
    return static_cast<DistT>(res);
}
