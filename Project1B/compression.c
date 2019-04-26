#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "zlib.h"

#if defined(MSDOS) || defined(OS2) || defined(WIN32) || defined(__CYGWIN__)
#  include <fcntl.h>
#  include <io.h>
#  define SET_BINARY_MODE(file) setmode(fileno(file), O_BINARY)
#else
#  define SET_BINARY_MODE(file)
#endif

#define CHUNK 16384

int compress_buffer(
  unsigned char *dest_buffer, int dest_size,
  unsigned char *src_buffer, int src_len
){
  z_stream defstream;
  defstream.zalloc = Z_NULL;
  defstream.zfree = Z_NULL;
  defstream.opaque = Z_NULL;
  defstream.avail_in = (uInt)(src_len); // size of input, string
  defstream.next_in = src_buffer; // input char array
  defstream.avail_out = (uInt)dest_size; // size of output
  defstream.next_out = dest_buffer; // output char array

  deflateInit(&defstream, Z_DEFAULT_COMPRESSION);
  deflate(&defstream, Z_FINISH);
  deflateEnd(&defstream);

  return defstream.next_out - dest_buffer;
}
int decompress_buffer(
  unsigned char *dest_buffer, int dest_size,
  unsigned char *src_buffer, int src_len
){
  z_stream infstream;
  infstream.zalloc = Z_NULL;
  infstream.zfree = Z_NULL;
  infstream.opaque = Z_NULL;
  infstream.avail_in = (uInt)src_len; // size of input
  infstream.next_in = (Bytef *)src_buffer; // input char array
  infstream.avail_out = (uInt)dest_size; // size of output
  infstream.next_out = (Bytef *)dest_buffer; // output char array

  inflateInit(&infstream);
  inflate(&infstream, Z_NO_FLUSH);
  inflateEnd(&infstream);
  return 0;
}