#include <iostream>
#include <string>
#include <stdexcept> 
using namespace std;
template<typename T>
class Stack {
private:
	T* data;
	int topIndex;
	int capacity;

	void resize() {
		int newCapacity = capacity * 2;
		T* newData = new T[newCapacity];
		for (int i = 0; i <= topIndex; i++) {
			newData[i] = data[i];
		} delete[] data;
		data = newData;
		capacity = newCapacity;
	}
public:
	// Constructors
	Stack(int initialCapacity = 10) : capacity(initialCapacity), topIndex(-1) { data = new T[capacity]; }
	~Stack() { delete[] data; }
	// Methods
	void push(const T& value) { // Adds an element in the end
		if (topIndex >= capacity - 1) resize();
		data[++topIndex] = value;
	}

	T pop() { // Returns the last element and deletes it
		if (isEmpty()) throw underflow_error("Stack is empty.");
		return data[topIndex--];
	}

	T top() const { // Returns the last element
		if (isEmpty()) throw underflow_error("Stack is empty.");
		return data[topIndex];
	}

	void print() const { // Outputs the array
		cout << "[";
		for (int i = 0; i <= topIndex; i++) {
			if (i) cout << ", ";
			cout << data[i];
		} cout << "]" << endl;
	}

	bool isEmpty() const { return topIndex == -1; }
	int size() const { return topIndex + 1; }
};
// Stack sorting function
template<typename T>	
void sortStack(Stack<T>& s) {
	Stack<T> addStack;
	while (!s.isEmpty()) { 
		T temp = s.pop(); // It takes out the top element and removes it.
		while (!addStack.isEmpty() && addStack.top() > temp) {
			s.push(addStack.pop()); // Moving it back to s.
		} addStack.push(temp);
	}
	while (!addStack.isEmpty()) { // Moving everything back to s.
		s.push(addStack.pop());
	}
}

int main() {
	Stack<int> p;

	p.push(15);
	p.push(3);
	p.push(42);
	p.push(8);
	p.push(21);
	p.push(5);

	cout << "Output: ";
	p.print();

	cout << "Size: " << p.size() << endl;
	cout << "Testing top(): " << p.top() << endl << endl;

	sortStack(p);
	cout << "Sort stack: ";
	p.print();

	cout << "Testing pop(): " << p.pop() << endl;
	cout << "Stack after pop(): ";
	p.print();
	return 0;
}