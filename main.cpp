#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Linked_list {
private:
	class Node {
	private:
		int data;
		Node* next_node;

	public:
		Node() : data(0), next_node(nullptr) {}
		Node(int data) : data(data), next_node(nullptr) {}
		Node(int data, Node* next_node) : data(data), next_node(next_node) {}

		int get_data() {
			return data;
		}
		Node* get_next_node() {
			return next_node;
		}

		void set_data(int data) {
			this->data = data;
		}
		void set_next_node(Node* next_node) {
			this->next_node = next_node;
		}

	};

	int size;
	Node* head;
	Node* tail;

	void free() {
		size = 0;
		head = nullptr;
		tail = nullptr;
	}

	Node* merge(Node* first, Node* second) {
		if (!first) {
			return second;
		}

		if (!second) {
			return first;
		}

		if (first->get_data() < second->get_data()) {
			first->set_next_node(merge(first->get_next_node(), second));
			return first;
		}
		else {
			second->set_next_node(merge(first, second->get_next_node()));
			return second;
		}
	}

	Node* get_middle(Node* head) {
		if (!head) {
			return head;
		}

		Node* slow = head;
		Node* fast = head;

		while (fast->get_next_node() && fast->get_next_node()->get_next_node()) {
			slow = slow->get_next_node();
			fast = fast->get_next_node()->get_next_node();
		}

		return slow;
	}

	Node* merge_sort(Node* head) {
		if (!head || !head->get_next_node()) {
			return head;
		}

		Node* middle = get_middle(head);
		Node* next_of_middle = middle->get_next_node();

		middle->set_next_node(nullptr);

		Node* left = merge_sort(head);
		Node* right = merge_sort(next_of_middle);

		Node* sorted_list = merge(left, right);
		return sorted_list;
	}

public:
	Linked_list() : head(nullptr), tail(nullptr), size(0) {}
	Linked_list(Node* head) : head(head), tail(nullptr), size(size++) {}
	Linked_list(Node* head, Node* tail) : head(head), tail(tail), size(0) {
		if (head == tail) size++;
		else size += 2;
	}
	Linked_list(const Linked_list& list) {
		if (this->head != nullptr) free();

		Node* current = list.head;
		while (current != nullptr) {
			append(current->get_data());
			current = current->get_next_node();
		}

		size = this->size;
	}
	Linked_list(initializer_list<int> init_list) : head(nullptr), tail(nullptr), size(0) {
		for (int value : init_list) {
			append(value);
		}
	}

	int get_size() const {
		return size;
	}

	bool is_empty() const {
		return head == nullptr;
	}

	void append(const int data) {
		Node* node = new Node(data);

		if (!is_empty()) {
			tail->set_next_node(node);
			tail = node;
		}
		else {
			head = node;
			tail = node;
		}

		size++;
	}

	void prepend(const int data) {
		Node* node = new Node(data);

		if (!is_empty()) {
			node->set_next_node(head);
			head = node;
		}
		else {
			head = node;
			tail = node;
		}

		size++;
	}

	void extend(Linked_list& list) {
		if (!is_empty() && !list.is_empty()) {
			this->tail->set_next_node(list.head);
			this->tail = list.tail;
			this->size += list.size;

			list.free();
		}
		else if (is_empty() && !list.is_empty()) {
			this->head = list.head;
			this->tail = list.tail;
			this->size = list.size;

			list.free();
		}
	}

	void insert(const int index, const int data) {
		if (index < 0 || index > size) {
			cerr << "Error: index is out of range" << endl;
			return;
		}

		if (index == 0) {
			prepend(data);
			return;
		}

		if (index == size) {
			append(data);
			return;
		}

		Node* node = new Node(data);
		Node* current = head;
		for (int i = 0; i < index - 1; i++) {
			current = current->get_next_node();
		}
		node->set_next_node(current->get_next_node());
		current->set_next_node(node);
		size++;
	}

	void insert_sorted(const int value) {
		Node* node = new Node(value);
		if (!head || head->get_data() >= node->get_data()) {
			node->set_next_node(head);
			head = node;
		}
		else {
			Node* current = head;
			while (current->get_next_node() && current->get_next_node()->get_data() < node->get_data()) {
				current = current->get_next_node();
			}
			node->set_next_node(current->get_next_node());
			current->set_next_node(node);
		}
		size++;
	}

	void remove_tail() {
		if (!is_empty()) {
			if (head == tail) {
				delete tail;
				head = nullptr;
				tail = nullptr;
			}
			else {
				Node* current = head;
				while (current->get_next_node() != tail) {
					current = current->get_next_node();
				}
				delete tail;
				tail = current;
				tail->set_next_node(nullptr);
			}
			size--;
		}
	}

	void remove_head() {
		Node* current = head->get_next_node();
		delete head;
		head = current;
		size--;
	}

	void remove_value(const int value) {
		if (is_empty()) {
			cerr << "Error: the list is empty" << endl;
			return;
		}

		Node* current = head;
		Node* previous = nullptr;
		while (current != nullptr) {
			if (current->get_data() == value) {
				if (current == head) {
					head = current->get_next_node();
				}
				else if (current == tail) {
					tail = previous;
					tail->set_next_node(nullptr);
				}
				else {
					previous->set_next_node(current->get_next_node());
				}
				delete current;
				size--;
				break;
			}
			previous = current;
			current = current->get_next_node();
		}
	}

	void remove_at(const int index) {
		if (index < 0 || index >= size) {
			cerr << "Error: index is out of range" << endl;
			return;
		}
		if (index == 0) {
			remove_head();
		}
		else if (index == size - 1) {
			remove_tail();
		}
		else {
			Node* current = head;
			for (int i = 0; i < index - 1; i++) {
				current = current->get_next_node();
			}
			Node* to_delete = current->get_next_node();
			current->set_next_node(to_delete->get_next_node());
			delete to_delete;
			size--;
		}
	}

	int pop() {
		if (is_empty()) {
			cerr << "Error: the list is empty" << endl;
			return -1;
		}
		int data = head->get_data();
		remove_head();
		return data;

	}

// Divide the list into two parts at the given index
Linked_list divide(int index) {
    Linked_list second_part;
    if (index < 0 || index >= size) {
        cerr << "Error: Index is out of range." << endl;
        return second_part;
    }

    Node* current = head;
    for (int i = 0; i < index - 1; i++) {
        current = current->get_next_node();
    }

    second_part.head = current->get_next_node();
    second_part.tail = tail;
    second_part.size = size - index;

    current->set_next_node(nullptr);
    tail = current;
    size = index;

    return second_part;
}

// Change the value of an element at the given index
void set_value(int index, int value) {
    if (index < 0 || index >= size) {
        cerr << "Error: Index is out of range." << endl;
        return;
    }

    Node* current = head;
    for (int i = 0; i < index; i++) {
        current = current->get_next_node();
    }
    current->set_data(value);
}

// Overload the [] operator to access elements by index
int& operator {
    if (index < 0 || index >= size) {
        cerr << "Error: Index is out of range." << endl;
        // Return a reference to a default value (you can choose a different one)
        static int dummy = -1;
        return dummy;
    }

    Node* current = head;
    for (int i = 0; i < index; i++) {
        current = current->get_next_node();
    }
    return current->get_data();
}


int find_max() const {
    if (!head) {
        cerr << "Error: List is empty." << endl;
        return -1;  
    }

    int max_value = head->get_data();
    Node* current = head->get_next_node();
    while (current) {
        if (current->get_data() > max_value) {
            max_value = current->get_data();
        }
        current = current->get_next_node();
    }
    return max_value;
}

int find_min() const {
    if (!head) {
        cerr << "Error: List is empty." << endl;
        return -1;  
    }

    int min_value = head->get_data();
    Node* current = head->get_next_node();
    while (current) {
        if (current->get_data() < min_value) {
            min_value = current->get_data();
        }
        current = current->get_next_node();
    }
    return min_value;
}


        int count_occurrences(int value) const {
    int count = 0;
    Node* current = head;
    while (current) {
        if (current->get_data() == value) {
            count++;
        }
        current = current->get_next_node();
    }
    return count;
	}


        void remove_duplicates() {
            if (!head) {
               return;
            }

    Node* current = head;
    while (current) {
        Node* runner = current;
        while (runner->get_next_node()) {
            if (runner->get_next_node()->get_data() == current->get_data()) {
                Node* duplicate = runner->get_next_node();
                runner->set_next_node(duplicate->get_next_node());
                delete duplicate;
                size--;
            } else {
                runner = runner->get_next_node();
            }
        }
        current = current->get_next_node();
    }
	}


	void print() const {
		Node* current = head;
		while (current) {
			cout << current->get_data() << " ";
			current = current->get_next_node();
		}
		cout << endl;
	}

	Linked_list slice(const int start, const int end) {
		Linked_list new_list;
		if (start < 0 || start > size || end < 0 || end > size || start > end) {
			cerr << "Error: index is out of range" << endl;
			return new_list;
		}
		Node* current = head;
		int index = 0;
		while (current) {
			if (index >= start && index < end) {
				new_list.append(current->get_data());
			}
			current = current->get_next_node();
			index++;
		}
		return new_list;
	}

	int get_element(const int index) const {
		if (index < 0 || index > size) {
			cerr << "Error: index is out of range" << endl;
			return -1;
		}

		if (index == 0) {
			return head->get_data();
		}

		if (index == size) {
			return tail->get_data();
		}

		Node* current = head;
		for (int i = 0; i <= index; i++)
		{
			current = current->get_next_node();
		}
		return current->get_data();
	}

	Node* find(int value) {
		Node* current = head;
		while (current != nullptr) {
			if (current->get_data() == value) {
				return current;
			}
			current = current->get_next_node();
		}
		return nullptr;
	}

	void sort() {
		head = merge_sort(head);
	}

	void reverse() {
		Node* current = head;
		Node* prev = nullptr, *next = nullptr;

		while (current) {
			next = current->get_next_node();
			current->set_next_node(prev);
			prev = current;
			current = next;
		}
		head = prev;
	}

	void swap(const int index1, const int index2) {
		if (index1 < 0 || index1 >= size || index2 < 0 || index2 >= size) {
			cerr << "Error: index is out of range" << endl;
			return;
		}

		Node* node1 = head;
		Node* node2 = head;
		for (int i = 0; i < index1; i++) {
			node1 = node1->get_next_node();
		}
		for (int i = 0; i < index2; i++) {
			node2 = node2->get_next_node();
		}

		int temp = node1->get_data();
		node1->set_data(node2->get_data());
		node2->set_data(temp);
	}

	Linked_list& operator=(const Linked_list& list) {
		if (this == &list) {
			return *this;
		}

		Node* current = head;
		while (current) {
			Node* next = current->get_next_node();
			delete current;
			current = next;
		}

		free();

		current = list.head;
		while (current != nullptr) {
			append(current->get_data());
			current = current->get_next_node();
		}

		return *this;
	}

	int operator[](const int index) const {
		return get_element(index);
	}

	bool contains(const int value) const {
		Node* current = head;
		while (current != nullptr) {
			if (current->get_data() == value) {
				return true;
			}
			current = current->get_next_node();
		}
		return false;
	}

	int index_of(const int value) const {
		Node* current = head;
		int index = 0;
		while (current != nullptr) {
			if (current->get_data() == value) {
				return index;
			}
			current = current->get_next_node();
			index++;
		}
		return -1;
	}

	void clear() {
		Node* current = head;
		while (current) {
			Node* next = current->get_next_node();
			delete current;
			current = next;
		}
		head = nullptr;
		tail = nullptr;
		size = 0;
	}

	vector<int> to_vector() const {
		vector<int> vec;
		Node* current = head;
		while (current) {
			vec.push_back(current->get_data());
			current = current->get_next_node();
		}
		return vec;
	}

	string to_string() const {
		string list_string = "";
		Node* current = head;
		while (current) {
			list_string += std::to_string(current->get_data()) + " ";
			current = current->get_next_node();
		}
		return list_string;
	}

	bool operator==(const Linked_list& list) const {
		if (this->size != list.size) {
			return false;
		}
		Node* current1 = this->head;
		Node* current2 = list.head;
		while (current1) {
			if (current1->get_data() != current2->get_data()) {
				return false;
			}
			current1 = current1->get_next_node();
			current2 = current2->get_next_node();
		}
		return true;
	}

	bool operator!=(const Linked_list& list) const {
		return !(*this == list);
	}

        Linked_list operator+(const Linked_list& other) const {
            Linked_list result(*this);  
            result.extend(other);       
            return result;
	}


	Linked_list copy() const {
		Linked_list new_list;
		Node* current = head;
		while (current) {
			new_list.append(current->get_data());
			current = current->get_next_node();
		}
		return new_list;
	}

	~Linked_list() {
		Node* current = head;
		while (current) {
			Node* next = current->get_next_node();
			delete current;
			current = next;
		}
		head = nullptr;
		tail = nullptr;
	}
};

int main() {
	Linked_list list;
	list.append(8);
	list.append(9);
	list.append(2);
	list.append(100);
	list.append(54);
	list.sort();
	list.print();
	list.reverse();
	list.print();

	return 0;
}
