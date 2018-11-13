
#include "TreeDB.h"

TreeDB::TreeDB() {
    root = NULL;
    probesCount = 0;
    activeCounter = 0;
}

TreeDB::~TreeDB() {
}

bool TreeDB::insert(DBentry* newEntry) {

    TreeDB treeBranch;

    if (root == NULL) {
        TreeNode* newTree = new TreeNode(newEntry);
        root = newTree;
        return true;
    } else {
        if (find(newEntry->getName()) == NULL) {

            if (root->getEntry()->getName() > newEntry->getName()) {
                treeBranch.root = root->getLeft();
                if (treeBranch.insert(newEntry))
                    root->setLeft(treeBranch.root);
            } else {
                treeBranch.root = root->getRight();
                if (treeBranch.insert(newEntry))
                    root->setRight(treeBranch.root);
            }
        } else return false;
    }
}

void TreeDB::countProbes(TreeNode* node, string name) {

    if (node->getEntry()->getName() > name) {
        probesCount++;
        if (node->getLeft() != NULL)
            countProbes(node->getLeft(), name);
    } else if (node->getEntry()->getName() < name) {
        probesCount++;
        if (node->getRight() != NULL)
            countProbes(node->getRight(), name);
    } else {
        probesCount++;
        return;
    }
    return;
}

DBentry* TreeDB::find(string name) {

    //when searching for a specific node, also get probes count
    probesCount = 0;
    if (root != NULL) {
        countProbes(root, name);
    }
    if (root == NULL) return NULL;
    else {

        TreeDB treeBranch;

        if (root->getEntry()->getName() > name) {
            treeBranch.root = root->getLeft();
            return (treeBranch.find(name));
        } else if (root->getEntry()->getName() < name) {
            treeBranch.root = root->getRight();
            return (treeBranch.find(name));
        } else {
            return (root->getEntry());
        }
    }

    return NULL;
}

TreeNode* TreeDB::findNodeToDelete(TreeNode* &parentptr, string name) {

    TreeNode* leftChild = NULL;
    TreeNode* rightChild = NULL;
    leftChild = parentptr->getLeft();
    rightChild = parentptr->getRight();

    if (parentptr->getEntry()->getName() > name) { //should look at the left
        if (leftChild->getEntry()->getName() == name) {
            return parentptr;
        } else {
            return (leftChild);
        }
    } else if (parentptr ->getEntry()->getName() < name) { //should look at the right
        if (rightChild->getEntry()->getName() == name) {
            return parentptr;
        } else {
            return (rightChild);
        }

    }
}

TreeNode* TreeDB::getLeftMax(TreeNode* ptr) {
    TreeNode* temp;
    if (ptr->getLeft() != NULL) ptr = ptr->getLeft();
    else return ptr;

    while (ptr->getRight() != NULL) {
        temp = ptr;
        ptr = ptr->getRight();
    }
    return ptr;

}

bool TreeDB::remove(string name) {
    TreeNode* ptr;

    if (root->getEntry()->getName() == name) {
        ptr = root;
        if (root->getLeft() == NULL && root->getRight() == NULL) {
            delete root;
            root = NULL;
        } else if (root->getLeft() != NULL && root->getRight() == NULL) {
            root = root->getLeft();
            delete ptr;
            ptr = NULL;
        } else if (root->getLeft() == NULL && root->getRight() != NULL) {
            root = root->getRight();
            delete ptr;
            ptr = NULL;
        } else { // two children
            //special case: when the left subtree of the node to delete is the
            //max node 
            if (root->getLeft() == getLeftMax(root)) {
                root->getLeft()->setRight(root->getRight());
                root = root->getLeft();
                delete ptr;
                ptr = NULL;
            } else {
                root = getLeftMax(root);
                root->setLeft(ptr->getLeft());
                root->setRight(ptr->getRight());
                delete ptr;
                ptr = NULL;
            }
        }
    } else {

        ptr = findNodeToDelete(root, name);
        if (ptr->getLeft() != NULL && ptr->getRight() != NULL) {
            while (ptr->getLeft()->getEntry()->getName() != name && ptr->getRight()->getEntry()->getName() != name)
                ptr = findNodeToDelete(ptr, name);

        }

        //now ptr is the pointer to delete
        if (ptr->getLeft() != NULL) {
            if (ptr->getLeft()->getEntry()->getName() == name) { //left should be deleted
                //leaf
                if (ptr->getLeft()->getLeft() == NULL && ptr->getLeft()->getRight() == NULL) {
                    delete ptr->getLeft();
                    ptr->setLeft(NULL);
                }//one child on the left
                else if (ptr ->getLeft()->getLeft() != NULL && ptr->getLeft()->getRight() == NULL) {
                    TreeNode* temp;
                    temp = ptr->getLeft();
                    ptr->setLeft(ptr->getLeft()->getLeft());
                    delete temp;
                    temp = NULL;
                }//one child on the right
                else if (ptr->getLeft()->getRight() != NULL && ptr ->getLeft()->getLeft() == NULL) {
                    TreeNode* temp;
                    temp = ptr->getLeft();
                    ptr->setLeft(ptr->getLeft()->getRight());
                    delete temp;
                    temp = NULL;
                } else { //two children
                    TreeNode* temp;
                    temp = ptr->getLeft();
                    if (ptr->getLeft()->getLeft() == getLeftMax(ptr->getLeft())) {
                        ptr->setLeft(getLeftMax(ptr->getLeft()));
                        ptr->getLeft()->setLeft(NULL);
                        ptr->getLeft()->setRight(temp->getRight());
                    } else {
                        ptr->setLeft(getLeftMax(ptr->getLeft()));
                        temp->getLeft()->setRight(ptr->getLeft()->getLeft());
                        ptr->getLeft()->setLeft(temp->getLeft());
                        ptr->getLeft()->setRight(temp->getRight());
                    }
                    delete temp;
                    temp = NULL;
                }
            }
        } else if (ptr->getRight() != NULL) {
            if (ptr->getRight()->getEntry()->getName() == name) { //right has to be deleted
                //leaf
                if (ptr->getRight()->getLeft() == NULL && ptr->getRight()->getRight() == NULL) {
                    delete ptr->getRight();
                    ptr->setRight(NULL);
                }//one child on the left
                else if (ptr ->getRight()->getLeft() != NULL && ptr->getRight()->getRight() == NULL) {
                    TreeNode* temp;
                    temp = ptr->getRight();
                    ptr->setRight(ptr->getRight()->getLeft());
                    delete temp;
                    temp = NULL;
                }//one child on the right
                else if (ptr->getRight()->getRight() != NULL && ptr ->getRight()->getLeft() == NULL) {
                    TreeNode* temp;
                    temp = ptr->getRight();
                    ptr->setRight(ptr->getRight()->getRight());
                    delete temp;
                    temp = NULL;
                } else { //two children
                    TreeNode *temp;
                    temp = ptr->getRight();
                    ptr->setRight(getLeftMax(ptr->getRight()));
                    //special case: when the left subtree of the node to delete is the
                    //max node 
                    if (ptr->getRight()->getLeft() == getLeftMax(ptr->getRight())) {
                        ptr->setRight(getLeftMax(ptr->getRight()));
                        (getLeftMax(ptr->getLeft()))->setLeft(temp->getLeft());
                        (getLeftMax(ptr->getLeft()))->setRight(NULL);
                    } else {
                        ptr->setRight(getLeftMax(ptr->getRight()));
                        (getLeftMax(ptr->getRight()))->setLeft(ptr->getRight()->getLeft());
                        (getLeftMax(ptr->getRight()))->setRight(ptr->getRight()->getRight());
                    }
                    delete temp;
                    temp = NULL;
                }
            }
        }
    }
}

void TreeDB::recursiveClear(TreeNode* currentNode) {
    if (currentNode == NULL) return;
    else {
        recursiveClear(currentNode->getLeft());

        recursiveClear(currentNode->getRight());

        currentNode->setLeft(NULL);
        currentNode->setRight(NULL);
        delete currentNode;
        currentNode = NULL;
        return;
    }

}

void TreeDB::clear() {

    recursiveClear(root);
    root = NULL;
    return;

}

void TreeDB::printProbes() const {
    cout << probesCount << endl;
}

int TreeDB::numOfActives(TreeNode* ptr) const {
    int counter = 0;

    if (ptr == NULL) return 0;
    else {
        if (ptr->getEntry()->getActive()) counter++;

        if (ptr->getLeft() != NULL) {
            counter = counter + numOfActives(ptr->getLeft());
        }
        if (ptr->getRight() != NULL) {
            counter = counter + numOfActives(ptr->getRight());
        }
    }
    return counter;
}

void TreeDB::countActive() const {
    cout << numOfActives(root) << endl;
}

ostream& operator<<(ostream& out, const TreeDB& rhs) {
    if (rhs.root == NULL) return out;
    else {
        out << rhs.root;
        return out;
    }
}

ostream& operator<<(ostream& out, TreeNode* rhs) {
    if (rhs ->getLeft() == NULL) {
        out << *(rhs->getEntry());
    } else {
        out << rhs->getLeft();
        out << *(rhs->getEntry());
    }

    if (rhs->getRight() == NULL) return out;
    else {
        out << rhs->getRight();
    }
    return out;
}