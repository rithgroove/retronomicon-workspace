#include <nlohmann/json.hpp>

#include <fstream>
#include <iostream>
#include <optional>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace {

struct Choice {
    std::string text;
    std::string next;
};

struct Node {
    std::string id;
    std::string speaker;
    std::string background;
    std::string expression;
    std::string text;
    std::optional<std::string> next;
    std::vector<Choice> choices;
};

using NodeMap = std::unordered_map<std::string, Node>;

std::string readFile(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("failed to open conversation file: " + path);
    }

    return std::string(std::istreambuf_iterator<char>(file),
                       std::istreambuf_iterator<char>());
}

NodeMap parseNodes(const nlohmann::json& document) {
    if (!document.contains("nodes") || !document["nodes"].is_object()) {
        throw std::runtime_error("conversation JSON must contain an object named 'nodes'");
    }

    NodeMap nodes;
    for (const auto& [id, value] : document["nodes"].items()) {
        Node node;
        node.id = id;
        node.speaker = value.value("speaker", "");
        node.background = value.value("background", "");
        node.expression = value.value("expression", "");
        node.text = value.value("text", "");

        if (value.contains("next") && !value["next"].is_null()) {
            node.next = value["next"].get<std::string>();
        }

        if (value.contains("choices")) {
            for (const auto& choiceValue : value["choices"]) {
                node.choices.push_back(Choice{
                    choiceValue.value("text", ""),
                    choiceValue.value("next", "")
                });
            }
        }

        nodes.emplace(id, std::move(node));
    }

    return nodes;
}

void validateLinks(const NodeMap& nodes) {
    for (const auto& [id, node] : nodes) {
        if (node.next && nodes.count(*node.next) == 0) {
            throw std::runtime_error("node '" + id + "' points to missing next node '" + *node.next + "'");
        }

        for (const auto& choice : node.choices) {
            if (nodes.count(choice.next) == 0) {
                throw std::runtime_error("node '" + id + "' has choice '" + choice.text
                    + "' pointing to missing node '" + choice.next + "'");
            }
        }
    }
}

void printTraversal(const NodeMap& nodes) {
    auto current = nodes.find("start");
    if (current == nodes.end()) {
        throw std::runtime_error("conversation must contain a 'start' node");
    }

    std::unordered_set<std::string> visited;
    while (current != nodes.end()) {
        const Node& node = current->second;
        if (!visited.insert(node.id).second) {
            std::cout << "[loop detected at " << node.id << "]\n";
            return;
        }

        std::cout << node.id << ": ";
        if (!node.speaker.empty()) {
            std::cout << node.speaker;
        } else {
            std::cout << "narrator";
        }

        if (!node.expression.empty()) {
            std::cout << " (" << node.expression << ")";
        }

        if (!node.background.empty()) {
            std::cout << " [" << node.background << "]";
        }

        std::cout << "\n  " << node.text << "\n";

        if (!node.choices.empty()) {
            std::cout << "  choices:\n";
            for (std::size_t i = 0; i < node.choices.size(); ++i) {
                std::cout << "    " << i << ": " << node.choices[i].text
                          << " -> " << node.choices[i].next << "\n";
            }
            current = nodes.find(node.choices.front().next);
        } else if (node.next) {
            current = nodes.find(*node.next);
        } else {
            return;
        }
    }
}

} // namespace

int main(int argc, char** argv) {
    const std::string path = argc > 1
        ? argv[1]
        : RETRONOMICON_DEFAULT_CONVERSATION_PATH;

    try {
        const auto document = nlohmann::json::parse(readFile(path));
        const auto nodes = parseNodes(document);
        validateLinks(nodes);
        printTraversal(nodes);
    } catch (const std::exception& error) {
        std::cerr << "conversation-console: " << error.what() << "\n";
        return 1;
    }

    return 0;
}
