#include <stdio.h>
#include <stdlib.h>

struct tree_node {
    int data;
    struct tree_node* left;
    struct tree_node* right;
};

struct tree_node *add_data(int data, struct tree_node *node);
char* prepare_string(int arg_count);
int count_unique(struct tree_node** forest, int amount);
int compare_trees(struct tree_node* tree1, struct tree_node* tree2);

void printTree(struct tree_node *treePtr, int p)
{
    int i;
        if(treePtr != NULL)
    {
        printTree(treePtr->right, p+3);
        for(i=0;i<p;i++)
        {
            printf(" ");
        }
        printf("%3d\n", treePtr->data);
        printTree(treePtr->left,p+3);
    }
}



int main() {
    int t_amount, e_amount;
    scanf("%d %d", &t_amount, &e_amount);
    struct tree_node *forest[t_amount]; //:)

    int value;
    for (int i = 0; i < t_amount; i++) {
        forest[i] = NULL;
        for (int j = 0; j < e_amount; j++) {
            scanf("%d", &value);
            forest[i] = add_data(value, forest[i]);
        }
    } 

    printf("%d\n", count_unique(forest, t_amount)); 

    for (int i = 0; i < t_amount; i++) free(forest[i]);
}



struct tree_node *add_data(int data, struct tree_node *node) {
    struct tree_node *new_node = calloc(1, sizeof(struct tree_node));
    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;

    if (node == NULL) { node = new_node; return node; }

    if (data < node->data) {
        if (node->left != NULL) { free(new_node); add_data(data, node->left); }
        else node->left = new_node;
    } else {
        if (node->right != NULL) { free(new_node); add_data(data, node->right); }
        else node->right = new_node;   
    }

    return node;
}

int count_unique(struct tree_node** forest, int amount) {
    int res = 0, flag = 1;
    for (int i = 0; i < amount; i++) {
        for (int j = 0; j < i; j++) {
            if (compare_trees(forest[i], forest[j])) {
                flag = 0;
                break;
            }
        }
        if (flag == 1) res++;
        flag = 1;
    }
    return res;
}

int compare_trees(struct tree_node* tree1, struct tree_node* tree2) {
    if (tree1 == NULL && tree2 == NULL) return 1;
    if ((tree1 == NULL && tree2 != NULL) || (tree1 != NULL && tree2 == NULL)) return 0;
    return compare_trees(tree1->left, tree2->left) && compare_trees(tree1->right, tree2->right);
}
