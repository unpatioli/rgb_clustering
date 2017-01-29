#ifndef RGB_CLUSTERING_PROCESSOR_H
#define RGB_CLUSTERING_PROCESSOR_H

#include <string>
#include <vector>
#include <boost/gil/gil_all.hpp>
#include <map>

#include "Element.h"
#include "Lattice.h"

using image_t = boost::gil::rgb8_image_t;
using view_t = boost::gil::rgb8_view_t;
using pixel_t = boost::gil::rgb8_pixel_t;

using ElementContT = std::vector<Element*>;
using ClusterMapT = std::map<int, Cluster*>;

class Cluster;

class Processor
{
    std::string _filename;
    float _dist;

    image_t _img;
    view_t _view;

    ElementContT _els;
    LatticeT _lattice;

    ClusterMapT _clusters;
    int _current_cluster_id;

public:
    Processor(const std::string& filename, float dist);

    void clusterize();

private:
    bool process_point(Element *el);
    Cluster* create_cluster(Element *el);
    void save(const std::string& suffix = "_clusters.jpg");
};


#endif //RGB_CLUSTERING_PROCESSOR_H
