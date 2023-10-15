#include <iostream>
using namespace std;

struct Node {
    int coef;
    int exp;
    Node* next;
    Node(int c, int e) : coef(c), exp(e), next(NULL) {}
};

typedef Node* link;

void insertNode(link& head, int coefficient, int exponent)
{
    link newnode = new Node(coefficient, exponent);
    if (!head) {
        head = newnode;
    }
    else {
        link curr = head;
        link prev = NULL;
        while (curr && curr->exp < exponent) { 
            prev = curr;
            curr = curr->next;
        }
        if (curr && curr->exp == exponent) {
            curr->coef += coefficient;
            delete newnode; 
        }
        else {
            if (!prev) {
                newnode->next = head;
                head = newnode;
            }
            else {
                prev->next = newnode;
                newnode->next = curr;
            }
        }
    }
}

link addPolynomials(link poly1, link poly2)
{
    link result = NULL;
    link curr1 = poly1;
    link curr2 = poly2;

    while (curr1 && curr2)
    {
        if (curr1->exp == curr2->exp)
        {
            int sum_coeff = curr1->coef + curr2->coef;
            if (sum_coeff != 0) {
                insertNode(result, sum_coeff, curr1->exp);
            }
            curr1 = curr1->next;
            curr2 = curr2->next;
        }
        else if (curr1->exp < curr2->exp)
        {
            insertNode(result, curr1->coef, curr1->exp);
            curr1 = curr1->next;
        }
        else {
            insertNode(result, curr2->coef, curr2->exp);
            curr2 = curr2->next;
        }
    }
    while (curr1)
    {
        insertNode(result, curr1->coef, curr1->exp);
        curr1 = curr1->next;
    }
    while (curr2)
    {
        insertNode(result, curr2->coef, curr2->exp);
        curr2 = curr2->next;
    }

    link prev = NULL;
    link curr = result;
    while (curr)
    {
        if (curr->coef == 0)//清除系数为0项
        {
            if (prev)
            {
                prev->next = curr->next;
                delete curr;
                curr = prev->next;
            }
            else
            {
                link temp = curr;
                curr = curr->next;
                delete temp;
                result = curr;
            }
        }
        else
        {
            prev = curr;
            curr = curr->next;
        }
    }

    return result;
}

link multiPolynomials(link poly1, link poly2)
{
    link result = NULL;
    link curr1 = poly1;
    while (curr1)
    {
        link curr2 = poly2;
        while (curr2)
        {
            int result_exp = curr1->exp + curr2->exp;
            int result_coeff = curr1->coef * curr2->coef;
            link existing = result;
            bool found = false;
            while (existing)
            {
                if (existing->exp == result_exp)
                {
                    existing->coef += result_coeff;
                    found = true;
                    break;
                }
                existing = existing->next;
            }
            if (!found)
            {
                insertNode(result, result_coeff, result_exp);
            }
            curr2 = curr2->next;
        }
        curr1 = curr1->next;
    }

    link prev = NULL;
    link curr = result;
    while (curr)
    {
        if (curr->coef == 0)
        {
            if (prev)
            {
                prev->next = curr->next;
                delete curr;
                curr = prev->next;
            }
            else
            {
                link temp = curr;
                curr = curr->next;
                delete temp;
                result = curr;
            }
        }
        else
        {
            prev = curr;
            curr = curr->next;
        }
    }

    return result;
}


link reverseList(link head)
{
    link prev = NULL;
    link curr = head;
    link next = NULL;

    while (curr != NULL) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }

    return prev;
}

void deleteList(link& head) {
    link temp;
    while (head) {
        temp = head;
        head = head->next;
        if(temp)
            delete temp;
    }
    head = NULL;  
}


void Output(link poly,int option)
{
    link reversedPoly = reverseList(poly);
    link curr = reversedPoly;
    bool first = true;
    if (option == 1) {
        while (curr)
        {
            if (!first && curr->coef >= 0) {
                cout << " ";
            }
            cout << curr->coef;
            if (curr->exp >= 0) {
                cout << " " << curr->exp;
            }
            first = false;
            curr = curr->next;
        }
        cout << endl;
    }
    else {
        ;
    }
}

int main()
{
    link poly1 = NULL;
    link poly2 = NULL;

    int m, n, operation;
    cin >> m;
    for (int i = 0; i < m; ++i)
    {
        int coef, exp;
        cin >> coef >> exp;
        insertNode(poly1, coef, exp);
    }
    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        int coef, exp;
        cin >> coef >> exp;
        insertNode(poly2, coef, exp);
    }
    cin >> operation;
    link result1 = NULL;
    link result2 = NULL;
    link reversedPoly1 = reverseList(poly1);
    link reversedPoly2 = reverseList(poly2);
    Output(reversedPoly1,0);
    Output(reversedPoly2,0);

    if (operation == 0)
    {
        result1 = addPolynomials(poly1, poly2);
        link reversedResult1 = reverseList(result1);
        Output(reversedResult1,1);
    }
    else if (operation == 1) {
        result2 = multiPolynomials(poly1, poly2);
        link reversedResult2 = reverseList(result2);
        Output(reversedResult2,1);
    }
    else {
        result1 = addPolynomials(poly1, poly2);
        link reversedResult1 = reverseList(result1);
        Output(reversedResult1,1);
        result2 = multiPolynomials(poly1, poly2);
        link reversedResult2 = reverseList(result2);
        Output(reversedResult2,1);
    }
    deleteList(result1);
    deleteList(result2);
    deleteList(reversedPoly1);
    deleteList(reversedPoly2);

    return 0;
}