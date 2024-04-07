using namespace s21;

template <typename Key, typename T>
void b_tree<Key, T>::copy(Node<Key, T>* node) {
    if (node) {
        insert_node(node->value);
        copy(node->left);
        copy(node->right);
    }
}

template <typename Key, typename T>
void b_tree<Key, T>::destroy(Node<Key, T>* node) {
    if (node) {
        destroy(node->left);
        destroy(node->right);
        delete node;
    }
}

template <typename Key, typename T>
b_tree<Key, T>::b_tree() : root(nullptr), size(0) {}

template <typename Key, typename T>
b_tree<Key, T>::b_tree(const b_tree &other) : root(nullptr), size(0) { copy(other.root); }

template <typename Key, typename T>
b_tree<Key, T>::~b_tree() { clear(); }

template <typename Key, typename T>
typename b_tree<Key, T>::b_tree& b_tree<Key, T>::operator=(const b_tree &t) noexcept {
    clear();
    copy(t.root);
    return *this;
}

template <typename Key, typename T>
Node<Key, T>* b_tree<Key, T>::first() const {
    Node<Key, T>* node = root;

    while (node && node->left) node = node->left;

    return node;
}

template <typename Key, typename T>
Node<Key, T>* b_tree<Key, T>::last() const {
    Node<Key, T>* node = root;

    while (node && node->right) node = node->right;

    return node;
}

template <typename Key, typename T>
Node<Key, T>* b_tree<Key, T>::find_node(const Key &key) const {
    Node<Key, T>* node = root;

    while (node && key != node->value.first) node = key < node->value.first ? node->left : node->right;

    return node;
}

template <typename Key, typename T>
Node<Key, T>* b_tree<Key, T>::insert_node(value_type v) {
    Node<Key, T>* inserted = nullptr;

    if (!root) {
        root = new Node(v);
        ++size;
        inserted = root;
    } else {
        Node<Key, T>* node = root;

        while (!(v.first > node->value.first && !node->right) && !(v.first < node->value.first && !node->left)) {
            node = v.first > node->value.first ? node->right : node->left;
        }

        if (v.first > node->value.first) {
            node->right = new Node(v);
            node->right->parent = node;
            ++size;
            inserted = node->right;
        } else if (v.first < node->value.first) {
            node->left = new Node(v);
            node->left->parent = node;
            ++size;
            inserted = node->left;
        }
    }

    return inserted;
}

template <typename Key, typename T>
void b_tree<Key, T>::clear() {
    destroy(root);
    root = nullptr;
    size = 0;
}

template <typename Key, typename T>
void b_tree<Key, T>::remove_node(Node<Key, T>* node) {
    Node<Key, T>* right = node->right;
    Node<Key, T>* left = node->left;

    if (node->parent) {
        if (node == node->parent->right) node->parent->right = nullptr;
        if (node == node->parent->left) node->parent->left = nullptr;
        size -= node->size();
        delete node;
    } else {
        delete root;
        root = nullptr;
        size = 0;
    }

    copy(right);
    copy(left);
    destroy(right);
    destroy(left);
}

template <typename Key, typename T>
size_t b_tree<Key, T>::get_size() const { return size; }