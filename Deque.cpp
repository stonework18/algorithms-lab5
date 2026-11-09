#include <iostream>
#include <string>
#include <stdexcept> 
using namespace std;
template<typename T>
class Deque {
private:
	struct Node {
		T data;
		Node* prev;
		Node* next;
		Node(const T& value) : data(value), prev(nullptr), next(nullptr) {}
	};
	Node* head;
	Node* tail;
	int count;
public:
	// Constructors
	Deque()	: head(nullptr), tail(nullptr), count(0) {}
	~Deque() {
		while (head != nullptr) {
			Node* temp = head;
			head = head->next;
			delete temp;
		}
	}
	// Methods
	void push_front(const T& value) { // Adds an element to the head
		Node* newNode = new Node(value);
		if (head == nullptr) head = tail = newNode;
		else {
			newNode->next = head;
			head->prev = newNode;
			head = newNode;
		} count++;
	}

	void push_back(const T& value) { // Adds an element to the tail
		Node* newNode = new Node(value);
		if (tail == nullptr) tail = head = newNode;
		else {
			tail->next = newNode;
			newNode->prev = tail;
			tail = newNode;
		} count++;
	}

	T pop_front() { // Removes the first element
		if (isEmpty()) throw underflow_error("Deque is empty");
		Node* temp = head;
		T value = temp->data;
		head = head->next;
		if (head != nullptr) head->prev = nullptr;
		else tail = nullptr;
		delete temp;
		count--;
		return value;
	}

	T pop_back() { // Removes the last element
		if (isEmpty()) throw underflow_error("Deque is empty");
		Node* temp = tail;
		T value = temp->data;
		tail = tail->prev;
		if (tail != nullptr) tail->next = nullptr;
		else head = nullptr;
		delete temp;
		count--;
		return value;
	}

	T back() { // Returns the last element
		if (isEmpty()) throw underflow_error("Deque is empty.");
		return tail->data;
	}

	T front() const { // Returns the first element
		if (isEmpty()) throw underflow_error("Deque is empty.");
		return head->data;
	}

	void print() const { // Outputs the array
		cout << "[";
		Node* current = head;
		bool isFirst = true;
		while (current != nullptr) {
			if (!isFirst) cout << ", ";
			isFirst = false;
			cout << current->data;
			current = current->next;
		} cout << "]" << endl;
	}

	bool isEmpty() const { return count == 0; }
	int size() const { return count; }

	void reverse() { // Reverses the array
		if (head == nullptr) return;
		Node* current = head; 
		while (current != nullptr) { 
			Node* nextNode = current->next; // Save the following (next) node
			current->next = current->prev; // Reversing the node
			current->prev = nextNode;
			current = nextNode; // Let’s move on
		} Node* temp = head; // Swap the head and the tail
		head = tail;
		tail = temp;
	}
};

int main() {
	Deque<int> d;

	d.push_back(30);
	d.push_back(40);
	d.push_back(50);
	d.push_front(5);
	d.push_front(10);
	d.push_front(20);

	cout << "Deque: ";
	d.print();
	cout << "Size: " << d.size() << endl;

	cout << "\nRemove from the array: ";
	cout << d.pop_front() << ", ";
	cout << d.pop_back() << endl;
	cout << "Testing front(): " << d.front() << endl;
	cout << "Testing back(): " << d.back() << endl;
	cout << "Deque after remove: ";
	d.print();

	cout << "\nReverse: ";
	d.reverse();
	d.print();

	return 0;
}