//
// Created by Pavel Slabunov on 30.03.26.
//

#include <fstream>
#include <stdexcept>

#include "GraphSerializer.h"
#include "JsonConverters.h"

namespace GraphSerializer {
    void save(const RelationshipGraph &graph, const std::filesystem::path &path) {
        nlohmann::json json;
        json["people"] = graph.allPeople();
        json["relationships"] = graph.allRelationships();

        std::ofstream file(path);
        if (!file.is_open()) {
            throw std::runtime_error("Cannot open file for writing: " + path.string());
        }

        file << json.dump(4); // 4-space indented
    }

    RelationshipGraph load(const std::filesystem::path &path) {
        std::ifstream file(path);
        if (!file.is_open()) {
            throw std::runtime_error("Cannot open file for reading: " + path.string());
        }

        const nlohmann::json json = nlohmann::json::parse(file);

        RelationshipGraph graph;
        graph.loadPeople(json.at("people").get<std::vector<Person> >());
        graph.loadRelationships(json.at("relationships").get<std::vector<Relationship> >());

        return graph;
    }
} // namespace GraphSerializer
