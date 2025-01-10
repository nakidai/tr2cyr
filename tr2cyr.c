#include <errno.h>
#include <wchar.h>
#include <wctype.h>

#include "tr2cyr.h"


int tr2cyr(tr2cyr_reader *reader, void *readerarg, tr2cyr_writer *writer, void *writerarg)
{
    size_t i;
    int lowercase;
    wint_t ch;

    while ((ch = reader(i++, readerarg)) != WEOF)
    {
        lowercase = towlower(ch) == ch;

        wchar_t towrite;
#define CASE(option, lower, upper) case option: towrite = lowercase ? lower : upper; break
        switch (towlower(ch))
        {
        CASE(L'a', L'а', L'А');
        CASE(L'b', L'б', L'Б');
        CASE(L'v', L'в', L'В');
        CASE(L'g', L'г', L'Г');
        CASE(L'd', L'д', L'Д');
        CASE(L'e', L'е', L'Е');
        CASE(L'z', L'з', L'З');
        CASE(L'i', L'и', L'И');
        CASE(L'j', L'й', L'Й');
        CASE(L'k', L'к', L'К');
        CASE(L'l', L'л', L'Л');
        CASE(L'm', L'м', L'М');
        CASE(L'n', L'н', L'Н');
        CASE(L'o', L'о', L'О');
        CASE(L'p', L'п', L'П');
        CASE(L'r', L'р', L'Р');
        CASE(L's', L'с', L'С');
        CASE(L't', L'т', L'Т');
        CASE(L'u', L'у', L'У');
        CASE(L'f', L'ф', L'Ф');
        CASE(L'h', L'х', L'Х');
        CASE(L'c', L'ц', L'Ц');
        case 'y':
        {
            if ((ch = reader(i++, readerarg)) == WEOF)
            {
                writer(lowercase ? L'y' : L'Y', writerarg);
                return errno ? -1 : 0;
            }

            switch(towlower(ch))
            {
            CASE(L'o', L'ё', L'Ё');
            CASE(L'z', L'ж', L'Ж');
            CASE(L'c', L'ч', L'Ч');
            CASE(L's', L'ш', L'Ш');
            CASE(L'g', L'щ', L'Щ');
            CASE(L'"', L'ъ', L'Ъ');
            CASE(L'i', L'ы', L'Ы');
            CASE(L'\'', L'ь', L'Ь');
            CASE(L'e', L'э', L'Э');
            CASE(L'u', L'ю', L'Ю');
            CASE(L'a', L'я', L'Я');
            default:
            {
                int ret = writer(lowercase ? L'y' : L'Y', writerarg);
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

        int ret = writer(towrite, writerarg);
        if (ret)
            return ret;
    }
    return errno ? -1 : 0;
}
