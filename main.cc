#include <iostream>
#include "UniquePtr.h"
#include "zip_archive.h"

int main(int argc, char** argv) {

  std::string zip_filename("/Users/merck/Projects/unzip2mem/files/Loop.jar");
  char image_classes_filename[] = "classes.dex";

  UniquePtr<art::ZipArchive> zip_archive(art::ZipArchive::Open(zip_filename));
  if (zip_archive.get() == NULL) {
    std::cout << "Failed to open zip file " << zip_filename << "\n";
    return -1;
  }

  UniquePtr<art::ZipEntry> zip_entry(zip_archive->Find(image_classes_filename));
  if (zip_entry.get() == NULL) {
    std::cout << "Failed to find " << image_classes_filename << " within " <<zip_filename << "\n";
    return -1;
  }

  std::cout << "Success\n";
  return 0;
}

