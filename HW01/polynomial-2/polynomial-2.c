#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int coeff;
    int exp;
    struct node* next;
} Pnode, * plink;

typedef struct {
    struct node* head;
} polynomial;

void Create(polynomial* p) {
    plink pn, pre, q;
    p->head = (plink)malloc(sizeof(Pnode));
    p->head->exp = -1;
    p->head->next = p->head;
    for (;;) {
        pn = (plink)malloc(sizeof(Pnode));
        scanf("%d", &pn->coeff);
        scanf("%d", &pn->exp);
        if (pn->exp < 0) break;
        pre = p->head;
        q = p->head->next;
        while (q && q->exp > pn->exp) {
            pre = q;
            q = q->next;
        }
        pn->next = q;
        pre->next = pn;
    }
}

void Output(polynomial p) {
    plink q;
    int flag = 1;
    q = p.head->next;
    if (!q) {
        return;
    }
    while (q != p.head) {
        if (!flag && (q->coeff > 0)) printf(" ");
        flag = 0;
        if (q->coeff == 0) return;
        printf("%d", q->coeff);
        switch (q->exp) {
            case 0: break;
            case 1: printf(" "); break;
            default: printf(" %d", q->exp); break;
        }
        q = q->next;
    }
}

void Add(polynomial* px, polynomial* qx) {
    plink q, q1 = qx->head, p, p1, temp;
    p = px->head->next;
    p1 = px->head;
    q = q1->next;
    while (p->exp >= 0) {
        while (p->exp < q->exp) {
            q1 = q;
            q = q->next;
        }
        if (p->exp == q->exp) {
            q->coeff = q->coeff + p->coeff;
            if (q->coeff == 0) {
                q1->next = q->next;
                free(q);
                q = q1->next;
                p = p->next;
            }
            else {
                q1 = q;
                q = q->next;
                p = p->next;
            }
        }
        else {
            temp = malloc(sizeof(Pnode));
            temp->coeff = p->coeff;
            temp->exp = p->exp;
            temp->next = q1->next;
            q1->next = temp;
            q1 = q1->next;
            p = p->next;
        }
    }
}

void Multiply(polynomial* px, polynomial* qx) {
    polynomial qx1, qx2;
    plink q1, q2, q3, q4, pre = NULL, q;
    qx1.head = (plink)malloc(sizeof(Pnode));
    qx1.head->exp = -1;
    qx1.head->next = qx1.head;
    q1 = px->head->next;
    q2 = qx->head->next;
    while (q2->exp != -1) {
        q3 = (plink)malloc(sizeof(Pnode));
        q3->coeff = q1->coeff * q2->coeff;
        q3->exp = q1->exp + q2->exp;
        if (qx1.head->next->exp == -1) {
            q3->next = qx1.head->next;
            qx1.head->next = q3;
            pre = qx1.head->next;
        }
        else {
            q3->next = qx1.head;
            pre->next = q3;
            pre = pre->next;
        }
        q2 = q2->next;
    }
    q1 = q1->next;
    while (q1->exp != -1) {
        q2 = qx->head->next; // Initialize q2 here
        qx2.head = (plink)malloc(sizeof(Pnode));
        qx2.head->exp = -1;
        qx2.head->next = qx2.head;
        while (q2->exp != -1) {
            q4 = (plink)malloc(sizeof(Pnode));
            q4->coeff = q1->coeff * q2->coeff;
            q4->exp = q1->exp + q2->exp;
            if (qx2.head->next->exp == -1) {
                q4->next = qx2.head->next;
                qx2.head->next = q4;
                pre = qx2.head->next;
            }
            else {
                q4->next = qx2.head;
                pre->next = q4;
                pre = pre->next;
            }
            q2 = q2->next;
        }
        Add(&qx2, &qx1);
        q1 = q1->next;
    }
    Output(qx1);
}

int main() {
    polynomial p, q;
    int x;
    Create(&p);
    Output(p);
    Create(&q);
    Output(q);
    scanf("%d", &x);
    switch (x) {
        case 0:
            Add(&p, &q);
            Output(q);
            break;
        case 1:
            Multiply(&p, &q);
            break;
        case 2:
            Add(&p, &q);
            Output(q);
            Multiply(&p, &q);
            break;
        default:
            break;
    }
    // Free dynamically allocated memory here
    return 0;
}
