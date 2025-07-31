// Spring 2023 
#include "hangman.h"

class Tester {
	friend class TrieNode;
public:
	bool testInsertNormal(TrieNode node); // insert words
	bool testInsertEdge(TrieNode node); // insert long string
	bool testInsertError(TrieNode node); // insert a duplicate word
	bool testRemoveNormal(TrieNode node); // remove words
	bool testRemoveError(TrieNode node); // attempt to remove a string not in trie
	bool testSearchWord(TrieNode node); // search an inserted string
	bool testSelectWord(TrieNode node); // test for a proper random selection of a word
	bool testGameEnd(TrieNode game); // test that game ends properly on both win/lose conditions
};

int main() {
	Tester test;
	TrieNode trie;
	
	cout << "Testing insert normal case\n";
	if (test.testInsertNormal(trie)) {
		cout << "\tinsert normal case test passed\n";
	}
	else {
		cout << "\tinsert normal case test failed\n";
	}
	
	cout << "Testing insert edge case\n";
	if (test.testInsertEdge(trie)) {
		cout << "\tinsert edge case test passed\n";
	}
	else {
		cout << "\tinsert edge case test failed\n";
	}
	
	cout << "Testing insert error case\n";
	if (test.testInsertError(trie)) {
		cout << "\tinsert error case test passed\n";
	}
	else {
		cout << "\tinsert error case test failed\n";
	}
	
	cout << "Testing remove normal case\n";
	if (test.testRemoveNormal(trie)) {
		cout << "\tremove normal case test passed\n";
	}
	else {
		cout << "\tremove normal case test failed\n";
	}
	
	cout << "Testing remove error case\n";
	if (test.testRemoveError(trie)) {
		cout << "\tremove error case test passed\n";
	}
	else {
		cout << "\tremove error case test failed\n";
	}

	cout << "Testing search word\n";
	if (test.testSearchWord(trie)) {
		cout << "\tsearch word test passed\n";
	}
	else {
		cout << "\tsearch word test failed\n";
	}

	cout << "Testing select word\n";
	if (test.testSelectWord(trie)) {
		cout << "\tselect word test passed\n";
	}
	else {
		cout << "\tselect word test failed\n";
	}

	cout << "Testing game end function; ignore dump\n";
	if (test.testGameEnd(trie)) {
		cout << "\t game end function test passed\n";
	}
	else {
		cout << "\t game end function test failed\n";
	}
	
	cout << "\nLoading game...\n";
	trie.playGame(trie); // only implemented for strings with one word with no spaces
	return 0;
}

bool Tester::testInsertNormal(TrieNode node) {
	TrieNode temp = node;
	bool test = true;
	vector<string> words = { "bear", "bell", "bid", "bull", "buy", "sell", "stock", "stop" }; 
	for (int i = 0; i < words.size(); i++) {
		temp.insertWord(&temp, words[i]);
		if (!temp.searchWord(&temp, words[i])) { // inserted word not found
			test = false;
		}
	}
	return test;
}

bool Tester::testInsertEdge(TrieNode node) {
	TrieNode temp = node;
	bool test = true;
	vector<string> words = { "pneumonoultramicroscopicsilicovolcanoconiosis" }; // long string for the edge case
	for (int i = 0; i < words.size(); i++) {
		temp.insertWord(&temp, words[i]);
		if (!temp.searchWord(&temp, words[i])) {
			test = false;
		}
	}
	return test;
}

bool Tester::testInsertError(TrieNode node) {
	TrieNode temp = node;
	bool test = true;
	vector<string> words = { "duplicate", "duplicate"};
	for (int i = 0; i < words.size(); i++) {
		temp.insertWord(&temp, words[i]); // inserts twice, second insert should not go through due to duplicate protection
	}
	temp.removeWord(&temp, words[1]); // removes "duplicate" from the trie
	if (temp.searchWord(&temp, words[0])) { // previous duplicate should not be found as only one insertion and removal occurred
		test = false;
	}
	return test;
}

bool Tester::testRemoveNormal(TrieNode node) {
	TrieNode temp = node;
	bool test = true;
	vector<string> toDelete = { "bear", "bell", "bid", "bull" };
	vector<string> words = { "bear", "bell", "bid", "bull", "buy", "sell", "stock", "stop" };
	for (int i = 0; i < words.size(); i++) {
		temp.insertWord(&temp, words[i]);
	}
	for (int i = 0; i < toDelete.size(); i++) {
		temp.removeWord(&temp, toDelete[i]);
		if (temp.searchWord(&temp, toDelete[i])) { // removed words should not be found
			test = false;
		}
	}
	return test;
}

bool Tester::testRemoveError(TrieNode node) {
	TrieNode temp = node;
	bool test = true;
	vector<string> toDelete = { "began" };
	vector<string> words = { "bear", "bell", "bid", "bull", "buy", "sell", "stock", "stop" };
	for (int i = 0; i < words.size(); i++) {
		temp.insertWord(&temp, words[i]);
	}
	temp.removeWord(&temp, toDelete[0]);
	if (temp.searchWord(&temp, toDelete[0])) { // makes sure empty removal does not modify the existing trie
		test = false;
	}
	return test;
}

bool Tester::testSearchWord(TrieNode node) {
	TrieNode temp = node;
	bool test = true;
	vector<string> words = { "bear", "bell", "bid", "bull", "buy", "sell", "stock", "stop" };
	for (int i = 0; i < words.size(); i++) {
		temp.insertWord(&temp, words[i]);
		if (!temp.searchWord(&temp, words[i])) { // any instance of the inserted word not being found is a fail
			test = false;
		}
	}
	return test;
}

bool Tester::testSelectWord(TrieNode node) {
	TrieNode temp = node;
	bool test = false;
	vector<string> words = { "bear", "bell", "bid", "bull", "buy", "sell", "stock", "stop" };
	for (int i = 0; i < words.size(); i++) {
		temp.insertWord(&temp, words[i]);
	}
	temp.selectWord(&temp, words);
	if (temp.searchWord(&temp, temp.m_word)) { // ensures the selected word is in the trie
		test = true;
	}
	return test;
}

bool Tester::testGameEnd(TrieNode game) { // dump may be ignored as its not modified to reflect the set win/loss conditions
	TrieNode temp = game;
	bool loss = false;;
	bool win = false;
	temp.m_correct = temp.m_word.length(); // set win condition
	if (temp.gameEnd()) {
		win = true;
	}
	temp.m_strikes = 7; // set loss condition
	if (temp.gameEnd()) {
		loss = true;
	}
	return (win && loss); // both win and loss are true;
}
