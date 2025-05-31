
static unsigned char ctr = 0;

void SystemInit(void)
{}

int main(void)
{
	while (1)
	{
		ctr++;
		for(unsigned long i = 0; i < 200000; i++);
	}

	return 0;
}