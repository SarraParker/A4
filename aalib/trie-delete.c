#include <stdio.h>
#include <string.h> // for strcmp()
#include <ctype.h> // for isprint()
#include <stdlib.h> // for malloc()
#include <assert.h>

#include "trie_defs.h"


/** recursively roll up the chain */
static int
walk_chain_to_delete(
		void **value,
		TrieNode *curSearchNode,
		AAKeyType key, size_t keylength,
		int *cost
	)
{
	// TO DO: remove nodes for deleted key
	if (curSearchNode == NULL) {
		return 0;
	}

	if (keylength == 0) {
		if (curSearchNode->isKeySoHasValue) {
			*value = curSearchNode->value;
			curSearchNode->isKeySoHasValue = 0;
			free(curSearchNode->value);
			curSearchNode->value = NULL;
		}
		return 1;
	}

	int index = key[0] % curSearchNode->nSubtries;
	TrieNode *nextNode = curSearchNode->subtries[index];

	int deleted = walk_chain_to_delete(value, nextNode, key + 1, keylength - 1, cost);

	return deleted;
}

/** delete a key from the trie */
void *trieDeleteKey(
		KeyValueTrie *root,
		AAKeyType key, size_t keylength,
		int *cost
	)
{
	void *valueFromDeletedKey = NULL;


	if (root->nSubtries == 0) {
		return NULL;
	}

	/**
	 ** TO DO: search for the right subchain and delete the key from it
	 **/

	int index = key[0] % root->nSubtries;
	TrieNode *subtree = root->subtries[index];

	walk_chain_to_delete(&valueFromDeletedKey, subtree, key, keylength, cost);
	
	return valueFromDeletedKey;
}

