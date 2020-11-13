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






IntSet::IntSet()
{
   
	used = 0;

}



int IntSet::size() const
{
   

	return used; 
}




bool IntSet::isEmpty() const
{
   
	if(used == 0){
		return true;
		}
	else{
		return false;
		};

}



//The method "contains" will traverse the array comparing each element to "anInt". If the element is found, "True" is returned. If each element has been traversed and compared with anInt 
//without success, "contains" will return "false".
bool IntSet::contains(int anInt) const
{
   
	for (base = 0 ;base <= used; base++){
		if (data[base] == anInt){
			return true;
				}
		else if (base == used){
			return false;
				}
}

//Method "isSubsetOf" first checks if IntSet is empty, returns true if it is. Then, the method compares each element of IntSet.data() to each element of otherIntSet.data().
// If an element of IntSet.data() finds an equivalent value in otherIntSet.data(), the loop progresses to the next element of IntSet.data(). If it reaches the last value of 
//otherIntSet.data() without finding a match, "false" is returned. If each element is compared and FOR loop is completed, "isSubsetof" returns "true".
   



bool IntSet::isSubsetOf(const IntSet& otherIntSet) const
{
   
	if (otherIntSet.used == 0){
			return true;
	}
	else{	
		for(base = 0; base <= otherIntSet.used;base++){
			for(base2 = 0; base2 <= used;base2++){
				if (otherIntSet.data[base] == data[base2]{
					break;
				}	
				else if(base2 == used){
					return false;
				}
			}
			return true;
		}
				
	}
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



//unionWith first creates an instance of IntSet and a dynamically allocated array of size equal to both IntSet& and otherIntSet. unionWith then adds values of IntSet& to new instance,
//proceeds to compare values of IntSet& with otherIntSet. If value is found in otherIntSet but not IntSet&, it is added to the new instance.data[].


IntSet IntSet::unionWith(const IntSet& otherIntSet) const
{
   
	IntSet tempIntSet= new IntSet();
	int* tempArr;
	int* checkArr;
	int count = used;

	tempArr = new int [used + otherIntSet.used];
	tempIntSet.data = tempArr;
	//dummy IntSet is set up and pointing to array of size intset+otherintset

	for(base = 0; base <= used; base++){
		tempIntSet.data[base] = data[base];
	}
	//tempIntSet.data now has all values from Intset.data, next step is to add all from otherIntSet that are not already represented
	
	for(base2 = 0; base2 <= otherIntSet.used; base2++){
		for(base3 = 0; base3 <= count; base++){
			if(otherIntSet.data(base2) != tempIntSet.data(base3)){
				if(base3 != count){
					continue;
				}
				else if(base3 == count){
					count++;
					tempIntSet.data(count) = otherIntSet.data(base2);
				}
			}
			else if(otherIntSet.data(base2) == tempIntSet.data(base3)){
				break;
			}
		}	
	}
	//All values of two input sets that are not duplicates have been stored in tempIntSet.data. Now adjust size of array with checkArr
	if (count < (used + otherIntSet.used)){
			checkArr = new int[count];
			for (base4 = 0; base4 <=count;base++0{
				checkArr[base] = tempIntSet[base]; 
			}
			tempIntSet.data = checkArr;
	}
	else if (count > (used + otherIntSet.used){
			cout << "Union count exceeded; FOR loop error."	
	}

	return tempIntSet;}



IntSet IntSet::intersect(const IntSet& otherIntSet) const
{
   
	cout << "intersect() is not implemented yet..." << endl;
   return IntSet(); // dummy IntSet object returned

}



IntSet IntSet::subtract(const IntSet& otherIntSet) const
{
   
	cout << "subtract() is not implemented yet..." << endl;
   return IntSet(); // dummy IntSet object returned

}



void IntSet::reset()
{
   
	for(base = 0; base <= used; base++){
		data[base] = 0;
	}
}



bool IntSet::add(int anInt)
{
  
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



bool IntSet::remove(int anInt)
{
   
	bool test = conatains(anInt);
	int temp;
	if(test = true){
		for (base = 0; base <= used; base++){
			if(data[base] != anInt){
				continue;
			}
			else{
				data[base] = NULL;
			}
		}

		for(base2 = 0; base2 <= used; base++)[
			if(data(base2) != NULL)){
				continue;
			}
			else if (data(base2) == NULL){
				if(data(base2 + 1) != NULL){
					data(base2) = data(base2 + 1);
					data(base2 + 1) = NULL;
				}
				else{
					cout << "Set is empty.";
				}
			}
				
		}
	return true;		
	}
	else {
		return false;
	}
}



//store instances into two seperate arrays, bubble sort each array, compare arrray. True if end is reached without returning false.

bool equal(const IntSet& is1, const IntSet& is2);{}
bool equal(const IntSet& is1, const IntSet& is2)
{
   
	int arr1[is1.used];
		int arr2[is2.used];
		int temp;

		if(is1.used != is2.used){
			return false;
		}

		for(base = 0; base <= is1.used; base++){
			arr1[base] = is1.data[base];
			arr2[base] = is2.data[base];
		}
		
		for (base2 = 0; base2 <= is1.used; base2++){
			if (arr1[base2]>arr1[base2 + 1]){
				temp = arr1[base2];
				arr1[base2] = arr1[base2 + 1];
				arr1[base2 + 1] = temp;
			}
		}
		for (base3 = 0; base3 <= is2.used; base3++){
			if(arr2[base3]>arr2[base3 + 1]){
				temp = arr2[base3 + 1]
				arr2[base3] = arr2[base3+1];
				arr2[base3 + 1] = temp;
			}
		}
		
		for (base4 = 0; base4 < is1.used; base4++){
			if(arr1[base4] == arr2[base4]){
				continue;
			}
			else if(arr1[base4] != arr2[base4]){
				return false;
			}
			else if(base4 == is1.used){
			
				return true;
			}
		}}
