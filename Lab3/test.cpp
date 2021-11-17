#include <iostream>
#include <queue>
#include <vector>
using namespace std;
enum RB_color
{
    RED,
    BLACK
};
struct RB_Node
{
    int key;
    RB_color color;
    RB_Node *left;
    RB_Node *right;
    RB_Node *p;
};
class RB_tree
{
private:
    RB_Node *root;
    RB_Node *nil;

public:
    RB_tree()
    {
        nil = new RB_Node{0, BLACK, nullptr, nullptr, nullptr};
        root = nil;
    }
    void left_rotate(RB_Node *x);
    void right_rotate(RB_Node *x);
    void insert_fixup(RB_Node *z);
    void insert_node(RB_Node *z);
    void insert_key(int key);
    void layerTraversal();
};
void RB_tree::left_rotate(RB_Node *x)
{
    RB_Node *y = x->right;
    x->right = y->left;
    if (y->left != nil)
    {
        y->left->p = x;
    }
    y->p = x->p;
    if (x->p == nil)
    {
        root = y;
    }
    else if (x == x->p->left)
    {
        x->p->left = y;
    }
    else
    {
        x->p->right = y;
    }
    y->left = x;
    x->p = y;
}
void RB_tree::right_rotate(RB_Node *x)
{
    RB_Node *y = x->left;
    x->left = y->right;
    if (y->right != nil)
    {
        y->right->p = x;
    }
    y->p = x->p;
    if (x->p == nil)
    {
        root = y;
    }
    else if (x == x->p->right)
    {
        x->p->right = y;
    }
    else
    {
        x->p->left = y;
    }
    y->right = x;
    x->p = y;
}
void RB_tree::insert_node(RB_Node *z)
{
    RB_Node *y = nil;
    RB_Node *x = root;
    while (x != nil)
    {
        y = x;
        if (z->key < x->key)
        {
            x = x->left;
        }
        else
        {
            x = x->right;
        }
    }
    z->p = y;
    if (y == nil)
    {
        root = z;
    }
    else if (z->key < y->key)
    {
        y->left = z;
    }
    else
    {
        y->right = z;
    }
    z->left = nil;
    z->right = nil;
    z->color = RED;
    insert_fixup(z);
}
void RB_tree::insert_fixup(RB_Node *z)
{
    while (z->p->color == RED)
    {
        if (z->p == z->p->p->left)
        {
            RB_Node *y = z->p->p->right;
            if (y->color == RED)
            {
                z->p->color = BLACK;
                y->color = BLACK;
                z->p->p->color = RED;
                z = z->p->p;
            }
            else 
            {
                if(z==z->p->right)
                {
                    z = z->p;
                    left_rotate(z);
                }
                z->p->color = BLACK;
                z->p->p->color = RED;
                right_rotate(z->p->p);
            }
        }
        else
        {
            RB_Node *y = z->p->p->left;
            if (y->color == RED)
            {
                z->p->color = BLACK;
                y->color = BLACK;
                z->p->p->color = RED;
                z = z->p->p;
            }
            else
            {
                if(z==z->p->left)
                {
                    z = z->p;
                    right_rotate(z);
                }
                z->p->color = BLACK;
                z->p->p->color = RED;
                left_rotate(z->p->p);
            }
        }
    }
    root->color = BLACK;
}
void RB_tree::layerTraversal()
{
    queue<RB_Node *> q;
    q.push(root);
    while (!q.empty())
    {
        for (int i = 0; i < q.size(); i++)
        {
            RB_Node *node = q.front();
            q.pop();
            cout << node->key << "," << node->color << " ";
            if (node->left != nil)
                q.push(node->left);
            if (node->right != nil)
                q.push(node->right);
        }
        cout << "\n";
    }
}
void RB_tree::insert_key(int key)
{
    RB_Node *node = new RB_Node({key, RED, nullptr, nullptr, nullptr});
    insert_node(node);
}
int main(int argc, char const *argv[])
{
    RB_tree rb_tree;
    int a[] = {12, 1, 9, 2, 0, 11, 7, 19, 4, 15, 18, 5, 14, 13, 10, 16, 6, 3, 8, 17};
    for (int i = 0; i < 20; i++)
    {
        rb_tree.insert_key(a[i]);
    }
    rb_tree.layerTraversal();
    return 0;
}