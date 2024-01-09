#pragma once

#include "drawable.hpp"
#include <iostream>

class Node {
public:
    Drawable* data;
    Node* next;
    Node* prev;
    
    Node(Drawable* data) : data(data), next(nullptr), prev(nullptr) {}
};

class LayeredDrawableList {
public:
    LayeredDrawableList() : head(nullptr) {}

    void insert(Drawable* drawable) {
        Node* newNode = new Node(drawable);
        if (!head) {
            head = newNode;
        } else {
            Node* current = head;
            while (current->next && current->next->data->getLayer() < drawable->getLayer()) {
                current = current->next;
            }
            if (current->data->getLayer() > drawable->getLayer()) {
                newNode->next = current;
                newNode->prev = current->prev;
                current->prev = newNode;
                if (newNode->prev)
                    newNode->prev->next = newNode;
                else {
                    head = newNode;
                }
            } else {
                newNode->prev = current;
                newNode->next = current->next;
                current->next = newNode;
            }
        }
    }

    void remove(Drawable* drawable) {
        Node* current = head;
        while (current) {
            if (current->data == drawable) {
                if (current->prev)
                    current->prev->next = current->next;
                else
                    head = current->next;
                if (current->next)
                    current->next->prev = current->prev;
                delete current;
                break;
            }
            current = current->next;
        }
    }

    void renderAll(SDL_Surface* mainSurface) const {
        Node* current = head;
        // std::cout << "Started render " << std::endl;
        while (current) {
            // std::cout << current->data->getLayer() << std::endl;
            current->data->updateSprite(mainSurface);
            current = current->next;
        }
    }

    void cleanupAll() const {
        Node* current = head;
        while (current) {
            current->data->cleanupSprite();
            current = current->next;
        }
    }
    
private:
    Node* head;
};