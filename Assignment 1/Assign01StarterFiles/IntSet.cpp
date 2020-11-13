// FILE: IntSet.cpp - header file for IntSet class
//       Implementation file for the IntStore class
//       (See IntSet.h for documentation.)
// INVARIANT for the IntSet class:
// (1) Distinct int values of the IntSet are stored in a 1-D,
//     compile-time array whose size is IntSet::MAX_SIZE;
//     the member variable data references the array.
// (2) The distinct int value with earliest membership is stored
//     in data[0], the distinct int value with the 2nd-earliest
//     membership is stored in data[1], and so on.
//     Note: No "prior membership" information is tracked; i.e.,
//           if an int value that was previously a member (but its
//           earlier membership ended due to removal) becomes a
//           member again, the timing of its membership (relative
//           to other existing members) is the same as if that int
//           value was never a member before.
//     Note: Re-introduction of an int value that is already an
//           existing member (such as through the add operation)
//           has no effect on the "membership timing" of that int
//           value.
// (4) The # of distinct int values the IntSet currently contains
//     is stored in the member variable used.
// (5) Except when the IntSet is empty (used == 0), ALL elements
//     of data from data[0] until data[used - 1] contain relevant
//     distinct int values; i.e., all relevant distinct int values
//     appear together (no "holes" among them) starting from the
//     beginning of the data array.
// (6) We DON'T care what is stored in any of the array elements
//     from data[used] through data[IntSet::MAX_SIZE - 1].
//     Note: This applies also when the IntSet is empry (used == 0)
//           in which case we DON'T care what is stored in any of
//           the data array elements.
//     Note: A distinct int value in the IntSet can be any of the
//           values an int can represent (from the most negative
//           through 0 to the most positive), so there is no
//           particular int value that can be used to indicate an
//           irrelevant value. But there's no need for such an
//           "indicator value" since all relevant distinct int
//           values appear together starting from the beginning of
//           the data array and used (if properly initialized and
//           maintained) should tell which elements of the data
//           array are actually relevant.

#include "IntSet.h"
#include <iostream>
#include <cassert>
using namespace std;


//	   Name: Constructor
//     Pre:  (none)
//     Post: The invoking IntSet is initialized to an empty
//           IntSet (i.e., one containing no relevant elements).
//	   Description: Sets array size to 0.
IntSet::IntSet()
{   
	used = 0;
}


//	   Name: Size
//     Pre:  (none)
//     Post: Number of elements in the invoking IntSet is returned.
//	 Description: Returns current size of array, allows access for mutators.
int IntSet::size() const
{
	return used; 
}



//	   Name: isEmpty
//     Pre:  (none)
//     Post: True is returned if the invoking IntSet has no relevant
//           relevant elements, otherwise false is returned.
//	   Description: Determines wether the object passed is empty or not.
bool IntSet::isEmpty() const
{
	if(used == 0){
		return true;
		}
	else{
		return false;
		}
}



//     Name: contains
//     Pre:  (none)
//     Post: true is returned if the invoking IntSet has anInt as an
//           element, otherwise false is returned.
//     Decription: checks if the provided int is contained within the object.
bool IntSet::contains(int anInt) const
{
	for (int base = 0 ;base < used; base++){
		if (data[base] == anInt){
			return true;
				}
		else{
			return false;
				}
	}
	return false;
}



//     Name:isSubsetOf 
//     Pre:  (none)
//     Post: True is returned if all elements of the invoking IntSet
//           are also elements of otherIntSet, otherwise false is
//           returned.
//           By definition, true is returned if the invoking IntSet
//           is empty (i.e., an empty IntSet is always isSubsetOf
//           another IntSet, even if the other IntSet is also empty).
//     Description: Checks if the the values in one object array are
//					present within the another object array.

bool IntSet::isSubsetOf(const IntSet& otherIntSet) const
{
	if (otherIntSet.used == 0){
			return true;
	}
	else{	
		for(int base = 0; base < otherIntSet.used;base++){
			for(int base2 = 0; base2 <= used;base2++){
				if (otherIntSet.data[base] == data[base2]){
					break;
				}	
				else if(base2 == used){
					return false;
				}
			}
			return true;
		}
				
	}
	return false;
}



void IntSet::DumpData(ostream& out) const
{  // already implemented ... DON'T change anything
   if (used > 0)
   {
      out << data[0];
      for (int i = 1; i < used; ++i)
         out << "  " << data[i];
   }
}

//     Name: unionWith
//     Pre:  size() + (otherIntSet.subtract(*this)).size() <= MAX_SIZE
//     Post: An IntSet representing the union of the invoking IntSet
//           and otherIntSet is returned.
//     Note: Equivalently (see postcondition of add), the IntSet
//           returned is one that initially is an exact copy of the
//           invoking IntSet but subsequently has all elements of
//           otherIntSet added.
//     Description: Combines two object arrays.

IntSet IntSet::unionWith(const IntSet& otherIntSet) const
{
	assert(size() + (otherIntSet.subtract(*this)).size() <= MAX_SIZE);
	int count =otherIntSet.size();
	IntSet tempIntSet = (*this);
	

	for(int base = 0; base < count; base++){
		if(tempIntSet.contains(otherIntSet.data[base])){
			continue;
		}
		else if (!tempIntSet.contains(otherIntSet.data[base])){
			tempIntSet.add(otherIntSet.data[base]);
		}
	}
	return tempIntSet;
}

//     Name:intersect
//     Post: An IntSet representing the intersection of the invoking
//           IntSet and otherIntSet is returned.
//     Note: Equivalently (see postcondition of remove), the IntSet
//           returned is one that initially is an exact copy of the
//           invoking IntSet but subsequently has all of its elements
//           that are not also elements of otherIntSet removed.
//     Description: Compares two object arrays and removes from one
//                  the matching elements of the other.

IntSet IntSet::intersect(const IntSet& otherIntSet) const
{
   	IntSet tempSet = (*this);

	for(int base = 0; base<used; base++){
		if(tempSet.contains(data[used])){
			continue;
		}
		else{
			tempSet.remove(otherIntSet.data[base]);
			
		}
	}
   return tempSet; 
}

//     Name: subtract
//     Pre:  (none)
//     Post: An IntSet representing the difference between the invoking
//           IntSet and otherIntSet is returned.
//     Description: compares two object arrays to remove similar elements
//                  of one from the other.

IntSet IntSet::subtract(const IntSet& otherIntSet) const
{
	IntSet tempSet = (*this);

	for(int base = 0; base < size(); base++){
		if(tempSet.contains(otherIntSet.data[base])){
			tempSet.remove(otherIntSet.data[base]);
		}
	}   
	return tempSet;
}

//     Name: reset
//     Pre:  (none)
//     Post: The invoking IntSet is reset to become an empty IntSet
//           (i.e., one containing no relevant elements).
//     Description: Resets all values of an object array to 0.

void IntSet::reset()
{
	for(int base = 0; base <= used; base++){
		data[base] = 0;
	}
}

//     Name: add
//     Pre:  contains(anInt) ? size() <= MAX_SIZE : size() < MAX_SIZE
//     Post: If contains(anInt) returns false, anInt has been
//           added to the invoking IntSet as a new element and
//           true is returned, otherwise the invoking IntSet is
//           unchanged and false is returned.
//     Descriptions: Compares two object arrays and add any elements
//                   unique to one into the other.
bool IntSet::add(int anInt)
{
	assert(contains(anInt) ? size() <= MAX_SIZE : size() < MAX_SIZE);
	bool test = contains(anInt); 	
	if(test == false){
		data[used] = anInt;
		used++;
		return true;
	}
	else{
	return false;
	}
}

//     Name: Remove
//     Pre:  (none)
//     Post: If contains(anInt) returns true, anInt has been
//           removed from the invoking IntSet and true is
//           returned, otherwise the invoking IntSet is unchanged
//           and false is returned.
//     Description: accepts a value and removes it from a given object array.

bool IntSet::remove(int anInt)
{	
//traverses for desired int, sets to 0 when found
	if(contains(anInt) == true){
		for (int base = 0; base <= used; base++){
			if(data[base] != anInt){
				continue;
			}
			else{
				data[base] = 0;
			}
		}
		for(int base2 = 0; base2 <= used; base2++){
			if(data[base2] != 0){
				continue;
			}
			else if (data[base2] == 0){
				if(data[base2 + 1] != 0){
					data[base2] = data[base2 + 1];
					data[base2 + 1] = 0;
				}
				else{
					cout << "Set is empty.";
				}
			}
		used--;		
		}
	return true;		
	}
	else {
		return false;
	}
}


//     Name: equal
//     Pre:  (none)
//     Post: True is returned if is1 and is2 have the same elements,
//           otherwise false is returned; for e.g.: {1,2,3}, {1,3,2},
//           {2,1,3}, {2,3,1}, {3,1,2}, and {3,2,1} are all equal.
//     Note: By definition, two empty IntSet's are equal.
//     Description: compares two object arrays to and returns 
//     whether or not they are equal.
bool equal(const IntSet& is1, const IntSet& is2)
{
	if(is1.isSubsetOf(is2)){
		if(is2.isSubsetOf(is1)){
			return true;
		}
		else{
			return false;
		}
	}
	return false;		
}
