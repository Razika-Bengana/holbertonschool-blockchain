#include "blockchain.h"

/**
 * block_destroy - program that deletes an existing block and frees
 * its allocated memory
 *
 * @block: a pointer to the block to delete
 *
 * Return: nothing (void)
 */

void block_destroy(block_t *block)
{
	if (block != NULL)
	{
		free(block);
	}
}
