#include "blockchain.h"

/**
 * write_block_to_file - program that writes a single block to a file
 *
 * This function takes a block from the blockchain, extracts its components,
 * and writes them to the specified file;
 * the components include the block's info, data length, data buffer,
 * and hash;
 * this function is typically called by llist_for_each() when serializing
 * the entire blockchain to a file
 *
 * @node: a pointer to the block to write, casted to a generic pointer
 * @idx: the index of the block within the blockchain;
 *       unused in this function, but may be used for logging or other
 *       purposes in future enhancements
 * @arg: a pointer to the file (FILE *) where the block data should be written
 *
 * Return: 0 on success
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



/**
 * blockchain_serialize - program that serializes the blockchain to a file
 *
 * this function opens a file at the given path and writes the blockchain's
 * metadata (magic number, version, endianness, and number of blocks)
 * followed by the serialized data of each block;
 * this serialization includes the block's info, data length, data buffer,
 * and hash;
 * the function uses write_block_to_file() to serialize each block
 *
 * @blockchain: Aapointer to the blockchain to serialize
 * @path: the file path where the blockchain should be saved
 *
 * Return: 0 on successful serialization, -1 if the file cannot be opened
 */

int blockchain_serialize(blockchain_t const *blockchain, char const *path)
{
	FILE *file;
	char hblk_magic[] = {'H', 'B', 'L', 'K', '\0'};
	char hblk_version[] = {'1', '.', '0', '\0'};
	uint8_t hblk_endian;
	uint32_t num_blocks;

	file = fopen(path, "wb");

	if (file == NULL)
	{
		return (-1);
	}

	hblk_endian = _get_endianness();
	num_blocks = llist_size(blockchain->chain);

	fwrite(hblk_magic, sizeof(char), sizeof(hblk_magic) - 1, file);
	fwrite(hblk_version, sizeof(char), sizeof(hblk_version) - 1, file);
	fwrite(&hblk_endian, sizeof(hblk_endian), 1, file);
	fwrite(&num_blocks, sizeof(num_blocks), 1, file);

	llist_for_each(blockchain->chain, write_block_to_file, file);

	fclose(file);

	return (0);
}
