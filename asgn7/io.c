#include "io.h"
#include "code.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>

static uint8_t readbuf[4096];
static uint8_t writebuf[4096];

int read_bytes(int infile, uint8_t *buf, int to_read)
{
int bytes = read(infile, buf, to_read);
int counter = 0;

if(bytes == 0)
{
return to_read;
}

counter += bytes;

int offset = to_read - bytes;
while(bytes != 0)
{
bytes = read(infile, buf+offset, offset);
counter+= bytes;
}

return counter;
}

int write_bytes(int outfile, uint8_t *buf, int to_write)
{

int bytes = write(outfile, buf, to_write);
int counter = 0;

if(bytes == 0)
{
return to_write;
}

counter += bytes;

int offset = to_write - bytes;
while(bytes != 0)
{
bytes = write(outfile, buf+offset, offset);
counter+= bytes;
}

return counter;


}


void read_header(int infile, FileHeader *header) { 

if (header->magic == MAGIC) {
   read_bytes(infile, (uint8_t*)header, sizeof(FileHeader));
 }


// then use fchmod here to match permisisons and set back to original

}

void write_header(int outfile, FileHeader *header) {

 struct stat srcstats;
 fstat(outfile, &srcstats);

header->magic = MAGIC;
header->protection = srcstats.st_mode;
write_bytes(outfile, (uint8_t*)header, sizeof(FileHeader));
}


//write is compression  (encode)
// read is decompress  (decode)

bool read_sym(int infile, uint8_t *sym) {

bool toread = 1;
static int i = 0;

// change this i here later maybe
int bytes = read_bytes(infile, readbuf+i, sizeof(readbuf));

if(bytes == 0)
{
toread = 0;
}
//printf("\n bytes are %d", bytes);


if(bytes == 4096)
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

bytes = read_bytes(infile, readbuf+i, sizeof(readbuf));

if(bytes==0){
   toread = 0;
}
}

}
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
}




/*  static bool notblock = 0;
  static bool block = 0;
  static int i = 0;
  static int x = 0;
  int bytes = 0;
  bool toread = 0;
  static int endbuf = 4096;

  bytes = read(infile, readbuf + i, sizeof(readbuf));

  if (bytes == 4096 || block == 1) {
    block = 1;
    if (i < bytes) {
      toread = 1;
      *sym = readbuf[i];
      i++;
      if (readbuf[i] == (uint8_t)NULL)
        toread = false;
    }
  }

  if (bytes < 4096 && bytes != 0) {
    endbuf = bytes;
  }

  if (bytes < 4096 || notblock == 1) {
    notblock = 1;
    if (x < endbuf) {
      toread = 1;
      *sym = readbuf[x];
      x++;
      if (readbuf[x] == (uint8_t)NULL)
        toread = false;
    }
  }
*/
//  return toread;
//}



// making the compressed versiob, putting into outfile, use write buffer, track w bits write
void buffer_pair(int outfile, uint16_t code, uint8_t sym, uint8_t bitlen) {
  static int bits_written = 0;
  int minbitscurrcode = (log2(code)) + 1;
  int pad = bitlen - minbitscurrcode;
  printf("\n the pad is : %d", pad);
  printf("\n the sym: %d", sym);
 
  
 for(int i = 0; i < bitlen; i++)
{
if(bits_written == 4096 * 8)
{
write_bytes(outfile, writebuf, sizeof(writebuf));

}
uint8_t curr_byt = bits_written / 4096;
uint8_t curr_bit = bits_written % bitlen;
uint8_t the_bitval = code & (00000001 << curr_bit);
the_bitval = the_bitval >> curr_bit;
if(the_bitval == 1)
{
uint8_t writebyte = writebuf[curr_byt];
uint8_t bit = writebyte | (00000001 << curr_bit);
printf("\n the supposed byte: %d", bit);
writebuf[curr_byt] = bit;
}
else if(the_bitval == 0)
{
uint8_t writebyte = writebuf[curr_byt];
uint8_t bit = writebyte & (00000001 << curr_bit);
printf("\n the supposed byte: %d", bit);
writebuf[curr_byt] |= bit;
}

//printf("\n at the bit: %d", curr_bit);
++bits_written;

}
printf("\n the final byte: %d", writebuf[0]);
  











  /*static int i = 0;

  int index = 0;
  int symcodeindex = 0;
  uint8_t storecode = 00000000;
  uint8_t storelen = minbitscurrcode;

  uint8_t thebyte = code;

  while (symcodeindex != minbitscurrcode) {
    uint8_t shiftbyte = (00000001 << symcodeindex);
    uint8_t newresult = thebyte & shiftbyte;
    uint8_t valueinbit = newresult >> symcodeindex;
    uint8_t temp = valueinbit << (--storelen);
    storecode |= temp;
    ++index;
    ++symcodeindex;
  }

  // check this ones fix later to make it loop at fill up entire byte based on index
  // until index is 7 and then use the syms to fill up accordingly.
  storecode = storecode << (pad + 1);
  index += pad;

  uint8_t symbyte = sym;
  symcodeindex = 0;
  int lentrack = index;
  uint8_t thebit = 0;

  while (index != 8) {
    // now track it with the symcodeindex, must be 8 to fill sym
    uint8_t shiftbyte = (00000001 << (symcodeindex));
    uint8_t newresult = symbyte & shiftbyte;
    uint8_t valueinbit = newresult >> (symcodeindex);
    if (index == 7) {
      thebit = newresult;
    } else if (index != 7) {
      thebit = valueinbit << (lentrack);
    }
    --lentrack;

    storecode |= thebit;
    ++index;
    ++symcodeindex;

    if (index == 8 || symcodeindex == 8) {
      if (index == 8) {
        writebuf[i] = storecode;
        storecode = 00000000;
        ++i;
        index = 0;
        printf("the symbol %d", symcodeindex);
      } else if (symcodeindex == 8) {
        storecode |= 00000000;
        writebuf[i] = storecode;
        storecode = 00000000;
        ++i;
        index = 0;
        break;
      }
    }
  }
  //printf("the symbol %d", storecode);
  if (i != 4096) {

    write(outfile, writebuf, sizeof(writebuf));
  }
}

void flush_pairs(int outfile) {
  int bytes = 0;
  int counter = 0;

  bytes = write(outfile, writebuf, sizeof(writebuf));
  counter += bytes;
  if (sizeof(writebuf) != counter) {
    while (bytes != 0) {
      bytes = write(outfile, writebuf, sizeof(writebuf));
      counter += bytes;
    }
  }*/
}

bool read_pair(int infile, uint16_t *code, uint8_t *sym, uint8_t bitlen) {

  // int minbitscurrcode = (log2(*code)) + 1;

  static uint8_t readbuffer[4096];
  int static i = 0;
  uint8_t finalcode = 0;
  static int index = 0;

  uint8_t symcodeindex = bitlen;

  read(infile, &(readbuffer[i]), sizeof(readbuffer));
  uint8_t storecode = readbuffer[i];
  //printf("the symbol %d", storecode);
  while (index != bitlen) {
    uint8_t shiftbyte = (00000001 << symcodeindex);
    uint8_t newresult = storecode & shiftbyte;
    uint8_t valueinbit = newresult >> (symcodeindex);

    finalcode += valueinbit * pow(2, index);
    ++index;
    --symcodeindex;
    if (index == 8) {

      *code = finalcode;
      ++i;
      read(infile, &(readbuffer[i]), sizeof(readbuffer));
      storecode = readbuffer[i];
      printf("\n thebit %d   %d", finalcode, index);
      *sym = storecode;
    }
  }
  printf("\n thebit %d   %d", finalcode, index);
  bool moretoread = 1;
  symcodeindex = 0;
  int finalsym = 0;

  if (finalcode == STOP_CODE)
    moretoread = 0;
  *code = finalcode;
  int tracker = 0;

  if (index != 8) {
    while (index != 8) {

      uint8_t shiftbyte = (00000001 << symcodeindex);
      uint8_t newresult = storecode & shiftbyte;
      uint8_t valueinbit = newresult >> (symcodeindex);
      int power = 8 - (index + 1);

      finalsym += valueinbit * pow(2, power);

      ++index;
      ++symcodeindex;
      ++tracker;

      if (index == 8) {
        ++i;
        read(infile, &(readbuffer[i]), sizeof(readbuffer));
        storecode = readbuffer[i];
        index = 0;
        symcodeindex = 0;
      } else if (symcodeindex == 7) {
        *sym = finalsym;
        ++i;
        break;
      }
    }
    printf("\n final sym %d", finalsym);
  }
  return true;
}

void buffer_word(int outfile, Word *w)
{

static uint8_t writebuffer[4096];
static int x = 0;

for(uint32_t i = 0; i<w->len;i++)
{

writebuffer[x] = w->syms[i];
++x;

}

if(x == 4096)
{
write(outfile, writebuffer, sizeof(writebuffer));

}

}
