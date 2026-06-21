#include "retronomicon/conversation/conversation_loader.h"
#include "retronomicon/conversation/conversation_state.h"

#include <iostream>
#include <stdexcept>
#include <string>
#include <unordered_set>

namespace {

void printTraversal(const retronomicon::conversation::ConversationDocument& document) {
    retronomicon::conversation::ConversationState state(document);
    std::unordered_set<std::string> visited;
    while (const auto* node = state.current()) {
        if (!visited.insert(node->id).second) {
            std::cout << "[loop detected at " << node->id << "]\n";
            return;
        }

        std::cout << node->id << ": ";
        if (!node->speaker.empty()) {
            std::cout << node->speaker;
        } else {
            std::cout << "narrator";
        }

        if (!node->expression.empty()) {
            std::cout << " (" << node->expression << ")";
        }

        if (!node->background.empty()) {
            std::cout << " [" << node->background << "]";
        }

        std::cout << "\n  " << node->text << "\n";

        if (!node->choices.empty()) {
            std::cout << "  choices:\n";
            for (std::size_t i = 0; i < node->choices.size(); ++i) {
                std::cout << "    " << i << ": " << node->choices[i].text
                          << " -> " << node->choices[i].next << "\n";
            }
            state.choose(0);
        } else if (node->next) {
            state.advance();
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
        const auto document = retronomicon::conversation::ConversationLoader::loadFromFile(path);
        const auto issues = document.validate();
        if (!issues.empty()) {
            throw std::runtime_error(issues.front().message);
        }
        printTraversal(document);
    } catch (const std::exception& error) {
        std::cerr << "conversation-console: " << error.what() << "\n";
        return 1;
    }

    return 0;
}
