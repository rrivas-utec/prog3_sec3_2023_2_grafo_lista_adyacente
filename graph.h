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
#include <queue>
#include <stack>
#include <unordered_set>

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

        KeyType get_key(size_t index) {
            auto it = std::find_if(
                    std::begin(vertices), std::end(vertices),
                    [index](auto vx) {
                        return vx.second.first == index;
                    });
            if (it != std::end(vertices)) {
                return it->first;
            }
            return KeyType{};
        }
        auto get_not_visited(const auto& adj, const auto& visited) {
            return std::find_if (
                    std::begin(adj), std::end(adj),
                    [&visited](auto item) { return !visited.contains(item.first);
                    });
        }
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
            std::queue<size_t> q;
            std::unordered_set<size_t> visited;
            // El vertice seleccionando
            auto idx = vertices[key].first;
            // Agregar el vertice seleccionado al queue y visited
            q.push(idx);
            visited.insert(idx);
            // Paso # 2
            while (!q.empty()) {
                // Paso # 3
                idx = q.front();
                auto k = get_key(idx);
                fn(k);
                // Paso # 4
                q.pop();
                // Paso # 5
                for (const auto& adj: buckets[idx])
                    if (visited.insert(adj.first).second) q.push(adj.first);
            }
        }
        template <typename UnaryFunction>
        void dfs(KeyType key, UnaryFunction fn) {
            // Estructuras
            std::stack<size_t> s;
            std::unordered_set<size_t> visited;
            // El vertice seleccionando
            auto idx = vertices[key].first;
            // Agregar el vertice seleccionado al stack y visited
            s.push(idx);
            visited.insert(idx);
            while (!s.empty()) {
                // Paso # 3
                auto actual = s.top();
                // Paso # 4
                auto adj = buckets[actual];
                auto it = get_not_visited(adj, visited);
                if (it != std::end(adj)) { // No visitado
                    s.push(it->first);
                    visited.insert(it->first);
                }
                else {
                    fn(get_key(actual));
                    s.pop();
                }

            }

        }
    };
}

#endif //PROG3_SEC3_2023_2_GRAFO_LISTA_ADYACENTE_GRAPH_H
