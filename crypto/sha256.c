#include "hblk_crypto.h"

/**
 * sha256 - program that computes the "SHA256" hash of a sequence of bytes
 *
 * this function takes a byte sequence ('s') and its length ('len'),
 * then calculates its SHA256 hash;
 * the hash result is stored in a pre-allocated 'digest' array
 * of 'SHA256_DIGEST_LENGTH' bytes (32 bytes);
 * it's designed to handle arbitrary lengths of data;
 *
 * the program uses OpenSSL's SHA256 functions for hashing, ensuring NULL
 * is returned for any processing errors or if 'digest' is NULL
 *
 * @s: a pointer to the byte sequence to hash
 * @len: the number of bytes in 's' to hash
 * @digest: the pre-allocated array where the hash is stored
 *
 * Return: a pointer to 'digest' with the hash, or NULL on failure or if 'digest' is NULL
 */


uint8_t *sha256(int8_t const *s, size_t len, uint8_t digest[SHA256_DIGEST_LENGTH])
{
	if (!digest)
	{
		return (NULL);
	}

	/* Initialize SHA256 context */
	SHA256_CTX ctx;

	if (!SHA256_Init(&ctx))
	{
		return (NULL); /* In case of error during initialization */
	}

	/* Update context with data */
	if (!SHA256_Update(&ctx, s, len))
	{
		return (NULL); /* In case of error during update */
	}

	/* Finalize the context and store the resulting hash in digest */
	if (!SHA256_Final(digest, &ctx))
	{
		return (NULL); /* In case of error during finalization */
	}

	/* digest = pointer to the resulting hash */
	return (digest);
}
