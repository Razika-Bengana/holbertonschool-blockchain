#include "hblk_crypto.h"

/**
 *
 * @param s
 * @param len
 * @param digest
 * @return
 */


uint8_t *sha256(const int8_t *s, size_t len, uint8_t digest[SHA256_DIGEST_LENGTH])
{
	if (!digest)
	{
		return (NULL);
	}

	SHA256_CTX context;
	if (SHA256_Init(&context) && SHA256_Update(&context, s, len) && SHA256_Final(digest, &context))
	{
		return (digest);
	}
	else
	{
		return (NULL);
	}
}
