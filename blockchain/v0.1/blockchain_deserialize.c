#include <blockchain.h>

static int load_blocks_into_blockchain(int fd, blockchain_t *blockchain,
				       uint8_t encoding, uint32_t num_blocks);

/**
 * blockchain_deserialize - program that deserializes a blockchain from a file
 *
 * @path: the path to the file containing the serialized blockchain data
 *
 * Return: a pointer to the deserialized blockchain, or NULL on failure
 */

blockchain_t *blockchain_deserialize(char const *path)
{
	int fd = open(path, O_RDONLY);
	unsigned char buf[sizeof(block_t)];
	uint8_t encoding;
	uint32_t num_blocks;
	blockchain_t *blockchain;

	if (fd == -1)
		return (NULL);

	if (read(fd, buf, sizeof(HBLK_MAGIC) - 1) <
	(ssize_t)sizeof(HBLK_MAGIC) - 1 ||
	memcmp(buf, HBLK_MAGIC, sizeof(HBLK_MAGIC) - 1) ||
	read(fd, buf, sizeof(HBLK_VERSION) - 1) <
	(ssize_t)sizeof(HBLK_VERSION) - 1 ||
	!(blockchain = blockchain_create()))
	{
		close(fd);
		return (NULL);
	}

	block_destroy((block_t *)llist_pop(blockchain->chain));
	read(fd, &encoding, sizeof(encoding));
	read_attribute(fd, encoding, &num_blocks, sizeof(num_blocks));

	if (!load_blocks_into_blockchain(fd, blockchain, encoding, num_blocks))
	{
		llist_destroy(blockchain->chain, true, (node_dtor_t)block_destroy);
		free(blockchain);
		close(fd);
		return (NULL);
	}

	close(fd);
	return (blockchain);
}



/**
 * load_blocks_into_blockchain - helper function to load blocks from the file
 * into the blockchain
 *
 * @fd: the file descriptor of the blockchain file
 * @blockchain: a pointer to the blockchain to add blocks to
 * @encoding: the encoding used in the blockchain file
 * @num_blocks: the number of blocks to read from the file
 *
 * Return: 1 on success, 0 on failure.
 */

static int load_blocks_into_blockchain(int fd, blockchain_t *blockchain,
				       uint8_t encoding, uint32_t num_blocks)
{
	block_t *block;

	while (num_blocks--)
	{
		block = calloc(1, sizeof(block_t));
		if (!block ||
		    !read_attribute(fd, encoding, &block->info.index,
				    sizeof(block->info.index)) ||
		    !read_attribute(fd, encoding, &block->info.difficulty,
				    sizeof(block->info.difficulty)) ||
		    !read_attribute(fd, encoding, &block->info.timestamp,
				    sizeof(block->info.timestamp)) ||
		    !read_attribute(fd, encoding, &block->info.nonce,
				    sizeof(block->info.nonce)) ||
		    !read_attribute(fd, encoding, block->info.prev_hash,
				    sizeof(block->info.prev_hash)) ||
		    !read_attribute(fd, encoding, &block->data.len,
				    sizeof(block->data.len)) ||
		    !read_attribute(fd, encoding, block->data.buffer, block->data.len) ||
		    !read_attribute(fd, encoding, block->hash,
				    sizeof(block->hash)))
		{
			free(block);
			return (0);
		}
		llist_add_node(blockchain->chain, block, ADD_NODE_REAR);
	}
	return (1);
}



/**
 * bswap - program that swaps bytes of a given attribute in memory
 * for endianness correction
 *
 * @p: a pointer to the attribute
 * @size: the size of the attribute in bytes
 *
 * Return: nothing (void)
 */

static void bswap(uint8_t *p, size_t size)
{
	uint8_t buf[64] = {0};
	int i;

	for (i = size - 1; i >= 0; i--)
		buf[size - i - 1] = p[i];

	for (i = 0; i < (int)size; i++)
		p[i] = buf[i];
}



/**
 * read_attribute - program that reads an attribute from a file,
 * optionally swapping bytes for endianness
 *
 * @fd: the file descriptor from which to read
 * @encoding: the encoding of the attribute (MSB or LSB)
 * @attr: a pointer to the buffer where the attribute should be stored
 * @size: the size of the attribute in bytes
 *
 * Return: 1 on success, 0 on failure
 */

int read_attribute(int fd, int encoding, void *attr, size_t size)
{
	if (read(fd, attr, size) != (ssize_t)size)
		return (0);

	if (encoding == MSB)
		bswap((uint8_t *)attr, size);

	return (1);
}
