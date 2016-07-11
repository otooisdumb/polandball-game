#include "kdtree.h"
#include <QPoint>
#include <queue>
#include <vector>

KDTree::KDTree()
{
   this->size = 0;
}

std::vector<GameObject*> KDTree::kNN(GameObject * obj, int k){
    std::priority_queue<Node *> queue;
    kNNRecursive(obj, &queue, k, this->root, 0);
    std::vector<GameObject *> list;
    for(int i = 0; i < queue.size(); i++){
        list.push_back(queue.pop());
    }
    return list;
}

void KDTree::kNNRecursive(GameObject* obj, std::priority_queue<Node*> *queue, int k, Node * node, int level){
    if(node == 0){
       return;
    }
    int x = obj->getX();
    int y = obj->getY();
    int treeX = node->data->getX();
    int treeY = node->data->getY();
    int distance = (x-treeX)*(x-treeX) + (y-treeY)*(y-treeY);
    node->priority = distance;
    queue->push(node);
    if(queue->size() > k){
        queue->pop();
    }
    if(level % 2 == 0){
        if(x < treeX){
            kNNRecursive(obj, queue, k, node->left, ++level);
            Node * greatest = queue->pop();
            queue->push(greatest);
            if(queue->size() < k || treeX-x < greatest->priority){
                kNNRecursive(obj, queue, k, node->right, ++level)
            }
        }
        else{
            kNNRecursive(obj, queue, k, node->right, ++level);
            Node * greatest = queue->pop();
            queue->push(greatest);
            if(queue->size() < k || x-treeX < greatest->priority){
                kNNRecursive(obj, queue, k, node->left, ++level);
            }
        }
    }
    else{
        if(y < treeY){
            kNNRecursive(obj, queue, k, node->left, ++level);
            Node * greatest = queue->pop();
            queue->push(greatest);
            if(queue->size() < k || treeY - y < greatest->priority){
                kNNRecursive(obj, queue, k, node->right, ++level)
            }
        }
        else{
            kNNRecursive(obj, queue, k, node->right, ++level);
            Node * greatest = queue->pop();
            queue->push(greatest);
            if(queue->size() < k || y - treeY < greatest->priority){
                kNNRecursive(obj, queue, k, node->left, ++level)
            }
        }
    }
}

KDTree::insert(GameObject * obj){
    Node node = new Node();
    node.data = obj;
    if(size == 0){
        root = node;
    }
    else{
        insertRecursive(obj, root, 0);
    }
}

KDTree::insertRecursive(GameObject* obj,Node * compare,  int level){
    int x = obj->getX();
    int y = obj->getY();
    int treeX = compare->data->getX();
    int treeY = compare->data->getY();
    if(level % 2 == 0){
        if(x < treeX){
            if(compare->left == 0){
                compare->left = new Node();
                compare->left->data = obj;
            }
            else{
                insertRecursive(obj, compare->left, ++level);
            }
        }
        else{
            if(compare->right == 0){
                compare->right = new Node();
                compare->right->data = obj;
            }
            else{
                insertRecursive(obj, compare->right, ++level);
            }
        }
    }
    else{
        if(y < treeY){
            if(compare->left == 0){
                compare->left = new Node();
                compare->left->data = obj;
            }
            else{
                insertRecursive(obj, compare->left, ++level);
            }
        }
        else{
            if(compare->right == 0){
                compare->right = new Node();
                compare->right->data = obj;
            }
            else{
                insertRecursive(obj, compare->right, ++level);
            }
        }

    }
}
