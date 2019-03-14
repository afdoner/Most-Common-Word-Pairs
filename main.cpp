/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Andrew
 *
 * Created on April 2, 2018, 10:41 PM
 */

#include <fstream>
#include <iostream>
#include <cstdlib>
using namespace std;

//------------------------------------------------------------------
// Insertion sort algorithm
//------------------------------------------------------------------
void insertion_sort(int int_data[], string str_data[], int low, int high)
{
   // Insert each element of unsorted list into sorted list
   for (int unsorted = low + 1; unsorted <= high; unsorted++)
   {
      // Select unsorted value to be inserted
      int int_value = int_data[unsorted];
      string str_value = str_data[unsorted];
      int posn = unsorted;

      // Make room for new data value
      while ((posn > 0) && (int_data[posn - 1] < int_value))
      {
	 int_data[posn] = int_data[posn - 1];
	 str_data[posn] = str_data[posn - 1];
	 posn--;
      }

      // Put new value into array
      int_data[posn] = int_value;
      str_data[posn] = str_value;
   }
}

void merge_sort(string data[], int low, int high)
{
   // Check terminating condition
   int range = high - low + 1;
   if (range > 1)
   {
      // Divide the array and sort both halves
      int mid = (low + high) / 2;
      merge_sort(data, low, mid);
      merge_sort(data, mid + 1, high);

      // Create temporary array for merged data
      string *copy = new string[range];

      // Initialize array indices
      int index1 = low;
      int index2 = mid + 1;
      int index = 0;

      // Merge smallest data elements into copy array
      while (index1 <= mid && index2 <= high)
      {
	 if (data[index1] < data[index2])
	    copy[index++] = data[index1++];
	 else
	    copy[index++] = data[index2++];
      }

      // Copy any remaining entries from the first half
      while (index1 <= mid)
	 copy[index++] = data[index1++];

      // Copy any remaining entries from the second half
      while (index2 <= high)
	 copy[index++] = data[index2++];

      // Copy data back from the temporary array
      for (index = 0; index < range; index++)
	 data[low + index] = copy[index];
      delete[]copy;
   }
}

//------------------------------------------------------------------
// Main program
//------------------------------------------------------------------
int main()
{
   // Declare word array
   const int NUM_WORDS = 100000;
   string words[NUM_WORDS];
   int num_words = 0;
   
   const int NUM_WORDS2 = 100000;
   string words2[NUM_WORDS2];
   int num_words2 = 0;

   // Declare pair arrays
   const int NUM_PAIRS = 15000;
   string pair_word[NUM_PAIRS];
   int pair_count[NUM_PAIRS];
   int num_pairs = 0;

   // Get input file
   cout << "Please enter a text file (including .txt)." << endl;
   string textfile = "";
   cin >> textfile;
   // Open input file
   ifstream din;
   din.open(textfile);

   // Read words from file
   while (!din.eof() && num_words < NUM_WORDS)
   {
      // Skip non-alphabetic characters
      char ch = ' ';
      while (!din.eof() && !isalpha(ch))
         din.get(ch);

      // Read alphabetic characters
      string word = "";
      while (!din.eof() && isalpha(ch))
      {
         word = word + char(tolower(ch));
         din.get(ch);
      }

      // Save word
      if (word != "")
         words[num_words++] = word;
   }

   // Close file
   din.close();
   
   for (int i=0; i<num_words-1; i++) {
       words2[i] = words[i] + " " + words[i+1];
       num_words2++;
       cout << words2[i] << endl;
   }

   // Sort words
   merge_sort(words2, 0, num_words2-1);

   // Count words
   pair_word[0] = words2[0]; 
   pair_count[0] = 1;
   for (int i=1; i<num_words2; i++)
   {
      // Same word found
      if (words2[i] == pair_word[num_pairs])
         pair_count[num_pairs]++;

      // Different word found
      else
      {
         num_pairs++;
         pair_word[num_pairs] = words2[i];
         pair_count[num_pairs] = 1;
      }
   }
   num_pairs++;

   // Sort pairs
   insertion_sort(pair_count, pair_word, 0, num_pairs-1);

   // Get user input
   cout << "How many top word pairs do you want to print? ";
   int num_top;
   cin >> num_top;
   if (num_top > num_pairs)
      num_top = num_pairs;

   // Print word pairs
   for (int i=0; i<num_top; i++)
      cout << pair_count[i] << " " 
           << pair_word[i] << endl;
}