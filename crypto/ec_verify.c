#include "hblk_crypto.h"

/**
 * ec_verify - program that checks the signature of a given set of bytes
 * using a given EC_KEY public key
 *
 * @key: a pointer to the EC_KEY structure containing the public key
 * @msg: a pointer to the bytes to verify the signature of
 * @msglen: the number of bytes to verify
 * @sig: a pointer to the signature to be checked
 *
 * Return: 1 if the signature is valid, 0 otherwise
 */

int ec_verify(EC_KEY const *key, uint8_t const *msg, size_t msglen, sig_t const *sig)
{
	if (!key || !msg || !sig)
		return (0);

	/* Perform the ECDSA signature verification */
	if (ECDSA_verify(0, msg, msglen, sig->sig, sig->len, (EC_KEY *)key) != 1)
		return (0);

	return (1);
}