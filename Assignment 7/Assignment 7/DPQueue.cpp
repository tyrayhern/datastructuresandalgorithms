// FILE: DPQueue.cpp
// IMPLEMENTS: p_queue (see DPQueue.h for documentation.)
//
// INVARIANT for the p_queue class:
//   1. The number of items in the p_queue is stored in the member
//      variable used.
//   2. The items themselves are stored in a dynamic array (partially
//      filled in general) organized to follow the usual heap storage
//      rules.
//      2.1 The member variable heap stores the starting address
//          of the array (i.e., heap is the array's name). Thus,
//          the items in the p_queue are stored in the elements
//          heap[0] through heap[used - 1].
//      2.2 The member variable capacity stores the current size of
//          the dynamic array (i.e., capacity is the maximum number
//          of items the array currently can accommodate).
//          NOTE: The size of the dynamic array (thus capacity) can
//                be resized up or down where needed or appropriate
//                by calling resize(...).
// NOTE: Private helper functions are implemented at the bottom of
// this file along with their precondition/postcondition contracts.

#include <cassert>   // provides assert function
#include <iostream>  // provides cin, cout
#include <iomanip>   // provides setw
#include <cmath>     // provides log2
#include "DPQueue.h"

using namespace std;

namespace CS3358_FA2019_A7
{
	// EXTRA MEMBER FUNCTIONS FOR DEBUG PRINTING
	void p_queue::print_tree(const char message[], size_type i) const
		// Pre:  (none)
		// Post: If the message is non-empty, it has first been written to
		//       cout. After that, the portion of the heap with root at
		//       node i has been written to the screen. Each node's data
		//       is indented 4*d, where d is the depth of the node.
		//       NOTE: The default argument for message is the empty string,
		//             and the default argument for i is zero. For example,
		//             to print the entire tree of a p_queue p, with a
		//             message of "The tree:", you can call:
		//                p.print_tree("The tree:");
		//             This call uses the default argument i=0, which prints
		//             the whole tree.
	{
		const char NO_MESSAGE[] = "";
		size_type depth;

		if (message[0] != '\0')
			cout << message << endl;

		if (i >= used)
			cout << "(EMPTY)" << endl;
		else
		{
			depth = size_type(log(double(i + 1)) / log(2.0) + 0.1);
			if (2 * i + 2 < used)
				print_tree(NO_MESSAGE, 2 * i + 2);
			cout << setw(depth * 3) << "";
			cout << heap[i].data;
			cout << '(' << heap[i].priority << ')' << endl;
			if (2 * i + 1 < used)
				print_tree(NO_MESSAGE, 2 * i + 1);
		}
	}

	void p_queue::print_array(const char message[]) const
		// Pre:  (none)
		// Post: If the message is non-empty, it has first been written to
		//       cout. After that, the contents of the array representing
		//       the current heap has been written to cout in one line with
		//       values separated one from another with a space.
		//       NOTE: The default argument for message is the empty string.
	{
		if (message[0] != '\0')
			cout << message << endl;

		if (used == 0)
			cout << "(EMPTY)" << endl;
		else
			for (size_type i = 0; i < used; i++)
				cout << heap[i].data << ' ';
	}

	// CONSTRUCTORS AND DESTRUCTOR
	//if valid capacity is given, dynamically allocate array of ItemType size capacity
	p_queue::p_queue(size_type initial_capacity) : capacity(initial_capacity), used(0)
	{
		if (initial_capacity <= 0) {
			capacity = DEFAULT_CAPACITY;
		}

		heap = new ItemType[capacity];
	}

	//copy constructor
	//makes a new heap if same size as src, copies all values into it
	p_queue::p_queue(const p_queue& src) : capacity(src.capacity), used(src.used)
	{
		heap = new ItemType[capacity];
		for (size_type base = 0; base < capacity; ++base) {
			heap[base] = src.heap[base];
		}
	}

	//destructor
	//deletes current heap, sets myHeap pointer to 0
	p_queue::~p_queue()
	{
		delete heap;
		heap = 0;
	}

	// MODIFICATION MEMBER FUNCTIONS


	p_queue& p_queue::operator=(const p_queue& rhs)
	{

		//if assigning to self, return self. Assignment complete.
		if (this == &rhs) return *this;

		//create temp array, copy rhs values
		ItemType* temp = new ItemType[rhs.capacity];
		for (size_type base = 0; base < rhs.used; ++base) {
			temp[base] = rhs.heap[base];
		}

		//remove array at old heap, reassign all variables to new array
		delete[] heap;
		heap = temp;
		capacity = rhs.capacity;
		used = rhs.used;



		return *this;
	}

	void p_queue::push(const value_type& entry, size_type priority)
	{
		//if full, resize
		if (used == capacity) {

			resize(size_type(1.25 * capacity) + 1);
		}

		//heap[used] is top, place entry there, increase used after saving base
		heap[used].priority = priority;
		heap[used].data = entry;
		size_type base = used;
		used++;

		//while stack not empty, if parent priority less than child, swap. 
		while (base != 0 && parent_priority(base) < heap[base].priority)
		{
			swap_with_parent(base);
			base = parent_index(base);
		}
	
	}

	void p_queue::pop()
	{
		assert(size() > 0);

		//pop
		heap[0].data = heap[used - 1].data;
		heap[0].priority = heap[used - 1].priority;
		--used;

		//track index
		size_type parentIndex = 0, childIndex = 0;

		//reheap
		while (!is_leaf(parentIndex)) {

			if (heap[parentIndex].priority <= big_child_priority(parentIndex))
			{
				childIndex = big_child_index(parentIndex);
				swap_with_parent(childIndex);
				parentIndex = childIndex;
			}
		}

	}

	// CONSTANT MEMBER FUNCTIONS

	p_queue::size_type p_queue::size() const
	{
		return used;

	}

	bool p_queue::empty() const
	{
		if (used == 0) {
			return true;
		}
		else {
			return false;
		}
	}

	p_queue::value_type p_queue::front() const
	{
		assert(size() > 0);
		return heap[0].data;
	}

	// PRIVATE HELPER FUNCTIONS
	void p_queue::resize(size_type new_capacity)
		// Pre:  (none)
		// Post: The size of the dynamic array pointed to by heap (thus
		//       the capacity of the p_queue) has been resized up or down
		//       to new_capacity, but never less than used (to prevent
		//       loss of existing data).
		//       NOTE: All existing items in the p_queue are preserved and
		//             used remains unchanged.
	{
		//if new capacity is less than heap, no resize needed
		if (new_capacity < used) {
			new_capacity = used;
			return;
		}

		//create new array of new capacity, copy existing nodes into it
		ItemType* temp = new ItemType[new_capacity];
		for (size_type base = 0; base < used; ++base) {
			temp[base] = heap[base];
		}

		//free old heap, set new heap and capacity
		delete[] heap;
		heap = temp;
		capacity = new_capacity;
	}

	bool p_queue::is_leaf(size_type i) const
		// Pre:  (i < used)
		// Post: If the item at heap[i] has no children, true has been
		//       returned, otherwise false has been returned.
	{
		//assert precondition
		assert(i <= used);

		//invert expression for finding parent functions, see if true
		if ((((i * 2) + 1) >= used) == true) {
			return true;
		}
		else {
			return false;
		}

	}

	p_queue::size_type
		p_queue::parent_index(size_type i) const
		// Pre:  (i > 0) && (i < used)
		// Post: The index of "the parent of the item at heap[i]" has
		//       been returned.
	{
		assert(i > 0);
		assert(i < used);
		//finds index of parent to return
		size_type index = static_cast<size_type>((i - 1) / 2);

		return index;
	}

	p_queue::size_type
		p_queue::parent_priority(size_type i) const
		// Pre:  (i > 0) && (i < used)
		// Post: The priority of "the parent of the item at heap[i]" has
		//       been returned.
	{
		assert(i > 0);
		assert(i < used);

		//get parent index, see priority
		size_type parent = parent_index(i);
		size_type weight = heap[parent].priority;

		return weight;
	}


	//Four options: i is root, check index 1 and 2; left is only child, return left; 
	//left is bigger child, return left; right is present and bigger, return right
	p_queue::size_type
		p_queue::big_child_index(size_type i) const
		// Pre:  is_leaf(i) returns false
		// Post: The index of "the bigger child of the item at heap[i]"
		//       has been returned.
		//       (The bigger child is the one whose priority is no smaller
		//       than that of the other child, if there is one.)
	{
		assert(!(is_leaf(i)));

		size_type left_child = (i * 2) + 1; /// Index of LHS child.
		size_type right_child = (i * 2) + 2; /// Index of RHS child.

		//if parent is root, compare child nodes
		if (i == 0) {
			if (heap[1].priority >= heap[2].priority) {
				return 1;
			}
			else {
				return 2;
			}
		}
		//if right child and its biggest, return right child,
	   //else if left is bigger or only child return left child
		if (right_child < used) {
			if (heap[right_child].priority > heap[left_child].priority) {
				return right_child;
			}
			else {
				return left_child;
			}
		}
		else {
			return left_child;
		}
	}

		p_queue::size_type
			p_queue::big_child_priority(size_type i) const
			// Pre:  is_leaf(i) returns false
			// Post: The priority of "the bigger child of the item at heap[i]"
			//       has been returned.
			//       (The bigger child is the one whose priority is no smaller
			//       than that of the other child, if there is one.)
		{
			assert(!(is_leaf(i)));

			//get index, then priority to return
			size_type bigIndex = big_child_index(i);
			size_type bigPriority = heap[bigIndex].priority;


			return bigPriority;
		}

		void p_queue::swap_with_parent(size_type i)
			// Pre:  (i > 0) && (i < used)
			// Post: The item at heap[i] has been swapped with its parent.
		{
			//assert preconditions
			assert(i > 0);
			assert(i < used);

			//get value into temp
			size_type parent = parent_index(i);
			ItemType temp = heap[parent];

			//swap using temp
			heap[parent] = heap[i];
			heap[i] = temp;

		}
	}

