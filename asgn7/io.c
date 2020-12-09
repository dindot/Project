#include "io.h"
#include <stdio.h>
#include <unistd.h>
#include "code.h"
//#include "bv.h"
#include <math.h>

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

int minbitscurrcode = (log2(code))+1;
int pad = bitlen - minbitscurrcode;
static int i = 0;

int index = 0;
int symcodeindex = 0;
uint8_t storecode = 00000000;
uint8_t storelen = minbitscurrcode;

uint8_t thebyte = code;

while(symcodeindex != minbitscurrcode){
  uint8_t shiftbyte = (00000001 << symcodeindex);
  uint8_t newresult = thebyte & shiftbyte;
  uint8_t valueinbit = newresult >> symcodeindex;
  uint8_t temp = valueinbit << (--storelen);
  printf("\nthe temp %d" ,temp);
  storecode |= temp;
  ++index;
  ++symcodeindex;
}

// check this ones fix later to make it loop at fill up entire byte based on index
// until index is 7 and then use the syms to fill up accordingly.
storecode = storecode << (pad+1);
index+=pad;
printf("\n stored code: %d   %d", storecode,index);


uint8_t symbyte = sym;


printf("\n th555sym %d    %d", symbyte, 0x0001);
symcodeindex = 0;
int lentrack = index;
uint8_t thebit = 0;
//int lentrack = 0;
//int storedlen = bitlen;
while(index != 8)
{
// now track it with the symcodeindex, must be 8 to fill sym
 
  uint8_t shiftbyte = (00000001 << (symcodeindex));

  uint8_t newresult = symbyte & shiftbyte;
  uint8_t valueinbit = newresult >> (symcodeindex);
  if(index == 7){
  thebit =  newresult;
  //--lentrack;  
}
else if(index !=7){
   thebit =  valueinbit << (lentrack);
}  --lentrack;

  //thebit = thebit | 0x1;
  storecode |= thebit;
printf("\ntheasdfasdfasd code inside%d\n", storecode);
  ++index;
  ++symcodeindex;

if(index == 8 || symcodeindex == 8)
{
if(index == 8){
writebuf[i] = storecode;
storecode = 00000000;
++i;
index = 0;
printf("the sym%d", symcodeindex);
}
else if(symcodeindex == 8){
storecode |= 00000000;
writebuf[i] = storecode;
storecode = 00000000;
++i;
index = 0;
break;
}


}


}

printf("\n code in the back: %d, %d", writebuf[1], symcodeindex);



if(i != 4096)
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

bool read_pair(int infile, uint16_t *code, uint8_t *sym, uint8_t bitlen)
{

int minbitscurrcode = (log2(*code))+1;

printf("\n%d   %d    %d    %d", minbitscurrcode, *code, *sym, bitlen);

static uint8_t readbuffer[4096];
int static i = 0;
uint8_t finalcode = 0;
int index = 0;

uint8_t symcodeindex =bitlen;

read(infile, &(readbuffer[i]), sizeof(readbuffer));
uint8_t storecode = readbuffer[i];

while(index != bitlen){
  uint8_t shiftbyte = (00000001 << symcodeindex);
  uint8_t newresult = storecode & shiftbyte;
  uint8_t valueinbit = newresult >> (symcodeindex);

  finalcode += valueinbit*pow(2,index);
  ++index;
  --symcodeindex;
if(index == 8)
{
printf("\n thebit %d   %d",finalcode,index);
// need it later     *code = finalcode;

++i;
read(infile, &(readbuffer[i]), sizeof(readbuffer));
storecode = readbuffer[i];
printf("\n thebit %d   %d",finalcode,index);
// need it later     *sym = finalcode;
}
}


symcodeindex = 0;
int finalsym = 0;
printf("\n thebit %d   %d",finalcode,index);
int tracker = 0;

if(index != 8)
{
while(index != 8){

  uint8_t shiftbyte = (00000001 << symcodeindex);
  uint8_t newresult = storecode & shiftbyte;
  uint8_t valueinbit = newresult >> (symcodeindex);
 //int power = 8-index;
 
  finalsym += valueinbit*pow(2,index);
  printf("first once 2^7 %d", finalsym);
   ++index;
    ++symcodeindex;
   ++tracker;


if(index ==8)
{
++i;
read(infile, &(readbuffer[i]), sizeof(readbuffer));
storecode = readbuffer[i];
index = 0;
symcodeindex=0;
}
else if(tracker == 8)
{


++i;
break;
}
}
printf("\n final sym %d",finalsym);

}
return true;

}






