#include <bits/stdc++.h>
using namespace std;

class Node
{
private:
    int data;
    Node *next;

public:
    Node(int d)
    {
        this->data = d;
        this->next = nullptr;
    }
    void set_next(Node *next)
    {
        this->next = next;
    }
    Node *get_next()
    {
        return this->next;
    }
    int get_data()
    {
        return this->data;
    }
    friend class LinkedList;
};

class LinkedList
{
private:
    Node *head;

public:
    LinkedList()
    {
        head = NULL;
    }

    Node *get_head()
    {
        return this->head;
    }

    bool empty()
    {
        return head == NULL;
    }

    int length()
    {
        Node *temp = head;
        int length = 0;
        while (temp != NULL)
        {
            length++;
            temp = temp->next;
        }
        return length;
    }

    void push_front(int num)
    {
        Node *new_head = new Node(num);
        new_head->next = head;
        head = new_head;
    }

    void pop_front()
    {
        if (this->empty())
        {
            return;
        }
        Node *temp = head;
        head = head->next;
        delete (temp);
    }

    void push_back(int num);

    void pop_back()
    {
        if (this->empty())
        {
            return;
        }
        if (!head->next)
        {
            delete (head);
            head = NULL;
            return;
        }
        Node *temp = head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        delete (temp->next);
        temp->next = NULL;
    }
    void print(Node *head)
    {
        if (!head)
        {
            return;
        }
        cout << head->data << "\n";
        print(head->next);
    }
    void print_reverse(Node *head)
    {
        if (head == NULL)
        {
            return;
        }
        print(head->next);
        cout << head->data << "\n";
    }
    bool contains(int d)
    {
        Node *temp = head;
        while (temp)
        {
            if (temp->data == d)
            {
                return true;
            }
            temp = temp->next;
        }
        return false;
    }
    void clear()
    {
        while (!this->empty())
        {
            pop_front();
        }
    }
    ~LinkedList()
    {
        clear();
    }
};

void LinkedList::push_back(int num)
{
    if (this->empty())
    {
        push_front(num);
        return;
    }
    Node *temp = head;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = new Node(num);
}

int main(void)
{
    LinkedList l;
    l.push_back(15);
    l.push_back(16);
    l.push_back(17);
    l.push_back(18);
    l.push_back(19);

    l.print(l.get_head());
    cout << l.get_head()->get_data() << "\n";
    cout << l.get_head()->get_next() << "\n";
}
