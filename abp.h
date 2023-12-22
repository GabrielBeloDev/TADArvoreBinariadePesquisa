#ifndef __ABP_H_
#define __ABP_H_

typedef struct t_node
{
    void *data;
    struct t_node *left;
    struct t_node *right;
} TNode;

typedef struct _time_
{
    char nome[50];
} Time;

void *abpQuery(TNode *t, void *key, int (*cmp)(void *, void *));
TNode *abpInsert(TNode *t, void *data, int (*cmp)(void *, void *));
void simetrico(TNode *t, void (*visit)(void *));
TNode *abpRemove(TNode *t, void *key, int (*cmp)(void *, void *), void **data);
Time *abpGetMaxTime(TNode *t);
Time *abpGetMinTime(TNode *t);
void destroyTree(TNode *t);
TNode *abpGetMinNode(TNode *t);

#endif
