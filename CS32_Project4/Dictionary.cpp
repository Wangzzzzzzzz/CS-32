// Dictionary.cpp

#include "Dictionary.h"
#include <algorithm>
#include <string>
#include <list>
using namespace std;

void removeNonLetters(string& s);

class DictionaryImpl
{
public:
	DictionaryImpl();
	~DictionaryImpl();
	void insert(string word);
	void lookup(string letters, void callback(string)) const;

private:
	struct Word {
		Word(string s);
		string m_word;
		string m_sorted;
	};
	unsigned int KeyGen(string& word) const;
	list<Word>* HashTable[10000];
};

DictionaryImpl::Word::Word(string s) 
	:m_word(s)
{
	sort(s.begin(), s.end());
	m_sorted = s;
}

DictionaryImpl::DictionaryImpl() {
	for(int i = 0;i<10000;i++)
		HashTable[i] = nullptr;
}

DictionaryImpl::~DictionaryImpl() {
	for (int i = 0; i < 10000; i++) {
		if (HashTable[i] != nullptr)
			delete HashTable[i];
	}
}

unsigned int DictionaryImpl::KeyGen(string& word) const {
	sort(word.begin(), word.end());
	unsigned int h = 2166136261U;
	for (int k = 0; k < word.size(); k++)
	{
		h += word[k];
		h *= 10012879;
	}
	return h % 10000;
}

void DictionaryImpl::insert(string word)
{
	removeNonLetters(word);
	if (!word.empty()) {
		string temp = word;
		int loc = KeyGen(word);
		if (HashTable[loc] == nullptr)
			HashTable[loc] = new list<Word>;
		HashTable[loc]->push_back(Word(temp));
	}
}

void DictionaryImpl::lookup(string letters, void callback(string)) const
{
	if (callback == nullptr)
		return;
	removeNonLetters(letters);
	if (letters.empty())
		return;
	unsigned int loc = KeyGen(letters);
	list<Word>* ptr = HashTable[loc];
	if (ptr == nullptr)
		return;

	for (list<Word>::iterator p = ptr->begin(); p != ptr->end(); p++) {
		if (p->m_sorted == letters)
			callback(p->m_word);
	}

}

void removeNonLetters(string& s)
{
	string::iterator to = s.begin();
	for (string::const_iterator from = s.begin(); from != s.end(); from++)
	{
		if (isalpha(*from))
		{
			*to = tolower(*from);
			to++;
		}
	}
	s.erase(to, s.end());  // chop everything off from "to" to end.
}

//******************** Dictionary functions ********************************

// These functions simply delegate to DictionaryImpl's functions.
// You probably don't want to change any of this code

Dictionary::Dictionary()
{
	m_impl = new DictionaryImpl;
}

Dictionary::~Dictionary()
{
	delete m_impl;
}

void Dictionary::insert(string word)
{
	m_impl->insert(word);
}

void Dictionary::lookup(string letters, void callback(string)) const
{
	m_impl->lookup(letters, callback);
}

