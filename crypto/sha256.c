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
		return (NULL);

	SHA256((const unsigned char *)s, len, digest);

	return (digest);
}
