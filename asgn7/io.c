#include "io.h"
#include <stdio.h>
#include <unistd.h>



int read_bytes(int infile, uint8_t *buf, int to_read)
{
int bytes = 0;
int counter = 0;

bytes = read(infile, buf, to_read);
counter +=bytes;
if(to_read != counter){
while(bytes != 0)
{
bytes = read(infile,buf,to_read);
counter+=bytes;

}}
return counter;

}

int write_bytes(int outfile, uint8_t *buf, int to_write)
{

int bytes = 0;
int counter = 0;

bytes = write(outfile, buf, to_write);
counter +=bytes;
if(to_write != counter){
while(bytes != 0)
{
bytes = write(outfile,buf,to_write);
counter+=bytes;

}}
return counter;



}


void read_header(int infile, FileHeader *header)
{

read_bytes(infile, (uint8_t*)header, sizeof(FileHeader));
}

void write_header(int outfile, FileHeader *header)
{

write_bytes(outfile, (uint8_t*)header, sizeof(FileHeader));
}

bool read_sym(int infile, uint8_t *byte)
{

int bytes = 0;

uint8_t buf[4096];

bytes = read_bytes(infile, buf, sizeof(buf));

printf("bytessssss %d, %s", bytes, byte);

printf("\n check buf: %hhu", buf[4]);
/*while(bytes!=0){
for(uint8_t i = 0; i<bytes; i++)
{
*byte = buf[i];
printf("\n check bytes: %s", byte);
}
}*/

/*if(bytes == 4095)
{
bytes = read_bytes(infile, buf, sizeof(buf));

}

}

if(buf[bytes+1] == (uint8_t)NULL)
{
return true;

}
else
return false;*/
return true;
}



