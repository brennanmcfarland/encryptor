#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <ctime>
#include <ctgmath>
#include <vector>
#include <fstream>
using namespace std;

int main()
{
	//setup
	string quit = "";
	string plainMessage;
	string encryptedMessage;
	time_t timer;
	const long long  KEY_GENERATOR = 12739103827338262911; //used to change time for key
	unsigned long long longkey = 0; //0 to 18446744073709551615
	long double keyA = 0.0;
	double keyB = 0.0;
	double keyC = 0.0;

	while (quit != "1")
	{
		//get info
		cout << "Enter message to encrypt:  ";
		getline(cin, plainMessage);
		cout << "This step may take a while...";

		//manipulate key
		longkey = time(&timer); //returns 10 digit # for key
		string tempStringKey = to_string(longkey);
		//takes last 3 digits of longkey (since the rest is always the same) and puts it in key
		long double key = (tempStringKey[tempStringKey.length() - 1] - 48) + (tempStringKey[tempStringKey.length() - 2] - 48) * 10 + (tempStringKey[tempStringKey.length() - 3] - 48) * 100;
		key = key / 100; //makes key a #.## value

		keyA = sin(key);
		keyB = cos(key);
		keyC = tan(key);

		//key = (key + KEY_GENERATOR) % 18446744073709551615; //combines time and constant to make key
		

		/*****************STAGE 1***************************
		**creates a 2d vector of values and their positions*
		****************************************************
		*/

		//vector to hold ascii values and their positions
		vector<vector<int>> stage1; //vector of int vectors
		vector<char> isprocessed; //holds values that are already processed
		isprocessed.reserve(1); //makes it at least 1 big
		//vector<int>* tempVector; //temporary vector pointer to hold values of that row until they're added in

		for (int i = 0; i < plainMessage.length(); i++) //for every character in the plain message
		{
			//see if the character is processed
			bool matchflag = false;
			for (int j = 0; j < isprocessed.size(); j++)
			{
				if (isprocessed[j] == plainMessage[i]){ matchflag = true; }
			}
			//if it's not, process it
			if (matchflag == false)
			{
				//add the value to the list of processed values
				isprocessed.push_back(plainMessage[i]);

				//add the value to the stage1 array and index its positions
				vector<int> tempVector = vector<int>(); //dereference the old vector so it doesn't get deleted, and create a new one
				tempVector.push_back(plainMessage[i]); //add the value
				for (int j = i; j < plainMessage.length(); j++) //scan the rest of the message for the same char and index all that char's positions, including the first one
				{
					if (plainMessage[j] == tempVector[0]) //if the characters match, index the position
					{
						tempVector.push_back(j);
					}
				}
				stage1.push_back(tempVector); //adds the contents of the temporary vector to stage1
			}
		}

		//at this point, it's a vector "grid", with the first column being the ascii values, and the rest being positions

		
		
		
		///*****************STAGE 2***************************
		//***multiplies each value in the 2d vector by key A, storing the result in stage2
		//
		
		vector<vector<long double>> stage2; //vector of double vectors

		stage2.resize(stage1.size());  //give stage2 same # rows as stage 1

		for (int i = 0; i < stage1.size(); i++)
		{
			for (int j = 0; j < stage1[i].size(); j++) //within that row, multiply the value by A for each index
			{
				stage2[i].push_back(((long double)(stage1[i][j]))*keyA);
			}
		}
		
		
		///******************STAGE 3 ************************
		//**intersperse a bunch of random junk in between, use
		//**fib sequence to figure out where each valid char is
		//
		
		string stage3 = ""; //holds concatination of vector stage2's elements

		for (int i = 0; i < stage2.size(); i++)
		{
			for (int j = 0; j < stage2[i].size(); j++)
			{
				stage3.append(to_string(stage2[i][j])); //makes everything one long string
				stage3.append(" "); //puts spaces in between each value so it can be decoded
			}
		}



		//it's having issues because the numbers are getting too big
		//either it's overflowing the data type, or just taking too long to compute

		unsigned long long fibonnaci1 = 1;
		unsigned long long fibonnaci2 = 1;
		unsigned long long fibonnacitemp = 0;
		string encryptedMessage; //the final, totally encrypted message

		
		for (int i = 0; i < stage3.length(); i++) //find the length that encryptedMessage will need to be to hold all values from stage3
		{
			if (fibonnaci2 > 1779979416004714189) //if it's going to overflow, start over
			{
				fibonnaci1 = 1;
				fibonnaci2 = 1;
			}
			else
			{
				fibonnacitemp = fibonnaci2; //holds value of fibonnaci2 so 1 can be updated
				fibonnaci2 = fibonnaci2 + fibonnaci1; //compute next number in fibonnaci sequence
				fibonnaci1 = fibonnacitemp; //move old value to fibonnaci1
			}
			
		}

		//below is a set of random digits i created by mashing the keypad
		int randomValues[] = {3,1,2,3,4,8,2,7,6,3,1,2,5,4,6,5,7,2,4,9,6,7,8,4,6,2,1,5,6,7,3,2,1,8,9,1,6,7,4,3,8,5,1,7,2,3,2,4,8,9,6,4,3,7,5,2,1,4,8,9,7,6,3,1,2,8,1,9,6,7,4,2,4,5,8,4,3,1,8,8,7,4,2,4,9,6,4,7,2,1,8,5,6,4,3,2,1,1,5,8,6,5,4,2,4,5,1,6,5,6,3,4,2,7,8,9,5,4,6,1,2,8,1,9,8,7,6,4,2,8,1,8,5,6,7,4,2,1,1,5,8,5,5,7,6,4,2,3,1,9,8,1,6,7,1,5,8,5,4,3,2,2,4,2,1,6,9,4,8,4,7,6,4,9,5,4,5,2,1,9,6,4};


		//reset fibonnaci numbers
		fibonnaci1 = 1;
		fibonnaci2 = 1;

		ofstream encryptionFile;
		encryptionFile.open("ENCRYPTED MESSAGE.txt", ios::out);

		for (int i = 0; i < stage3.length(); i++) //do the interspersing
		{
			//update fibonnaci numbers
			if (fibonnaci2 > 987)
			{
				fibonnaci1 = 1;
				fibonnaci2 = 1;
			}
			else
			{
				fibonnacitemp = fibonnaci2; //holds value of fibonnaci2 so 1 can be updated
				fibonnaci2 = fibonnaci2 + fibonnaci1; //compute next number in fibonnaci sequence
				fibonnaci1 = fibonnacitemp; //move old value to fibonnaci1
			}

			int x = 0;
			for (int j = 0; j < fibonnaci2; j++) //insert a bunch of random characters before a real one
			{
				//prints a random digit
				if (x == 0 || x == 3 || x == 6 || x == 9)
				{
					string randomNumbertempstring = to_string(abs(cos(time(&timer) + randomValues[j%182])));
					encryptionFile << (randomNumbertempstring[randomNumbertempstring.length() - 1] - 48);
					x++;
					if (x == 10){x = 0;}
				}
				else if (x == 1 || x == 2 || x == 7)
				{
					string randomNumbertempstring = to_string(abs(sin(time(&timer) + randomValues[j%182])));
					encryptionFile << (randomNumbertempstring[randomNumbertempstring.length() - 1] - 48);
					x++;
					if (x == 10){ x = 0; }
				}
				else
				{
					string randomNumbertempstring = to_string(abs(tan(time(&timer) + randomValues[j%182])));
					encryptionFile << (randomNumbertempstring[randomNumbertempstring.length() - 1] - 48);
					x++;
					if (x == 10){ x = 0; }
				}
			}
			encryptionFile << stage3[i]; //add the real value
		}
		encryptionFile << int(key * 100); //append key as last 3 digits
		encryptionFile.close();
		stage3 = ""; //reset stage 3 (so that the decryptor doesn't "cheat"

			//ideas: insert key at intervals through message, make them not even
			//expand uncoded characters into many, dependent on position

		


		
		/*						DECRYPTION
		******DON'T FORGET TO TAKE THIS PART OUT AT THE END********
		***********************************************************
		***********************************************************
		*/
		
		//*************STAGE 3***********************
		//read the correct values from the file, obtain the key and the message
		
		
		streampos begin, end;
		ifstream decryptionFile;
		decryptionFile.open("ENCRYPTED MESSAGE.txt", ios::in); //open the encrypted message file
		if (!decryptionFile.is_open())
		{
			cout << "error";
		}


		decryptionFile.seekg(0);
		char testtesttesting[] = {'0','0','0','0','0'};

		//reset fibonnaci numbers
		fibonnaci1 = 1;
		fibonnaci2 = 1;

		//determine the file size in characters minus the key and store into validcharsinFile
		long validcharsinFile = 0;
		decryptionFile.seekg(0, ios::end); //go to the end of the file
		validcharsinFile = decryptionFile.tellg();
		validcharsinFile = validcharsinFile - 3;
		decryptionFile.seekg(0, ios::beg); //go back to the beginning for decrypting

		char holder = '0'; //holder value to receive char from file to append to stage3
		while (decryptionFile.tellg() < validcharsinFile) //while we're still in the part of the file that contains the encrypted message
		{
			//update fibonnaci numbers
			if (fibonnaci2 > 987)
			{
				fibonnaci1 = 1;
				fibonnaci2 = 1;
			}
			else
			{
				fibonnacitemp = fibonnaci2; //holds value of fibonnaci2 so 1 can be updated
				fibonnaci2 = fibonnaci2 + fibonnaci1; //compute next number in fibonnaci sequence
				fibonnaci1 = fibonnacitemp; //move old value to fibonnaci1
			}

			int x = 0;
			for (int j = 0; j < fibonnaci2; j++) //skip through the irrelevant characters
			{
				//move the cursor forward one char
				decryptionFile.seekg(1, ios_base::cur);
			}
			//read the real value (where the cursor is now) into string stage3
			decryptionFile >> noskipws >> holder;
			stage3.append(to_string(holder));
		}

		//then, take the last 3 digits and use that to make the key

		decryptionFile.seekg(-3, ios::end); //put the cursor before the last 3 digits
		decryptionFile >> key; //put that value into key
		key = key / 100; //find the original key
		keyA = sin(key); //recalculate keyA
		

		decryptionFile.close(); //close the file

		

		
		//******************STAGE 2*******************

		//divide the values in stage2 by keyA, and store in stage1
		for (int i = 0; i < stage2.size(); i++)
		{
			for (int j = 0; j < stage2[i].size(); j++) //within that row, divide the value by A for each index
			{
				stage1[i][j] = (((long double)(stage2[i][j])) / keyA);
			}
		}
		
		//**********STAGE 1*******************
		//start by finding the highest location value in the stage1 vector
		int highest = 0;
		for (int i = 0; i < stage1.size(); i++)
		{
			for (int j = 1; j < stage1[i].size(); j++) //skip the first value because that's the character
			{
				if (stage1[i][j] > highest)
				{
					highest = stage1[i][j];
				}

			}
		}
		//now create a string with that number of positions, filled initially with NULL
		string decryptedMessage = "";
		decryptedMessage.resize(highest+1);
		//now fill the string with the characters specified by stage1
		for (int i = 0; i < stage1.size(); i++) //for every row
		{
			for (int j = 1; j < stage1[i].size(); j++) //again skip 1st value cause it's character
			{
				decryptedMessage[stage1[i][j]] = (char)(stage1[i][0]); //add the specified character at the specified position to the string
			}
		}
		
		
		//display
		cout << decryptedMessage << "\n";
		cout << "The encrypted message has been saved as a text file in this program's directory.  Have fun!\n";
		cout << "Press 1 to quit.  Hit enter to continue.  ";
		//cout << charIndex;
		getline(cin, quit);
	}
	return 0;
}