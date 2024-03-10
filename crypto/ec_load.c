#include "hblk_crypto.h"

/**
 * ec_load - program that loads an EC key pair from disk
 *
 * @folder: the path to the folder from which to load the keys
 *
 * Return: a pointer to the created EC key pair upon success,
 *         or NULL upon failure
 */

EC_KEY *ec_load(char const *folder)
{
	char priv_key_path[PATH_MAX];
	char pub_key_path[PATH_MAX];
	EC_KEY *key = NULL;
	FILE *priv_key_file;

	if (!folder)
		return (NULL);

	snprintf(priv_key_path, PATH_MAX, "%s/%s", folder, PRI_FILENAME);
	snprintf(pub_key_path, PATH_MAX, "%s/%s", folder, PUB_FILENAME);

	/* Load the private key from PEM format */
	priv_key_file = fopen(priv_key_path, "r");

	if (!priv_key_file)
		return (NULL);

	key = PEM_read_ECPrivateKey(priv_key_file, NULL, NULL, NULL);

	fclose(priv_key_file);

	return (key);
}
