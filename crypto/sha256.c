#include "hblk_crypto.h"

/**
 * sha256 - computes the hash of a sequence of bytes
 * @s: sequence of bytes to be hashed
 * @len: number of bytes to hash in `s`
 * @digest: resulting hash stored in this buffer, if not NULL
 * Return: pointer to `digest`, or NULL on failure
 */

uint8_t *sha256(const int8_t *s, size_t len, uint8_t digest[SHA256_DIGEST_LENGTH])
{
	if (!digest)
	{
		fprintf(stderr, "sha256: NULL digest\n");
		return (NULL);
	}


	if (SHA256((const unsigned char *)s, len, digest))
	{
		return (digest);
	}
	else
	{
		fprintf(stderr, "sha256: SHA256 computation failure\n");
		return (NULL);
	}
}
