#include "blockchain.h"

/**
 * write_block_to_file - program that
 *
 * @node:
 * @idx:
 * @arg:
 *
 * Return:
 */

int write_block_to_file(llist_node_t node, unsigned int idx, void *arg)
{
	block_t *block;
	FILE *file;

	(void)idx;

	file = (FILE *)arg;
	block = (block_t *)node;

	fwrite(&(block->info), sizeof(block_info_t), 1, file);
	fwrite(&(block->data.len), sizeof(uint32_t), 1, file);
	fwrite(block->data.buffer, sizeof(int8_t), block->data.len, file);
	fwrite(block->hash, sizeof(uint8_t), SHA256_DIGEST_LENGTH, file);

	return (0);
}

int blockchain_serialize(blockchain_t const *blockchain, char const *path)
{
	char hblk_magic;
	char hblk_version;
	uint8_t hblk_endian;
	uint32_t num_blocks;
	FILE *file;

	file = fopen(path, "wb");

	if (file == NULL)
	{
		return (-1);
	}

	hblk_magic[4] = { 'H', 'B', 'L', 'K' };
	hblk_version[3] = { '1', '.', '0' };
	hblk_endian = _get_endianness();

	fwrite(hblk_magic, sizeof(char), 4, file);
	fwrite(hblk_version, sizeof(char), 3, file);
	fwrite(&hblk_endian, sizeof(uint8_t), 1, file);

	num_blocks = llist_size(blockchain->chain);

	fwrite(&num_blocks, sizeof(uint32_t), 1, file);

	llist_for_each(blockchain->chain, write_block_to_file, file);

	fclose(file);

	return (0);
}
