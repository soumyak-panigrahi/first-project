#ifndef __B_S_TREE__
#define __B_S_TREE__

//Required Libraries

#include <iostream>
#include <cmath>
#include <memory>

//!END OF Required Libraries

template<typename T> class BStrNode;
template<typename T> class bsTree;

//Aliases used for Data-type

template<typename T> using uPtrBStr = std::unique_ptr<BStrNode<T>>;

template<typename T> using wPtrBStr = std::weak_ptr<BStrNode<T>>;
template<typename T> using cwPtrBStr = std::weak_ptr<const BStrNode<T>>;
template<typename T> using wwPtrBStr = std::weak_ptr<std::weak_ptr<BStrNode<T>>>;

template<typename T> using sPtrBStr = std::shared_ptr<BStrNode<T>>;
template<typename T> using ssPtrBStr = std::shared_ptr<std::shared_ptr<BStrNode<T>>>;

template<typename T> using swPtrBStr = std::shared_ptr<std::weak_ptr<BStrNode<T>>>;
template<typename T> using wsPtrBStr = std::weak_ptr<std::shared_ptr<BStrNode<T>>>;

//!END OF Aliases used for Data-type

///Required Data-type

template<typename T>
struct BStrNode
{
    T data;
    wPtrBStr<T> p;
    sPtrBStr<T> left, right;
    bool flag;
    BStrNode(T input = T{}) : data{ input }, left{ nullptr }, right{ nullptr }, flag{ false } { }
    bool operator==(const BStrNode<T>& other) const { return (this->data == other.data); }
    bool operator!=(const BStrNode<T>& other) const { return (this->data != other.data); }
    bool operator>(const BStrNode<T>& other) const { return (this->data > other.data); }
    bool operator>=(const BStrNode<T>& other) const { return (this->data >= other.data); }
    bool operator<(const BStrNode<T>& other) const { return (this->data < other.data); }
    bool operator<=(const BStrNode<T>& other) const { return (this->data >= other.data); }
    operator T() const { return data; }
};

//!END OF Required Data-type

/******************** CLASS DEFINATION *************************/

template<typename T>
class bsTree
{
    sPtrBStr<T> root;
    size_t size, height;
    void clear() noexcept { root.reset(); size = 0; return; }
    void transplant(const wPtrBStr<T>&, const wPtrBStr<T>&);
public:
    bsTree() : root{ nullptr }, size{ 0 }, height{ 0 } { }
    size_t getSize() const noexcept { return this->size; }
    size_t getHeight() const noexcept { return this->height; }
    bool isBalanced() const noexcept;
    size_t subHeight(const wPtrBStr<T>&) const noexcept;
    void inorderTreeWalk() const noexcept;
    void postorderTreeWalk() const noexcept;
    wPtrBStr<T> treeSearch(T) const noexcept;
    T treeMax() const noexcept;
    wPtrBStr<T> treeMax(const wPtrBStr<T>&) const noexcept;
    T treeMin() const noexcept;
    wPtrBStr<T> treeMin(const wPtrBStr<T>&) const noexcept;
    wPtrBStr<T> treeSuccessor(const wPtrBStr<T>&) const noexcept;
    wPtrBStr<T> treePredecessor(const wPtrBStr<T>&) const noexcept;
    bool insert(T);
    T remove(const wPtrBStr<T>&) noexcept;
    void leftRotation(const wPtrBStr<T>&) noexcept;
    void rightRotation(const wPtrBStr<T>&) noexcept;
    /** Default destructor */
    virtual ~bsTree();
};

/*!!!!!!!!!!!!!!!!!!!!!!!!!!!! END OF CLASS DEFINATION !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/

/********************* CLASS METHODS *******************************/

template<typename T>
bool bsTree<T>::isBalanced() const noexcept
{
    size_t h{ log2(size + 1) };
    if (h <= height && height <= (2 * h)) // Compared To Red-Black Tree
        return true;
    return false;
}

template<typename T>
size_t bsTree<T>::subHeight(const wPtrBStr<T>& src) const noexcept
{
    if (src.expired())
        return 0;
    else {
        auto x{ src.lock() };
        size_t lheight{ this->subHeight(x->left) }, rheight{ this->subHeight(x->right) };
        if (lheight > rheight)
            return (lheight + 1);
        else
            return (rheight + 1);
    }
}

template<typename T>
void bsTree<T>::inorderTreeWalk() const noexcept
{
    auto x{ root };
    if (x) {
        sPtrBStr<T> prev{ nullptr };
        while (x) {
            if (x->p.lock() == prev && x->left) {
                prev = x;
                x = x->left;
            } else if ((prev == x->p.lock()) || (prev == x->left)) {
                std::cout << x->data << " ";
                prev = x;
                if (x->right)
                    x = x->right;
                else
                    x = x->p.lock();
            } else {
                prev = x;
                x = x->p.lock();
            }
        }
    }
    return;
}

template<typename T>
void bsTree<T>::postorderTreeWalk() const noexcept
{
    auto x{ root };
    if (x) {
        sPtrBStr<T> prev{ nullptr };
        while (x) {
            if (x->p.lock() == prev && x->right) {
                prev = x;
                x = x->right;
            } else if (x->p.lock() == prev || x->right == prev) {
                std::cout << (x->data) << " ";
                prev = x;
                if (x->left)
                    x = x->left;
                else
                    x = x->p.lock();
            } else {
                prev = x;
                x = x->p.lock();
            }
        }
    }
    return;
}

template<typename T>
wPtrBStr<T> bsTree<T>::treeSearch(T data) const noexcept
{
    auto x{ root };
    while (x || x->data != data) {
        if (x->data >= data)
            x = x->left;
        else
            x = x->right;
    }
    return wPtrBStr<T>(x);
}

template<typename T>
T bsTree<T>::treeMin() const noexcept
{
    auto x{ root };
    while (x->left)
        x = x->left;
    return x->data;
}

template<typename T>
wPtrBStr<T> bsTree<T>::treeMin(const wPtrBStr<T>& src) const noexcept
{
    auto x{ src.lock() };
    while (x->left)
        x = x->left;
    return x;
}

template<typename T>
T bsTree<T>::treeMax() const noexcept
{
    auto x{ root };
    while (x->right)
        x = x->right;
    return x->data;
}

template<typename T>
wPtrBStr<T> bsTree<T>::treeMax(const wPtrBStr<T>& src) const noexcept
{
    auto x{ src.lock() };
    while (x->right)
        x = x->right;
    return x;
}

template<typename T>
wPtrBStr<T> bsTree<T>::treeSuccessor(const wPtrBStr<T>& x) const noexcept
{
    if (x->right)
        return this->treeMin(x->right);
    auto y{ (x->p).lock() };
    while (y && x == y->right) { // (x == y->right) :== (x->data >= y->data)
        x = y;
        y = y->p;
    }
    return wPtrBStr<T>(y);
}

template<typename T>
wPtrBStr<T> bsTree<T>::treePredecessor(const wPtrBStr<T>& x) const noexcept
{
    if (x->left)
        return this->treeMax(x->left);
    auto y{ x->p.lock() };
    while (y && x == y->left) {
        x = y;
        y = y->p;
    }
    return wPtrBStr<T>(y);
}

template<typename T>
bool bsTree<T>::insert(T data)
{
    size_t ht{ 0 };
    sPtrBStr<T> y{ nullptr }, x{ root };
    while (x.get() != nullptr) {
        y = x;
        if (data == x->data)
            x->flag ^= true;
        if (data < x->data || x->flag)
            x = x->left;
        else
            x = x->right;
        ht++;
    }
    auto z = std::make_shared<BStrNode<T>>();
    if (z.get() == nullptr)
        return false;
    z->data = data;
    z->p = y;
    if (root.get() != nullptr) {
        if (z->data < y->data)
            y->left = z;
        else
            y->right = z;
    } else
        root = z;
    if (ht > height)
        height = ht;
    size++;
    return true;
}

template<typename T>
void bsTree<T>::transplant(const wPtrBStr<T>& dest, const wPtrBStr<T>& src)
{
    auto u{ dest.lock() }, v{ src.lock() };
    sPtrBStr<T> p{ u->p.lock() };
    if (!p.get())
        root = v;
    else if (u.get() == p->left.get())
        p->left = v;
    else
        p->right = v;
    if (v)
        v->p = u->p;
    return;
}

template<typename T>
T bsTree<T>::remove(const wPtrBStr<T>& src) noexcept
{
    auto z{ src.lock() };
    if (z->left.get() == nullptr)
        this->transplant(z, z->right);
    else if (z->right.get() == nullptr)
        this->transplant(z, z->left);
    else {
        sPtrBStr<T> y{ (this->treeMin(z->right)).lock() };
        sPtrBStr<T> p{ y->p.lock() };
        if (p.get() != z.get()) {
            this->transplant(y, y->right);
            y->right = z->right;
            y->right->p = y;
        }
        this->transplant(z, y);
        y->left = z->left;
        y->left->p = y;
    }
    size--;
    return z->data;
}

template<typename T>
void bsTree<T>::leftRotation(const wPtrBStr<T>& src) noexcept
{
    if (!src.expired()) {
        auto x{ src.lock() };
        auto y{ x->right };
        x->right = y->left;
        if (y->left.get())
            y->left->p = x;
        y->p = x->p;
        auto px{ x->p.lock() };
        if (px.get() == nullptr)
            root = y;
        else if (px->left.get() == x.get())
            px->left = y;
        else
            px->right = y;
        y->left = x;
        x->p = y;
    }
    return;
}

template<typename T>
void bsTree<T>::rightRotation(const wPtrBStr<T>& src) noexcept
{
    if (!src.expired()) {
        auto y{ src.lock() };
        auto x{ y->left };
        y->left = x->right;
        x->p = y->p;
        if (x->right.get())
            x->right->p = y;
        auto py{ x->p.lock() };
        if (py.get() == nullptr)
            root = x;
        else if (py->left.get() == y.get())
            py->left = x;
        else
            py->right = x;
        x->right = y;
        y->p = x;
    }
}

/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! END OF CLASS METHODS !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/


#endif //__B_S_TREE__