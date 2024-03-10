#include "hblk_crypto.h"

/**
 * ec_save - program that saves an existing EC key pair on disk
 *
 * @key: a pointer to the EC key pair to be saved
 * @folder: the path to the folder in which to save the keys
 *
 * Return: 1 on success, 0 on failure
 */

int ec_save(EC_KEY *key, char const *folder)
{
	char priv_key_path[PATH_MAX];
	char pub_key_path[PATH_MAX];
	FILE *priv_key_file, *pub_key_file;

	if (!key || !folder)
		return (0);

	if (mkdir(folder, 0700) == -1 && errno != EEXIST)
		return (0);

	snprintf(priv_key_path, PATH_MAX, "%s/%s", folder, PRI_FILENAME);
	snprintf(pub_key_path, PATH_MAX, "%s/%s", folder, PUB_FILENAME);

	/* Save the private key in PEM format */
	priv_key_file = fopen(priv_key_path, "w");

	if (!priv_key_file)
		return (0);

	if (!PEM_write_ECPrivateKey(priv_key_file, key, NULL, NULL, 0, NULL, NULL))
	{
		fclose(priv_key_file);
		return (0);
	}
	fclose(priv_key_file);

	/* Save the public key in PEM format */
	pub_key_file = fopen(pub_key_path, "w");

	if (!pub_key_file)
		return (0);

	if (!PEM_write_EC_PUBKEY(pub_key_file, key))
	{
		fclose(pub_key_file);
		return (0);
	}
	fclose(pub_key_file);

	return (1);
}
