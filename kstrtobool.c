#include "kstrtobool.h"

int kstrtobool(const char *s, bool *res)
{
	if (!s)
		return -EINVAL;

	switch (s[0]) {
	case 'y':
	case 'Y':
	case '1':
		*res = true;
		return 0;
	case 'n':
	case 'N':
	case '0':
		*res = false;
		return 0;
	case 'o':
	case 'O':
		switch (s[1]) {
		case 'n':
		case 'N':
			*res = true;
			return 0;
		case 'f':
		case 'F':
			*res = false;
			return 0;
		default:
			break;
		}
	default:
		break;
	}

	return -EINVAL;
}

#ifdef FUZZ_MAIN

int LLVMFuzzerTestOneInput(const uint8_t *data,
                           size_t size)
{
	if (data == NULL || size == 3) {
		bool res;
		kstrtobool((const char *)data, &res);
	}
	return 0;
}
#endif

#ifdef DUMMY_MAIN

int main(int argc, char *argv[])
{
	bool res;

	kstrtobool("y",  &res); kstrtobool("Y",  &res);
	kstrtobool("n",  &res); kstrtobool("N",  &res);
	kstrtobool("0",  &res); kstrtobool("1",  &res);
	kstrtobool("on", &res); kstrtobool("On", &res);
	kstrtobool("oN", &res); kstrtobool("ON", &res);
	kstrtobool("of", &res); kstrtobool("oF", &res);
	kstrtobool("Of", &res); kstrtobool("OF", &res);

	return 0;
}
#endif
