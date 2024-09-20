#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 26

typedef struct TrieNode
{
    struct TrieNode *child[MAX];
    int count;
};
struct Trie_node* Getnode()
{
    struct TrieNode *node = (struct TrieNode *)malloc(sizeof(struct TrieNode));

    node->count= 0;
    for(int i = 0; i < MAX; i++)
    {
        node->child[i] = NULL;
    }
    return node;
}
char *Insert(struct Trie_node **root, char *word)
{
    struct Trie_node * curr = (*root);
    int i = 0;
    int index = 0;
    while(word[i])
    {
        index = word[i] - 'a';
        if(curr.child[index] == NULL)
        {
            curr.child[index] = Getnode();
        }

    }
}

int main()
{

}