#include <stdio.h>
#include <iostream>
#include "UniquePtr.h"
#include "zip_archive.h"

int8_t ConvertDWordToByte( uint32_t *Data, uint32_t Offset ) {

    uint32_t tmp, off, bs;

    off = Offset / 4;
    bs = Offset % 4;
    if( bs ) {

        tmp = *(Data + off);
        tmp = ((tmp >> (bs * 8)) & 0xFF);
        return tmp;
    }

    tmp = ((*(Data + off)) & 0xFF);
    return tmp;
}

void DumpData( uint32_t *Data, uint32_t Length, uint32_t BaseAddr ) {

    uint32_t i, j;
    uint32_t c;

    printf( "\n\n== Dump Start ==\n\n" );
    printf( " Address | 00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F|   ASCII DATA   \n" );
    printf( "---------------------------------------------------------------------------\n" );

    for( i = 0 ; i <= Length ; i++ ) {

        if( !(i % 16) ) {

            if( (i > 15) ) {

                for( j = i - 16 ; j < i ; j++ ) {

                    c = ConvertDWordToByte( Data, j );
                    if( ((c >= '!') && (c <= '~')) ) {

                        printf( "%c", c );
                    }
                    else {

                        printf( "." );
                    }
                }
            }

            if( i )
                printf( "\n" );

            if( i == Length )
                break;

            printf( "%8.8X : ", i + BaseAddr );
        }

        printf( "%2.2X ", ConvertDWordToByte( Data, i ) & 0xFF );
    }

    printf( "---------------------------------------------------------------------------\n" );
    printf( "\n== Dump End ==\n\n" );
}

int main(int argc, char** argv) {

#ifdef __APPLE__
  std::string zip_filename("/Users/merck/Projects/unzip2mem/files/Loop.jar");
#else
	std::string zip_filename("files/Loop.jar");
#endif
  char image_classes_filename[] = "classes.dex";
  char buf[ 1024 ];

  // Open a zip file
  UniquePtr<art::ZipArchive> zip_archive(art::ZipArchive::Open(zip_filename));
  if (zip_archive.get() == NULL) {
    std::cout << "Failed to open zip file " << zip_filename << "\n";
    return -1;
  }

  // Find the specified entry
  UniquePtr<art::ZipEntry> zip_entry(zip_archive->Find(image_classes_filename));
  if (zip_entry.get() == NULL) {
    std::cout << "Failed to find " << image_classes_filename << " within " <<zip_filename << "\n";
    return -1;
  }

  // Extract to the buffer
  if (zip_entry->ExtractToMemory((uint8_t *)buf, sizeof(buf)) == false) {
    std::cout << "Failed to extract file " << image_classes_filename << " within " << zip_filename << "\n";
    return -1;
  }

  // Dump data
  DumpData(reinterpret_cast<uint32_t *>(buf), sizeof(buf), 0);
  std::cout << "Success\n";
  return 0;
}
