#include "blockchain.h"

/**
 * open_and_verify_file - program that opens and verifies a file for blockchain
 * deserialization
 *
 * this function opens a file at the specified path and verifies the header
 * information to ensure it's a valid blockchain file
 *
 * @path: the path to the file to open and verify
 *
 * Return: a FILE pointer to the opened file upon success, or NULL upon failure
 */

FILE *open_and_verify_file(char const *path)
{
	char hblk_magic[5], hblk_version[4];
	uint8_t hblk_endian;
	uint32_t num_blocks;
	FILE *file;

	file = fopen(path, "rb");

	if (!file)
	{
		return (NULL);
	}

	fread(hblk_magic, sizeof(char), 4, file);
	hblk_magic[4] = '\0';
	fread(hblk_version, sizeof(char), 3, file);
	hblk_version[3] = '\0';
	fread(&hblk_endian, sizeof(uint8_t), 1, file);
	fread(&num_blocks, sizeof(uint32_t), 1, file);

	if (strcmp(hblk_magic, "HBLK") != 0 || strcmp(hblk_version, "1.0") != 0)
	{
		fclose(file);
		return (NULL);
	}

	return (file);
}



/**
 * read_blocks_and_build_blockchain - program that reads blocks from a file and builds
 * a blockchain
 *
 * this function reads block data from the provided file and constructs a blockchain
 * structure based on the information read
 *
 * @file: the FILE pointer to the file containing block data
 *
 * Return: a pointer to the constructed blockchain upon success, or NULL upon failure
 */

blockchain_t *read_blocks_and_build_blockchain(FILE *file)
{
	uint32_t num_blocks, i;
	blockchain_t *blockchain = blockchain_create();
	block_t *block;

	fread(&num_blocks, sizeof(uint32_t), 1, file);

	for (i = 0; i < num_blocks; i++)
	{
		block = malloc(sizeof(block_t));

		fread(&(block->info), sizeof(block_info_t), 1, file);
		fread(&(block->data.len), sizeof(uint32_t), 1, file);
		memcpy(block->data.buffer, malloc(block->data.len * sizeof(int8_t)),
		       block->data.len);
		fread(block->data.buffer, sizeof(int8_t), block->data.len, file);
		fread(block->hash, sizeof(uint8_t), SHA256_DIGEST_LENGTH, file);

		llist_add_node(blockchain->chain, block, ADD_NODE_REAR);
	}

	return (blockchain);
}



/**
 * blockchain_deserialize - program that deserializes a Blockchain from a file
 *
 * this function deserializes a Blockchain from a file by opening and verifying the file,
 * reading block data, and building the blockchain structure
 *
 * @path: the path to the file containing the serialized Blockchain
 *
 * Return: a pointer to the deserialized Blockchain upon success, or NULL upon failure
 */

blockchain_t *blockchain_deserialize(char const *path)
{
	FILE *file;

	file = open_and_verify_file(path);

	if (!file)
	{
		return (NULL);
	}

	blockchain_t *blockchain = read_blocks_and_build_blockchain(file);

	fclose(file);

	return (blockchain);
}


