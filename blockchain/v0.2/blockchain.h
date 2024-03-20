#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H


#include <llist.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include <openssl/sha.h>
#include "./provided/endianness.h"



#define GENESIS_HASH "\xc5\x2c\x26\xc8\xb5\x46\x16\x39\x63\x5d\x8e\xdf\x2a\x97\xd4\x8d\x0c\x8e\x00\x09\xc8\x17\xf2\xb1\xd3\xd7\xff\x2f\x04\x51\x58\x03"


/* v0.2 */
#define SHA256_DIGEST_LENGTH 32



/**
 * struct block_info_s - Block info structure
 *
 * @index:      Index of the Block in the Blockchain
 * @difficulty: Difficulty of proof of work (hash leading zero bits)
 * @timestamp:  Time the Block was created at (UNIX timestamp)
 * @nonce:      Salt value used to alter the Block hash
 * @prev_hash:  Hash of the previous Block in the Blockchain
 */

typedef struct block_info_s
{
    /*
     * The order of the elements in this structure should remain the same.
     * It was designed so every element of this structure is aligned and
     * doesn't require padding from the compiler.
     * Therefore, it is possible to use the structure as an array of char,
     * on any architecture.
     */
    uint32_t    index;
    uint32_t    difficulty;
    uint64_t    timestamp;
    uint64_t    nonce;
    uint8_t     prev_hash[SHA256_DIGEST_LENGTH];
} block_info_t;



#define BLOCKCHAIN_DATA_MAX 1024



/**
 * struct block_data_s - Block data
 *
 * @buffer: Data buffer
 * @len:    Data size (in bytes)
 */

typedef struct block_data_s
{
    /*
     * @buffer must stay first, so we can directly use the structure as
     * an array of char
     */
    int8_t      buffer[BLOCKCHAIN_DATA_MAX];
    uint32_t    len;
} block_data_t;



/**
 * struct blockchain_s - Blockchain structure
 *
 * @chain: Linked list of pointers to block_t
 */

typedef struct blockchain_s
{
    llist_t     *chain;
} blockchain_t;



/**
 * struct block_s - Block structure
 *
 * @info: Block info
 * @data: Block data
 * @hash: 256-bit digest of the Block, to ensure authenticity
 */

typedef struct block_s
{
    block_info_t    info; /* This must stay first */
    block_data_t    data; /* This must stay second */
    uint8_t     hash[SHA256_DIGEST_LENGTH];
} block_t;



/* v0.1 --------------------------------------------------------------------------------------------------- */


/* task 0 */
blockchain_t *blockchain_create(void);

/* task 1 */
block_t *block_create(block_t const *prev, int8_t const *data,
		      uint32_t data_len);

/* task 2 */
void block_destroy(block_t *block);

/* task 3 */
void blockchain_destroy(blockchain_t *blockchain);

/* task 4 */
uint8_t *block_hash(block_t const *block,
		    uint8_t hash_buf[SHA256_DIGEST_LENGTH]);

/* task 5 */
int write_block_to_file(llist_node_t node, unsigned int idx, void *arg);
int blockchain_serialize(blockchain_t const *blockchain, char const *path);

/* task 6 */
blockchain_t *blockchain_deserialize(char const *path);

/* task 7 */



/* v0.2 --------------------------------------------------------------------------------------------------- */


/* task 0 */
int hash_matches_difficulty(uint8_t const hash[SHA256_DIGEST_LENGTH],
			    uint32_t difficulty);

/* task 1 */
int block_is_valid(block_t const *block, block_t const *prev_block);

/* task 2 */
void block_mine(block_t *block);

/* task 3 */
uint32_t blockchain_difficulty(blockchain_t const *blockchain);



#endif /* BLOCKCHAIN_H */
