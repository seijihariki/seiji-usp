#include <cstdlib>
#include <string>
#include <cstdio>
unsigned char M[100000];

typedef unsigned int uint;

char* str = (char*)"Google was founded by Larry Page and Sergey Brin while they were Ph.D. students at Stanford University, California. Together, they own about 14 percent of its shares and control 56 percent of the stockholder voting power through supervoting stock. They incorporated Google as a privately held company on September 4, 1998. An initial public offering (IPO) took place on August 19, 2004, and Google moved to its new headquarters in Mountain View, California, nicknamed the Googleplex.\n\n In August 2015, Google announced plans to reorganize its interests as a holding company called Alphabet Inc. When this restructuring took place on October 2, 2015, Google became Alphabet's leading subsidiary, as well as the parent for Google's Internet interests.";

int main()
{
	uint cols = 20;
	char c = 1;
	for(int i = 0, cnt = 0; c; i++) M[i] = c = str[cnt++];

	printf("Copied to memory\n");
	printf("String is %s\n", &M);

	uint pos = 0;
	do
	{
		//printf("Line from pos %d\n", pos);
		uint spaces = 0;
		uint r = 0;
		uint g = 0;
		uint b = 1;
		uint dist = 0;
		int i = 0;
		for(c = M[pos + i]; c && c^10 && i < cols; i++)
		{
			//printf("char %c\n",c);
			c = M[pos + i];
			if (c == 0x20) spaces++;
		}
		if (M[pos + i] && M[pos + i]^0x20)
		{
			for(; b <= i; b++)
			{
				c = M[pos + i - b + 1];
				if (c == 0x20) break;
			}
			//printf("Neg delta = %d\n",b);
			i -= b;
			if (i < 0)
			{
				while (M[pos + i + 1] != 0x20)i++;
			} else
			{
				dist = b - 1;
				spaces--;
				if (spaces)
				{
					g = dist/spaces;
					r = dist%spaces;
				}
			}
			//printf("g r %d %d\n", g, r);
		} else i--;
		uint spc = 0;
		i += pos;
		//printf("i at %d\n", i);
		bool last_line = false;

		for(int z = pos; z <= i; z++)
		{
			c = M[z];
			if (c == 10 || !c) last_line = true;
		}

		//printf("ll: %d\n", last_line);

		for(; pos <= i; pos++)
		{
			c = M[pos];
			if (c == 0x20 && !last_line)
			{
				spc++;
				for(int k = 0; k < g + 1; k++) putchar(32);
				if(spc > spaces - r) putchar(32);
			}else putchar(c);
			if(!c)break;
		}
		if (!last_line) putchar(10);
		pos++;
	}while(M[pos]);
}
//Google was founded by Larry Page and  Sergey  Brin
