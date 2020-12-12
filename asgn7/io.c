#include "io.h"
#include "code.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>


<<<<<<< HEAD
//int readinbytes = 0;
static uint8_t readbuf[4096];
static uint8_t writebuf[4096];
=======
static char readbuf[4096];
static char writebuf[4096];
>>>>>>> a809f7126498695b8387771537a9abd28e8c2d45
static int bits_written = 0;
static int words_write = 0;
static uint8_t word_buff[4096];

<<<<<<< HEAD
int read_bytes(int infile, uint8_t *buf, int to_read) {
  static int offset = 0;
  int read_bytes;

  while ((read_bytes = read(infile, buf + offset, to_read)) > 0)
  {
    offset += read_bytes;
  }
  if (offset == 0)
    return to_read;

  return offset;
=======
int read_bytes(int infile, char *buf, int to_read)
{
static int offset= 0;
int read_bytes;

while((read_bytes=read(infile, buf+offset, to_read-offset)) >0)
{
offset +=  read_bytes;
printf("\nin reader %d", read_bytes);
}
return  offset;
}



int write_bytes(int outfile, uint8_t *buf, int to_write)
{
static int offset= 0;
int write_bytes;

while((write_bytes=write(outfile, buf+offset, to_write-offset)) > 0 )
{
offset +=  write_bytes;
printf("\nin the writr %d", write_bytes);
}
return  offset;
>>>>>>> a809f7126498695b8387771537a9abd28e8c2d45
}

int write_bytes(int outfile, uint8_t *buf, int to_write) {
  static int offset = 0;
  int write_bytes;

  while ((write_bytes = write(outfile, buf + offset, to_write - offset)) > 0) {
       offset += write_bytes;
     }
  if (offset == to_write)
    return to_write;

<<<<<<< HEAD
  return offset;
}
=======
if (header->magic == MAGIC) {
   read_bytes(infile, (char*)header, sizeof(FileHeader));
 }
>>>>>>> a809f7126498695b8387771537a9abd28e8c2d45

void read_header(int infile, FileHeader *header) {

  if (header->magic == MAGIC) {
    read_bytes(infile, (uint8_t *)header, sizeof(FileHeader));
  }

  // then use fchmod here to match permisisons and set back to original
}

void write_header(int outfile, FileHeader *header) {

<<<<<<< HEAD
  write_bytes(outfile, (uint8_t *)header, sizeof(FileHeader));
=======
write_bytes(outfile, (char*)header, sizeof(FileHeader));
>>>>>>> a809f7126498695b8387771537a9abd28e8c2d45
}

//write is compression  (encode)
// read is decompress  (decode)

bool read_sym(int infile, uint8_t *sym) {

<<<<<<< HEAD
  
  bool toread = 1;
  static int i = 0;
=======
bool toread = 1;
static int i = 0;

int bytes = read_bytes(infile, readbuf, sizeof(readbuf));

//i+=bytes;

printf("haliuiuil %d",bytes);


if(bytes < 4096)
{
*sym = readbuf[i];
++i;
if(i == bytes)
{
//lseek(infile,i, SEEK_CUR);
return 0;
}
}




//if(bytes == 0)
{
*sym = readbuf[i];
++i;


if(i == 4096)
{
i = 0;

for(int i = 0; i < 4096; i++)
{
readbuf[i] = 0;
}

bytes = read_bytes(infile, readbuf, sizeof(readbuf));

if(bytes==0){
   toread = 0;
}
}
>>>>>>> a809f7126498695b8387771537a9abd28e8c2d45

 int readinbytes = read_bytes(infile, readbuf, sizeof(readbuf));

  if (readinbytes < 4096) {
    *sym = readbuf[i];
  printf("\n whats the buf: %d\n", readbuf[i]);
    ++i;
    if (i == readinbytes)
      toread = 0;
  }

<<<<<<< HEAD
  return toread;
=======
if(bytes < 4096)
{
*sym = readbuf[i];
++i;
if(i == bytes)
{
return 0;
}
}
return toread;
>>>>>>> a809f7126498695b8387771537a9abd28e8c2d45
}

// making the compressed versiob, putting into outfile, use write buffer, track w bits write
void buffer_pair(int outfile, uint16_t code, uint8_t sym, uint8_t bitlen) {
static int checkbytes = 0;
 printf("\n thr sym %d", sym);
++checkbytes;
 printf("\n total byts %d", checkbytes);
  for (int i = 0; i < bitlen; i++) {
    if (bits_written == 4096 *8) {
      write_bytes(outfile, writebuf, sizeof(writebuf));
    }
    uint8_t curr_byt = bits_written / 8;
    uint16_t curr_bit = bits_written % bitlen;
    uint16_t the_bitval = code & (00000001 << curr_bit);
    the_bitval = the_bitval >> curr_bit;
    if (the_bitval == 1) {
      uint16_t writebyte = writebuf[curr_byt];
      uint16_t bit = writebyte | (00000001 << curr_bit);
      //printf("\n the supposed byte: %d", bit);
      writebuf[curr_byt] = bit;
      ++bits_written;
    } else if (the_bitval == 0) {
      uint16_t writebyte = writebuf[curr_byt];
      uint16_t bit = writebyte & (00000001 << curr_bit);
      //printf("\n the supposed byte: %d", bit);
      writebuf[curr_byt] |= bit;
      ++bits_written;
    }

    //printf("\n at the bit: %d", curr_bit);
  }
  //printf("\n the final byte: %d", writebuf[0]);

  for (int i = 0; i < 8; i++) {
    if (bits_written == 4096 * 8) {
      write_bytes(outfile, writebuf, sizeof(writebuf));
    }
    //printf("\n bits wrote: %d", bits_written);
    uint8_t curr_byt = bits_written / 8;
    uint8_t curr_bit = bits_written % 8;
    uint8_t the_bitval = sym & (00000001 << ((curr_bit - curr_bit) + i));
    the_bitval = the_bitval >> ((curr_bit - curr_bit) + i);
    if (the_bitval == 1) {
      uint8_t writebyte = writebuf[curr_byt];
      uint8_t bit = writebyte | (00000001 << curr_bit);
      //printf("\n the supposed byte: %d", bit);
      writebuf[curr_byt] = bit;
      ++bits_written;
    } else if (the_bitval == 0) {
      uint8_t writebyte = writebuf[curr_byt];
      uint8_t bit = writebyte & (00000001 << curr_bit);
      //printf("\n the supposed byte: %d", bit);
      writebuf[curr_byt] |= bit;
      ++bits_written;
    }

    //printf("\n the final byte: %d", writebuf[1]);
  }
  printf("\n bits wr: %d", bits_written);
}

void flush_pairs(int outfile) {
  if (bits_written != 4096 * 8) {
    write_bytes(outfile, writebuf, bits_written);
  }
}

bool read_pair(int infile, uint16_t *code, uint8_t *sym, uint8_t bitlen) {

  bool moreread = 1;
  *code = 0;
  *sym = 0;

  static int bits_read = 0;

  for (int i = 0; i < bitlen; i++) {
    if (bits_read == 4096 * 8) {
      read_bytes(infile, readbuf, sizeof(readbuf));
    }

    uint8_t curr_byt = readbuf[bits_read / 8];
    uint16_t curr_bit = bits_read % bitlen;
    uint16_t the_bitval = curr_byt & (00000001 << curr_bit);
    the_bitval = the_bitval >> curr_bit;
    if (the_bitval == 1) {
      uint16_t bit = *code | (00000001 << curr_bit);
      *code = bit;
      //printf("\n *the supposed byte: %d", bit);
      ++bits_read;
    } else if (the_bitval == 0) {
      uint16_t bit = *code & (00000001 << curr_bit);
      *code = bit;
      //printf("\n *the supposed byte: %d", bit);
      ++bits_read;
    }
  }

  if (*code == STOP_CODE) {
    moreread = 0;
    return moreread;
  }
  //printf("\n read code: %d", *code);

  for (int i = 0; i < 8; i++) {
    if (bits_read == 4096 * 8) {
      read_bytes(infile, readbuf, sizeof(readbuf));
    }

    uint8_t curr_byt = readbuf[bits_read / 8];
    uint8_t curr_bit = bits_read % bitlen;
    uint8_t the_bitval = curr_byt & (00000001 << curr_bit);
    the_bitval = the_bitval >> curr_bit;
    if (the_bitval == 1) {
      uint8_t bit = *sym | (00000001 << ((curr_bit - curr_bit) + i));
      *sym = bit;
      //printf("\n *the supposed byte: %d", bit);
      ++bits_read;
    } else if (the_bitval == 0) {
      uint8_t bit = *sym & (00000001 << ((curr_bit - curr_bit) + i));
      *sym = bit;
      //printf("\n *the supposed byte: %d", bit);
      ++bits_read;
    }
  }
  return moreread;
}

void buffer_word(int outfile, Word *w) {
  //static int words_write = 0;
  //static uint8_t word_buff[4096];
  // or might need to use global one and change the words write var

  for (uint32_t i = 0; i < w->len; i++) {
    if (words_write == 4096) {
      write_bytes(outfile, word_buff, sizeof(word_buff));
    }

    word_buff[i] = w->syms[i];
    ++words_write;
  }
}

void flush_words(int outfile) {
  if (words_write != 4096) {
    write_bytes(outfile, word_buff, sizeof(word_buff));
  }
}
