#include "hblk_crypto.h"

/**
 * ec_save - program that saves an existing EC key pair on the disk
 *
 * @key: the EC key pair to be saved on disk
 * @folder: the path to the folder in which to save the keys
 *
 * Return: 1 upon success, 0 upon failure
 */


int ec_save(EC_KEY *key, const char *folder)
{
	FILE *priv_key_file;
	FILE *pub_key_file;

	if (!key || !folder)
	{
		return (0);
	}
	if (mkdir(folder, 0700) == -1 && errno != EEXIST)
	{
		return (0);
	}
	priv_key_file = fopen(folder, "/key.pem");

	if (!priv_key_file)
	{
		return (0);
	}
	if (!PEM_write_ECPrivateKey(priv_key_file, key, NULL, NULL, 0, NULL, NULL))
	{
		fclose(priv_key_file);
		return (0);
	}
	fclose(priv_key_file);

	pub_key_file = fopen(folder, "/key_pub.pem");

	if (!pub_key_file)
	{
		return (0);
	}
	if (!PEM_write_EC_PUBKEY(pub_key_file, key))
	{
		fclose(pub_key_file);
		return (0);
	}
	fclose(pub_key_file);

	return (1);
}
