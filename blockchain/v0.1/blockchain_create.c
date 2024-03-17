#include "blockchain.h"

/**
 * blockchain_create - program that initializes and returns a new blockchain
 * structure
 *
 * this function allocates memory for a new blockchain and its genesis block;
 *
 * the genesis block is the first block in the blockchain, with pre-defined
 * values:
 * - index is set to 0
 * - difficulty is set to 0
 * - timestamp is set to 1537578000 (a fixed UNIX timestamp)
 * - nonce is set to 0
 * - prev_hash is filled with zeroes
 * - data is set to "Holberton School"
 * - data length is set to 16 bytes
 * - hash is set to a pre-defined genesis block hash
 *
 * Return: a pointer to the newly created blockchain structure,
 *         or NULL if any memory allocation fails during the process
 *         (the function cleans up any allocated resources and returns NULL=
 */

blockchain_t *blockchain_create(void)
{
	blockchain_t *blockchain;
	block_t *genesis_block;

	blockchain = malloc(sizeof(*blockchain));
	if (!blockchain)
		return (NULL);

	blockchain->chain = llist_create(MT_SUPPORT_FALSE);

	if (!blockchain->chain)
	{
		free(blockchain);
		return (NULL);
	}
	genesis_block = malloc(sizeof(*genesis_block));

	if (!genesis_block)
	{
		llist_destroy(blockchain->chain, 1, NULL);
		free(blockchain);
		return (NULL);
	}
	genesis_block->info.index = 0;
	genesis_block->info.difficulty = 0;
	genesis_block->info.timestamp = 1537578000;
	genesis_block->info.nonce = 0;

	memset(genesis_block->info.prev_hash, 0, SHA256_DIGEST_LENGTH);
	memcpy(genesis_block->data.buffer, "Holberton School", 16);
	genesis_block->data.len = 16;
	memcpy(genesis_block->hash, GENESIS_HASH, SHA256_DIGEST_LENGTH);

	if (llist_add_node(blockchain->chain, genesis_block, ADD_NODE_FRONT) == -1)
	{
		free(genesis_block);
		llist_destroy(blockchain->chain, 1, NULL);
		free(blockchain);
		return (NULL);
	}
	return (blockchain);
}
