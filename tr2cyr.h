#ifndef __TR2CYR_H__
#define __TR2CYR_H__

#include <wchar.h>


typedef int tr2cyr_writer(wchar_t ch, void *arg);
typedef wint_t tr2cyr_reader(size_t i, void *arg);

int tr2cyr(tr2cyr_reader *reader, void *readerarg, tr2cyr_writer *writer, void *writerarg);

#endif /* __TR2CYR_H__ */
