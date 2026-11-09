#include <iostream>
#include <string>
#include <stdexcept> 
using namespace std;
template<typename T>
class Queue {
private:
	T* data;
	int frontIndex;
	int rearIndex;
	int count;
	int capacity;

	void resize() {
		int newCapacity = capacity * 2;
		T* newData = new T[newCapacity];
		for (int i = 0; i < count; i++) {
			newData[i] = data[(frontIndex+i)% capacity];
		} delete[] data;
		data = newData;
		frontIndex = 0;
		rearIndex = count;
		capacity = newCapacity;
	}
public:
	// Constructors
	Queue(int initialCapacity = 10) 
		: capacity(initialCapacity), frontIndex(0), rearIndex(0), count(0) { 
		data = new T[capacity]; }
	~Queue() { delete[] data; }
	// Operators
	Queue(const Queue&) = delete;
	Queue& operator=(const Queue&) = delete;
	// Methods
	void enqueue(const T& value) { // Adds an element in the end
		if (count >= capacity) resize();
		data[rearIndex] = value;
		rearIndex = (rearIndex + 1) % capacity;
		count++;
	}

	T dequeue() { // Returns the first element and deletes it
		if (isEmpty()) throw underflow_error("Queue is empty.");
		T value = data[frontIndex];
		frontIndex = (frontIndex + 1) % capacity;
		count--;
		return value;
	}

	T front() const { // Returns the first element
		if (isEmpty()) throw underflow_error("Queue is empty.");
		return data[frontIndex];
	}

	void print() const { // Outputs the array
		cout << "[";
		for (int i = 0; i < count; i++) {
			if (i) cout << ", ";
			cout << data[(frontIndex + i) % capacity];
		} cout << "]" << endl;
	}

	bool isEmpty() const { return count == 0; }
	int size() const { return count; }
};

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
		int newCapacity = capacity * 2;
		Element* newElements = new Element[newCapacity];
		for (int i = 0; i < count; i++) {
			newElements[i] = elements[i];
		} delete[] elements;
		elements = newElements;
		capacity = newCapacity;
	}
public:
	// Constructors
	PriorityQueue(int initialCapacity = 10)
		: capacity(initialCapacity), count(0) {
		elements = new Element[capacity];
	}
	~PriorityQueue() { delete[] elements; }
	// Operators
	PriorityQueue(const PriorityQueue&) = delete;
	PriorityQueue& operator=(const PriorityQueue&) = delete;
	// Methods
	void enqueue(const T& value, int priority) { // Adds an element in the end
		if (count >= capacity) resize();
		elements[count].data = value;
		elements[count].priority = priority;
		count++;
	}
	T dequeue() { // Returns the priority elements
		if (isEmpty()) throw underflow_error("Queue is empty.");
		int maxID = 0;
		for (int i = 1; i < count; i++) {
			if (elements[i].priority > elements[maxID].priority) { // Found a higher priority
				maxID = i;
			} // Remembered the data
		} T result = elements[maxID].data;
		for (int i = maxID; i < count - 1; i++) { // Remove from the array
			elements[i] = elements[i + 1];
		} count--;
		return result;
	}

	T front() const { // Take the element
		if (isEmpty()) throw underflow_error("Queue is empty.");
		int maxID = 0;
		for (int i = 1; i < count; i++) {
			if (elements[i].priority > elements[maxID].priority) {
				maxID = i;
			}
		}
		return elements[maxID].data;
	}

	void print() const {
		cout << "[";
		for (int i = 0; i < count; i++) {
			if (i) cout << ", ";
			cout << elements[i].data << " (" << elements[i].priority << ")";
		}
		cout << "]" << endl;
	}

	bool isEmpty() const { return count == 0; }
	int size() const { return count; }
};

int main() {
	Queue<int> shopQueue;
	shopQueue.enqueue(1);
	shopQueue.enqueue(2);
	shopQueue.enqueue(3);
	shopQueue.enqueue(4);
	shopQueue.enqueue(5);

	cout << "Queue: ";
	shopQueue.print();

	cout << "Size: " << shopQueue.size() << endl;
	cout << "Testing front(): " << shopQueue.front() << endl;
	cout << "Testing dequeue(): " << shopQueue.dequeue() << endl;
	cout << "Queue after dequeue(): ";
	shopQueue.print();

	PriorityQueue<string> hospitalQueue;
	hospitalQueue.enqueue("Runny nose", 1);
	hospitalQueue.enqueue("Fracture", 5);
	hospitalQueue.enqueue("Cut", 3);
	hospitalQueue.enqueue("Heart attack", 10);
	hospitalQueue.enqueue("Bruise", 3);

	cout << "\nQueue: ";
	hospitalQueue.print();

	cout << "Priority:" << endl;
	cout << "1. " << hospitalQueue.dequeue() << endl;
	cout << "2. " << hospitalQueue.dequeue() << endl;
	cout << "3. " << hospitalQueue.dequeue() << endl;
	cout << "4. " << hospitalQueue.dequeue() << endl;
	cout << "5. " << hospitalQueue.dequeue() << endl;
	return 0;
}
