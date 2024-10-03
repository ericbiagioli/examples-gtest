#pragma once

/**************************************************************************

MODIFIQUE ESTE ARCHIVO Y EL CORRESPONDIENTE ARCHIVO .CC DE MANERA TAL QUE
LOS UNIT TESTS PASEN.

**************************************************************************/

#include <cstdlib>
#include <algorithm>

// Nodo de un árbol AVL
template <typename T>
struct AVLNode
{
    T data;
    AVLNode *left;
    AVLNode *right;
    int height;
    AVLNode(T value) : data(value), left(nullptr), right(nullptr), height(0) {}
};

// Clase AVL Tree
template <typename T>
class AVLTree {
private:
    AVLNode<T>* root;

    // Función para obtener la altura de un nodo
    int height(AVLNode<T>* node) {
        return node == nullptr ? 0 : node->height;
    }

    // Función para obtener el factor de balanceo de un nodo
    int getBalance(AVLNode<T>* node) {
        return node == nullptr ? 0 : height(node->left) - height(node->right);
    }

    // Rotaciones para mantener el balance del árbol
    AVLNode<T>* rightRotate(AVLNode<T>* y) {
        AVLNode<T>* x = y->left;
        AVLNode<T>* T2 = x->right;

        // Realizar la rotación
        x->right = y;
        y->left = T2;

        // Actualizar las alturas
        y->height = std::max(height(y->left), height(y->right)) + 1;
        x->height = std::max(height(x->left), height(x->right)) + 1;

        // Retornar la nueva raíz
        return x;
    }

    AVLNode<T>* leftRotate(AVLNode<T>* x) {
        AVLNode<T>* y = x->right;
        AVLNode<T>* T2 = y->left;

        // Realizar la rotación
        y->left = x;
        x->right = T2;

        // Actualizar las alturas
        x->height = std::max(height(x->left), height(x->right)) + 1;
        y->height = std::max(height(y->left), height(y->right)) + 1;

        // Retornar la nueva raíz
        return y;
    }

    // Función para insertar un nuevo nodo en el árbol
    AVLNode<T>* insert(AVLNode<T>* node, T key) {
        // 1. Insertar normalmente en un árbol binario de búsqueda
        if (node == nullptr)
            return new AVLNode<T>(key);

        if (key < node->data)
            node->left = insert(node->left, key);
        else if (key > node->data)
            node->right = insert(node->right, key);
        else
            return node; // No se permiten duplicados

        // 2. Actualizar la altura de este nodo ancestro
        node->height = 1 + std::max(height(node->left), height(node->right));

        // 3. Obtener el factor de balanceo y balancear el árbol si es necesario
        int balance = getBalance(node);

        // Si el nodo está desbalanceado, hay 4 casos:

        // Caso izquierda izquierda
        if (balance > 1 && key < node->left->data)
            return rightRotate(node);

        // Caso derecha derecha
        if (balance < -1 && key > node->right->data)
            return leftRotate(node);

        // Caso izquierda derecha
        if (balance > 1 && key > node->left->data) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // Caso derecha izquierda
        if (balance < -1 && key < node->right->data) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node; // Retornar el nodo (sin cambios si no es necesario balanceo)
    }

    // Recorrido inorder (en orden)
    void inorder(AVLNode<T>* root, std::vector<T> &ret) {
        if (root != nullptr) {
            inorder(root->left, ret);
            ret.push_back(root->data);
            inorder(root->right, ret);
        }
    }

    // Buscar un nodo en el árbol
    bool search(AVLNode<T>* node, T key) {
        if (node == nullptr)
            return false;
        if (key == node->data)
            return true;
        if (key < node->data)
            return search(node->left, key);
        return search(node->right, key);
    }

    // Obtener el valor mínimo del árbol
    AVLNode<T>* minValueNode(AVLNode<T>* node) {
        AVLNode<T>* current = node;
        while (current->left != nullptr)
            current = current->left;
        return current;
    }

    // Función para eliminar un nodo
    AVLNode<T>* deleteNode(AVLNode<T>* root, T key) {
        // 1. Realizar eliminación estándar en un árbol binario de búsqueda
        if (root == nullptr)
            return root;

        if (key < root->data)
            root->left = deleteNode(root->left, key);
        else if (key > root->data)
            root->right = deleteNode(root->right, key);
        else {
            // Nodo con un hijo o sin hijos
            if ((root->left == nullptr) || (root->right == nullptr)) {
                AVLNode<T>* temp = root->left ? root->left : root->right;

                if (temp == nullptr) {
                    temp = root;
                    root = nullptr;
                } else
                    *root = *temp;
                delete temp;
            } else {
                // Nodo con dos hijos
                AVLNode<T>* temp = minValueNode(root->right);

                root->data = temp->data;
                root->right = deleteNode(root->right, temp->data);
            }
        }

        if (root == nullptr)
            return root;

        // 2. Actualizar la altura del nodo actual
        root->height = 1 + std::max(height(root->left), height(root->right));

        // 3. Obtener el balance del nodo y balancearlo si es necesario
        int balance = getBalance(root);

        // Casos de balanceo
        if (balance > 1 && getBalance(root->left) >= 0)
            return rightRotate(root);

        if (balance > 1 && getBalance(root->left) < 0) {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }

        if (balance < -1 && getBalance(root->right) <= 0)
            return leftRotate(root);

        if (balance < -1 && getBalance(root->right) > 0) {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root;
    }

public:
    AVLTree() : root(nullptr) {}

    // Función pública para insertar un nodo
    void insert(T key) {
        root = insert(root, key);
    }

    // Función pública para eliminar un nodo
    void deleteNode(T key) {
        root = deleteNode(root, key);
    }

    // Función pública para buscar un nodo
    bool search(T key) {
        return search(root, key);
    }

    // Función pública para realizar un recorrido inorder
    std::vector<T> inorderTraversal() {
        std::vector<T> ret;
        inorder(root, ret);
        return ret;
        //std::cout << std::endl;
    }

    // Función pública para obtener la altura del árbol
    int height() {
        return height(root);
    }

    // Función pública para verificar si el árbol está balanceado
    bool isBalanced() {
        return abs(getBalance(root)) <= 1;
    }
};
