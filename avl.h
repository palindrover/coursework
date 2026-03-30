#include <algorithm>
#include <queue>
#include <iostream>

template <typename T>
class AVL
{
private:
    struct node
    {
        node* left = nullptr;
        node* right = nullptr;
        T value;
        int height = 1;

        node(T x) : value(std::move(x)), height(1) {}
    };

    node* root = nullptr;
    int tree_size = 0;

public:
    AVL() = default;

    void insert(T x)
    {
        root = insertHelper(root, std::move(x));
    }

    bool find(T key) const
    {
        node* cur = root;
        while (cur)
        {
            if (cur->value == key) return true;
            cur = (key > cur->value) ? cur->right : cur->left;
        }
        return false;
    }

    void print() const
    {
        if (!root) 
		{
            std::cout << "Tree is empty\n";
            return;
        }

        std::queue<node*> q;
        q.push(root);

        while (!q.empty())
        {
            int levelSize = static_cast<int>(q.size());
            bool hasNonNull = false;

            for (int i = 0; i < levelSize; ++i)
            {
                node* cur = q.front();
                q.pop();

                if (cur == nullptr)
                {
                    std::cout << "* ";
                    q.push(nullptr);
                    q.push(nullptr);
                }
                else
                {
                    std::cout << cur->value << " ";
                    q.push(cur->left);
                    q.push(cur->right);
                    if (cur->left || cur->right) hasNonNull = true;
                }
            }
            std::cout << '\n';

            if (!hasNonNull && !q.empty()) while (!q.empty()) q.pop();
        }
    }

    int height() const { return getHeight(root); }
    int size() const { return tree_size; }

private:
    int getHeight(node* vertex) const
    {
        return vertex ? vertex->height : 0;
    }

    void updateHeight(node* vertex)
    {
        if (vertex)
            vertex->height = 1 + std::max(getHeight(vertex->left), getHeight(vertex->right));
    }

    int balanceFactor(node* vertex) const
    {
        return vertex ? getHeight(vertex->left) - getHeight(vertex->right) : 0;
    }

    node* rotateRight(node* y)
    {
        node* x = y->left;
        node* t = x->right;
        x->right = y;
        y->left = t;
        updateHeight(y);
        updateHeight(x);
        return x;
    }

    node* rotateLeft(node* x)
    {
        node* y = x->right;
        node* t = y->left;
        y->left = x;
        x->right = t;
        updateHeight(x);
        updateHeight(y);
        return y;
    }

    node* balance(node* node_ptr)
    {
        if (!node_ptr) return nullptr;

        updateHeight(node_ptr);
        int bf = balanceFactor(node_ptr);

        if (bf > 1)
        {
            if (balanceFactor(node_ptr->left) < 0) node_ptr->left = rotateLeft(node_ptr->left);
            return rotateRight(node_ptr);
        }

        if (bf < -1)
        {
            if (balanceFactor(node_ptr->right) > 0) node_ptr->right = rotateRight(node_ptr->right);
            return rotateLeft(node_ptr);
        }

        return node_ptr;
    }

    node* insertHelper(node* node_ptr, T x)
    {
        if (!node_ptr)
        {
            tree_size++;
            return new node(std::move(x));
        }

        if (x < node_ptr->value) node_ptr->left = insertHelper(node_ptr->left, std::move(x));
        else if (x > node_ptr->value) node_ptr->right = insertHelper(node_ptr->right, std::move(x));

        return balance(node_ptr);
    }
};
