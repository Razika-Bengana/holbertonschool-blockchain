#include "hblk_crypto.h"

/**
 * ec_create - program that creates a new EC key pair
 *
 * We have to use the secp256k1 elliptic curve to create
 * the new pair (See EC_CURVE macro)
 *
 * Return: a pointer to an EC_KEY structure, containing both
 *         the public and private keys, or NULL upon failure
 */

EC_KEY *ec_create(void)
{
	EC_KEY *key = EC_KEY_new_by_curve_name(EC_CURVE);

	if (!key)
	{
		perror("EC_KEY_new_by_curve_name");
		return (NULL);
	}

	if (!EC_KEY_generate_key(key))
	{
		perror("EC_KEY_generate_key");
		EC_KEY_free(key);
		return (NULL);
	}

	return (key);
}
