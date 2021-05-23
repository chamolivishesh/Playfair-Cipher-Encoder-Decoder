//*****************************************************************************
// PLAYFAIR CIPHER
//*****************************************************************************
//
// Note: Condition where 2 letters are in the same pair doesn't work properly
// Note: The letter 'J' should not be present in either Plaintext or Key 
//	 otherwise the cipher won't work properly
//*****************************************************************************

#include<iostream>
#include<string.h>
#include<ctype.h>

using namespace std;


char Grid [6][6];

//Making the Grid
void Grid_Write (char Key[])
{
	char Letters[] = "ABCDEFGHIKLMNOPQRSTUVWXYZ";

	int col_count = 0, row_count = 1;

	//Initializing the Key with '_'
	for (int i=0; i < 5; i++)
		for (int j=0; j < 5; j++)
			Grid [i][j] = '_';

	//Move the Key letters to the 1st row of the grid and mark the common letters in Letters[]
	for (int i=0; i < 5; i++)
		for (int j=0; j < 25; j++)
			if (Key [i] == Letters [j])
			{
				Grid [0][i] = Key [i];
				Letters [j] = '_';
				break;
			}

	//Move the remaining letters to the Grid
	for (int i=0; i < 25; i++)
	{
		if (Letters [i] != '_')
		{
			Grid [row_count][col_count] = Letters [i];

			if (col_count < 4)
				col_count ++;
			else
			{
				col_count = 0;
				row_count ++;
			}
		}
	}
}

//Encryption Algorithm
void Encrypt_Algorithm(char Plaintext[], char Ciphertext[])
{
	//Starting to pick 1 pair of letters from Plaintext at a time
	for (int p=0; p < strlen(Plaintext); p += 2)
	{

		//Selecting the positions for the 2 letters in pos1 and pos2 from the Grid
		int pos1 [2] = {6,6}, pos2 [2] = {6,6}, flag=0;
		for (int i=0; i < 5; i++)
		{
			for (int j=0; j < 5; j++)
			{
				if (Plaintext [p] == Grid [i][j])
				{
					pos1 [0] = i;
					pos1 [1] = j;
				}

				if (Plaintext [p+1] == Grid [i][j])
				{
					pos2 [0] = i; 
                                        pos2 [1] = j;
				}

				if (pos1 [0] != 6 && pos1 [1] != 6 && pos2 [0] != 6 && pos2 [1] != 6)
					flag = 1;
			}
			if (flag == 1)
				break;
		}

		//Encryption Starts
		//If in same column condition
		if (pos1 [1] == pos2 [1])
		{
			pos1 [0] ++;
			pos2 [0] ++;

			//checking if position go out of bound i.e more than 4
			if (pos1 [0] > 4)
				pos1 [0] = 0;

			if (pos2 [0] > 4)
				pos2 [0] = 0;
		}

		//If in same row condition
		if (pos1 [0] == pos2 [0])
		{
			pos1 [1] ++;
			pos2 [1] ++;

			//checking if position go out of bound i.e more than 4
			if (pos1 [1] > 4)
				pos1 [1] = 0;

			if (pos2 [1] > 4)
				pos2 [1] = 0;
		}

		//If in different row and column
		if (pos1 [0] != pos2 [0] && pos1 [1] != pos2 [1])
		{
			pos1 [1] = pos1 [1] + pos2 [1];
			pos2 [1] = pos1 [1] - pos2 [1];
			pos1 [1] = pos1 [1] - pos2 [1];
		}

		Ciphertext [p] = Grid [pos1 [0]][pos1 [1]];
		Ciphertext [p+1] = Grid [pos2 [0]][pos2 [1]];
	}
}

//Decryption Algorithm (Not implemented)
void Decrypt_Algorithm(char Plaintext[], char Ciphertext[])
{
	//Starting to pick 1 pair of letters from Ciphertext at a time
	for (int p=0; p < strlen(Ciphertext); p += 2)
	{

		//Selecting the positions for the 2 letters in pos1 and pos2 from the Grid
		int pos1 [2] = {6,6}, pos2 [2] = {6,6}, flag=0;
		for (int i=0; i < 5; i++)
		{
			for (int j=0; j < 5; j++)
			{
				if (Ciphertext [p] == Grid [i][j])
				{
					pos1 [0] = i;
					pos1 [1] = j;
				}

				if (Ciphertext [p+1] == Grid [i][j])
				{
					pos2 [0] = i; 
                                        pos2 [1] = j;
				}

				if (pos1 [0] != 6 && pos1 [1] != 6 && pos2 [0] != 6 && pos2 [1] != 6)
					flag = 1;
			}
			if (flag == 1)
				break;
		}

		//Encryption Starts
		//If in same column condition
		if (pos1 [1] == pos2 [1])
		{
			pos1 [0] --;
			pos2 [0] --;

			//checking if position go out of bound i.e more than 4
			if (pos1 [0] < 0)
				pos1 [0] = 4;

			if (pos2 [0] < 0)
				pos2 [0] = 4;
		}

		//If in same row condition
		if (pos1 [0] == pos2 [0])
		{
			pos1 [1] --;
			pos2 [1] --;

			//checking if position go out of bound i.e more than 4
			if (pos1 [1] < 0)
				pos1 [1] = 4;

			if (pos2 [1] < 0)
				pos2 [1] = 4;
		}

		//If in different row and column
		if (pos1 [0] != pos2 [0] && pos1 [1] != pos2 [1])
		{
			pos1 [1] = pos1 [1] + pos2 [1];
			pos2 [1] = pos1 [1] - pos2 [1];
			pos1 [1] = pos1 [1] - pos2 [1];
		}

		Plaintext [p] = Grid [pos1 [0]][pos1 [1]];
		Plaintext [p+1] = Grid [pos2 [0]][pos2 [1]];
	}
}

//Called if encryption is selected
int encryption()
{
	char Plaintext [100];
	char Ciphertext [100];
	char Key [6];
	
	cout << "\nEnter the Plaintext (without spaces) - ";
	cin >> Plaintext;
	
	//To check if invalid alphabets present in plaintext and if all correct, make the whole string upper case
	for (int i=0; i < strlen (Plaintext); i++)
	{
		if (!isalpha (Plaintext [i]))
		{
			cout << "\nError: Invalid chars present in Plaintext\nExiting...\n";
			return 0;
		}
		if (Plaintext [i] > 90)
			Plaintext [i] = Plaintext [i] - 32;
	}
	
	//If Plaintext has odd no. of chars, add 'X' at end to complete the pair
	if (strlen (Plaintext) % 2 != 0)
	{
		Plaintext [strlen (Plaintext)] = 'X';
		cout << "Adding 'X' at the end to complete the pair.\n";
	}
	
	cout << "Enter the 5 digit Key - ";
	
	cin >> Key;
	
	//To check the Key is exactly 5 characters
	if (strlen (Key) != 5)
	{
		cout << "\nError: The key is not 5 letters.\nExiting...\n";
		return 0;
	}
	
	//To check if invalid alphabets present in Key and if all correct, make the whole string upper case
	for (int i=0; i < strlen (Key); i++)
	{
		if (!isalpha (Key [i]))
		{
			cout << "\nError: Invalid chars present in Key\nExiting...\n";
			return 0;
		}
		if (Key [i] > 90)
			Key [i] = Key [i] - 32;
	}
	
	//Generate the Grid
	Grid_Write(Key);

	cout << "\nThe generated Grid is:\n";
	//Display the Grid
        for (int i=0; i < 5; i++)
        {
                for (int j=0; j < 5; j++)
                        cout << Grid [i][j] << " ";
                cout << "\n";
        }

	Encrypt_Algorithm(Plaintext, Ciphertext);

	cout << "\nThe Encrypted CipherText is:\n" << Ciphertext << "\n";
	return 0;
}

//Called if decryption is selected
int decryption()
{
	char Plaintext [100];
	char Ciphertext [100];
	char Key [6];
	
	cout << "\nEnter the Ciphertext (without spaces) - ";
	cin >> Ciphertext;
	
	//If Ciphertext has odd no. of chars, then Ciphertext is invalid
	if (strlen (Ciphertext) % 2 != 0)
	{
		cout << "Invalid Ciphertext.\nExiting...\n";
		return 0;
	}
	
	//To check if invalid alphabets present in Ciphertext and if all correct, make the whole string upper case
	for (int i=0; i < strlen (Ciphertext); i++)
	{
		if (!isalpha (Ciphertext [i]))
		{
			cout << "\nError: Invalid chars present in Ciphertext\nExiting...\n";
			return 0;
		}
		if (Ciphertext [i] > 90)
			Ciphertext [i] = Ciphertext [i] - 32;
	}
	
	cout << "Enter the 5 digit Key - ";

	cin >> Key;
	
	//To check the Key is exactly 5 characters
	if (strlen (Key) != 5)
	{
		cout << "\nError: The key is not 5 letters.\nExiting...\n";
		return 0;
	}
	
	//To check if invalid alphabets present in Key and if all correct, make the whole string upper case
	for (int i=0; i < strlen (Key); i++)
	{
		if (!isalpha (Key [i]))
		{
			cout << "\nError: Invalid chars present in Key\nExiting...\n";
			return 0;
		}
		if (Key [i] > 90)
			Key [i] = Key [i] - 32;
	}
	
	//Generate the Grid
	Grid_Write(Key);

	cout << "\nThe generated Grid is:\n";
	//Display the Grid
        for (int i=0; i < 5; i++)
        {
                for (int j=0; j < 5; j++)
                        cout << Grid [i][j] << " ";
                cout << "\n";
        }

	Decrypt_Algorithm(Plaintext, Ciphertext);

	cout << "\nThe Decrypted PlainText is:\n" << Plaintext << "\n";
	return 0;
}

int main()
{

	char ed;
	
	cout << "PLAYFAIR CIPHER\n\n";
	cout << "Do you want to Encrypt or Decrypt? (E/D) - ";
	cin >> ed;
	
	if (ed == 'e' || ed == 'E')
		encryption();
		
	else if (ed == 'd' or ed == 'D')
		decryption();
		
	else
		cout << "Invalid option.\nExiting...\n";
	
	return 0;
}


