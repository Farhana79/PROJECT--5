

// Farhana Sultana 
// farhana.sultana79@myhunter.cuny.edu
// Csci 235
// project 5

#ifndef CARD_SHOP_HPP_
#define CARD_SHOP_HPP_

#include "DoublyLinkedList.hpp"
#include "YGOCard.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

class CardShop : public DoublyLinkedList<YGOCard *>
{
public:
CardShop() = default; //default constructor
~CardShop(); //destructor calls clear

/**
@pre : the input file is in csv format: "name,type,level_rank,race,attribute,atk,def"
@param: the name of the input file
@post: Reads the input file and adds pointers to YGOCard objects
instantiated with the information read from the file.
*/
CardShop(std::string input_file_name); //parameterized constructor

//@post: displays information of all cards in the shop, one per line
void display();

//@param: the index of the first card to be displayed
//@param: the index of the last card to be displayed
//@post: displays the names of all cards in the shop with startRange and endRange,
// inclusive, one per line
void displayName(int startRange, int endRange);

//@post: removes all cards from the shop
void clear();

//@return: true if all the cards in rhs are equal to the cards in the shop, false otherwise
bool operator==(const CardShop &rhs) const;

//@post: sorts the cards in the shop using bubble sort algorithm
void bubbleSort();

//@post: sorts the cards in the shop using insertion sort algorithm
void insertionSort();

//@post: sorts the cards in the shop using quick sort algorithm
void quickSort(int low, int high);

//@post: sorts the cards in the shop using merge sort algorithm
void mergeSort(int left, int right);

private:
// Helper function for bubbleSort
void swap(int i, int j);

// Helper function for insertionSort
void insertion(int index);

// Helper function for quickSort
int partition(int low, int high);

// Helper function for mergeSort
void merge(int left, int mid, int right);
};

#endif
