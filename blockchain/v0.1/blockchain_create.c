#include "blockchain.h"

/**
 * blockchain_create - program that initializes and returns a new blockchain
 * instance
 *
 * this function creates a new blockchain, initializing it with a single
 * genesis block;
 *
 * the genesis block is the first block in the blockchain, with pre-defined
 * values:
 * - index: 0
 * - difficulty: 0
 * - timestamp: 1537578000
 * - nonce: 0
 * - prev_hash: an array filled with zeros
 * - data: "Holberton School"
 * - hash: a predetermined hash value represented in GENESIS_HASH
 *
 * the blockchain is implemented as a linked list, using the llist library
 * to manage the list of blocks;
 *
 * Return: a pointer to the newly created blockchain if successful,
 *         otherwise NULL (on failure, any allocated memory is properly
 *         freed before returning NULL to avoid memory leaks)
 */

blockchain_t *blockchain_create(void)
{
	blockchain_t *blockchain;
	block_t *genesis_block;
	uint8_t genesis_hash[SHA256_DIGEST_LENGTH] = GENESIS_HASH;

	blockchain = malloc(sizeof(*blockchain));
	if (blockchain == NULL)
		return (NULL);

	blockchain->chain = llist_create(MT_SUPPORT_FALSE);
	if (blockchain->chain == NULL)
	{
		free(blockchain);
		return (NULL);
	}
	genesis_block = malloc(sizeof(*genesis_block));
	if (genesis_block == NULL)
	{
		llist_destroy(blockchain->chain, 1, NULL);
		free(blockchain);
		return (NULL);
	}
	memset(genesis_block, 0, sizeof(*genesis_block));

	genesis_block->info.index = 0;
	genesis_block->info.difficulty = 0;
	genesis_block->info.timestamp = 1537578000;
	genesis_block->info.nonce = 0;
	memset(genesis_block->info.prev_hash, 0, SHA256_DIGEST_LENGTH);
	strncpy((char *)genesis_block->data.buffer, "Holberton School",
		BLOCKCHAIN_DATA_MAX);
	genesis_block->data.len = 16;
	memcpy(genesis_block->hash, genesis_hash, SHA256_DIGEST_LENGTH);
	if (llist_add_node(blockchain->chain, genesis_block, ADD_NODE_FRONT) != 0)
	{
		free(genesis_block);
		llist_destroy(blockchain->chain, 1, NULL);
		free(blockchain);
		return (NULL);
	}
	return (blockchain);
}
