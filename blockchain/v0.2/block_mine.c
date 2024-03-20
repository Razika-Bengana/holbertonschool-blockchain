#include "blockchain.h"

/**
 * block_mine - program that mines a block by finding a hash that matches
 * the block's difficulty
 *
 * the function updates the block's nonce and hash once a matching hash
 * is found
 *
 * @block: points to the block to be mined
 *
 * Return: nothing (void)
 */

void block_mine(block_t *block)
{
	uint8_t hash_buf[SHA256_DIGEST_LENGTH];
	block_info_t *info;
	uint64_t nonce = 0;
	int match;

	info = &block->info;

	do {
		info->nonce = nonce++;
		block_hash(block, hash_buf);
		match = hash_matches_difficulty(hash_buf, info->difficulty);

	} while (match == 0);

	memcpy(block->hash, hash_buf, SHA256_DIGEST_LENGTH);
}
