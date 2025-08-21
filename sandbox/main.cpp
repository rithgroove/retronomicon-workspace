#include "retronomicon/lib/conversation/conversation_loader.h"
#include <iostream>

int main() {
    auto* scene = retronomicon::lib::conversation::ConversationLoader::loadFromJSON("asset/conversation/conversation.json");
    if (!scene) {
        std::cerr << "Failed to load conversation.\n";
        return 1;
    }

    scene->init();

    auto* node = scene->getCurrentNode();
    while (node) {
        std::cout << node->speaker << " (" << node->expression << "): " << node->text << "\n";

        if (!node->choices.empty()) {
            std::cout << "Choices:\n" <<std::endl;
            for (size_t i = 0; i < node->choices.size(); ++i) {
                std::cout << "  " << i << ") " << node->choices[i].getText() << "\n";
            }
            // Auto-pick first choice for testing
            scene->setCurrentNode(node->choices[0].getNext());
        } else if (node->next.has_value()) {
            scene->setCurrentNode(node->next.value());
        } else {
            break; // End
        }

        node = scene->getCurrentNode();
    }

    return 0;
}
