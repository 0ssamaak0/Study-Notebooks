#include <iostream>
using namespace std;

class BinaryHeap
{
private:
    const static int MAX_SIZE = 15;
    int heap[MAX_SIZE];
    int size = 0;

public:
    // find relatives

    static int parent(int i)
    {
        return (i - 1) / 2;
    }
    static int leftChild(int i)
    {
        return (2 * i) + 1;
    }
    static int rightChild(int i)
    {
        return (2 * i) + 2;
    }

    // Printing
    void print_heap()
    {
        for (int i = 0; i < size; i++)
        {
            cout << heap[i] << " ";
        }
        cout << "\n";
    }

    // insertion

    void insert(int data)
    {
        if (size >= MAX_SIZE)
        {
            cout << "Size exceeded\n";
            return;
        }
        heap[size] = data;
        size++;

        int i = size - 1;
        // if the element is not the root, and it's parent is smaller than it
        // (Sift up)
        while (i != 0 && heap[parent(i)] < heap[i])
        {
            swap(heap[parent(i)], heap[i]);
            i = parent(i);
        }
    }

    // deletion

    int extractMax()
    {
        // Select the root
        int maxItem = heap[0];

        // replace the root with the rightmost leftmost element (last inserted element)
        heap[0] = heap[size - 1];
        size--;

        // Sift down untill the heap property
        Heapify(size, 0);
        return maxItem;
    }

    // Restores the heap property (max)
    // (Sift down)
    void Heapify(int n, int i)
    {
        int left = leftChild(i);
        int right = rightChild(i);

        int largest = i;

        // find the largest among three nodes
        if (left <= n && heap[left] > heap[largest])
        {
            largest = left;
        }

        if (right <= n && heap[right] > heap[largest])
        {
            largest = right;
        }
        if (largest != i)
        {
            swap(heap[i], heap[largest]);
            Heapify(n, largest);
        }
    }

    // getting max and min
    int get_size()
    {
        return size;
    }

    int get_max()
    {
        return heap[0];
    }

    int get_min()
    {
        int min_val = heap[0];
        for (int i = 0; i < size; i++)
        {
            min_val = min(min_val, heap[i]);
        }
        return min_val;
    }

    int get_min_better()
    {
        // the min will be in the leaves
        int min_val = heap[0];
        for (int i = size / 2; i < size; i++)
        {
            // continue if it's not a leaf
            if ((2 * i + 1) < size || (2 * i + 2 < size))
            {
                continue;
            }
            if (heap[i] < min_val)
            {
                min_val = heap[i];
            }
        }
        return min_val;
    }

    // HeapSort
    void heapsort()
    {
        for (int i = size - 1; i >= 0; i--)
        {
            swap(heap[0], heap[i]);

            // Heapify root element to get highest element at root again
            Heapify(i - 1, 0);
        }
    }
};

// Sheet 6 - Q1
bool isHeap(int heapArr[], int ln)
{
    // iterate from the root, and check if each node has the heap property
    for (int i = 0; i < ln; i++)
    {
        int parent = heapArr[i];

        // the expressions will be shortcircuited

        // left child
        if ((2 * i) + 1 < ln && heapArr[(2 * i) + 1] >= heapArr[i])
        {
            return false;
        }
        // right child
        if ((2 * i) + 2 < ln && heapArr[(2 * i) + 2] >= heapArr[i])
        {
            return false;
        }
    }
    return true;
}

int main(void)
{
    int arr1[] = {10, 15, 8, 20, 14, 17, 12, 9, 13, 500};
    // cout << isHeap(arr1, 9) << "\n";

    int arr2[] = {100, 65, 8, 40, 34, 7, 2, 9, 13};
    // cout << isHeap(arr2, 9) << "\n";

    BinaryHeap h;
    for (int i = 0; i < 10; i++)
    {
        h.insert(arr1[i]);
    }
    cout << h.get_size() << "\n";
    h.print_heap();
    h.heapsort();
    h.print_heap();
}