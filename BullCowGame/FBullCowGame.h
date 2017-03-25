#pragma once
#include <string>
// ??

using FString = std::string;
using int32 = int;

// two int32s, initialised to zero
struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus
{
	Invalid_Status,
	OK,
	Not_All_Letters,
	Not_Lowercase,
	Not_Isogram,
	Wrong_Length,

};

class FBullCowGame
{
public:
	FBullCowGame();	// Constructor

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const;
	
	void Reset(); // TODO make Reset more rich return value
	FBullCowCount SubmitValidGuess(FString);

	
private:
	int32 MyCurrentTry;	//
	int32 MyMaxTries;		// Constructor now holds initial values
	FString MyHiddenWord;
	bool bGameIsWon;

	bool IsIsogram(FString) const;
};