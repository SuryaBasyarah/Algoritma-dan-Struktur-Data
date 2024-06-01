#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int MAX_SIZE = 100;
const int MAX_LENGTH = 1000;

void swap(char& a, char& b) 
{
    char temp = a;
    a = b;
    b = temp;
}

void heapifyUp(char heap[], int size, int index) 
{
    while (index > 0) 
    {
        int parent = (index - 1) / 2;
        if (heap[index] > heap[parent]) 
        {
            swap(heap[index], heap[parent]);
            index = parent;
        } 
        else 
        {
            break;
        }
    }
}

void ReheapUp(char heap[], int size, int index) 
{
    heapifyUp(heap, size, index);
}

void heapifyDown(char heap[], int size, int index) 
{
    while (2 * index + 1 < size) 
    {
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;
        int largest = index;

        if (leftChild < size && heap[leftChild] > heap[largest]) 
        {
            largest = leftChild;
        }

        if (rightChild < size && heap[rightChild] > heap[largest]) 
        {
            largest = rightChild;
        }

        if (largest != index) 
        {
            swap(heap[index], heap[largest]);
            index = largest;
        } 
        else 
        {
            break;
        }
    }
}

void ReheapDown(char heap[], int size, int index) 
{
    heapifyDown(heap, size, index);
}

void enqueue(char heap[], int& size, char value) 
{
    if (size < MAX_SIZE) 
    {
        heap[size++] = value;
        ReheapUp(heap, size, size - 1);
    } 
    else 
    {
        std::cerr << "Priority queue is full.\n";
    }
}

void dequeue(char heap[], int& size) 
{
    if (size > 0) 
    {
        heap[0] = heap[--size];
        ReheapDown(heap, size, 0);
    } 
    else 
    {
        std::cerr << "Priority queue is empty.\n";
    }
}

bool isEmpty(int size) 
{
    return size == 0;
}

int main() {
    char priorityQueue[MAX_SIZE];
    int size = 0;

    vector<string> strings = {"introspective", "intelligent", "intellectual", "intimate", "intensive", "interesting", "internal", "into", "in", "intro"};

    bool printedLengths[MAX_LENGTH] = {false};

    
    for (int i = 0; i < strings.size(); i++) 
    {
        string& value = strings[i];
        int length = value.length();
        if (!printedLengths[length]) 
        {
            enqueue(priorityQueue, size, length);
            printedLengths[length] = true;
        }
    }

    enqueue(priorityQueue, size, string("interviewing").length());

    cout << "Sort by length: " << endl;
    while (!isEmpty(size)) 
    {
        int length = priorityQueue[0];
        dequeue(priorityQueue, size);

        for (int i = 0; i < strings.size(); i++) 
        {
            if (strings[i].length() == length) 
            {
                cout << strings[i] << " ";
            }
        }
    }
    cout << endl;

    cout << "Expected output: " << endl;
    cout << "introspective interviewing intellectual intelligent interesting intensive intimate internal intro into in" << endl;

    //output berbeda dengan expected output
    return 0;
}

