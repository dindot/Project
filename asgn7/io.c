#include "io.h"
#include <stdio.h>
#include <unistd.h>

//static int var = 4096;
static uint8_t readbuf[4096];
//static uint8_t writebuf[4096];

void read_header(int infile, FileHeader *header)
{



int bytes = 0;
int counter = 0;
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

int bytes = 0;
bool toread = 0;
int i =0;

bytes = read(infile, readbuf, sizeof(readbuf));

sym=readbuf[i];
 printf("sym is %d", *sym);
  toread = 1;
++i;

if(i == bytes+1)
return false;


if(bytes == 4096)
{
while(bytes != 0){
for(int i = 0; i<bytes-1;i++)
{
*sym=readbuf[i];
 printf("sym is %d", *sym);

}

bytes = read(infile, readbuf, sizeof(readbuf));

}}

return toread;
}
