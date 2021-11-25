#include "DataRow.h"
#include "includes.h"

class HashFunction
{
	int CalculateHash(char* data, int dataLength, int mod)
	{
		int result = 0;
		for (int i = 0; i < dataLength; i++)
		{
			result += (int)data[i]; // add the bits of this character as a byte to the int
			result <<= 3;			// shift the bits in the int to the left 8 bytes.  Overflow bits fall off
		}

		// Sampe call
		DataRow myDataRow;
		char buffer[80];
		sprintf(&buffer[0], "%d%s", myDataRow.ints[0], myDataRow.strs[0]);
		CalculateHash(buffer, strlen(buffer), 23);

		return result % mod;

		
		
	}
};