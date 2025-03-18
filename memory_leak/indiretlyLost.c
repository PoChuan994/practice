# include <stdio.h>

typedef struct Node{
    int val;
    struct Node *left;
    struct Node *right;
}Node;

void createTree()
{
    Node *root = malloc(sizeof(Node));
    root->val = 1;
    root->left = malloc(sizeof(Node));
    roor->right = malloc(sizeof(Node));
    /* 
     * without the state 'free(root)' will leads 
     * both directly lost and indirectly lost
     */
    // free(root);

    /* 
     * If only free left and right sub-node with causes
     * directly lost but without indirectly lost 
     */
    // free(root->left);
    // free(root->right);

}

int main()
{
    createTree();
    return 0;
}
