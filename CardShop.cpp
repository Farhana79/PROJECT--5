

// Farhana Sultana 
// farhana.sultana79@myhunter.cuny.edu
// Csci 235
// project 5

#include "CardShop.hpp"
#include "Node.hpp"
#include <iostream>
#include <fstream>
#include <sstream>


/**
  @pre  : the input file is in csv format: "name,type,level_rank,race,attribute,atk,def"
  @param: the name of the input file
  @post:  Reads the input file and adds pointers to YGOCard objects 
          instantiated with the information read from the file. 
    */
CardShop::CardShop(std::string input_file_name) 
{
  std::ifstream fin(input_file_name);
  if (fin.fail())
  {
    std::cerr << "File cannot be opened for reading. \n";
    exit(1); // exit if failed to open the file
  }
  //we don't use the first line
  std::string ignore;
  getline(fin, ignore);

  //the columns of the csv associated with the data members
  std::string name, type, race, attribute;
  int level_rank, atk, def;

  std::string temp_string;
  int temp_int;
  int item_counter = 0;
  while (getline(fin, temp_string, ','))
  {
    name = temp_string;

    getline(fin, type, ',');
  
    getline(fin, temp_string, ',');
    std::istringstream(temp_string) >> temp_int;
    level_rank = temp_int;

    getline(fin, race, ',');

    getline(fin, attribute, ',');

    getline(fin, temp_string, ',');
    std::istringstream(temp_string) >> temp_int;
    atk = temp_int;

    getline(fin, temp_string);
    std::istringstream(temp_string) >> temp_int;
    def = temp_int;

    //create new card
    YGOCard *card_ptr = new YGOCard(name, type, level_rank, race, attribute, atk, def);

    //add to linked list and increment counter
    insert(item_counter++, card_ptr);
  }
}

//@post: removes all cards from the shop
//Deallocate and delete items
void CardShop::clear()
{
  for (int i = 0; i < item_count_; i++)
  {
    YGOCard *ptr = getItem(i);
    delete ptr;
    ptr = nullptr;
  }
  DoublyLinkedList::clear();
}

//destructor
CardShop::~CardShop()
{
  clear();
}

//@post: displays information of all cards in the shop, one per line
void CardShop::display()
{
  for (int i = 0; i < item_count_; i++)
  {
    getItem(i)->display();
  }
}

  //@param: the index of the first card to be displayed
  //@param: the index of the last card to be displayed
  //@post: displays the names of all cards in the shop with startRange and endRange, 
  //       inclusive, one per line
void CardShop::displayName(int startRange, int endRange)
{
  for (int i = startRange; i <= endRange; i++)
  {
    getItem(i)->displayName();
    if (i != endRange)
    {
      std::cout << ", ";
    }
    else
    {
      std::cout << std::endl;
    }
  }
}


//@return:  true if all the cards in rhs are equal to the cards in the shop, false otherwise
bool CardShop::operator==(const CardShop &rhs) const
{
  if (getLength() != rhs.getLength())
  {
    return false;
  }
  for (int i = 0; i < getLength(); i++)
  {
    if (*(getPointerTo(i)->getItem()) == *(rhs.getPointerTo(i)->getItem()))
    {
      
    }
    else
    {
      return false;
    }
  }
  return true;
}

// Helper function for bubbleSort
void CardShop::swap(int i, int j) 
{
    Node* tempNode = getPointerTo(i);
    YGOCard* tempCard = tempNode->getItem();
    setPointerTo(i, getPointerTo(j));
    setPointerTo(j, tempNode);
    tempNode->setItem(tempCard);
}
//------------bubble sort algorithm----------------
void CardShop::bubbleSort()
{
    for (int i = 0; i < item_count_ - 1; i++)
    {
        for (int j = 0; j < item_count_ - i - 1; j++)
        {
            if (*(getItem(j)) > *(getItem(j + 1)))
            {
                swap(j, j + 1);
            }
        }
    }
}

//-----------------Helper function for insertionSort
void CardShop::insertion(int index) {
    YGOCard* key = getItem(index);
    int j = index - 1;
    while (j >= 0 && *(getItem(j)) > *key) {
        setPointerTo(j+1, getPointerTo(j));
        j--;
    }
    setPointerTo(j+1, getNode(index));
    getNode(index)->setItem(key);
}


//-----------------------Insertion sort algorithm
void CardShop::insertionSort()
{
    for (int i = 1; i < item_count_; i++)
    {
        insertion(i);
    }
}


//---------------------Helper function for quickSort
int CardShop::partition(int low, int high) {
    YGOCard* pivot = getItem(high);
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (*(getItem(j)) < *pivot) {
            i++;
            swap(i, j);
        }
    }
    swap(i + 1, high);
    return (i + 1);
}


//-----------------Helper function for quickSort
int CardShop::partition(int low, int high) {
    YGOCard* pivot = getItem(high);
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (*(getItem(j)) < *pivot) {
            i++;
            swap(i, j);
        }
    }
    swap(i + 1, high);
    return i + 1;
}

//------------------Quick sort algorithm
void CardShop::quickSort(int low, int high) {
    if (low < high) {
        int pi = partition(low, high);
        quickSort(low, pi - 1);
        quickSort(pi + 1, high);
    }
}


//------------------Helper function for mergeSort
void CardShop::merge(int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temp arrays
    YGOCard* leftArr[n1];
    YGOCard* rightArr[n2];

    // Copy data to temp arrays
    for (i = 0; i < n1; i++)
        leftArr[i] = getItem(left + i);
    for (j = 0; j < n2; j++)
        rightArr[j] = getItem(mid + 1 + j);

    // Merge the temp arrays back into arr[l..r]
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = left; // Initial index of merged subarray
    while (i < n1 && j < n2) {
        if (*leftArr[i] <= *rightArr[j]) {
            setPointerTo(k++, new Node(leftArr[i++]));
        }
        else {
            setPointerTo(k++, new Node(rightArr[j++]));
        }
    }

    // Copy the remaining elements of leftArr[], if there are any
    while (i < n1) {
        setPointerTo(k++, new Node(leftArr[i++]));
    }

    // Copy the remaining elements of rightArr[], if there are any
    while (j < n2) {
        setPointerTo(k++, new Node(rightArr[j++]));
    }
}

//-----------------------------Merge sort algorithm
void CardShop::mergeSort(int left, int right) {
    if (left < right) {
        // Same as (left+right)/2, but avoids overflow for
        // large left and right
        int mid = left + (right - left) / 2;

        // Sort first and second halves
        mergeSort(left, mid);
        mergeSort(mid + 1, right);

        // Merge the sorted halves
        merge(left, mid, right);
    }
}

