#include <locale.h>
#include <stdio.h>
#include <wchar.h>

#include "tr2cyr.h"


static wint_t reader(size_t i, void *arg)
{
    return getwchar();
}

static int writer(wchar_t ch, void *arg)
{
    (void)arg;
    return putwchar(ch) == WEOF ? -1 : 0;
}

int main(int argc, char **argv)
{
    setlocale(LC_CTYPE, "");
    tr2cyr(&reader, 0, &writer, 0);
}
