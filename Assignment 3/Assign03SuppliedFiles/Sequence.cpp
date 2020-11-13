// FILE: Sequence.cpp
// CLASS IMPLEMENTED: sequence (see sequence.h for documentation)
// INVARIANT for the sequence ADT:
//   1. The number of items in the sequence is in the member variable
//      used;
//   2. The actual items of the sequence are stored in a partially
//      filled array. The array is a dynamic array, pointed to by
//      the member variable data. For an empty sequence, we do not
//      care what is stored in any of data; for a non-empty sequence
//      the items in the sequence are stored in data[0] through
//      data[used-1], and we don't care what's in the rest of data.
//   3. The size of the dynamic array is in the member variable
//      capacity.
//   4. The index of the current item is in the member variable
//      current_index. If there is no valid current item, then
//      current_index will be set to the same number as used.
//      NOTE: Setting current_index to be the same as used to
//            indicate "no current item exists" is a good choice
//            for at least the following reasons:
//            (a) For a non-empty sequence, used is non-zero and
//                a current_index equal to used indexes an element
//                that is (just) outside the valid range. This
//                gives us a simple and useful way to indicate
//                whether the sequence has a current item or not:
//                a current_index in the valid range indicates
//                that there's a current item, and a current_index
//                outside the valid range indicates otherwise.
//            (b) The rule remains applicable for an empty sequence,
//                where used is zero: there can't be any current
//                item in an empty sequence, so we set current_index
//                to zero (= used), which is (sort of just) outside
//                the valid range (no index is valid in this case).
//            (c) It simplifies the logic for implementing the
//                advance function: when the precondition is met
//                (sequence has a current item), simply incrementing
//                the current_index takes care of fulfilling the
//                postcondition for the function for both of the two
//                possible scenarios (current item is and is not the
//                last item in the sequence).

#include <cassert>
#include "Sequence.h"
#include <iostream>
using namespace std;

namespace CS3358_FA2019
{
   // CONSTRUCTORS and DESTRUCTOR
	//constructor asserts precondition
   sequence::sequence(size_type initial_capacity):  used(0), current_index(0), capacity(initial_capacity)
   {
	   if (initial_capacity < 1) { 
		   capacity = 1; 
	   }

	   data = new value_type[capacity];
   }
   //copy constructor
   sequence::sequence(const sequence& source) : used(source.used), capacity(source.capacity), current_index(source.current_index)
   {
	   data = new value_type[capacity];

	   for (size_type i = 0; i < used; ++i) {
		   data[i] = source.data[i];
	   }

   }

   sequence::~sequence()
   {
	   delete[] data;
	   data = NULL;

   }

   // MODIFICATION MEMBER FUNCTIONS

   //adjusts capacity. If less than used, is equal to used. if equal to 0, is now 1. new_capacity is then assigned to capacity.
   void sequence::resize(size_type new_capacity)
   {
	  
	   if (new_capacity < used) {
		   new_capacity = used;
	   }
	   else if(new_capacity == 0){
		   new_capacity = 1;
	   }

	   capacity = new_capacity;

	   value_type* tempData = new value_type[capacity];
	   for (size_type i = 0; i < used; ++i) {
		   tempData[i] = data[i];
	   }

	   delete[] data;

	   data = tempData;
   }

   //current index is reset to the start of the sequence.
   void sequence::start()
   {
	   current_index = 0;
   }

   //as long as the current item isnt the last item, move to the next item
   void sequence::advance()
   {
	   assert(is_item());

		++current_index;
   }

   //resizes the sequence to one more than current, traverses array assigning all 
   //values before to same positions, places entry at current, assigns all following 
   //indexes to the values following current, points data to new array before deleting
   void sequence::insert(const value_type& entry)
   {

	 

	   if (used == capacity) { 
		   resize(size_type(1.25 * capacity) + 1);
	   }

	   if (!is_item()) {

		   current_index = 0;
		   for (size_type i = used + 1; i > current_index; --i) {
			   data[i] = data[i - 1];
		   }
		   data[current_index] = entry;
		   ++used;

	   }
	   else {
		   for (int i = used + 1; i > current_index; --i) {
			   data[i] = data[i - 1];
		   }
		   data[current_index] = entry;
		   ++used;
	   }


   }

   void sequence::attach(const value_type& entry)
   {

	   if (used == capacity) { 
		   resize(size_type(1.25 * capacity) + 1); 
	   }
	   if (!is_item()) {
		   current_index = 0;
		   data[current_index] = entry;
	   }
	   ++used;
	   resize(used);
	   data[used] = entry;
	   current_index = used;
   }

   void sequence::remove_current()
   {
	   assert(is_item());
	   for (int i = 0; i < used-1; ++i) {
		   if (i >= current_index) {
			   data[i] = data[i + 1];
		   }
	 }
	   --used;
   }


   //creates temporary instance of sequence, copies all info of source sequence into new instantiation
   sequence& sequence::operator=(const sequence& source)
   {
	   sequence tempSeq = (*this);
	   
	   for (int i = 0; i < source.size(); ++i) {
		   tempSeq.data[i] = source.data[i];
	   }
	   used = source.size();
	   capacity = source.capacity;
	   current_index = source.current();
      return *this;
   }

   // CONSTANT MEMBER FUNCTIONS

   // the size of data is the value of private member used
   sequence::size_type sequence::size() const
   {
   return used;
   }

   //used tracks number of elements in data, so if it's greater than 0 then theres a number
   bool sequence::is_item() const
   {
      return (current_index != used); 
   }


   //accesses current_index private member
   sequence::value_type sequence::current() const
   {
	   assert(is_item());

      
      return data[current_index];
   }
}

