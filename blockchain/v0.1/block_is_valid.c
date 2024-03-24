#include "blockchain.h"

/**
 * block_is_valid - program that validates a block within a blockchain context
 *
 * This function checks whether a given block adheres to the blockchain's
 * validity criteria, including its relationship with the previous block,
 * its index, and the integrity of its hash values
 *
 * @block: a pointer to the block to be validated;
 *         it should not be NULL except for the genesis block
 *         which is the first block in the chain
 * @prev_block: a pointer to the block immediately preceding the current block
 *              in the blockchain;
 *              this should be NULL if and only if the block being validated
 *              is the genesis block
 *
 * Return: 0 if the block is valid according to the blockchain's criteria;
 *         1 if the block is invalid, if any of the validation checks fail,
 *         or if any parameters are incorrectly provided (such as a
 *         NULL block pointer when not validating the genesis block)
 */

int block_is_valid(block_t const *block, block_t const *prev_block)
{
	block_t const tmp = GENESIS_BLOCK;
	uint8_t hash[SHA256_DIGEST_LENGTH] = {0};

	if (!block || (!prev_block && block->info.index != 0))
		return (1);

	if (block->info.index == 0)
		return (memcmp(block, &tmp, sizeof(tmp)));

	if (block->info.index != prev_block->info.index + 1)
		return (1);

	if (!block_hash(prev_block, hash) ||
	    memcmp(hash, prev_block->hash, SHA256_DIGEST_LENGTH))
		return (1);

	if (memcmp(prev_block->hash, block->info.prev_hash, SHA256_DIGEST_LENGTH))
		return (1);

	if (!block_hash(block, hash) ||
	    memcmp(hash, block->hash, SHA256_DIGEST_LENGTH))
		return (1);

	if (block->data.len > BLOCKCHAIN_DATA_MAX)
		return (1);

	return (0);
}
