//
//  Transform to Palindrome.cpp
//  Hackerrank
//
//  Created by Mikael Arakelian on 6/15/17.
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
    DisjointSetUnion(const std::set<DisjointSetUnionParameters>& parameters =
                     DefaultDisjointSetUnionParameters()): parameters(parameters) {
        this->equivalence_classes = 0;
    }
    
    ~DisjointSetUnion() {
        this->inverse_enumeration.clear();
        for (auto it = this->enumeration.begin(); it != this->enumeration.end(); ++it) {
            auto node = it->second;
            it->second = nullptr;
            delete node;
        }
    }
    
    bool contains(const T& t) {
        return enumeration.find(t) != enumeration.end();
    }
    
    void add(const T& t) {
        if (this->contains(t)) {
            return;
        }
        DisjointSetNode* new_node = new DisjointSetNode();
        this->enumeration.insert({t, new_node});
        this->inverse_enumeration.insert({new_node, t});
        this->equivalence_classes++;
    }
    
    size_t get_class_subtree_size(const T& t) {
        DisjointSetNode* class_parent = this->get_node_class_parent(t);
        return class_parent->subtree_size;
    }
    
    size_t get_equivalence_classes_count() {
        return this->equivalence_classes;
    }
    
    void merge(const T& t1, const T& t2) {
        DisjointSetNode* u = this->get_node_class_parent(t1);
        DisjointSetNode* v = this->get_node_class_parent(t2);
        
        if (this->use_subtree_merge_heuristics()) {
            if (u->subtree_size < v->subtree_size) {
                std::swap(u, v);
            }
        }
        if (u != v) {
            this->equivalence_classes--;
            v->set_parent(u);
        }
    }
    
    T get_node_class_parent_value(T& t) {
        DisjointSetNode* parent_node = this->get_node_class_parent(t);
        return inverse_enumeration[parent_node];
    }
    
private:
    DisjointSetNode* get_node(const T& t) {
        if (!this->contains(t)) {
            return nullptr;
        }
        return this->enumeration[t];
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
    
    bool use_path_compression() {
        return this->has_parameter(USE_PATH_COMPRESSION);
    }
    
    bool use_subtree_merge_heuristics() {
        return this->has_parameter(USE_SUBTREE_MERGE_HEURISTICS);
    }
    
    bool has_parameter(DisjointSetUnionParameters parameter) {
        return this->parameters.find(parameter) != this->parameters.end();
    }
    
    std::unordered_map<T, DisjointSetNode*> enumeration;
    std::unordered_map<DisjointSetNode*, T> inverse_enumeration;
    size_t equivalence_classes;
    std::set<DisjointSetUnionParameters> parameters;
};

int longest_palindromic_subsequence(const std::vector<int>& v) {
    const int n = (int) v.size();
    
    std::vector< std::vector<int> > dp(n, std::vector<int>(n + 1));
    for (int i = 0; i < n; ++i) {
        dp[i][1] = 1;
        dp[i][0] = 0;
    }
    for (int length = 2; length <= n; ++length) {
        for (int i = 0; i + length <= n; ++i) {
            if (v[i] == v[i + length - 1]) {
                dp[i][length] = 2 + dp[i + 1][length - 2];
            }
            else {
                dp[i][length] = std::max(dp[i][length - 1], dp[i + 1][length - 1]);
            }
        }
    }
    return dp[0][n];
}



int main() {
    DisjointSetUnion<int> equivalence_class;
    
    int letters, relations, word_length;
    std::cin >> letters >> relations >> word_length;
    
    for (int i = 1; i <= letters; ++i) {
        equivalence_class.add(i);
    }
    
    for (int i = 0; i < relations; ++i) {
        int letter_1, letter_2;
        std::cin >> letter_1 >> letter_2;
        equivalence_class.merge(letter_1, letter_2);
    }
    
    std::vector<int> word_sequence(word_length);
    for (int i = 0; i < word_length; ++i) {
        int letter;
        std::cin >> letter;
        word_sequence[i] = equivalence_class.get_node_class_parent_value(letter);
    }
    
    std::cout << longest_palindromic_subsequence(word_sequence);
}
