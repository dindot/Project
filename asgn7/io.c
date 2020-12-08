#include "io.h"
#include <stdio.h>
#include <unistd.h>
#include "code.h"
#include "bv.h"

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

bytes = read(infile, readbuf+i, sizeof(readbuf));

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
static int i = 0;
int index = 0;
  int thebit = 0;
 uint8_t codebit = 0;
int len = bitlen;

 while(index != bitlen){
  uint8_t thebyte = code;

  uint8_t shiftbyte = (00000001 << thebit);
  uint8_t newresult = thebyte & shiftbyte;
   //newresult = newresult << thebit;
 uint8_t val = newresult >> thebit; 
//printf("code bit: %d", val);
uint8_t ia = 0000;
uint8_t thep = val << (--len);
uint8_t cea = ia | thep;
printf("code bit: %d", cea);
  codebit|=cea;
  ++index;
  ++thebit;
}

printf("\ncode bit: %d", codebit);
int symbit = 0;
codebit = codebit << index;
while(index !=8 ){
  uint8_t thebyte = sym;

  uint8_t shiftbyte = (00000001 << sym);
  uint8_t newresult = thebyte & shiftbyte;
printf("\n%d", newresult);

 codebit|=newresult;
//printf("\n%d", codebit);
  ++index;
   ++symbit;
}

printf("\n%d", codebit);

if(i == 4096)
{

write(outfile, writebuf, sizeof(writebuf));

}
}


void flush_pairs(int outfile)
{
int bytes = 0;
int counter = 0;

bytes = write(outfile, writebuf, sizeof(writebuf));
counter +=bytes;
if(sizeof(writebuf) != counter){
while(bytes != 0)
{
bytes = write(outfile, writebuf, sizeof(writebuf));
counter+=bytes;
}}
}

/*bool read_pair(int infile, uint16_t *code, uint8_t *sym, uint8_t bitlen)
{

int counter = 0;
static uint8_t readbuffer[4096];
int index = counter % 8;

int bytes = read(infile, readbuffer, sizeof(readbuffer));
if(bytes == 4096)
{

uint8_t thebyte = readbuffer[i];



}







}*/
