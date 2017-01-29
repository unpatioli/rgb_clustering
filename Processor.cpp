#include "Processor.h"

#include <set>
#include <random>
#include <boost/gil/extension/io/jpeg_io.hpp>

#include "Cluster.h"

Processor::Processor(const std::string& filename, float dist) :
        _filename(filename), _dist(dist),
        _els(), _lattice(), _clusters(),
        _current_cluster_id(0)
{
    boost::gil::jpeg_read_image(filename, _img);

    _view = boost::gil::view(_img);

    auto els_count = _img.height() * _img.width();
    _els.reserve(els_count);
}

void Processor::clusterize()
{
    for (int y = 0; y < _img.height(); ++y) {
        for (auto it = _view.row_begin(y); it != _view.row_end(y); ++it) {
            auto r = (boost::gil::at_c<0>(*it));
            auto g = (boost::gil::at_c<1>(*it));
            auto b = (boost::gil::at_c<2>(*it));
            auto el = std::make_shared<Element>(r, g, b);
            _els.push_back(el);

            CoordT r_bucket = static_cast<CoordT>(std::floor(r / _dist));
            CoordT g_bucket = static_cast<CoordT>(std::floor(g / _dist));
            CoordT b_bucket = static_cast<CoordT>(std::floor(b / _dist));
            _lattice[r_bucket][g_bucket][b_bucket].push_back(el);
        }
    }

    if (_els.size() == 0) {
        return;
    }

    for (auto &el : _els) {
        if (el->_cluster_id != 0) { continue; }

        auto neighbor_found = process_point(el);
        if (!neighbor_found) { continue; }

        std::set<ElementPtrT> stack;

        for (auto limit_point : el->_cluster->get_limits().all()) {
            stack.insert(limit_point);
        }

        std::set<ElementPtrT> visited;

        while (!stack.empty()) {
            auto point = *stack.begin();
            stack.erase(stack.begin());
            visited.insert(point);
            neighbor_found = process_point(point);
            if (!neighbor_found) { continue; }

            for (auto limit_point : point->_cluster->get_limits().all()) {
                if (visited.find(limit_point) == visited.end()) {
                    stack.insert(limit_point);
                }
            }
        }
    }

    save();
}

bool Processor::process_point(ElementPtrT& el)
{
    auto r_b = static_cast<CoordT>(std::floor(el->_r / _dist));
    auto r_b_from = r_b - 1;
    auto r_b_to = r_b + 1;

    auto g_b = static_cast<CoordT>(std::floor(el->_g / _dist));
    auto g_b_from = g_b - 1;
    auto g_b_to = g_b + 1;

    auto b_b = static_cast<CoordT>(std::floor(el->_b / _dist));
    auto b_b_from = b_b - 1;
    auto b_b_to = b_b + 1;

    bool neighbor_found = false;
    for (auto i = r_b_from; i <= r_b_to; ++i) {
        for (auto j = g_b_from; j <= g_b_to; ++j) {
            for (auto k = b_b_from; k <= b_b_to; ++k) {

                auto &bucket = _lattice[i][j][k];

                for (auto &lat_el : bucket) {
                    if (el->_cluster_id == lat_el->_cluster_id && lat_el->_cluster_id != 0) {
                        continue;
                    }
                    if (el->dist(*lat_el) > _dist) { continue; }

                    if (el->_cluster_id == 0) {
                        if (lat_el->_cluster_id == 0) {
                            // Create new cluster
                            auto cluster = create_cluster(el);
                            cluster->add_element(lat_el);
                            neighbor_found = true;
                        } else {
                            // Existing cluster found
                            auto it = _clusters.find(lat_el->_cluster_id);
                            if (it != _clusters.end()) {
                                it->second->add_element(el);
                            }
                            neighbor_found = true;
                        }
                    } else {
                        if (lat_el->_cluster_id == 0) {
                            // New point found
                            auto it = _clusters.find(el->_cluster_id);
                            if (it != _clusters.end()) {
                                it->second->add_element(lat_el);
                            }
                            neighbor_found = true;
                        } else {
                            // Combine clusters
                            auto to_it = _clusters.find(el->_cluster_id);
                            auto from_it = _clusters.find(lat_el->_cluster_id);
                            if (to_it != _clusters.end() && from_it != _clusters.end()) {
                                to_it->second->add_element(from_it->second);
                                _clusters.erase(from_it);
                            }
                            neighbor_found = true;
                        }
                    }
                }
            }
        }
    }
    if (!neighbor_found) {
        // Create new cluster from one point
        create_cluster(el);
    }

    return neighbor_found;
}

ClusterPtrT Processor::create_cluster(ElementPtrT el)
{
    ++_current_cluster_id;
    auto cluster = Cluster::create(_current_cluster_id, el);
    _clusters.insert(std::make_pair(_current_cluster_id, cluster));

    return cluster;
}

void Processor::save(const std::string& suffix)
{
    std::vector<ClusterPtrT> sorted_clusters;
    sorted_clusters.reserve(_clusters.size());

    std::transform(_clusters.begin(), _clusters.end(),
                   std::back_inserter(sorted_clusters),
                   [](const ClusterMapT::value_type& p) {
                       return p.second;
                   });

    std::partial_sort(sorted_clusters.begin(), std::next(sorted_clusters.begin(), 3),
                      sorted_clusters.end(),
                      [](const ClusterPtrT& a, const ClusterPtrT& b) {
                          return a->size() > b->size();
                      });

    std::map<int, pixel_t> color_map;
    auto sc_it = sorted_clusters.begin();
    if (sc_it != sorted_clusters.end()) { color_map[(*sc_it++)->id()] = pixel_t(255, 0, 0); }
    if (sc_it != sorted_clusters.end()) { color_map[(*sc_it++)->id()] = pixel_t(0, 255, 0); }
    if (sc_it != sorted_clusters.end()) { color_map[(*sc_it++)->id()] = pixel_t(0, 0, 255); }

    std::random_device rnd_d;
    std::default_random_engine re(rnd_d());
    std::uniform_int_distribution<unsigned char> uni_dist(0, 180);
    for (; sc_it != sorted_clusters.end(); ++sc_it) {
        color_map[(*sc_it)->id()] = pixel_t(uni_dist(re), uni_dist(re), uni_dist(re));
    }

    for (int y = 0; y < _img.height(); ++y) {
        for (int x = 0; x < _img.width(); ++x) {
            auto el = _els[y * _img.width() + x];
            auto cm_it = color_map.find(el->_cluster_id);
            auto color = (cm_it != color_map.end())
                         ? cm_it->second
                         : pixel_t(uni_dist(re), uni_dist(re), uni_dist(re));
            *(_view.row_begin(y) + x) = pixel_t(color);
        }
    }
    boost::gil::jpeg_write_view(_filename + suffix, _view, 100);
}
