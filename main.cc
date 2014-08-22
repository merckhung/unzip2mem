#include <iostream>
#include "UniquePtr.h"
#include "zip_archive.h"

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

  std::cout << "Success\n";
  return 0;
}
