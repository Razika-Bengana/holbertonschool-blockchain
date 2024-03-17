#include "blockchain.h"

/**
 * block_hash - program that computes the SHA-256 hash of a given
 * block's contents
 *
 * this function calculates the hash based on the block's info and data;
 * the resulting hash is stored in the provided buffer 'hash_buf'
 *
 * @block: a pointer to the block to be hashed;
 *         this includes both its metadata and data
 * @hash_buf: a buffer where the resulting SHA-256 hash will be stored;
 *            this buffer must be at least SHA256_DIGEST_LENGTH bytes long
 *
 * Return: a pointer to the buffer containing the hash if successful,
 *         or NULL if the operation fails due to invalid input parameters
 *         or memory allocation issues
 */

uint8_t *block_hash(block_t const *block,
		    uint8_t hash_buf[SHA256_DIGEST_LENGTH])
{
	size_t data_size;
	uint8_t *data_to_hash;

	if (!block || !hash_buf)
		return (NULL);

	data_size = sizeof(block->info) + block->data.len;
	data_to_hash = malloc(data_size);

	if (!data_to_hash)
		return (NULL);

	memcpy(data_to_hash, &block->info, sizeof(block->info));
	memcpy(data_to_hash + sizeof(block->info), block->data.buffer,
	       block->data.len);

	SHA256(data_to_hash, data_size, hash_buf);

	free(data_to_hash);

	return (hash_buf);
}
