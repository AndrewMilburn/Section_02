#include "FBullCowGame.h"
#include <map>
#define TMap std::map

using FString = std::string;
using int32 = int;

FBullCowGame::FBullCowGame() { Reset(); }

int32 FBullCowGame::GetMaxTries() const { return MyMaxTries; }
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return (bGameIsWon); }

//	Reset tries and word (plus difficulty)
void FBullCowGame::Reset()
{
	constexpr int32 MAX_TRIES = 5;
	const FString HIDDEN_WORD = "planet";
	
	MyMaxTries = MAX_TRIES;
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameIsWon = false;

	return;
}


EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess)) 
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (false)	// TODO if not all lowercase
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (GetHiddenWordLength() != Guess.length()) // if guess length is wrong
	{
		return EGuessStatus::Wrong_Length;
	}
	else		// return OK
	{
		return EGuessStatus::OK;
	}

}

// Counts Bulls and Cows, and increases try # (assuming valid guess)
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	// loop through letters in hidden word
	int32 HiddenWordLength = MyHiddenWord.length();
	for (int32 MHWChar = 0; MHWChar < HiddenWordLength; MHWChar++)
	{
		// compare letters against guess
		for (int32 GChar = 0; GChar < HiddenWordLength; GChar++)
		{
			// if they match then
			if (MyHiddenWord[MHWChar] == Guess[GChar])
			{
				if (MHWChar == GChar) // inc bulls if in the right place
				{
					BullCowCount.Bulls++;
				}
				else		// inc Cows if not
				{
					BullCowCount.Cows++;
				}
			}
		}
	}
	bGameIsWon = (BullCowCount.Bulls == HiddenWordLength);
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Guess) const
{
	// treat 0 & 1 letter words as isograms
	if (Guess.length() <= 1) { return true; }
	// setup map
	TMap<char, bool> LetterSeen;

	// loop through each letter in guess
	for (auto Letter : Guess)
	{
		Letter = tolower(Letter);	// Allows mixed Case Guesses
		if (LetterSeen[Letter])
			// we do NOT have isogram
			return false;
		else
			// add it to the map
			LetterSeen[Letter] = true;
	}
	
	return true;
}

