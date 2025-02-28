#include <fstream>
#include <string>
#include <cctype>
#include <iostream>
#include <math.h>
using namespace std;

struct player
{
	string name;
	int score = 0;
	int rank = 1;
};

int read_questions(ifstream &, string [][5]); //Returns num of questions
int read_answers(ifstream &, char []); //Returns num of answers
void play_game(int , string [][5], char [], player &);
void show_question(string [][5], int, char, bool, player &, int); //Displays questions and omits wrong choices
void sort_score(fstream &, player &, player &);
char player_try(); //Checks if player guess is within range
bool validRandNum(int, int, int []); //Prevents repeated questions from rand




int main(int argc, char* argv[])
{	
	int numQuestions = 0;
	int numAnswers = 0;
	int playerScore = 0;
	int playerCount = 0;

	string questions[50][5];
 	char answers[50];

	ifstream questionFile;
	ifstream answerFile;
	fstream scoreBoard;

	if (argc != 4) //Checks for usage errors
	{
		cout << "Incorrect program usage." << endl;
		cout << "Please read the program description and try again. Exiting" << endl;

		return -1;
	}

	//Finds path of input files and seed for rand
	string questionFilePath = argv[1];
	string answerFilePath = argv[2];
	int seedRand = stoi(argv[3]);

	//Open required files
	questionFile.open(questionFilePath);
	answerFile.open(answerFilePath);
	scoreBoard.open("summary.txt", fstream::out | fstream::in | fstream::app);

	if (!questionFile.is_open() && !answerFile.is_open()) //Check that files opened properly
	{
		cout << "Error opening files. Exiting program." << endl;
		return -1;
	}

	if (questionFile.peek() == questionFile.eof() || answerFile.peek() == answerFile.eof()) //Checks for empty input files
	{
		cout << "The question file or the answer file is empty." << endl;
		cout << "Please check files and try again. Exiting." << endl;

		return -1;
	}

	numQuestions = read_questions(questionFile, questions);
	numAnswers = read_answers(answerFile, answers);

	if (numQuestions != numAnswers)
	{
		cout << "The question and answer files have different number of items." << endl;
		cout << "Please check the files and try again. Exiting." << endl;
		return -1;
	}

	player currentPlayer; //Creates struct for current player information
	currentPlayer.score = 0;

	srand(seedRand);//Seeds rand

	play_game(numQuestions, questions, answers, currentPlayer);
	cout << endl;

	cout << currentPlayer.name << ", your final score was: " << currentPlayer.score << " points." << endl;
	cout << "This will be recorded to the game history file." << endl << endl;

	scoreBoard << currentPlayer.name << "\t" << currentPlayer.score << endl; //Outputs current player's name and score

	player firstPlace = { currentPlayer.name, currentPlayer.score, 1 }; //Sets currentPlayer as first place



	scoreBoard.seekg(0);

	sort_score(scoreBoard, firstPlace, currentPlayer);

	scoreBoard.close();
	questionFile.close();
	answerFile.close();

	return 0;
}

int read_questions(ifstream & inFile, string questions[][5])
{
	
	int i = 0; //Num of questions
	int j = 0;
	string temp;

	while (!inFile.eof())
	{
		for (j = 0; j < 5; j++)
		{
			getline(inFile, questions[i][j], '\n'); //Reads answer choices
		}

		getline(inFile, temp); //Skips the space between questions

		i++;
	}

	return i;
}

int read_answers(ifstream & inFile, char answers[])
{
	int i = 0; //Num of answers

	while (!inFile.eof())
	{
		inFile >> answers[i];

		i++;
	}

	return i - 1;
}

void play_game(int numQuestions, string questions[][5], char answers[], player &currentPlayer)
{
	string playerName;
	int randQuestion;
	int currentPoints;
	int previousPoints = 1;
	char playerChoice;
	char correctAnswer;
	char retryQuestion;

	int previousRand[6] = { -1, -1, -1, -1, -1, -1 }; //Used to check for valid rand numbers

	cout << "What's your name? >";
	cin >> currentPlayer.name;

	for (int i = 0; i < 6; i++)
	{
		currentPoints = previousPoints * 10;

		randQuestion = rand() % numQuestions; //Generates random question

		while (!validRandNum(randQuestion, i, previousRand)) //Validates rand is not repeated, loops otherwise
		{
			randQuestion = rand() % numQuestions;
		}

		correctAnswer = answers[randQuestion];

		show_question(questions, randQuestion, ' ', false, currentPlayer, i + 1); //Initial display of question
		playerChoice = player_try();

		if (playerChoice == correctAnswer)
		{
			cout << endl << "You got that one right, for " << currentPoints << " points.";

			currentPlayer.score += currentPoints;

			previousPoints = currentPoints;
		}
		else
		{
			cout << "That's an incorrect answer." << endl;
			cout << "Do you want to try again for 1/2 points? (Y/N) >" << endl;
			cin >> retryQuestion;

			if (retryQuestion == 'Y' || retryQuestion == 'y')
			{
				currentPoints /= 2;

				show_question(questions, randQuestion, playerChoice, true, currentPlayer, i + 1); //Display question without incorrect answer
				playerChoice = player_try();

				if (playerChoice == correctAnswer)
				{

					cout << "You got that one right, for " << currentPoints << " points.";

					currentPlayer.score += currentPoints;

					previousPoints = currentPoints;

				}
				else
				{
					cout << "Oh, that's wrong again. Sorry, but you've lost." << endl;
					cout << "Come back and try again after you study more" << endl;

					break;
				}
			}

		}

		if (i == 5) //Formats output
		{
			cout << endl << "That's the end of the game, there are no more questions!" << endl;
		}
		else
		{
			cout << endl;
		}
	}
}

void show_question(string questions[][5], int randQuestion, char firstAttempt, bool secondAttempt, player &currentPlayer, int currentQuestion)
{
	char answerLetters = 'A';

	cout << endl << currentPlayer.name << "\tHere's Question Number " << currentQuestion;

	if (secondAttempt) 
	{
		cout << " (2nd try)" << endl;
	}
	else
	{
		cout << endl;
	}

	cout << questions[randQuestion][0] << endl; //Displays question

	for (int i = 1; i < 5; i++) //Displays choices
	{
		if (answerLetters == firstAttempt) //Removes first attempt answer
		{
			cout << endl;
		}
		else
		{
			cout << answerLetters << ". " << questions[randQuestion][i] << endl;
		}

		answerLetters++;

	}
}

char player_try()
{
	char playerAttempt; 
	
	cout << endl << "Your choice? > ";
	cin >> playerAttempt;

	playerAttempt = toupper(playerAttempt);

	while (playerAttempt < 'A' || playerAttempt > 'D') //Checks range and reprompts user input 
	{
		cout << "Error: Answer choice outside the range of A-D ";
		cout << ", please select a choice within range." << endl;
		cout << "Your choice? > ";

		cin >> playerAttempt;
		playerAttempt = toupper(playerAttempt);

		cout << endl;
	}

	return playerAttempt;
}

bool validRandNum(int randNum, int index, int previousRand[])
{

	for (int i = 0; i < 6; i++)
	{
		if (randNum == previousRand[i])
		{
			return false; 
		}
	}
	previousRand[index] = randNum;

	return true;
}

void sort_score(fstream &scoreBoard, player &firstPlace, player &currentPlayer)
{
	while (!scoreBoard.eof())
	{
		string tempPlayerName;
		string tempPlayerScore;
		int tempScore;
		getline(scoreBoard, tempPlayerName, '\t');
		getline(scoreBoard, tempPlayerScore);

		if (tempPlayerScore != "") //Skips endl character at the end of file
		{
			tempScore = stoi(tempPlayerScore);

			if (currentPlayer.score < tempScore) //Determines current player's rank
			{
				currentPlayer.rank += 1;
			}

			if (firstPlace.score < tempScore) //Determines rank 1
			{
				firstPlace.name = tempPlayerName;
				firstPlace.score = tempScore;
			}
		}
	}

	cout << "The current record holder is " << firstPlace.name;
	cout << " with " << firstPlace.score << " points." << endl;
	cout << "You have achieved rank " << currentPlayer.rank;
	cout << " with " << currentPlayer.score << " points." << endl;

	cout << endl << "Thanks for playing, we hope you'll send all your friends to play." << endl;

}
