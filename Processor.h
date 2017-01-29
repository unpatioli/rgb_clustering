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

using ElementContT = std::vector<ElementPtrT>;
using ClusterMapT = std::map<int, ClusterPtrT>;

class Cluster;

class Processor
{
    std::string _filename;
    DistT _dist;

    image_t _img;
    view_t _view;

    ElementContT _els;
    LatticeT _lattice;

    ClusterMapT _clusters;
    int _current_cluster_id;

public:
    Processor(const std::string& filename, DistT dist);
    Processor(const Processor&) = delete;
    Processor& operator= (const Processor&) = delete;

    void clusterize();

private:
    bool process_point(ElementPtrT& el);
    ClusterPtrT create_cluster(ElementPtrT el);
    void save(const std::string& suffix = "_clusters.jpg");
};


#endif //RGB_CLUSTERING_PROCESSOR_H
