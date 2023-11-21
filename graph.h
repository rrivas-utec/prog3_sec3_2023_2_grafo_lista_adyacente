//
// Created by rrivas on 21/11/2023.
//

#ifndef PROG3_SEC3_2023_2_GRAFO_LISTA_ADYACENTE_GRAPH_H
#define PROG3_SEC3_2023_2_GRAFO_LISTA_ADYACENTE_GRAPH_H

#include <tuple>

namespace utec {
    template <typename KeyType, typename ValueType, typename WeightType>
    class graph {
    public:
        graph() = default;

        bool push_vertex(KeyType key, ValueType value) {
            return bool();
        }

        bool push_edge(std::tuple<KeyType, KeyType, WeightType> edge) {
            return bool();
        }

        ValueType get_vertex(KeyType key) {
            return ValueType{};
        }

        WeightType get_edge(KeyType a, KeyType b) {
            return WeightType{};
        }
    };
}

#endif //PROG3_SEC3_2023_2_GRAFO_LISTA_ADYACENTE_GRAPH_H
