#include "io.h"
#include "code.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

static int offset = 0;
static int wrtoffset = 0;
static uint8_t readbuf[4096];
static uint8_t writebuf[4096];
static int bits_written = 0;
static int words_write = 0;
static uint8_t word_buff[4096];

//uint16_t curr_byt = 0;
//uint8_t curr_bit = 0;


int read_bytes(int infile, uint8_t *buf, int to_read) {

  int read_bytes;

  while ((read_bytes = read(infile, buf + offset, to_read)) != 0) {
    offset += read_bytes;
   // printf("byeeee %d",read_bytes);
  }

  if (offset == to_read)
    return to_read;

  return offset;
}

int write_bytes(int outfile, uint8_t *buf, int to_write) {

 // static int wrtoffset = 0;
  int write_bytes;
  to_write = offset;

  while((write_bytes = write(outfile, buf + wrtoffset, to_write - wrtoffset)) >0)
        {
    wrtoffset += write_bytes;
//   printf("written %d", write_bytes);
  }
 // printf("written %d", write_bytes);
  if (wrtoffset == to_write)
    return to_write;

  return wrtoffset;
}

void read_header(int infile, FileHeader *header) {

  if (header->magic == MAGIC) {
    read_bytes(infile, (uint8_t *)header, sizeof(FileHeader));
  }

  // then use fchmod here to match permisisons and set back to original
}

void write_header(int outfile, FileHeader *header) {
 
write(outfile,(uint8_t*)header, sizeof(FileHeader));
// write_bytes(outfile, (uint8_t *)header, sizeof(FileHeader));
 offset += sizeof(FileHeader);
 // printf("head %lu", sizeof(FileHeader));
}

//write is compression  (encode)
// read is decompress  (decode)

bool read_sym(int infile, uint8_t *sym) {

  bool toread = 1;
  static int i = 8;
   //i = wrtoffset;
  //static boo left = 0;
  static int readinbytes = 0;

  if (i == 8){
    readinbytes = read_bytes(infile, readbuf, sizeof(readbuf));
  printf("\n%d", readinbytes);}
  //left == 1;

  if (readinbytes < 4096) {
    *sym = readbuf[i];
    printf("\n%d", *sym);
    //  printf("\n whats in the buf: %d\n", readbuf[i]);
    ++i;
    if (i == readinbytes)
      toread = 0;
  }

  return toread;
}

// making the compressed versiob, putting into outfile, use write buffer, track w bits write
void buffer_pair(int outfile, uint16_t code, uint8_t sym, uint8_t bitlen) {
printf("code is %d", code);
printf("sym is %d", sym);
printf("nitlennn is %d", bitlen);
  for (int i = 0; i < bitlen; i++) {
    if (bits_written == (offset-8) * 8) {
      //printf("\n bits wr: %d", bits_written);
      write_bytes(outfile, writebuf, sizeof(writebuf));
      bits_written = 0;
    }
   
   uint16_t curr_byt = bits_written / 8;
   uint8_t curr_bit = bits_written % 8;
  
    uint16_t the_bitval = code & (00000001 << i);
    the_bitval = the_bitval >> i;

    if (the_bitval == 1) {
      printf("\n the bit %d", the_bitval);
      uint16_t writebyte = writebuf[curr_byt];
  //   printf("\nwritebyee %d", writebyte); 
    printf("currbyt %d",   curr_byt);
     uint16_t bit = writebyte | (00000001 << (curr_bit));
     // printf("cccjcjc %d",  bit);
      writebuf[curr_byt] |= bit;
      // printf("cccjcjc %d",   writebuf[curr_byt]);
     ++bits_written;
    } else if (the_bitval == 0) {
     printf("\n the bit %d", the_bitval);
      uint16_t writebyte = writebuf[curr_byt];
      uint16_t bit = writebyte & (00000001 << (curr_bit));
      writebuf[curr_byt] |= bit;
     ++bits_written;
    }
//  ++bits_written;
  }


   int i = 0;
  for (i = 0; i < 8; i++) {
    if (bits_written == (offset-8) * 8) {
      write_bytes(outfile, writebuf, sizeof(writebuf));
      bits_written = 0;
    }
    uint8_t curr_byt = bits_written / 8;
    uint8_t curr_bit = bits_written % 8;
    uint8_t the_bitval = sym & (00000001 << ((curr_bit-curr_bit) +  i));
    the_bitval = the_bitval >>  ((curr_bit-curr_bit) +  i);
    if (the_bitval == 1) {
        printf("\n the bit %d", the_bitval);
      uint8_t writebyte = writebuf[curr_byt];
printf("\n bytte val%d", curr_byt);      
uint8_t bit = writebyte | (00000001 << curr_bit);
      writebuf[curr_byt] |= bit;
      ++bits_written;
    } else if (the_bitval == 0) {
       printf("\n the bit %d", the_bitval);
      uint8_t writebyte = writebuf[curr_byt];
      uint8_t bit = writebyte & (00000001 << curr_bit);
      writebuf[curr_byt] |= bit;
     ++bits_written;
    }
  }
//++bits_written;
 printf("\n bits wr: %d", bits_written);
printf("\n bytes writeen: %d", writebuf[1]);
}

void flush_pairs(int outfile) {
  if (bits_written != offset * 8) {
    write_bytes(outfile, writebuf, bits_written);
  }
}

bool read_pair(int infile, uint16_t *code, uint8_t *sym, uint8_t bitlen) {

  bool moreread = 1;
  *code = 0;
  *sym = 0;

  static int bits_read = 0;

  for (int i = 0; i < bitlen; i++) {
    if (bits_read == offset * 8) {
      read_bytes(infile, readbuf, sizeof(readbuf));
      bits_read = 0;
    }
    read_bytes(infile, readbuf, sizeof(readbuf));

    uint8_t curr_byt = readbuf[bits_read / 8];
    uint16_t curr_bit = bits_read % bitlen;
    uint16_t the_bitval = curr_byt & (00000001 << curr_bit);

    the_bitval = the_bitval >> curr_bit;
    if (the_bitval == 1) {
      uint16_t bit = *code | (00000001 << curr_bit);
      *code |= bit;
      printf("\n *the supposed byte: %d", bit);
      ++bits_read;
    } else if (the_bitval == 0) {
      uint16_t bit = *code & (00000001 << curr_bit);
      *code |= bit;
      ++bits_read;
    }
  }

  if (*code == STOP_CODE) {
    moreread = 0;
    return moreread;
  }

  for (int i = 0; i < 8; i++) {
    if (bits_read == bits_read * 8) {
      read_bytes(infile, readbuf, sizeof(readbuf));
    }

    uint8_t curr_byt = readbuf[bits_read / 8];
    uint8_t curr_bit = bits_read % bitlen;
    uint8_t the_bitval = curr_byt & (00000001 << curr_bit);
    the_bitval = the_bitval >> curr_bit;
    if (the_bitval == 1) {
      uint8_t bit = *sym | (00000001 << ((curr_bit - curr_bit) + i));
      *sym |= bit;
      ++bits_read;
    } else if (the_bitval == 0) {
      uint8_t bit = *sym & (00000001 << ((curr_bit - curr_bit) + i));
      *sym |= bit;
      ++bits_read;
    }
  }
  read_bytes(infile, readbuf, sizeof(readbuf));
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
