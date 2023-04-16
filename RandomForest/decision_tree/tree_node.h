//
// Created by Konrad on 13.04.2023.
//
#include <vector>
#include <string>
#include "../type.h"

#ifndef RANDOMFOREST_TREE_NODE_H
#define RANDOMFOREST_TREE_NODE_H

//posibility to use union

class tree_node {
private:
    std::vector<tree_node> children;
    int value_int;
    double value_double;
    std::string value_string;
    Type type_value;

    int decision_index_value = -1;

public:

    void set_type_and_index_value(Type type, int index_col) {
        decision_index_value = index_col;
        type_value = type;
    }

    //empty node this is awfull
    tree_node(Type type) {
        if (type == Type::empty_type) {
            type_value = type;
        } else {
            throw std::invalid_argument("This constructor create only empty node");
        }

    }

    tree_node(int value_elem, int decision_index) {
        value_int = value_elem;
        set_type_and_index_value(Type::integer_type, decision_index);
    }

    tree_node(double value_elem, int decision_index) {
        value_double = value_elem;
        set_type_and_index_value(Type::double_type, decision_index);
    }

    tree_node(std::string value_elem, int decision_index) {
        value_string = value_elem;
        set_type_and_index_value(Type::string_type, decision_index);
    }

    Type get_type_value() {
        return type_value;
    };


    void add_child(tree_node child) {
        children.push_back(child);
    }

    std::vector<tree_node> get_children() {
        return children;
    }

    template<typename T>
    T get_value() {
        if (type_value == Type::string_type) {
            return value_string;
        } else if (type_value == Type::integer_type) {
            return value_int;
        } else {
            return value_double;
        }
    }

    int get_decision_index() {
        return decision_index_value;
    }

    bool is_root() {
        if (decision_index_value == -1 && type_value == Type::empty_type) {
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

        if (type_value == Type::integer_type) {

            return "[" + std::to_string(value_int) + "=" + std::to_string(decision_index_value) + "]";
        } else if (type_value == Type::string_type) {
            return "[" + value_string + "=" + std::to_string(decision_index_value) + "]";
        } else {
            return "[" + std::to_string(value_double) + "=" +  std::to_string(decision_index_value) + "]";
        }
    }

};


#endif //RANDOMFOREST_TREE_NODE_H
