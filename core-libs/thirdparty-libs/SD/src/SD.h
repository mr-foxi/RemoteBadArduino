/*

  SD - a slightly more friendly wrapper for sdfatlib

  This library aims to expose a subset of SD card functionality
  in the form of a higher level "wrapper" object.

  License: GNU General Public License V3
          (Because sdfatlib is licensed with this.)

  (C) Copyright 2010 SparkFun Electronics

*/
#ifdef USING_SD
#ifndef __SD_H__
#define __SD_H__

#include <Arduino.h>

#include "utility/SdFat.h"
#include "utility/SdFatUtil.h"

#define FILE_READ O_READ
#define FILE_WRITE (O_READ | O_WRITE | O_CREAT | O_APPEND)

namespace SDLib {

  class File : public Stream {
    private:
      char _name[13]; // our name
      SdFile *_file;  // underlying file pointer

    public:
      File(SdFile f, const char *name);     // wraps an underlying SdFile
      File(void);      // 'empty' constructor
      virtual size_t write(uint8_t);
      virtual size_t write(const uint8_t *buf, size_t size);
      virtual int availableForWrite();
      virtual int read();
      virtual int peek();
      virtual int available();
      virtual void flush();
      int read(void *buf, uint16_t nbyte);
      bool seek(uint32_t pos);
      uint32_t position();
      uint32_t size();
      void close();
      operator bool();
      char * name();

      bool isDirectory(void);
      File openNextFile(uint8_t mode = O_RDONLY);
      void rewindDirectory(void);

      using Print::write;
  };

  class SDClass {

    private:
      // These are required for initialisation and use of sdfatlib
      Sd2Card card;
      SdVolume volume;
      SdFile root;

      // my quick&dirty iterator, should be replaced
      SdFile getParentDir(const char *filepath, int *indx);
    public:
      // This needs to be called to set up the connection to the SD card
      // before other methods are used.
      bool begin(uint8_t csPin = SD_CHIP_SELECT_PIN);
      bool begin(uint32_t clock, uint8_t csPin);

      //call this when a card is removed. It will allow you to insert and initialise a new card.
      void end();

      // Open the specified file/directory with the supplied mode (e.g. read or
      // write, etc). Returns a File object for interacting with the file.
      // Note that currently only one file can be open at a time.
      File open(const char *filename, uint8_t mode = FILE_READ);
      File open(const String &filename, uint8_t mode = FILE_READ) {
        return open(filename.c_str(), mode);
      }

      // Methods to determine if the requested file path exists.
      bool exists(const char *filepath);
      bool exists(const String &filepath) {
        return exists(filepath.c_str());
      }

      // Create the requested directory heirarchy--if intermediate directories
      // do not exist they will be created.
      bool mkdir(const char *filepath);
      bool mkdir(const String &filepath) {
        return mkdir(filepath.c_str());
      }

      // Delete the file.
      bool remove(const char *filepath);
      bool remove(const String &filepath) {
        return remove(filepath.c_str());
      }

      bool rmdir(const char *filepath);
      bool rmdir(const String &filepath) {
        return rmdir(filepath.c_str());
      }

    private:

      // This is used to determine the mode used to open a file
      // it's here because it's the easiest place to pass the
      // information through the directory walking function. But
      // it's probably not the best place for it.
      // It shouldn't be set directly--it is set via the parameters to `open`.
      int fileOpenMode;

      friend class File;
      friend bool callback_openPath(SdFile&, const char *, bool, void *);
  };

  extern SDClass SD;

};

// We enclose File and SD classes in namespace SDLib to avoid conflicts
// with others legacy libraries that redefines File class.

// This ensure compatibility with sketches that uses only SD library
using namespace SDLib;

// This allows sketches to use SDLib::File with other libraries (in the
// sketch you must use SDFile instead of File to disambiguate)
typedef SDLib::File    SDFile;
typedef SDLib::SDClass SDFileSystemClass;
#define SDFileSystem   SDLib::SD

#endif
#endif
