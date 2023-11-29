#include <stdio.h>
#include <string.h> // for strcmp()
#include <ctype.h> // for isprint()
#include <stdlib.h> // for malloc()
#include <assert.h>

#include "trie_defs.h"



/** compare a key with the letter in a node */
int
trie_subtreeSearchComparator(const void *keyValue, const void *nodePtr)
{
	TrieNode **node = (TrieNode **) nodePtr;

	AAKeyType key = (AAKeyType) keyValue;
	return (key[0] - (*node)->letter);
}


/** create a whole chain for the rest of the key */
static TrieNode *
trie_create_chain(AAKeyType key, size_t keylength, void *value, int *cost)
{
	TrieNode *current = trieCreateNode();

	// TO DO: create a new chain the the required key letters
	int i;
	for (i = 1; i < keylength; i++){
		TrieNode* newNode = trieCreateNode();
		newNode->letter = key[i];
		current->subtries[current->nSubtries++] = newNode;
		current = newNode;
		if (cost != NULL) {
			(*cost)++;
		}
	}

	current->isKeySoHasValue = 1;
	current->value = value;
	return current;
}

/** add the given chain to the list of tries in the current node */
static int
trie_add_chain(
		TrieNode **subtreeList, int nSubtries,
		AAKeyType key,
		TrieNode *newChain
	)
{
	// TO DO:  add the provided chain to the node; the first letter
	// of the key may be used to organize where within the set of
	// subtries you add this

	int index = key[0] % nSubtries;
	TrieNode *existingChain = subtreeList[index];

	if (existingChain == NULL) {
		subtreeList[index] = newChain;
		return 0;
	}

	else {

	// TO DO: you probably want to replace this return statement
	// with your own code
	return -1;
	}
}


/** link the provided key into the current chain */
static int
trie_link_to_chain(TrieNode *current,
		AAKeyType key, size_t keylength,
		void *value, int *cost)
{
	// TO DO: add the remaining portions of the key
	// into this chain, forming a new branch if and when
	// they stop matching existing letters within the subtries
	int i;
	AAKeyType remainingKey;
	for (size_t i = 0; i < keylength; i++) {
		remainingKey = key + i;

		int found = 0;
		int j;
		for (j = 0; j < current->nSubtries; j++) {
			if (current->subtries[j]->letter == remainingKey[0]) {
				current = current->subtries[j];
				found = 1;
				break;
			}
		}

		if (!found) {
			TrieNode *newNode = trieCreateNode();
			newNode->letter = remainingKey[0];
			current->subtries[current->nSubtries++] = newNode;
			current = newNode;
			if (cost != NULL) {
				(*cost)++;
			}
		}
	}

	current->isKeySoHasValue = 1;
	current->value = value;

	// TO DO: you probably want to replace this return statement
	// with your own code
	return 0;
}


int
trieInsertKey(KeyValueTrie *root,
		AAKeyType key, size_t keylength,
		void *value, int *cost)
{
	/** keep the max key length in order to keep a buffer for interation */
	if (root->maxKeyLength < keylength)
		root->maxKeyLength = keylength;

	if (root->nSubtries == 0) {
		root->subtries[root->nSubtries++] = trie_create_chain(
				key, keylength, value, cost);
		return 0;
	}

	
	// TO DO: find the subtrie with the leading letter of the
	// key, and insert the new key into the correct subtrie
	// chain based on that letter
	int index = key[0] % root->nSubtries;
	TrieNode *subtree = root->subtries[index];

	if (subtree == NULL) {
		root->subtries[index] = trie_create_chain(key, keylength, value, cost);
	}
	else {
		trie_link_to_chain(subtree, key, keylength, value, cost);
	}

	// TO DO: you probably want to replace this return statement
	// with your own code
	return 0;
}


