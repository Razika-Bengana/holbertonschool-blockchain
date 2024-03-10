#include "hblk_crypto.h"

/**
 *
 * @return
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
