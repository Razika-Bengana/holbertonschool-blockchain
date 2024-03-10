#include "hblk_crypto.h"

/**
 * ec_from_pub - program that creates an EC_KEY structure from a public key
 *
 * @pub: the array containing the public key to be converted
 *
 * Return: a pointer to the created EC_KEY structure upon success, or NULL upon failure
 */

EC_KEY *ec_from_pub(uint8_t const pub[EC_PUB_LEN])
{
	if (pub == NULL)
		return (NULL);

	EC_KEY *key = EC_KEY_new_by_curve_name(EC_CURVE);

	if (key == NULL)
		return (NULL);

	EC_GROUP *group = EC_GROUP_new_by_curve_name(EC_CURVE);

	if (group == NULL)
	{
		EC_KEY_free(key);
		return (NULL);
	}

	EC_POINT *point = EC_POINT_new(group);

	if (point == NULL)
	{
		EC_GROUP_free(group);
		EC_KEY_free(key);
		return (NULL);
	}

	if (!EC_POINT_oct2point(group, point, pub, EC_PUB_LEN, NULL))
	{
		EC_POINT_free(point);
		EC_GROUP_free(group);
		EC_KEY_free(key);

		return (NULL);
	}

	if (!EC_KEY_set_public_key(key, point))
	{
		EC_POINT_free(point);
		EC_GROUP_free(group);
		EC_KEY_free(key);

		return (NULL);
	}

	EC_POINT_free(point);
	EC_GROUP_free(group);

	return (key);
}
