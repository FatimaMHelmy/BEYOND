
#include <iostream>

class Node {
public:
    int data;
    Node* prev;
    Node* next;

    Node(int value) {
        data = value;
        prev = nullptr;
        next = nullptr;
    }
};

class DoublyLinkedList {
private:
    Node* head;
    Node* tail;

public:
    DoublyLinkedList() {
        head = nullptr;
        tail = nullptr;
    }

    void Add(int element) {
        Node* newNode = new Node(element);
        // construct a new linked list
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        }
        // if linked list already exist
        else {
            // link both tail and new node
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode; // make the tail point to the new node

        }
    }

    void Add(int element, int position) {
        // check if it is in the head posion
        Node* newNode = new Node(element);

        if (position == 0) {
            // check it list exist
            if (head == nullptr) {
                head = newNode;
                tail = newNode;
            }

            else {

                newNode->next = head;
                head->prev = newNode;
                head = newNode;
            }

        }
        // in the middle or at the end
        else {

            Node* cur = head;
            int counter = 0;

            while (cur->next != nullptr) {

                if (counter == position) {
                    break;

                }

                cur = cur->next;
                counter++;

            }
            // first at the end
            if (cur == nullptr) {
                Add(element);
            }
            else {

                // link the node which curr point at with the new node
                newNode->prev = cur->prev;
                cur->prev->next = newNode;
                // make current point at the new node
                newNode->next = cur;
                cur->prev = newNode;
            }
        }
    }


    bool Search(int element)
    {
        Node* cur = head;
        while (cur->next != nullptr) {

            // we found the element
            if (cur->data == element) { return true; }

            cur = cur->next;
        }
        return false;
    }

    void Remove(int element) {
        bool removed = false;
        Node* cur = head;
        while (cur != nullptr) {

            // we found the element
            if (cur->data == element) {

                // at the head
                if (cur == head) {
                    head = head->next;
                }
                // at the tail
                else if (cur == tail) {
                    tail = tail->prev;
                    tail->next = nullptr;
                }
                // at the middel
                else {
                    cur->prev->next = cur->next;
                    cur->next->prev = cur->prev;
                }
                removed = true;
            }
            cur = cur->next;
        }

        // print if element delent or not found
        if (removed == true) {
            std::cout << "Element deleted: " << element << std::endl;
        }
        else {
            std::cout << "Element not found." << std::endl;
        }

    }

    void Clear() {

        head = nullptr;
        tail = nullptr;
        std::cout << "The list is clrared " << std::endl;

    }

    void PrintList() {
        Node* curr = head;

        while (curr != nullptr) {
            std::cout << curr->data << " ";
            curr = curr->next;
        }

        std::cout << std::endl;
    }

    Node* Merge_Lists(Node* first_lst, Node* second_lst) {
        if (first_lst == nullptr)
            return second_lst;
        if (second_lst == nullptr)
            return first_lst;
        // iterate over the two linkedlists to sort them accending
        if (first_lst->data <= second_lst->data) {
            first_lst->next = Merge_Lists(first_lst->next, second_lst);
            first_lst->next->prev = first_lst;
            first_lst->prev = nullptr;
            return first_lst;
        }
        else {
            second_lst->next = Merge_Lists(first_lst, second_lst->next);
            second_lst->next->prev = second_lst;
            second_lst->prev = nullptr;
            return second_lst;
        }
    }


    void Merge_Sort() {
        if (head == nullptr || head->next == nullptr)
            return;

        // Split the list into two halves
        DoublyLinkedList firstHalf;
        DoublyLinkedList secondHalf;
        // using the fast slow technique
        Node* slow = head;
        Node* fast = head->next;
        // when the fast reach the end of the linkedlist , so, the slow reachs the middle
        while (fast != nullptr) {
            fast = fast->next;
            if (fast != nullptr) {
                slow = slow->next;
                fast = fast->next;
            }
        }
        // divide the large linkedlist 
        // the firstHalf takes from the head to the slow pointer
        firstHalf.head = head;
        firstHalf.tail = slow;
        // the secondHalf takes from the slow->next to the tail of the linkedlist
        secondHalf.head = slow->next;
        secondHalf.tail = tail;
        slow->next = nullptr;

        // Recursively sort each half
        firstHalf.Merge_Sort();
        secondHalf.Merge_Sort();

        // Merge the sorted halves
        head = Merge_Lists(firstHalf.head, secondHalf.head);
        tail = secondHalf.tail;
    }


};

int main() {
    DoublyLinkedList myList;

    // Add test values to the list
    myList.Add(14);
    myList.Add(10);
    myList.Add(15);
    myList.Add(3);
    myList.Add(1);
    myList.Add(19);

    // Print the initial list
    std::cout << "Initial list: ";
    myList.PrintList();

    // Search for an element
    int searchElement = 15;
    if (myList.Search(searchElement)) {
        std::cout << "Element " << searchElement << " found in the list!" << std::endl;
    }
    else {
        std::cout << "Element " << searchElement << " not found in the list." << std::endl;
    }

    // Remove an element
    int removeElement = 10;
    myList.Remove(removeElement);
    std::cout << "After removing element " << removeElement << ": ";
    myList.PrintList();



    // Add elements at specific positions
    myList.Add(100, 0);
    myList.Add(200, 1);
    myList.Add(300, 2);
    std::cout << "List after adding elements: ";
    myList.PrintList();

    // Sort the list
    myList.Merge_Sort();
    std::cout << "Sorted list: ";
    myList.PrintList();

    // Clear the list
    myList.Clear();

    return 0;
}
