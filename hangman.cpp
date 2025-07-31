// Spring 2023 
#include "hangman.h"

TrieNode::TrieNode() { // constructor
	m_wordEnd = false;
	m_correct = 0;
	m_strikes = 0;
	m_word = "NONE";
	m_correctChar = { };
	m_wrongChar = { };
	m_allWords = { };
	for (int i = 0; i < N; i++) { // allocate for all children of the node
		children[i] = nullptr;
	}
}

TrieNode::~TrieNode() { // destructor
	for (int i = 0; i < N; i++) { // delete all children
		delete[] children[i];
	}
	m_wordEnd = false; // reinitiallize variables
	m_correct = 0;
	m_strikes = 0;
	m_word = "NONE";
	m_correctChar = { };
	m_wrongChar = { };
	m_allWords = { };
}

void TrieNode::insertWord(TrieNode* root, string word) { // inserts a string
	TrieNode* temp = root;
	if (!searchWord(temp, word) && word != " ") { // word not found, proceed with insert
		for (int i = 0; word[i] < word.length(); i++) {
			if (temp->children[word[i] - 'a'] == nullptr) { // path does not exist
				temp->children[word[i] - 'a'] = new TrieNode(); // make node
			}
			temp = temp->children[word[i] - 'a']; // go to next node
		}
		m_wordEnd = true; // mark the end of the inserted string
	}
}

void TrieNode::removeWord(TrieNode* root, string word) {
	TrieNode* temp = root;
	if (searchWord(temp, word)) { // word found, proceed with remove
		for (int i = 0; word[i] < word.length(); i++) {
			delete[] temp->children[word[i] - 'a']; // delete node
			temp = temp->children[word[i] - 'a']; // go to next node
		}
		m_wordEnd = true; // mark the end of the inserted string
	}
}

bool TrieNode::searchWord(TrieNode* root, string word) {
	TrieNode* temp = root;
	for (int i = 0; word[i] < word.length(); i++) {
		if (temp->children[word[i] - 'a'] == nullptr) { // path does not exist
			return false; // word not found
		}
		temp = temp->children[word[i] - 'a'];
	}
	if (temp != nullptr && temp->m_wordEnd == true) { // end of string, word not included
		return false; // word not found
	}
	return true;
}

bool TrieNode::selectWord(TrieNode* root, vector<string> words) {
	bool select = false;
	TrieNode* temp = root;
	string random = words[rand() % words.size()]; // selects a random word using modulus
	if (searchWord(temp, random)) {
		m_word = random;
		select = true;
	}
	else {
		cout << "Error: selected word not in the trie\n";
	}
	return select;
}

void TrieNode::guessLetter() {
	char letter;
	int guessed = 0;
	bool repeated = true;

	while (repeated) {
		cout << "\nEnter a letter: "; // user input prompt
		cin >> letter;
		letter = tolower(letter); // all words are modified to lowercase for simpler functionality
		if (!checkRepeat(letter)) { // repeat protection
			repeated = false;
		}
		else {
			cout << "You have already guessed that letter. Try another one\n";
		}
	}
	for (int i = 0; i < m_word.length(); i++) {
		if (letter == m_word[i]) {
			m_correctChar.push_back(letter);
			m_correct++; // correct guesses
			guessed++;
		}
	}
	if (guessed == 0) { // letter not in word
		m_wrongChar.push_back(letter); // added to vector for future display purposes
		m_strikes++; // each strike is a limb for the hangman
	}
}

bool TrieNode::checkChar(char letter) {
	bool guessed = false;
	for (int i = 0; i < m_correctChar.size(); i++) {
		if (letter == m_correctChar[i]) {
			guessed = true;
		}
	}
	return guessed;
}
bool TrieNode::checkRepeat(char letter) {
	bool repeat = false;
	for (int i = 0; i < m_correctChar.size(); i++) {
		if (letter == m_correctChar[i]) {
			repeat = true;
		}
	}
	for (int i = 0; i < m_wrongChar.size(); i++) {
		if (letter == m_wrongChar[i]) {
			repeat = true;
		}
	}
	return repeat;
}


void TrieNode::displayLetters() { // displays wrong letters in the game
	cout << "Wrong letters: ";
	for (int i = 0; i < m_wrongChar.size(); i++) {
		cout << m_wrongChar[i] << " ";
	}
	cout << endl;
}

void TrieNode::displayWord() { // displays the word with only guessed letters shown
	cout << "\t";
	for (int i = 0; i < m_word.length(); i++) {
		if (checkChar(m_word[i])) {
			cout << m_word[i] << " ";
		}
		else {
			cout << "_ ";
		}	
	}
	cout << endl;
}

void TrieNode::displayHang() { // displays stickman progression with strikes
	switch (m_strikes) {
	case 0: // 0 wrong guesses; no stickman
		cout << "\t______" << endl << "\t|" << endl << "\t|" << endl << "\t|" << endl << "\t|" << endl << "\t|" << endl << "\t---------" << endl;
		break;
	case 1: // 1 wrong guess; rope
		cout << "\t______" << endl << "\t|    |" << endl << "\t|" << endl << "\t|" << endl << "\t|" << endl << "\t|" << endl << "\t---------" << endl;
		break;
	case 2: // 2 wrong guesses; stickman head
		cout << "\t______" << endl << "\t|    |" << endl << "\t|    O" << endl << "\t|" << endl << "\t|" << endl << "\t|" << endl << "\t---------" << endl;
		break;
	case 3: // 3 wrong guesses; stickman body
		cout << "\t______" << endl << "\t|    |" << endl << "\t|    O" << endl << "\t|    |" << endl << "\t|" << endl << "\t|" << endl << "\t---------" << endl;
		break;
	case 4: // 4 wrong guesses; stickman left arm
		cout << "\t______" << endl << "\t|    |" << endl << "\t|    O" << endl << "\t|   /|" << endl << "\t|" << endl << "\t|" << endl << "\t---------" << endl;
		break;
	case 5: // 5 wrong guesses; stickman right arm
		cout << "\t______" << endl << "\t|    |" << endl << "\t|    O" << endl << "\t|   /|\\" << endl << "\t|" << endl << "\t|" << endl << "\t---------" << endl;
		break;
	case 6: // 6 wrong guesses; stickman left leg
		cout << "\t______" << endl << "\t|    |" << endl << "\t|    O" << endl << "\t|   /|\\" << endl << "\t|   /" << endl << "\t|" << endl << "\t---------" << endl;
		break;
	case 7: // 7 wrong guesses; stickman right leg; ded xP
		cout << "\t______" << endl << "\t|    |" << endl << "\t|    O" << endl << "\t|   /|\\" << endl << "\t|   / \\" << endl << "\t|" << endl << "\t---------" << endl;
		break;

	}
}

bool TrieNode::gameEnd() { 
	bool over = false;
	if (m_strikes == 7) { // game over display
		displayWord();
		displayHang();
		displayLetters();
		cout << "Game Over.\n";
		cout << "Correct word was: " << m_word << endl;
		over = true;
	}
	if (m_correct == m_word.length()) { // correct display
		displayWord();
		displayHang();
		displayLetters();
		cout << "Correct!\n";
		over = true;
	}
	return over;
}

void TrieNode::playGame(TrieNode game) { // runs the full game; allows user to input the words to be guessed
	char another;
	bool add = true;
	cout << "\n\tHANGMAN\n";
	game.displayHang();

	while (add) { // while loop used so user can add as many words for guessing as desired; game setup
		string word;
		cout << "Enter a single word to be used: ";
		cin >> word;
		for (int i = 0; i < word.length(); i++) {
			word[i] = tolower(word[i]);
		}
		m_allWords.push_back(word); // used for random selection later
		for (int i = 0; i < m_allWords.size(); i++) {
			game.insertWord(&game, m_allWords[i]);
		}
		cout << "Press y to add another word; press any other key to continue: "; // any other key ends loop
		cin >> another;
		if (another == 'y' || another == 'Y') { // both included in case caps lock is on
			add = true;
		}
		else {
			add = false;
		}
	}

	if (game.selectWord(&game, m_allWords)) { // actual game
		while (!game.gameEnd()) {
			game.displayWord();
			game.displayHang();
			game.displayLetters();
			game.guessLetter();
		}
	}
	else {
		add = true;
	}
}
