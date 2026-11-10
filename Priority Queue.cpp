#include <iostream>
#include <string>
using namespace std;
template<typename T>
class PriorityQueue {
private:
    struct Element {
        T data;
        int priority;
    };
    Element* elements;
    int count;
    int capacity;

    void resize() {
        capacity = capacity * 2;
        Element* newElements = new Element[capacity];
        for (int i = 0; i < count; i++) newElements[i] = elements[i];
        delete[] elements;
        elements = newElements;
    }

public:
    PriorityQueue(int initialCapacity = 10) // Deafault constructor
        : capacity(initialCapacity), count(0) {
        elements = new Element[capacity];
    }
    ~PriorityQueue() { delete[] elements; } // Destructor

    void push(const T& value, int priority) {
        if (count >= capacity) resize();
        elements[count].data = value;
        elements[count].priority = priority;
        count++;
    }

    T top() { // Founds maximum priority
        if (count == 0) throw underflow_error("PriorityQueue is empty.");
        int maxID = 0;
        for (int i = 1; i < count; i++) {
            if (elements[i].priority > elements[maxID].priority) {
                maxID = i;
            }
        } T result = elements[maxID].data;
        for (int i = maxID; i < count - 1; i++) {
            elements[i] = elements[i + 1];
        }
        count--;
        return result;
    }
    // Returns true, if element found and changes
    bool updatePriority(const T& value, int newPriority) {
        for (int i = 0; i < count; i++) {
            if (elements[i].data == value) { 
                elements[i].priority = newPriority; // Swaps the priority
                return true;
            }
        }
        return false; // Element not found
    }

    void print() const {
        cout << "[";
        for (int i = 0; i < count; i++) {
            if (i) cout << ", ";
            cout << elements[i].data << " (" << elements[i].priority << ")";
        }
        cout << "]" << endl;
    }
};
int main() {
    PriorityQueue<string> pq;
    pq.push("I", 4);
    pq.push("P", 1);
    pq.push("F", 5);
    pq.push("A", 3);
    pq.push("S", 2);

    cout << "Output: ";
    pq.print();

    cout << "\nUpdating priority in A..." << endl;
    pq.updatePriority("A", 6);

    cout << "After update: ";
    pq.print();

    cout << "\nFirst element: " << pq.top() << endl;
    cout << "Second element: " << pq.top() << endl;
    
    return 0;
}