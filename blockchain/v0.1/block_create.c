#include "blockchain.h"

/**
 * block_create - program that creates a new block in the blockchain with given data
 * and links it to the previous block
 *
 * this function allocates memory for a new block, initializes it with the provided
 * data, and sets its metadata fields;
 * the new block's index is set to one more than the previous block's index,
 * or 0 if it is the first block;
 * the difficulty and nonce are initialized to 0, and the current time is set as
 * the block's timestamp;
 * the data is copied into the block, ensuring that it does not exceed the maximum
 * allowed size and is null-terminated;
 * the block's hash is initially reset to zero;
 *
 * @prev: a pointer to the previous block in the blockchain,
 *        or NULL if this is the first block
 * @data: a pointer to the data to be included in the new block;
 *        the data will be copied into the block's buffer
 * @data_len: the length of the data to copy;
 *            if this length exceeds BLOCKCHAIN_DATA_MAX, only BLOCKCHAIN_DATA_MAX - 1 bytes
 *            are copied to ensure the data is null-terminated
 *
 * Return: a pointer to the newly created block, or NULL if memory allocation fails
 */

block_t *block_create(block_t const *prev, int8_t const *data, uint32_t data_len)
{
	block_t *block = malloc(sizeof(*block));

	if (!block)
		return (NULL);

	block->info.index = prev ? prev->info.index + 1 : 0;
	block->info.difficulty = 0;
	block->info.nonce = 0;
	block->info.timestamp = (uint64_t)time(NULL);

	if (prev)
	{
		memcpy(block->info.prev_hash, prev->hash, SHA256_DIGEST_LENGTH);
	}
	else
	{
		memset(block->info.prev_hash, 0, SHA256_DIGEST_LENGTH);
	}

	if (data_len >= BLOCKCHAIN_DATA_MAX)
	{
		data_len = BLOCKCHAIN_DATA_MAX - 1;
	}
	memcpy(block->data.buffer, data, data_len);
	block->data.buffer[data_len] = '\0';
	block->data.len = data_len + 1;

	memset(block->hash, 0, SHA256_DIGEST_LENGTH);

	return (block);
}

