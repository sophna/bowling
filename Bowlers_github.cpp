#include <iostream>
#include <string>
#include <iomanip> //should be included in order to use 'setfill'
#include <cassert>
#include <fstream>

const int HEADER_WIDTH = 60; //total lenght of the stream to output the program data
const int HEADER_WIDTH_LEFT_ALIGN = 45; //number of chars for banner including text
const int HEADER_WIDTH_RIGHT_ALIGN = 15; //numbers of chars for the banner to complete up to 70 chars

const int ALIGN_TABLE_DATA = 5;
const int ALIGN_SCORES = 20;
const int ALIGN_AVERAGE = 4;
const int ALIGN_LEFT_SCORES = 18;
const int ALIGN_RIGHT_SCORES = 14;

const int FILE_NUM_OF_BOWLERS = 10; // since the file format is guaranteed to be the same, we always going to read 10 lines from input file
const int NUM_OF_SCORES = 5; // since the file format is guaranteed to be the same, we always going to read 5 scores from input file
const int MAX_CHARS_PER_LINE = 200; //just a big number to function as limit on the number of chars to read while using the .get(str, m+1)

using namespace std;

struct Bowlers
{
  /* data */
  string bowlerName;
  int scores[NUM_OF_SCORES];
  int averageScore;
};


//declare function prototypes, they should be declared before function main, the second dimension of the two-size array can't be ommited 
bool GetBowlingData(string filename, Bowlers lbowlers[]);
void GetAverageScore(Bowlers lbowlers[]);
void PrettyPrintResults(Bowlers lbowlers[]);

int main(int argc, char* argv[])
{

  Bowlers bowlers[FILE_NUM_OF_BOWLERS];

  cout << setfill('*'); //use setfill to change the fill char to *
  cout << setw(HEADER_WIDTH) << "" << endl; //set the width of the line to 70 chars, output a null char to print the whole stream
  cout << setw(HEADER_WIDTH_LEFT_ALIGN) << "Welcome to my Bowlers program 2.0" << setw(HEADER_WIDTH_RIGHT_ALIGN) << "" << endl; //message is 34 chars lenght, fill up to HEADER_WIDTH_LEFT_ALIGN chars and then up to HEADER_WIDTH_RIGHT_ALIGN chars after the message
  cout << setw(HEADER_WIDTH) << "" << endl << endl; //output the * in the third row
    
	if (argc < 2) //The executable name and at least one argument?
	{
		std::cout << "Error - Please specify a file to analyze" << std::endl; //Display an error if argument is less than 2
		return 1;
	}

  bool result = GetBowlingData(argv[1], bowlers);
  if(result == true)
  {
    GetAverageScore(bowlers);
  }
  else{
    cout << "There was an error while proccesing the file, please use a valid format";
    return -1;
  }


  PrettyPrintResults(bowlers);
}
//define body of function GetBowlingData
bool GetBowlingData(string filename, Bowlers lbowlers[])
{
    string bowler_name;
    std::ifstream inFile;

    inFile.open(filename); //Open the file specified by argument 1
	  if (!inFile) //If specified file is not found
	  {
	  	std::cout << "Error with file name.." << std::endl; //display error
		  return false;
	  }

    for (int bowler_id = 0; bowler_id < FILE_NUM_OF_BOWLERS; bowler_id++) // since arrays first index is 0, and there always be only 5 scores, we loop from 0 to 4
    {
      int score_from_file=0;
      if (inFile >> bowler_name)
      {
        //do nothing, input was valid
      }
      else
      {
        return false; //error retunn from the extractor operator
      }
       //get from the file stream the bowler name, assuming the first element of the line is a string (bowlers name)
      lbowlers[bowler_id].bowlerName = bowler_name; 
      for (int score =0; score < NUM_OF_SCORES; score ++) //loop NUM_OF_SCORES times to get each score
      {
        if (inFile >> score_from_file) //get from the file stream the bowler score
        {
         //do nothing, input was valid
        } 
        else
        {
          return false; //input format incorrect, expecting an integer, but something else was in the file
        }
        lbowlers[bowler_id].scores[score] = score_from_file;
      }

    }
  return true;
}

void GetAverageScore(Bowlers lbowlers[])
{
    for (int bowler_id = 0; bowler_id < FILE_NUM_OF_BOWLERS; bowler_id++) // since arrays first index is 0, and there always be only 5 scores, we loop from 0 to 4
    {
      int average=0;
      for (int score =0; score < NUM_OF_SCORES; score ++) //loop NUM_OF_SCORES times to get each score
      {
        average = average + lbowlers[bowler_id].scores[score];
      }
      lbowlers[bowler_id].averageScore = average/NUM_OF_SCORES; //calculate the average of the scores and store it in the array since it was by reference
    }
}

void PrettyPrintResults(Bowlers lbowlers[])
{
    cout << setfill(' '); //use setfill to change the fill char to ' '
    cout << setw(ALIGN_TABLE_DATA) << left << "" << setw(ALIGN_SCORES - ALIGN_TABLE_DATA) << left << "Bowler";
    cout << setw(ALIGN_LEFT_SCORES) << right << "Scores"  << setw(ALIGN_RIGHT_SCORES) << right << "";
    cout << setw(ALIGN_TABLE_DATA) << left << "Average" << endl;
    
    for (int bowler_id = 0; bowler_id < FILE_NUM_OF_BOWLERS; bowler_id++) // since arrays first index is 0, and there always be only 5 scores, we loop from 0 to 4
    {
      cout << setw(ALIGN_SCORES - ALIGN_TABLE_DATA) << left << lbowlers[bowler_id].bowlerName <<  setw(ALIGN_TABLE_DATA) << left << "|";
      for (int score =0; score < NUM_OF_SCORES; score ++) //loop NUM_OF_SCORES times to get each score
      {
        cout << setw(ALIGN_TABLE_DATA) << left << lbowlers[bowler_id].scores[score] << ' ';
      }
      cout << setw(ALIGN_AVERAGE) << left << "|" << lbowlers[bowler_id].averageScore << endl;
    }
    
}