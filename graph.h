//
// Created by rrivas on 21/11/2023.
//

#ifndef PROG3_SEC3_2023_2_GRAFO_LISTA_ADYACENTE_GRAPH_H
#define PROG3_SEC3_2023_2_GRAFO_LISTA_ADYACENTE_GRAPH_H

#include <tuple>
#include <utility>
#include <unordered_map>
#include <forward_list>
#include <vector>
#include <algorithm>
#include <limits>

namespace utec {
    template <typename KeyType, typename ValueType, typename WeightType>
    class graph {
        // Tipos Auxiliares
        using AdjancentType = std::pair<size_t, WeightType>;
        using ItemType = std::pair<size_t, ValueType>;
        using AdjancentListType = std::forward_list<AdjancentType>;
        // Atributos
        std::unordered_map<KeyType, ItemType> vertices;
        std::vector<AdjancentListType> buckets;
    public:
        graph() = default;

        bool push_vertex(KeyType key, ValueType value) {
            if (vertices.try_emplace(key, std::size(buckets), value).second) {
                buckets.emplace_back();
                return true;
            }
            return false;
        }

        void push_edge(std::tuple<KeyType, KeyType, WeightType> edge) {
            // Obtener los campos de la tupla
            //const auto& [u, v, w] = edge;
            const auto& u = std::get<0>(edge);
            const auto& v = std::get<1>(edge);
            const auto& w = std::get<2>(edge);
            // Validacion de vertices
//            if (!vertices.contains(u))
//                throw std::runtime_error("Vertice u no existe");
//            if (!vertices.contains(v))
//                throw std::runtime_error("Vertice u no existe");
            if (!vertices.contains(u)) push_vertex(u, ValueType{});
            if (!vertices.contains(v)) push_vertex(v, ValueType{});
            auto idx_u = vertices[u].first;
            auto idx_v = vertices[v].first;
            buckets[idx_u].emplace_front(idx_v, w);
            buckets[idx_v].emplace_front(idx_u, w);
        }

        ValueType get_vertex(KeyType key) {
            return vertices[key].second;
        }

        WeightType get_edge(KeyType u, KeyType v) {
            auto idx_u = vertices[u].first;
            auto idx_v = vertices[v].first;
            auto it = std::find_if(
                    std::begin(buckets[idx_u]), std::end(buckets[idx_u]),
                    [idx_v](const auto& adj) {
                       return adj.first == idx_v;
                    });
            if (it != std::end(buckets[idx_u])) // encontrado
                return it->second;
            return std::numeric_limits<WeightType>::infinity();
        }

        template <typename UnaryFunction>
        void bfs(KeyType key, UnaryFunction fn) {

        }
    };
}

#endif //PROG3_SEC3_2023_2_GRAFO_LISTA_ADYACENTE_GRAPH_H
