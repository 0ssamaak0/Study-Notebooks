#include <iostream>
#include <stdlib.h>
using namespace std;

#define MAX 1000
class Node
{
    int data;
    Node *next;
    Node(int data)
    {
        this->data = data;
        this->next = NULL;
    }
    friend class Stack_L;
    friend class LinkedList;
};

class LinkedList
{
    Node *head;

public:
    LinkedList()
    {
        head = NULL;
    }
    void pop_front()
    {
        Node *temp = head;
        head = head->next;
        delete temp;
    }
    void push_front(int data)
    {
        if (head == NULL)
        {
            head = new Node(data);
        }
        else
        {
            Node *temp = new Node(data);
            temp->next = head;
            head = temp;
        }
    }
    friend class Stack_L;
};
class Stack_L
{
    LinkedList l;

public:
    void push(int data)
    {
        l.push_front(data);
    }
    void pop()
    {
        l.pop_front();
    }
    int getTop()
    {
        return l.head->data;
    }
    bool isEmpty()
    {
        return (l.head == NULL);
    }
};
class Stack_A
{
    int top;
    int a[MAX];

public:
    Stack_A()
    {
        top = -1;
    }
    bool push(int x)
    {
        if (top >= (MAX - 1))
        {
            cout << "Stack Overflow";
            return false;
        }
        else
        {
            a[++top] = x;
            cout << x << " pushed into the Stack\n";
            return true;
        }
    }
    void pop()
    {
        if (top < 0)
        {
            cout << "Stack Underflow\n";
            return;
        }
        top--;
    }
    int getTop()
    {
        if (top < 0)
        {
            cout << "Staci is Empty";
            return 0;
        }
        else
        {
            return a[top];
        }
    }
    bool isEmpty()
    {
        return (top < 0);
    }
};
string string_reverse(string x)
{
    string r = x;
    Stack_A s;
    for (int i = 0; i < x.size(); i++)
    {
        s.push(x[i]);
    }
    for (int i = 0; i < x.size(); i++)
    {
        r[i] = (char)s.getTop();
        s.pop();
    }

    return r;
}

bool balanced_brackets(string x)
{
    Stack_L s;
    for (int i = 0; i < x.size(); i++)
    {
        if (x[i] == '{' || x[i] == '(' || x[i] == '[')
        {
            s.push(x[i]);
        }
        else
        {
            if (s.isEmpty())
            {
                return false;
            }
            if (x[i] == ')' && s.getTop() == '(' || x[i] == '}' && s.getTop() == '{' || x[i] == ']' && s.getTop() == '[')
            {
                s.pop();
            }
            else
            {
                return false;
            }
        }
    }
    if (s.isEmpty())
    {
        return false;
    }
    return true;
}

int main(void)
{
    cout << balanced_brackets("{[()]}") << "\n";
}