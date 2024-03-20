#include "blockchain.h"

/**
 * blockchain_difficulty - program that computes the difficulty
 * for the next block in the blockchain
 *
 * @blockchain: points to the Blockchain to analyze
 *
 * Return: the difficulty to be assigned to a potential next Block
 *         in the Blockchain
 */

uint32_t blockchain_difficulty(blockchain_t const *blockchain)
{
	block_t *latest_block;
	block_t *adjusted_block;
	uint64_t expected_time;
	uint64_t actual_time;

	if (blockchain == NULL || llist_size(blockchain->chain) == 0)
	{
		return (0);
	}

	latest_block = llist_get_node_at(blockchain->chain, llist_size(blockchain->chain) - 1);

	if (latest_block == NULL)
	{
		return (0);
	}

	if ((latest_block->info.index + 1) % DIFFICULTY_ADJUSTMENT_INTERVAL == 0 && latest_block->info.index != 0)
	{
		adjusted_block = llist_get_node_at(blockchain->chain, llist_size(blockchain->chain) - DIFFICULTY_ADJUSTMENT_INTERVAL);

		expected_time = BLOCK_GENERATION_INTERVAL * DIFFICULTY_ADJUSTMENT_INTERVAL;
		actual_time = latest_block->info.timestamp - adjusted_block->info.timestamp;

		/* Adjust difficulty */
		if (actual_time < expected_time / 2)
		{
			return (latest_block->info.difficulty + 1);
		}

		else if (actual_time > expected_time * 2)
		{
			return (latest_block->info.difficulty > 0 ? latest_block->info.difficulty - 1 : 0);
		}
	}

	return (latest_block->info.difficulty);
}
