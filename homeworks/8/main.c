/* 
 * File:   main.c
 * Author: Magicmaster
 *
 * Created on 1. prosinec 2012, 10:51
 */

#ifndef __PROGTEST__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TELCO_NUMBERS 10

typedef struct TNode {
    char * m_Dest;
    struct TNode * m_Child[TELCO_NUMBERS];
} TNODE;

#endif /* __PROGTEST__ */

/* MOJE FUNKCE */

void initNode(TNODE ** node) {

    int i;
    
    *node = (TNODE*) malloc(sizeof (TNODE));
    for (i = 0; i < 10; i++) {
        (*node)->m_Child[i] = NULL;
        (*node)->m_Dest = NULL;
    }
}

int addStr(TNODE * node, const char *str) {
    node->m_Dest = (char*) malloc((strlen(str) + 1) * sizeof (char));
    strncpy(node->m_Dest, str, strlen(str) + 1);

    if (node->m_Dest == NULL) return 0;
    else return 1;
}

int isPrefixOK(const char *prefix) {
    unsigned int i;

    for (i = 0; i < strlen(prefix); i++)
        if (!isdigit(prefix[i])) return 0;

    return 1;
}

int recDelNode(TNODE *node, unsigned int level, const char *prefix) {
    /*
     * RETURN
     * -1 - wanted prefix doesnt exist
     * 0 - prefix deleted, node stays
     * 1 - prefix deleted and the whole node deleted
     */

    int i, canDel, recDelRes;

    
    if (level == strlen(prefix)) {
        if (node->m_Dest != NULL) {
            free(node->m_Dest);
            node->m_Dest = NULL;
        } else {
            return -1;
        }
    } else { // Not the final node
        if (node->m_Child[prefix[level] - '0'] != NULL) {
    
            recDelRes = recDelNode(node->m_Child[prefix[level] - '0'], level + 1, prefix);
            if (recDelRes == -1)
                return -1;
            else if (recDelRes == 0) {
                return 0;
            }
            else if (recDelRes == 1) {
                node->m_Child[prefix[level] - '0'] = NULL;
            }
        } else {
            return -1;
        }
    }

    canDel = 0;
    if (node->m_Dest == NULL) {
        canDel = 1;
        for (i = 0; i < TELCO_NUMBERS; i++) {
            if (node->m_Child[i] != NULL) {
    
                canDel = 0;
                break;
            } else{
            }
        }
    }

    if (canDel) {
        free(node);
        return 1;
    }

    return 0;
}

void recDelTree(TNODE *node, int level) {
    int i;

    if (node == NULL) return;

    for (i = 0; i < TELCO_NUMBERS; i++) {
        recDelTree(node->m_Child[i], level + 1);
        node->m_Child[i] = NULL;
    }


    free(node->m_Dest);

    free(node);

    return;
}

/* POZADOVANE FUNKCE */

void delTree(TNODE * root) {

    recDelTree(root, 0);

}

int addDest(TNODE ** root, const char * prefix, const char * dest) {
    unsigned int i;
    TNODE *curNode;

    if (!isPrefixOK(prefix)) return 0;

    if (*root == NULL) initNode(root);

    curNode = *root;
    for (i = 0; i < strlen(prefix); i++) {
        if (curNode->m_Child[prefix[i] - '0'] == NULL) {
            initNode(&(curNode->m_Child[prefix[i] - '0']));
        }
        curNode = curNode->m_Child[prefix[i] - '0'];
    }

    if (curNode->m_Dest != NULL) {
        free(curNode->m_Dest);
    }

    if (addStr(curNode, dest)) {
        return 1;
    } else {
        return 0;
    }
}

int delDest(TNODE ** root, const char *prefix) {

    int res;
    
    if (*root == NULL) return 0;
    if (!isPrefixOK(prefix)) return 0;

    res = recDelNode(*root, 0, prefix);
    
    if (res==-1) return 0;
    else if (res==0) return 1;
    else{ //res==1
        *root = NULL;
        return 1;
    }
}

const char * search(TNODE * root, const char * number) {
    unsigned int i;
    char *lastFound = NULL;
    TNODE *curNode;
    int index;

    if (!isPrefixOK(number)) return 0;
    if (root==NULL) return NULL;

    curNode = root;
    for (i = 0; i < strlen(number); i++) {
        index = number[i] - '0';
        
        if (curNode->m_Child[index] != NULL) {
            curNode = curNode->m_Child[index];
            if (curNode->m_Dest != NULL) {
                lastFound = curNode->m_Dest;
            } 
        } else {
            return lastFound;
        }
    }

    return lastFound;
}

/*
 * 
 */

#ifndef __PROGTEST__

int main(int argc, char** argv) {
    return (EXIT_SUCCESS);
}
#endif
