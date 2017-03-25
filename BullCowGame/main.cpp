/*	This is the console executable, that makes use of the BullCow Class
This acts as the view in a MVC pattern, and is responsible for all
user interaction. For game logic see the FBullCowGame Class.
*/

#include <iostream>
#include <string>
#include "FBullCowGame.h"

// 2.44 7:12
 

using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
bool AskToPlayAgain();
FText GetValidGuess();
void PrintGameSummary();

// Instantiate a new game
FBullCowGame BCGame;	

// entry Point of App
int main() 
{
	bool bPlayAgain = false;
	do
	{
		PrintIntro();
		PlayGame();
		PrintGameSummary();
		bPlayAgain = AskToPlayAgain();
	}
	while (bPlayAgain);
	
	std::cout << std::endl;
	return 0;	// Exit App
}

//Output Welcome & Rules
void PrintIntro() 
{

	std::cout << "\n\nWelcome to Bulls and Cows. A fun word game.\n";
	std::cout << "An Isogram is a word (or phrase) with no repeatedd letters.\n";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I am thinking of?\n";
	std::cout << "You have " << BCGame.GetMaxTries() << " tries\n";

	return;
}

//Loop for number of tries
void PlayGame()
{ 
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	
	//	loop asking for guesses while game is NOT won
	// and there are still tries available

	while( !BCGame.IsGameWon() && BCGame.GetCurrentTry()<= MaxTries)
	{
		FText Guess = GetValidGuess();

		//	Submit Valid guess to the game and get counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		
		// Print number of bulls and cows
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << std::endl;
		std::cout << std::endl;
	}
	return;
}

// Get guess from player and loop until it is valid (isogram, right length etc.)
FText GetValidGuess()
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do
	{
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "\nTry " << CurrentTry << ". Enter your Guess: ";
		std::getline(std::cin, Guess);
		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Not_All_Letters:
			std::cout << "Guess must not contain any numbers or special characters\n";
			std::cout << "Please Enter a " << BCGame.GetHiddenWordLength() << " letter word\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Guess must be in Lower Case\n";
			std::cout << "Please Enter a " << BCGame.GetHiddenWordLength() << " letter word\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Guess must be an isogram\n";
			std::cout << "Please Enter a " << BCGame.GetHiddenWordLength() << " letter word\n";
			break;
		case EGuessStatus::Wrong_Length:
			std::cout << "Guess must contain " << BCGame.GetHiddenWordLength() << " letters\n";
			std::cout << "Please Enter a " << BCGame.GetHiddenWordLength() << " letter word\n";
			break;
		default:
			break;
		}
	} while (Status != EGuessStatus::OK);
	return Guess;
}

// How did Player do?
void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "** YOU WON!! ** \n";
	}
	else
	{
		std::cout << "Better Luck Next time :-(\n";
	}
}

// Has the player had enough?
bool AskToPlayAgain()
{
	std::cout << "\nDo you want to play again (y / n)? ";
	FText Response = "";
	std::getline(std::cin, Response);
	return ((Response[0] == 'y') || (Response[0] == 'Y'));

}