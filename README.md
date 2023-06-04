# BEYOND_TASKS
## TASK_2 || Linked list 

# !! ** you will find the whole project in projects folder and cpp file in files folder**

This is a C++ implementation of a doubly linked list. It provides various operations such as adding elements, searching for an element, removing an element, clearing the list, and sorting the list using merge sort algorithm.

### **Node Class**
The Node class represents a node in the doubly linked list. Each node contains an integer value, a pointer to the previous node (prev), and a pointer to the next node (next).

### **DoublyLinkedList Class**
The DoublyLinkedList class represents the doubly linked list. It has private member variables head and tail which point to the first and last nodes of the list, respectively.

### Constructor

DoublyLinkedList(): Initializes an empty doubly linked list.

### Methods

- void Add(int element): Adds an element to the end of the list.

- void Add(int element, int position): Adds an element at the specified position in the list.
- bool Search(int element): Searches for the specified element in the list and returns true if found, false otherwise.
- void Remove(int element): Removes the specified element from the list if it exists.
- void Clear(): Clears the entire list.
- void PrintList(): Prints the elements of the list.
- Node* Merge_Lists(Node* first_lst, Node* second_lst): Merges two sorted lists into a single sorted list.
- void Merge_Sort(): Sorts the list using merge sort algorithm.
### **USAGE**
It inckudes the test cases just run it.

The main function demonstrates the usage of the doubly linked list. It creates an instance of DoublyLinkedList, adds elements to the list, performs operations like searching and removing elements, adds elements at specific positions, sorts the list, and clears the list.
### **Result**
![image](https://github.com/FatimaMHelmy/BEYOND/blob/master/images/test_case_TASK2.png)

## TASK_3 ||Home Made Sobel 

# !! ** you will find the whole project in projects folder and cpp file in files folder**

### **steps**

Just enter the image path if you don't have one it's handeled in the code to use a test case image just run the code

### **Code Explanation**

- The SobelEdgeDetector class represents the edge detection algorithm.

- The constructor takes the path to the input image and loads it using the OpenCV imread function.

- The vertical and horizontal Sobel filter matrices are manually defined.

- The detectEdges method performs the edge detection process. It applies image smoothing using Gaussian blur, calculates the gradients using the Sobel filters, and computes the edge magnitude.

- The applyGaussianBlur method applies Gaussian blur to the input image using the OpenCV GaussianBlur function and Sharpening. || it's optional for high performance 

- The showEdgeImage method displays the original image and the filtered images side by side using OpenCV's imshow function.

### **Prerequisites**

OpenCV: Ensure that you have OpenCV installed on your system and properly configured.

### *RESULTS*

#### ******the result after applying bluring it is not suitable for all images*****


![image](https://github.com/FatimaMHelmy/BEYOND/blob/master/images/with_bluring.png)



#### ******the result without any smoothing*********


![image](https://github.com/FatimaMHelmy/BEYOND/blob/master/images/with_out_bluring.png)

## TASK1|| Face detection

Face Detection and Swaping:

Regarding the face detection and swaping task, I have made progress in extracting faces from images. I have experimented with different techniques and have successfully extracted faces. However, I am currently facing challenges with aligning the detected faces during the swaping process. Despite trying various approaches, the alignment is not optimal. I am still actively working on this issue and exploring different methods to improve the alignment.


