#include "io.h"
#include "code.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>


//int readinbytes = 0;
static int offset = 0;
static uint8_t readbuf[4096];
static uint8_t writebuf[4096];
static int bits_written = 0;
static int words_write = 0;
static uint8_t word_buff[4096];

int read_bytes(int infile, uint8_t *buf, int to_read) {

 int read_bytes;
//  static int atbit = 1;
while((read_bytes = read(infile,buf+offset,to_read))!=0)
{
offset += read_bytes;
//++atbit;
printf("\n%d",read_bytes);


}
if(offset == to_read)
return to_read;


//printf("\n%d", offset);
return offset;
//printf("toread : %d",to_read);







/*
  int read_bytes;
  static int atbit = 1; 
  read_bytes = read(infile, buf + offset, to_read);
 ++atbit;
    offset += read_bytes;

  while (read_bytes!=0 || atbit == to_read)
  {
     read_bytes = read(infile, buf + offset, atbit);
    ++atbit;
  printf("read byt %d", atbit);
    offset += read_bytes;
  
  if (read_bytes == 0)
    return offset;
}*/
//  return offset;
}


int write_bytes(int outfile, uint8_t *buf, int to_write) {

static int wrtoffset = 0;
int write_bytes;
to_write = offset;
  while((write_bytes = write(outfile,buf+wrtoffset,to_write-wrtoffset))>0)
  {
  wrtoffset += write_bytes;
  printf("\n%d",write_bytes);


  }
  if(wrtoffset == to_write)
    return to_write;


  //printf("\n%d", offset);
  return wrtoffset;
}







 
/*static int offsets = 0;
  int write_bytes;
  static int atbit = 1;
  write_bytes = write(outfile, buf + offsets, to_write);
 ++atbit;
    offsets += write_bytes;

  while (write_bytes!=0 || atbit == to_write)
  {
     write_bytes = write(outfile, buf + offsets, atbit);
    ++atbit;
  printf("write byt %d", atbit);
    offsets += write_bytes;

  if (write_bytes == 0)
    return offsets;
}
  return offsets;




 static int offset = 0;
  int write_bytes;

  while ((write_bytes = write(outfile, buf + offset, to_write - offset)) > 0) {
       offset += write_bytes;
     }
  if (offset == to_write)
    return to_write;

  return offset;*/



void read_header(int infile, FileHeader *header) {

  if (header->magic == MAGIC) {
    read_bytes(infile, (uint8_t *)header, sizeof(FileHeader));
  }

  // then use fchmod here to match permisisons and set back to original
}

void write_header(int outfile, FileHeader *header) {

  write_bytes(outfile, (uint8_t *)header, sizeof(FileHeader));
}

//write is compression  (encode)
// read is decompress  (decode)

bool read_sym(int infile, uint8_t *sym) {

bool toread = 1;
static int i = 0;

int readinbytes = read_bytes(infile, readbuf, sizeof(readbuf));

  if (readinbytes < 4096) {
    *sym = readbuf[i];
//  printf("\n whats in the buf: %d\n", readbuf[i]);
    ++i;
    if (i == readinbytes)
      toread = 0;
  }

  return toread;
}

// making the compressed versiob, putting into outfile, use write buffer, track w bits write
void buffer_pair(int outfile, uint16_t code, uint8_t sym, uint8_t bitlen) {

static int checkbytes = 0;
 printf("\n the sym %d", sym);
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

}

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
