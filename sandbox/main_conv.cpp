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
        std::cout 
            << node->getSpeaker() 
            << " (" << node->getExpression() << "): " 
            << node->getText() << "\n";

        const auto& choices = node->getChoices();
        if (!choices.empty()) {
            std::cout << "Choices:\n" << std::endl;
            for (size_t i = 0; i < choices.size(); ++i) {
                std::cout << "  " << i << ") " << choices[i].getText() << "\n";
            }
            // Auto-pick first choice for testing
            scene->setCurrentNode(choices[0].getNext());
        } else if (node->getNext().has_value()) {
            scene->setCurrentNode(node->getNext().value());
        } else {
            break; // End
        }

        node = scene->getCurrentNode();
    }

    return 0;
}
