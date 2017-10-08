//
//  maximum-cost-queries.cpp
//  Hackerrank
//
//  Created by Mikael Arakelian on 6/7/17.
//  Copyright © 2017 Mikael Arakelian. All rights reserved.
//

#include <algorithm>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>
#include <map>
#include <stdexcept>
#include <numeric>
#include <iterator>

enum DisjointSetUnionParameters {
    USE_PATH_COMPRESSION,
    USE_SUBTREE_MERGE_HEURISTICS
};

std::set<DisjointSetUnionParameters> DefaultDisjointSetUnionParameters() {
    return std::set<DisjointSetUnionParameters>({USE_PATH_COMPRESSION, USE_SUBTREE_MERGE_HEURISTICS});
}

struct DisjointSetNode {
    DisjointSetNode() {
        this->parent = this;
        this->subtree_size = 1;
    }
    ~DisjointSetNode() {}
    DisjointSetNode* parent;
    size_t subtree_size;
    
    DisjointSetNode* equivalence_class_parent() {
        DisjointSetNode* class_parent = this;
        
        while (class_parent != class_parent->parent) {
            class_parent = class_parent->parent;
        }
        
        return class_parent;
    }
    
    void set_parent(DisjointSetNode* new_parent) {
        new_parent->subtree_size += this->subtree_size;
        this->parent = new_parent;
    }
};

template <class T>
class DisjointSetUnion {
public:
    DisjointSetUnion(
        size_t expected_size = 100,
        const std::set<DisjointSetUnionParameters>& parameters =
                     DefaultDisjointSetUnionParameters()): parameters(parameters) {
        this->nodes.reserve(expected_size);
    }
    
    ~DisjointSetUnion() {
        for (auto& node: this->nodes) {
            delete node;
        }
        this->nodes.clear();
    }
    
    bool contains(const T& t) {
        return enumeration.find(t) != enumeration.end();
    }

    void add(const T& t) {
        if (this->contains(t)) {
            return;
        }
        size_t index = this->enumeration.size();
        this->enumeration.insert({t, index});
        this->nodes.push_back(new DisjointSetNode());
    }
    
    size_t get_class_subtree_size(const T& t) {
        DisjointSetNode* class_parent = this->get_node_class_parent(t);
        return class_parent->subtree_size;
    }
    
    void merge(const T& t1, const T& t2) {
        DisjointSetNode* u = this->get_node_class_parent(t1);
        DisjointSetNode* v = this->get_node_class_parent(t2);
        
        if (this->use_subtree_merge_heuristics()) {
            if (u->subtree_size < v->subtree_size) {
                std::swap(u, v);
            }
        }
        v->set_parent(u);
    }

private:
    DisjointSetNode* get_node(const T& t) {
        return this->nodes[this->get_node_index(t)];
    }
    
    DisjointSetNode* get_node_class_parent(const T& t) {
        return this->get_node_class_parent(this->get_node(t));
    }
    
    DisjointSetNode* get_node_class_parent(DisjointSetNode* node) {
        DisjointSetNode* class_parent = node->equivalence_class_parent();
        
        if (this->use_path_compression()) {
            while (node != class_parent) {
                auto next_node = node->parent;
                node->parent = class_parent;
                node = next_node;
            }
        }
        
        return class_parent;
    }
    
    size_t get_node_index(const T& t) {
        if (!this->contains(t)) {
            throw std::out_of_range("DisjointSetUnion out of range");
        }
        return this->enumeration[t];
    }
    
    bool use_path_compression() {
        return this->has_parameter(USE_PATH_COMPRESSION);
    }
    
    bool use_subtree_merge_heuristics() {
        return this->has_parameter(USE_SUBTREE_MERGE_HEURISTICS);
    }
    
    bool has_parameter(DisjointSetUnionParameters parameter) {
        return this->parameters.find(parameter) != this->parameters.end();
    }
    
    std::unordered_map<T, size_t> enumeration;

    std::vector<DisjointSetNode*> nodes;
    std::set<DisjointSetUnionParameters> parameters;
};

template<class T>
class RangeSumQuery {
public:
    RangeSumQuery(const std::vector<T>& range) {
        std::partial_sum(
            range.begin(), range.end(),
            std::back_inserter(this->partial_sums));
    }

    T query(size_t start, size_t end) {
        T result = this->partial_sums[end];
        if (start > 0) {
            result -= this->partial_sums[start - 1];
        }
        return result;
    }
private:
    std::vector<T> partial_sums;
};

struct Edge {
    Edge() {}
    Edge(int start, int end, int cost): start(start), end(end), cost(cost) {}
    int start;
    int end;
    int cost;
    
    std::tuple<int, int, int> to_tuple() const {
        return std::tie(this->cost, this->start, this->end);
    }
};

bool operator < (const Edge& e1, const Edge& e2) {
    return e1.to_tuple() < e2.to_tuple();
}

std::istream& operator >> (std::istream& in, Edge& e) {
    in >> e.start >> e.end >> e.cost;
    return in;
}

int main() {
    int nodes, queries;
    std::cin >> nodes >> queries;
    
    DisjointSetUnion<int> d(nodes);
    
    for (int node = 1; node <= nodes; ++node) {
        d.add(node);
    }
    
    std::vector<Edge> edges(nodes - 1);
    
    std::map<int, size_t> cost_to_number_of_paths;
    for (int i = 0; i < nodes - 1; ++i) {
        std::cin >> edges[i];
        cost_to_number_of_paths.insert({edges[i].cost, 0});
    }
    
    std::sort(edges.begin(), edges.end());
    
    for (auto edge: edges) {
        size_t new_paths = d.get_class_subtree_size(edge.start) * d.get_class_subtree_size(edge.end);
        d.merge(edge.start, edge.end);
        cost_to_number_of_paths[edge.cost] += new_paths;
    }
    
    std::map<int, size_t> cost_index;
    std::vector<size_t> number_of_paths;
    for (auto it: cost_to_number_of_paths) {
        cost_index[it.first] = number_of_paths.size();
        number_of_paths.push_back(it.second);
    }
    
    RangeSumQuery<size_t> query_answer(number_of_paths);
    
    int smallest_cost = cost_index.begin()->first;
    int greatest_cost = cost_index.rbegin()->first;
    
    for (int i = 0; i < queries; ++i) {
        int query_start, query_end;
        std::cin >> query_start >> query_end;
        
        if (query_end < smallest_cost || query_start > greatest_cost) {
            std::cout << "0\n";
            continue;
        }
        
        query_start = std::max(query_start, smallest_cost);
        query_end = std::min(query_end, greatest_cost);
        
        size_t query_start_index = cost_index.lower_bound(query_start)->second;
        auto query_end_it = cost_index.lower_bound(query_end);
        size_t query_end_index = query_end_it->second;
        if (query_end_it != cost_index.begin() && query_end_it->first != query_end) {
            query_end_index = (--query_end_it)->second;
        }
        
        std::cout << query_answer.query(query_start_index, query_end_index) << "\n";
    }
}
