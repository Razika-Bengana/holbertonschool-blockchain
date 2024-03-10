#include "hblk_crypto.h"

/**
 * ec_to_pub - program that extracts the public key from an EC_KEY structure
 *
 * @key: a pointer to the EC_KEY structure to retrieve the public key from
 * @pub: the address to store the extracted public key (not compressed)
 *
 * Return: a pointer to pub on success, or NULL on failure
 */

uint8_t *ec_to_pub(EC_KEY const *key, uint8_t pub[EC_PUB_LEN])
{
	const EC_POINT *point;

	if (!key || !pub)
		return (NULL);

	point = EC_KEY_get0_public_key(key);

	if (!point)
		return (NULL);

	if (!EC_POINT_point2oct(EC_KEY_get0_group(key), point,
				POINT_CONVERSION_UNCOMPRESSED, pub, EC_PUB_LEN, NULL))

		return (NULL);

	return (pub);
}
