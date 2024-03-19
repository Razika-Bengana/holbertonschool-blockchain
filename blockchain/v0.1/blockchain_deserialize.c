#include "blockchain.h"

/**
 * open_and_verify_file - program that opens a file and verifies its
 * blockchain header
 *
 * this function attempts to open the specified file in read-binary mode
 * and reads the blockchain's header information to verify its validity;
 * The header includes a magic number, version, and endianness indicator
 *
 * @path: the path to the blockchain file to open
 * @num_blocks: a pointer to store the number of blocks read from the file
 *              header
 *
 * Return: the FILE pointer on success,
 *         NULL if the file cannot be opened or if the header is invalid
 */

FILE *open_and_verify_file(char const *path, uint32_t *num_blocks)
{
	char hblk_magic[5], hblk_version[4];
	uint8_t hblk_endian;
	FILE *fp = NULL;

	fp = fopen(path, "rb");

	if (!fp)
		return (NULL);

	fread(hblk_magic, sizeof(hblk_magic) - 1, 1, fp);
	hblk_magic[4] = '\0';
	fread(hblk_version, sizeof(hblk_version) - 1, 1, fp);
	hblk_version[3] = '\0';
	fread(&hblk_endian, sizeof(hblk_endian), 1, fp);

	if (strcmp(hblk_magic, "HBLK") || strcmp(hblk_version, "1.0"))
	{
		fclose(fp);
		return (NULL);
	}

	fread(num_blocks, sizeof(*num_blocks), 1, fp);

	return (fp);
}



/**
 * build_blockchain - program that builds a blockchain from a file
 *
 * this function reads block data from an open file pointer and constructs
 * a blockchain by creating and appending blocks;
 * each block's information, including its info, data, and hash,
 * is read from the file
 *
 * @fp: the File pointer to read the block data from
 * @num_blocks: the number of blocks to read and construct
 *
 * Return: a pointer to the newly created blockchain or NULL on error
 */

blockchain_t *build_blockchain(FILE *fp, uint32_t num_blocks)
{
	blockchain_t *blockchain = blockchain_create();
	block_t *block;
	uint32_t i;

	if (!blockchain)
	{
		return (NULL);
	}

	for (i = 0; i < num_blocks; ++i)
	{
		block = malloc(sizeof(*block));

		if (!block)
		{
			blockchain_destroy(blockchain);
			return (NULL);
		}
		fread(&block->info, sizeof(block->info), 1, fp);
		fread(&block->data.len, sizeof(block->data.len), 1, fp);
		fread(&block->data.buffer, block->data.len, 1, fp);
		fread(&block->hash, sizeof(block->hash), 1, fp);

		if (llist_add_node(blockchain->chain, block, ADD_NODE_REAR))
		{
			free(block);
			blockchain_destroy(blockchain);
			return (NULL);
		}
	}
	return (blockchain);
}



/**
 * blockchain_deserialize program that deserializes a blockchain from a file
 *
 * this function opens a blockchain file, verifies its header, reads
 * the number of blocks, and constructs a blockchain from the blocks data
 * in the file
 *
 * @path: the path to the blockchain file to deserialize
 *
 * Return: a pointer to the deserialized blockchain or NULL on error
 */

blockchain_t *blockchain_deserialize(char const *path)
{
	uint32_t num_blocks;
	FILE *fp = open_and_verify_file(path, &num_blocks);
	blockchain_t *blockchain;

	if (!fp)
		return (NULL);

	blockchain = build_blockchain(fp, num_blocks);

	fclose(fp);

	return (blockchain);
}
