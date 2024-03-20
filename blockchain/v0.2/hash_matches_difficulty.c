#include "blockchain.h"

/**
 * hash_matches_difficulty - program that checks if a given hash meets
 * a specified difficulty level
 *
 * the difficulty level is represented by the number of leading zeros
 * in the binary representation of the hash
 *
 * @hash: a SHA-256 hash to check, represented as an array of uint8_t
 * @difficulty: the minimum number of leading zeros required for the hash
 *              to be considered as matching the difficulty
 *
 * Return: 1 if the hash matches the difficulty level by having the required
 *         number of leading zeros, 0 otherwise
 */

int hash_matches_difficulty(uint8_t const hash[SHA256_DIGEST_LENGTH],
			    uint32_t difficulty)
{
	uint32_t zeroBitsNeeded = difficulty;
	uint32_t zeroBitsCount = 0;
	int i, bit;

	for (i = 0; i < SHA256_DIGEST_LENGTH; ++i)
	{
		for (bit = 7; bit >= 0; --bit)
		{
			if ((hash[i] >> bit) & 1)
			{
				return (zeroBitsCount >= zeroBitsNeeded ? 1 : 0);
			}
			else
			{
				zeroBitsCount++;
			}
		}
	}

	return (zeroBitsCount >= zeroBitsNeeded ? 1 : 0);
}
