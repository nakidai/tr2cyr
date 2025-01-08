#include <errno.h>
#include <locale.h>
#include <stdio.h>
#include <wchar.h>

/*
 * a = а
 * b = б
 * v = в
 * g = г
 * d = д
 * e = е
 * yo = ё
 * yz = ж
 * z = з
 * i = и
 * j = й
 * k = к
 * l = л
 * m = м
 * n = н
 * o = о
 * p = п
 * r = р
 * s = с
 * t = т
 * u = у
 * f = ф
 * h = х
 * c = ц
 * yc = ч
 * ys = ш
 * yg = щ
 * y" = ъ
 * yi = ы
 * y' = ь
 * ye = э
 * yu = ю
 * ya = я
 */

typedef int Translator_Writer(wchar_t ch, void *arg);

int Translator_convert(FILE *file, Translator_Writer *writer, void *arg)
{
    wint_t ch;
    while ((ch = getwchar()) != WEOF)
    {
        wchar_t towrite;
#define CASE(x, y) case x: towrite = y; break
        switch (ch)
        {
        CASE(L'a', L'а');
        CASE(L'b', L'б');
        CASE(L'v', L'в');
        CASE(L'g', L'г');
        CASE(L'd', L'д');
        CASE(L'e', L'е');
        CASE(L'z', L'з');
        CASE(L'i', L'и');
        CASE(L'j', L'й');
        CASE(L'k', L'к');
        CASE(L'l', L'л');
        CASE(L'm', L'м');
        CASE(L'n', L'н');
        CASE(L'o', L'о');
        CASE(L'p', L'п');
        CASE(L'r', L'р');
        CASE(L's', L'с');
        CASE(L't', L'т');
        CASE(L'u', L'у');
        CASE(L'f', L'ф');
        CASE(L'h', L'х');
        CASE(L'c', L'ц');
        case 'y':
        {
            if ((ch = getwchar()) == WEOF)
                return errno ? -1 : 0;

            switch(ch)
            {
            CASE(L'o', L'ё');
            CASE(L'z', L'ж');
            CASE(L'c', L'ч');
            CASE(L's', L'ш');
            CASE(L'g', L'щ');
            CASE(L'"', L'ъ');
            CASE(L'i', L'ы');
            CASE(L'\'', L'ь');
            CASE(L'e', L'э');
            CASE(L'u', L'ю');
            CASE(L'a', L'я');
            default:
            {
                int ret = writer(L'y', arg);
                if (ret)
                    return ret;

                towrite = ch;
            } break;
            }
        } break;
        default:
            towrite = ch;
        }
#undef CASE

        int ret = writer(towrite, arg);
        if (ret)
            return ret;
    }
    return errno ? -1 : 0;
}

static int writer(wchar_t ch, void *arg)
{
    (void)arg;
    return putwchar(ch) == WEOF ? -1 : 0;
}

int main(int argc, char **argv)
{
    setlocale(LC_CTYPE, "");
    Translator_convert(stdin, &writer, 0);
}
