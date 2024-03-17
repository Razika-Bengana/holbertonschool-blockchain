#include "blockchain.h"

/**
 *
 * @param block
 * @param hash_buf
 * @return
 */

uint8_t *block_hash(block_t const *block, uint8_t hash_buf[SHA256_DIGEST_LENGTH])
{
	size_t data_size;
	uint8_t *data_to_hash;

	if (!block || !hash_buf)
		return (NULL);

	data_size = sizeof(block->info) + block->data.len;
	data_to_hash = malloc(data_size);

	if (!data_to_hash) return NULL;

	memcpy(data_to_hash, &block->info, sizeof(block->info));
	memcpy(data_to_hash + sizeof(block->info), block->data.buffer, block->data.len);

	SHA256(data_to_hash, data_size, hash_buf);

	free(data_to_hash);

	return (hash_buf);
}
