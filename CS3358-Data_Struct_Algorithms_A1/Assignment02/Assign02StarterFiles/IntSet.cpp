// FILE: IntSet.cpp - header file for IntSet class
//       Implementation file for the IntStore class
//       (See IntSet.h for documentation.)
// INVARIANT for the IntSet class:
// (1) Distinct int values of the IntSet are stored in a 1-D,
//     dynamic array whose size is stored in member variable
//     capacity; the member variable data references the array.
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
//     from data[used] through data[capacity - 1].
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
//
// DOCUMENTATION for private member (helper) function:
//   void resize(int new_capacity)
//     Pre:  (none)
//           Note: Recall that one of the things a constructor
//                 has to do is to make sure that the object
//                 created BEGINS to be consistent with the
//                 class invariant. Thus, resize() should not
//                 be used within constructors unless it is at
//                 a point where the class invariant has already
//                 been made to hold true.
//     Post: The capacity (size of the dynamic array) of the
//           invoking IntSet is changed to new_capacity...
//           ...EXCEPT when new_capacity would not allow the
//           invoking IntSet to preserve current contents (i.e.,
//           value for new_capacity is invalid or too low for the
//           IntSet to represent the existing collection),...
//           ...IN WHICH CASE the capacity of the invoking IntSet
//           is set to "the minimum that is needed" (which is the
//           same as "exactly what is needed") to preserve current
//           contents...
//           ...BUT if "exactly what is needed" is 0 (i.e. existing
//           collection is empty) then the capacity should be
//           further adjusted to 1 or DEFAULT_CAPACITY (since we
//           don't want to request dynamic arrays of size 0).
//           The collection represented by the invoking IntSet
//           remains unchanged.
//           If reallocation of dynamic array is unsuccessful, an
//           error message to the effect is displayed and the
//           program unconditionally terminated.

#include "IntSet.h"
#include <iostream>
#include <cassert>
using namespace std;

void IntSet::resize(int new_capacity)
{

    //set new_capacity to the minimum if needed
    if (new_capacity < used)
    {
        new_capacity = used;
    }

    //prevent array of capacity 0
    if (new_capacity == 0)
    {
        new_capacity == DEFAULT_CAPACITY;
    }


    int* newData = new int[new_capacity];

    for (int i = 0; i < used; i++)
    {
        newData[i] = data[i];
    }

    //deallocate data and replace it with newData
    delete[] data;
    data = newData;

    capacity = new_capacity;
}

IntSet::IntSet(int initial_capacity)
{
    used = 0; 
    capacity = initial_capacity;
    data = new int[capacity];
}

IntSet::IntSet(const IntSet& src)
{
    used = src.used;
    capacity = src.capacity;
    data = new int[capacity];

    //initialize all elem of data[]
    for (int i = 0; i < capacity; i++)
    {
        data[i] = src.data[i];
    }
}


IntSet::~IntSet()
{
    delete[] data;
}

IntSet& IntSet::operator=(const IntSet& rhs)
{
    used = rhs.used;
    capacity = rhs.capacity;
    
    //Dealocate data array
    delete[] data;

    //Initialize new data array
    data = new int[capacity];

    //repopulate this->data[] with rhs.data[]
    for (int i = 0; i < rhs.used; i++)
    {
        data[i] = rhs.data[i];
    }

   return *this;
}

int IntSet::size() const
{
    return used;
}

bool IntSet::isEmpty() const
{
    if (used == 0)
    {
        return true;
    }

    return false;
}

bool IntSet::contains(int anInt) const
{
    for (int i = 0; i < used; i++)
    {
        if (data[i] == anInt)
        {
            return true;
        }
    }
    return false;
}

bool IntSet::isSubsetOf(const IntSet& otherIntSet) const
{
    //tracks shared elements
    int sharedElm = 0;

    //returns true if IntSet is empty 
    if (used == 0)
    {
        return true;
    }

    //returns false if invoking IntSet is larger than otherIntSet
    if (used > otherIntSet.used)
    {
        return false;
    }

    //traverse both arrays and itterates sharedElm 
    for (int i = 0; i < used; i++)
    {
        for (int j = 0; j < otherIntSet.used; j++)
        {
            if (data[i] == otherIntSet.data[j])
            {
                sharedElm++;
            }
        }
    }

    //checks if all elemnts of IntSet are shared elements
    if (sharedElm == used)
    {
        return true;
    }
    else
    {
        return false;
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

IntSet IntSet::unionWith(const IntSet& otherIntSet) const
{
    //call copy constr
    IntSet tempIntSet(*this);

    //resize tempIntSet with worst case scenerio (all unique elem)
    tempIntSet.resize(capacity + otherIntSet.capacity);

    //adds elements from otherIntSet to tempIntSet
    for (int i = 0; i < otherIntSet.used; i++)
    {
        if (!tempIntSet.contains(otherIntSet.data[i]))
        {
            tempIntSet.data[tempIntSet.used] = otherIntSet.data[i];
            tempIntSet.used++;
        }

    }

    return tempIntSet;
}

IntSet IntSet::intersect(const IntSet& otherIntSet) const
{
    IntSet tempIntSet;

    //resize to the smallest capacity of the two IntSets
    if (capacity < otherIntSet.capacity)
    {
        tempIntSet.resize(capacity);
    }
    else
    {
        tempIntSet.resize(otherIntSet.capacity);
    }

    for (int i = 0; i < used; i++)
    {
        for (int j = 0; j < otherIntSet.used; j++)
        {
            if (data[i] == otherIntSet.data[j])
            {
                tempIntSet.data[tempIntSet.used] = otherIntSet.data[j];
                tempIntSet.used++;
            }
        }
    }

    return tempIntSet;
}

IntSet IntSet::subtract(const IntSet& otherIntSet) const
{
    //call copy constr
    IntSet tempIntSet(*this);

    for (int i = 0; i < used; i++)
    {
        for (int j = 0; j < otherIntSet.used; j++)
        {
            if (data[i] == otherIntSet.data[j])
            {
                tempIntSet.remove(data[i]);
            }
        }
    }

    return tempIntSet;
}

void IntSet::reset()
{
    used = 0;
}

bool IntSet::add(int anInt)
{
    //check if anInt already exists in data[]
    if (this->contains(anInt))
    {
        return false;
    }

    //check if data[] is full
    if (used == capacity)
    {
        //Increase capacity
        this->resize((capacity * 1.5) + 1);
    }

    //add elem
    data[used] = anInt;
    used++;

    return true;
}

bool IntSet::remove(int anInt)
{
    if (this->contains(anInt))
    {
        int index = 0;

        //find index of anInt
        for (int i = 0; i < used; i++)
        {
            if (data[i] == anInt)
            {
                index = i;
                break;
            }
        }

        //shift index of other elements -1
        for (index; index < used - 1; index++)
        {
            this->data[index] = data[index + 1];
        }

        used--;

        return true;
    }

    return false;
}

bool operator==(const IntSet& is1, const IntSet& is2)
{

    //check if both sets are empty
    if (is1.size() == 0 && is2.size() == 0)
    {
        return true;
    }
    else if (is1.size() != is2.size())
    {
        //check if both sets are the same size
        return false;
    }
    else
    {
        IntSet temp1(is1);
        IntSet temp2(is2);

        //use temp IntSets to avoid changing originals
        temp1 = temp1.subtract(temp2);

        //if temp1.size == 0 after subtracting temp2, then they are equal
        if (temp1.size() == 0)
        {
            return true;
        }
    }

   return false;
}
