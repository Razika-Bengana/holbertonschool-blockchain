#include "blockchain.h"

/**
 * blockchain_destroy - program that destroys a blockchain and frees
 * all the blocks it contains
 *
 * @blockchain: a pointer to the blockchain structure to delete
 *
 * Return: nothing (void)
 */

void blockchain_destroy(blockchain_t *blockchain)
{
	if (blockchain == NULL)
	{
		return;
	}

	llist_destroy(blockchain->chain, 1, NULL);

	free(blockchain);
}
