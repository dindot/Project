#include "io.h"
#include "code.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>

static uint8_t readbuf[4096];
static uint8_t writebuf[4096];
static int bits_written = 0;

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
 // static int bits_written = 0;
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
uint8_t curr_byt = bits_written / 8;
uint8_t curr_bit = bits_written % bitlen;
uint8_t the_bitval = code & (00000001 << curr_bit);
the_bitval = the_bitval >> curr_bit;
if(the_bitval == 1)
{
uint8_t writebyte = writebuf[curr_byt];
uint8_t bit = writebyte | (00000001 << curr_bit);
printf("\n the supposed byte: %d", bit);
writebuf[curr_byt] = bit;
++bits_written;
}
else if(the_bitval == 0)
{
uint8_t writebyte = writebuf[curr_byt];
uint8_t bit = writebyte & (00000001 << curr_bit);
printf("\n the supposed byte: %d", bit);
writebuf[curr_byt] |= bit;
++bits_written;
}

//printf("\n at the bit: %d", curr_bit);

}
printf("\n the final byte: %d", writebuf[0]);
  


for(int i = 0; i < 8; i++)
{
if(bits_written == 4096 * 8)
{
write_bytes(outfile, writebuf, sizeof(writebuf));

}
printf("\n bits wrote: %d", bits_written);
uint8_t curr_byt = bits_written / 8;
uint8_t curr_bit = bits_written % 8;
uint8_t the_bitval = sym & (00000001 <<((curr_bit-curr_bit)+i ));
the_bitval = the_bitval >> ((curr_bit-curr_bit)+i);
if(the_bitval == 1)
{
uint8_t writebyte = writebuf[curr_byt];
uint8_t bit = writebyte | (00000001 << curr_bit);
printf("\n the supposed byte: %d", bit);
writebuf[curr_byt] = bit;
++bits_written;
}
else if(the_bitval == 0)
{
uint8_t writebyte = writebuf[curr_byt];
uint8_t bit = writebyte & (00000001 << curr_bit);
printf("\n the supposed byte: %d", bit);
writebuf[curr_byt] |= bit;
++bits_written;
}


printf("\n the final byte: %d", writebuf[1]);
}
}


void flush_pairs(int outfile) {
if(bits_written != 4096 * 8)
{
write_bytes(outfile, writebuf, bits_written);
}
}


bool read_pair(int infile, uint16_t *code, uint8_t *sym, uint8_t bitlen) {

bool moreread = 1;
*code = 0;
*sym = 0;

static int bits_read = 0;

for(int i = 0; i < bitlen; i++)
{
if(bits_read == 4096 * 8)
{
read_bytes(infile, readbuf, sizeof(readbuf));

}

uint8_t curr_byt = readbuf[bits_read/8];
uint16_t curr_bit = bits_read % bitlen;
uint16_t the_bitval = curr_byt & (00000001 << curr_bit);
the_bitval = the_bitval >> curr_bit;
if(the_bitval == 1)
{
uint16_t bit = *code | (00000001 << curr_bit);
*code = bit;
printf("\n *the supposed byte: %d", bit);
++bits_read;
}
else if(the_bitval == 0)
{
uint16_t bit = *code & (00000001 << curr_bit);
*code = bit;
printf("\n *the supposed byte: %d", bit);
++bits_read;
}

}

if(*code == STOP_CODE)
{
moreread = 0;
return moreread;
}
printf("\n read code: %d", *code);  




for(int i = 0; i < 8; i++)
{
if(bits_read == 4096 * 8)
{
read_bytes(infile, readbuf, sizeof(readbuf));

}

uint8_t curr_byt = readbuf[bits_read/8];
uint16_t curr_bit = bits_read % bitlen;
uint16_t the_bitval = curr_byt & (00000001 << curr_bit);
the_bitval = the_bitval >> curr_bit;
if(the_bitval == 1)
{
uint16_t bit = *sym | (00000001 << ((curr_bit-curr_bit)+i ));
*sym = bit;
printf("\n *the supposed byte: %d", bit);
++bits_read;
}
else if(the_bitval == 0)
{
uint16_t bit = *sym & (00000001 << ((curr_bit-curr_bit)+i ));
*sym = bit;
printf("\n *the supposed byte: %d", bit);
++bits_read;
}

}
return moreread;
}


void buffer_word(int outfile, Word *w)
{

for(uint32_t i = 0; i<w->len;i++)
{

writebuffer[x] = w->syms[i];
++x;

}

}


