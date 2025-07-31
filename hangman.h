// Spring 2023
#ifndef HANGMAN_H
#define HANGMAN_H
#include <iostream>
#include <string>
#include <vector>
using namespace std;
const int N = 26;

class TrieNode {
	friend class Tester;
public:
	TrieNode(); // constructor
	~TrieNode(); // destructor
	void insertWord(TrieNode* root, string word); // inserts a string into trie
	void removeWord(TrieNode* root, string word); // removes a string from trie
	bool searchWord(TrieNode* root, string word); // searches for a string in trie
	bool selectWord(TrieNode* root, vector<string> words); // selects a random word 
	void guessLetter(); // checks if a letter has been guessed
	bool checkChar(char letter); // updates the guessed letters on the word
	bool checkRepeat(char letter); // checks for repeated entry 
	void displayLetters(); // letters entered
	void displayWord(); // dispalys the word and its progression
	void displayHang(); // displays stickman progression with wrong guesses
	bool gameEnd(); // ends the game when a win/loss condition is met
	void playGame(TrieNode game); // launches the game
private:
	TrieNode* children[N];
	bool m_wordEnd; // signifies end of word
	int m_correct; // number of correct guesses
	int m_strikes; // amount of wrong guesses
	string m_word; // word to be guessed
	vector<char> m_correctChar; // correct letters that have been entered
	vector<char> m_wrongChar; // wrong letters that have been entered
	vector<string> m_allWords; // contains all words in the trie, used only to run the game
};


#endif
