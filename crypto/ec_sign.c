#include "hblk_crypto.h"

/**
 * ec_sign - program that signs a given set of bytes using a given
 * EC_KEY private key
 *
 * @key: a pointer to the EC_KEY structure containing the private key
 * @msg: a pointer to the bytes to be signed
 * @msglen: the number of bytes to sign
 * @sig: the address at which to store the signature
 *
 * Return: a pointer to the signature buffer upon success,
 *         or NULL upon failure
 */

uint8_t *ec_sign(EC_KEY const *key, uint8_t const *msg, size_t msglen,
		 sig_t *sig)
{
	if (!key || !msg || !sig)
		return (NULL);

	sig->len = 0;

	/* Perform the ECDSA signature */
	if (ECDSA_sign(0, msg, msglen, sig->sig, (unsigned int *)&(sig->len),
		       (EC_KEY *)key) != 1)

		return (NULL);

	return (sig->sig);
}
