#include <stdio.h>
#include <stdlib.h>
#include "abp.h"

void *abpQuery(TNode *t, void *key, int (*cmp)(void *, void *))
{
    if (t != NULL)
    {
        int result = cmp(key, t->data);
        if (result == 0)
        {
            return t->data;
        }
        else if (result < 0)
        {
            return abpQuery(t->left, key, cmp);
        }
        else
        {
            return abpQuery(t->right, key, cmp);
        }
    }
    return NULL;
}

TNode *abpInsert(TNode *t, void *data, int (*cmp)(void *, void *))
{
    if (t != NULL)
    {
        int result = cmp(data, t->data);
        if (result <= 0)
        {
            t->left = abpInsert(t->left, data, cmp);
        }
        else
        {
            t->right = abpInsert(t->right, data, cmp);
        }
    }
    else
    {
        t = (TNode *)malloc(sizeof(TNode));
        if (t != NULL)
        {
            t->data = data;
            t->left = NULL;
            t->right = NULL;
        }
    }
    return t;
}

void simetrico(TNode *t, void (*visit)(void *))
{
    if (t != NULL)
    {
        simetrico(t->left, visit);
        visit(t->data);
        simetrico(t->right, visit);
    }
}

TNode *abpRemove(TNode *t, void *key, int (*cmp)(void *, void *), void **data)
{
    if (t != NULL)
    {
        int result = cmp(key, t->data);
        if (result < 0)
        {
            t->left = abpRemove(t->left, key, cmp, data);
        }
        else if (result > 0)
        {
            t->right = abpRemove(t->right, key, cmp, data);
        }
        else
        {
            *data = t->data;
            if (t->left == NULL)
            {
                TNode *temp = t->right;
                free(t);
                return temp;
            }
            else if (t->right == NULL)
            {
                TNode *temp = t->left;
                free(t);
                return temp;
            }
            TNode *temp = abpGetMinNode(t->right);
            t->data = temp->data;
            t->right = abpRemove(t->right, temp->data, cmp, &temp->data);
        }
    }
    return t;
}

Time *abpGetMaxTime(TNode *t)
{
    if (t != NULL)
    {
        while (t->right != NULL)
        {
            t = t->right;
        }
        return t->data;
    }
    return NULL;
}

Time *abpGetMinTime(TNode *t)
{
    if (t != NULL)
    {
        while (t->left != NULL)
        {
            t = t->left;
        }
        return t->data;
    }
    return NULL;
}

TNode *abpGetMinNode(TNode *t)
{
    if (t != NULL)
    {
        while (t->left != NULL)
        {
            t = t->left;
        }
    }
    return t;
}

void destroyTree(TNode *t)
{
    if (t != NULL)
    {
        destroyTree(t->left);
        destroyTree(t->right);
        free(t);
    }
}
