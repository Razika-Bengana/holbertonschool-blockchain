#include "blockchain.h"

/**
 * block_create - program that creates and initializes a new block
 * in the blockchain
 *
 * this function allocates memory for a new block and initializes it
 * with given data, linking it to the previous block in the chain;
 * the new block's index is set to one more than the previous block's index;
 * the difficulty and nonce are initialized to 0, and the timestamp is set to
 * the current time;
 * the data is copied into the new block, respecting the maximum allowed size
 * defined by BLOCKCHAIN_DATA_MAX;
 * finally, the block's hash is initialized to zero
 *
 * @prev: a pointer to the previous block in the blockchain
 *        --> must not be NULL
 * @data: a pointer to the data to be included in the new block
 *        --> must not be NULL
 * @data_len: the size of the data to copy;
 *            if greater than BLOCKCHAIN_DATA_MAX,
 *            only BLOCKCHAIN_DATA_MAX bytes are copied
 * Return: a pointer to the newly created block, or NULL if an error occurs
 *         during allocation
 */

block_t *block_create(block_t const *prev, int8_t const *data,
		      uint32_t data_len)
{
	block_t *block = calloc(1, sizeof(block_t));

	if (!prev || !data)
	{
		fprintf(stderr, "block_create: Invalid input parameters.\n");
		return (NULL);
	}

	if (!block)
	{
		fprintf(stderr, "block_create: Memory allocation failed.\n");
		return (NULL);
	}

	block->info.index = prev->info.index + 1;
	block->info.difficulty = 0;
	block->info.nonce = 0;
	block->info.timestamp = (uint64_t)time(NULL);

	memcpy(block->info.prev_hash, prev->hash, SHA256_DIGEST_LENGTH);

	block->data.len = data_len > BLOCKCHAIN_DATA_MAX ?
		BLOCKCHAIN_DATA_MAX : data_len;

	memcpy(block->data.buffer, data, block->data.len);
	memset(block->hash, 0, SHA256_DIGEST_LENGTH);

	return (block);
}
