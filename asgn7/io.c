#include "io.h"
#include <stdio.h>
#include <unistd.h>
#include "code.h"

static uint8_t readbuf[4096];
static uint8_t writebuf[4096];

void read_header(int infile, FileHeader *header)
{
int bytes = 0;
int counter = 0;
//printf("magic man %d",header->magic);
if(header->magic == MAGIC){
bytes = read(infile, (uint8_t*)header, sizeof(FileHeader));
counter +=bytes;
if(sizeof(FileHeader) != counter){
while(bytes != 0)
{
bytes = read(infile, (uint8_t*)header,sizeof(FileHeader));
counter+=bytes;

}}
}
}

void write_header(int outfile, FileHeader *header)
{

int bytes = 0;
int counter = 0;

bytes = write(outfile, (uint8_t*)header, sizeof(FileHeader));
counter +=bytes;
if(sizeof(FileHeader) != counter){
while(bytes != 0)
{
bytes = write(outfile, (uint8_t*)header,sizeof(FileHeader));
counter+=bytes;

}}
}

bool read_sym(int infile, uint8_t *sym)
{
static bool notblock = 0;
static bool block = 0;
static int i = 0;
static int x = 0;
int bytes = 0;
bool toread = 0;
static int endbuf = 4096;

bytes = read(infile, readbuf, sizeof(readbuf));

if(bytes == 4096 || block == 1)
{
block = 1;
if(i < bytes){
  toread = 1;
  *sym = readbuf[i];
   i++;
  if(readbuf[i] == (uint8_t)NULL)
  toread= false;
}
//if(i==bytes)  // check to realloc for when i reaches max buffer if theres more
//{

//}
}

if(bytes < 4096 && bytes !=0)
{
endbuf = bytes;
}

if(bytes < 4096 || notblock ==1)
{
notblock = 1;
if(x < endbuf){
  toread = 1;
  *sym = readbuf[x];
  x++;
  if(readbuf[x] == (uint8_t)NULL)
  toread= false;
}
}

return toread;
}

void buffer_pair(int outfile, uint16_t code, uint8_t sym, uint8_t bitlen)
{
writebuf[2] =3;
char bits[16];
int counter = 0;
 while (code > 0) {
    int x = code; // temp storing num
    code = (code / 2); // find the quotient of num and keep going until its 0
    int remainder = x % 2;
    bits[counter] = remainder;
    counter++;
  }




}




