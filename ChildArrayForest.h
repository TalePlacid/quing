#ifndef CHILDARRAYFOREST_H
#define CHILDARRAYFOREST_H
#include <cstdint>
#include <vector>

using namespace std;

typedef int64_t Int;

template <typename T>
class ChildArrayForest{
public:
    class Node{
        friend class ChildArrayForest<T>;
    public:
        Node();
        Node(T element);
        Node(Node* parent, T element);
        ~Node();
        Node(const Node& source);
        Node& operator=(const Node& source);
    private:
        Node* parent;
        vector<Node*> childs;
        Int length;
        T element;
    };
public:
    ChildArrayForest();
    ~ChildArrayForest();
    ChildArrayForest(const ChildArrayForest& source);
    ChildArrayForest& operator=(const ChildArrayForest& source);

    Node* Insert(T object);
    Node* Insert(Node* parent, T object);
    void Delete(Node* node);
    Node* Update(Node* node, T object);
    template <typename Key>
    Node* Search(Key key, bool (*match)(const T& object, Key key));

    Int GetLength() const;
private:
    Node* CloneSubTree(const Node* source, Node* parent);
    template <typename Key>
    Node* SearchSubTree(Node* node, const Key& key, bool (*match)(const T& object, Key key));
private:
    vector<Node*> roots;
    Int length;
};

template <typename T>
ChildArrayForest<T>::Node::Node()
    :childs(0) {
    this->parent = 0;
    this->length = 0;
}

template <typename T>
ChildArrayForest<T>::Node::Node(T element)
    :childs(0) {
    this->parent = 0;
    this->length = 0;
    this->element = element;
}

template <typename T>
ChildArrayForest<T>::Node::Node(Node* parent, T element)
    :childs(0) {
    this->parent = parent;
    this->length = 0;
    this->element = element;
}

template <typename T>
ChildArrayForest<T>::Node::~Node(){
    if(this->length > 0){
        Int i = 0;
        while(i < this->length){
            delete this->childs[i];
            i++;
        }
    }
}

template <typename T>
ChildArrayForest<T>::ChildArrayForest()
    :roots(0) {
    this->length = 0;
}

template <typename T>
ChildArrayForest<T>::~ChildArrayForest(){
    Int i = 0;
    while (i < this->length)
    {
        delete this->roots[i];
        i++;
    }
}

template <typename T>
ChildArrayForest<T>::ChildArrayForest(const ChildArrayForest& source)
    :roots(source.length) {
    Int i = 0;
    while (i < source.length)
    {
        roots[i] = this->CloneSubTree(source.roots[i], 0);
        i++;
    }
    this->length = source.length;
}

template <typename T>
ChildArrayForest<T>& ChildArrayForest<T>::operator=(const ChildArrayForest& source){
    Int i = 0;
    while (i < this->length)
    {
        delete this->roots[i];
        this->roots[i] = 0;
        i++;
    }

    this->roots.resize(source.length);
    this->length = source.length;

    i = 0;
    while (i < source.length)
    {
        roots[i] = this->CloneSubTree(source.roots[i], 0);
        i++;
    }

    return *this;
}

template <typename T>
typename ChildArrayForest<T>::Node* ChildArrayForest<T>::Insert(T object){
    Node* node = new Node(object);
    this->roots.push_back(node);
    this->length++;

    return node;
}

template <typename T>
typename ChildArrayForest<T>::Node* ChildArrayForest<T>::Insert(Node* parent, T object){
    Node* node = new Node(parent, object);
    parent->childs.push_back(node);
    parent->length++;

    return node;
}

template <typename T>
void ChildArrayForest<T>::Delete(Node* node){
    if(node->parent == 0){
        Int i = 0;
        while (i < this->length)
        {
            if (this->roots[i] == node)
            {
                this->roots.erase(this->roots.begin() + i);
                this->length--;
                i = this->length;
            }
            else
            {
                i++;
            }
        }
    }
    else
    {
        Int i = 0;
        while (i < node->parent->length)
        {
            if (node->parent->childs[i] == node)
            {
                node->parent->childs.erase(node->parent->childs.begin() + i);
                node->parent->length--;
                i = node->parent->length;
            }
            else
            {
                i++;
            }
        }
    }

    delete node;
}

template <typename T>
typename ChildArrayForest<T>::Node* ChildArrayForest<T>::Update(Node* node, T object){
    node->element = object;

    return node;
}

template <typename T>
template <typename Key>
typename ChildArrayForest<T>::Node* ChildArrayForest<T>::Search(
    Key key,
    bool (*match)(const T& object, Key key)){
    Node* result = 0;
    Int i = 0;
    while (i < this->length)
    {
        result = this->SearchSubTree(this->roots[i], key, match);
        if (result != 0)
        {
            i = this->length;
        }
        else
        {
            i++;
        }
    }

    return result;
}

template <typename T>
Int ChildArrayForest<T>::GetLength() const{
    return this->length;
}

template <typename T>
typename ChildArrayForest<T>::Node* ChildArrayForest<T>::CloneSubTree(
    const typename ChildArrayForest<T>::Node* source,
    typename ChildArrayForest<T>::Node* parent) {
    Node *node = new Node(parent, source->element);
    if (source->length > 0)
    {
        node->childs.resize(source->length);
        node->length = source->length;
        Int i = 0;
        while (i < source->length)
        {
            node->childs[i] = this->CloneSubTree(source->childs[i], node);
            i++;
        }
    }

    return node;
}

template <typename T>
template <typename Key>
typename ChildArrayForest<T>::Node* ChildArrayForest<T>::SearchSubTree(
    Node* node,
    const Key& key,
    bool (*match)(const T& object, Key key)){
    Node* result = 0;
    if (match(node->element, key))
    {
        result = node;
    }
    else if (node->length > 0)
    {
        Int i = 0;
        while (i < node->length)
        {
            result = this->SearchSubTree(node->childs[i], key, match);
            if (result != 0)
            {
                i = node->length;
            }
            else
            {
                i++;
            }
        }
    }

    return result;
}

#endif // CHILDARRAYFOREST_H
