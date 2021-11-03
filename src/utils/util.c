#include "util.h"

INDEX_T GetRandomNumber(INDEX_T min, INDEX_T max)
{
	return (rand() % (max - min + 1)) + min;
}
