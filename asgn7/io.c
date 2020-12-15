#include "io.h"
#include "code.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

static int offset = 0; // global counters to keep track off index
static int wrtoffset = 0;
static uint8_t readbuf[4096];
static uint8_t writebuf[4096];
static int bits_written = 0;
static int bits_read = 0;

int read_bytes(int infile, uint8_t *buf, int to_read) {

  int read_bytes;
  // reads in until eof or to_read block reached
  while ((read_bytes = read(infile, buf + offset, to_read)) != 0) {
    offset += read_bytes;
  }

  if (offset == to_read)
    return to_read;

  return offset;
}

int write_bytes(int outfile, uint8_t *buf, int to_write) {

  int write_bytes;
  to_write = offset;
  // write out until eof or to_write block reached
  while ((write_bytes = write(outfile, buf + wrtoffset, to_write - wrtoffset))
         > 0) {
    wrtoffset += write_bytes;
  }
  if (wrtoffset == to_write)
    return to_write;

  return wrtoffset;
}

void read_header(int infile, FileHeader *header) {
  // must check to see if header matched the magic # of the infile
  if (header->magic == MAGIC) {
    read_bytes(infile, (uint8_t *)header, sizeof(FileHeader));
  }
}

void write_header(int outfile, FileHeader *header) {

  write(outfile, (uint8_t *)header, sizeof(FileHeader));
  offset
      += sizeof(FileHeader); // 8bytes will be already written so updated index
}

bool read_sym(int infile, uint8_t *sym) {

  bool toread = 1;
  static int i = 8;
  static int readinbytes = 0;

  if (i == 8) {
    readinbytes = read_bytes(infile, readbuf, sizeof(readbuf));
  }
  if (readinbytes < 4096) { // if less than block of 4096 read in, update buffer
    *sym = readbuf[i];
    ++i;
    if (i == readinbytes)
      toread = 0;
  }
  if (readinbytes == 4096) {
    *sym = readbuf[i];
    ++i;
    if (i
        == readinbytes) { // when entire block of 4096 read in, read another block in
      readinbytes = read_bytes(infile, readbuf, sizeof(readbuf));
      toread = 0;
    }
  }
  return toread;
}

void buffer_pair(int outfile, uint16_t code, uint8_t sym, uint8_t bitlen) {

  for (int i = 0; i < bitlen; i++) {
    if (bits_written == (offset)*8) {
      write_bytes(outfile, writebuf, sizeof(writebuf)); // when buffer exhausted
      bits_written = 0;
    }

    uint16_t curr_byt = (bits_written) / 8; // get the byte
    uint8_t curr_bit = (bits_written) % 8; // get the bit

    uint16_t the_bitval = code & (00000001 << i);
    the_bitval = the_bitval >> i;

    if (the_bitval
        == 1) { // perform bit shifts and masks to set set bytes w variable len encoding
      uint16_t writebyte = writebuf[curr_byt];
      uint16_t bit = writebyte | (00000001 << (curr_bit));
      writebuf[curr_byt] |= bit;
      ++bits_written;
    } else if (the_bitval == 0) {
      uint16_t writebyte = writebuf[curr_byt];
      uint16_t bit = writebyte & (00000001 << (curr_bit));
      writebuf[curr_byt] |= bit;
      ++bits_written;
    }
  }

  int i = 0;
  for (i = 0; i < 8;
       i++) { // perform the same operations for the symbol to put into buffer
    if (bits_written == (offset)*8) {
      write_bytes(outfile, writebuf, sizeof(writebuf));
      bits_written = 0;
    }
    uint8_t curr_byt = (bits_written) / 8;
    uint8_t curr_bit = (bits_written) % 8;
    uint8_t the_bitval = sym & (00000001 << ((curr_bit - curr_bit) + i));
    the_bitval = the_bitval >> ((curr_bit - curr_bit) + i);
    if (the_bitval == 1) {
      uint8_t writebyte = writebuf[curr_byt];
      uint8_t bit = writebyte | (00000001 << curr_bit);
      writebuf[curr_byt] |= bit;
      ++bits_written;
    } else if (the_bitval == 0) {
      uint8_t writebyte = writebuf[curr_byt];
      uint8_t bit = writebyte & (00000001 << curr_bit);
      writebuf[curr_byt] |= bit;
      ++bits_written;
    }
  }
}

void flush_pairs(int outfile) {
  if (bits_written
      != offset * 8) { // if there are any pairs in buffer left, flush to buffer
    write_bytes(outfile, writebuf, bits_written);
  }
}

bool read_pair(int infile, uint16_t *code, uint8_t *sym, uint8_t bitlen) {

  bool moreread = 1;
  *code = 0;
  *sym = 0;
  // read in the pairs for decompression, going as same as buffer pairs, but access readbuf
  for (int i = 0; i < bitlen; i++) {
    if (bits_read == offset * 8) {
      read_bytes(infile, readbuf, sizeof(readbuf));
      bits_read = 0;
    }
    uint8_t curr_byt = readbuf[bits_read / 8];
    uint16_t curr_bit = bits_read % 8;
    uint16_t the_bitval = curr_byt & (00000001 << i);

    the_bitval = the_bitval >> i;
    if (the_bitval == 1) {
      uint16_t bit = *code | (00000001 << curr_bit);
      *code |= bit;
      ++bits_read;
    } else if (the_bitval == 0) {
      uint16_t bit = *code & (00000001 << curr_bit);
      *code |= bit;
      ++bits_read;
    }
  }

  if (*code == STOP_CODE) { // if the stopcode has been reached need to return
    moreread = 0;
    return moreread;
  }

  // perform same operations as above to read in the symbols this time
  for (int i = 0; i < 8; i++) {
    if (bits_read == offset * 8) {
      read_bytes(infile, readbuf, sizeof(readbuf));
      bits_read = 0;
    }

    uint8_t curr_byt = readbuf[bits_read / 8];
    uint8_t curr_bit = bits_read % 8;
    uint8_t the_bitval = curr_byt & (00000001 << i);
    the_bitval = the_bitval >> i;

    if (the_bitval == 1) {
      uint8_t bit = *sym | (00000001 << curr_bit);
      *sym |= bit;
      ++bits_read;
    } else if (the_bitval == 0) {
      uint8_t bit = *sym & (00000001 << curr_bit);
      *sym |= bit;
      ++bits_read;
    }
  }
  return moreread;
}

void buffer_word(
    int outfile, Word *w) { // output any words left in buffer to file

  if (w != NULL) {
    if (bits_read != offset * 8) {
      write_bytes(outfile, readbuf, offset);
    }
  }
}

void flush_words(int outfile) { // out put any symbols left in buffer to file
  if (bits_read != 4096) {
    write_bytes(outfile, readbuf, sizeof(readbuf));
  }
}
