//
// Created by Konrad on 13.04.2023.
//
#include <vector>
#include <string>
#include "../type.h"
#include "cnumpy/cnumpy.h"

#ifndef RANDOMFOREST_TREE_NODE_H
#define RANDOMFOREST_TREE_NODE_H



class tree_node {


private:
    std::vector<tree_node> children;
    Cnumpy value;
    bool is_empty = true;
    int level = 0;
    Cnumpy label;

    int decision_index_value = -1;

public:

    Cnumpy get_label(){
        return value;
    }


    Cnumpy get_value(){
        return value;
    }

    tree_node(int decision_index,int lvl,Cnumpy lab) : value(Cnumpy::of(0.0)),label(lab){
        decision_index_value = decision_index;
        is_empty = true;
        level = lvl;
    }

    void set_level(int lvl){
        level = lvl;
    }

    int get_level(){
        return level;
    }

    tree_node() : value(Cnumpy::of(0.0)),label(Cnumpy::of(0)) {
        is_empty = true;
    }

    tree_node(Cnumpy value_, int decision_index,int lvl,Cnumpy lab) : value(value_),label(lab) {
        decision_index_value = decision_index;
        is_empty = false;
        level =lvl;
    }

    tree_node(Cnumpy value_, int decision_index,int lvl, std::vector<tree_node> childs,Cnumpy lab) : value(value_),label(lab) {
        decision_index_value = decision_index;
        children = childs;
        is_empty = false;
        level =lvl;
    }


    void add_child(tree_node child) {
        children.push_back(child);
    }

    std::vector<tree_node> get_children() {
        return children;
    }


    int get_decision_index() {
        return decision_index_value;
    }

    bool is_root() {
        if (decision_index_value == -1 && is_empty) {
            return true;
        }

        return false;
    }

    bool is_leaf() {
        return children.empty();
    }

    std::string get_name() {
        if (is_root()) {
            return "root";
        }

        if (value.get_type_columns()[0] == Type::integer_type) {

            return "[" + std::to_string(value.get_xy_int(0,0)) + "=" + std::to_string(decision_index_value) + "]";
        } else if (value.get_type_columns()[0] == Type::string_type) {
            return "[" + value.get_xy_string(0,0) + "=" + std::to_string(decision_index_value) + "]";
        } else {
            return "[" + std::to_string(value.get_xy_double(0,0)) + "=" +  std::to_string(decision_index_value) + "]";
        }
    }

};




#endif //RANDOMFOREST_TREE_NODE_H
