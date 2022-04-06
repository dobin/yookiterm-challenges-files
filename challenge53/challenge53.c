#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

struct _FileHeader {
    char header[4];
    int16_t size;
    int16_t imageCount;
};
typedef struct _FileHeader FileHeader;

struct _FileImage {
    int width;
    int height;
    int size;
};
typedef struct _FileImage FileImage;

struct _ImageEntry {
    int idx;
    int size;
    char *data;
};
typedef struct _ImageEntry ImageEntry;

ImageEntry** parseFileHeader(FileHeader *fileHeader, char *buf);
ImageEntry** readFile(char *filename);

ImageEntry** readFile(char *filename) {
    char buf[128];
    FILE *f;
    FileHeader fileHeader;
    size_t ret;

    f = fopen(filename, "r");
    if (f == NULL) {
		printf("Can't open file or file doesn't exist: %s\n", filename);
		exit(0);
    }

    // Read: FileHeader Header
    ret = fread(&fileHeader, sizeof(fileHeader), 1, f);
    if (ret <= 0) {
        printf("Read error in fileHeaderlen: %zu\n", ret);
		exit(0);
    }

    // Read: Rest of FileHeader
    ret = fread(&buf, fileHeader.size, 1, f); // Buffer Overflow here (when fileHeader.size > 128)
    if (ret <= 0) {
        printf("Read error in copy fileHeader: %zu\n", ret);
		exit(0);
    }

    // Parse: FileHeader
    return parseFileHeader(&fileHeader, buf);
}
 
ImageEntry** parseFileHeader(FileHeader *fileHeader, char *buf) {
    ImageEntry **entries;
    FileImage *img;
    char *ptr = buf;
    int imageCnt = fileHeader->imageCount;

    entries = malloc(sizeof(ImageEntry) * 8);

    for(int n=0; n<imageCnt; n++) {
        img = (FileImage *) ptr;
        //printf("FileImage: %i/%i %i\n", img->height, img->width, img->size);
        int dataSize = img->height * img->width;

        ImageEntry *entry = malloc(sizeof(ImageEntry));
        entry->idx = n;
        entry->size = dataSize;
        entry->data = malloc(dataSize);
        memcpy(entry->data, ptr+sizeof(FileImage), img->size);
        entry->data[img->size-1] = 0;
        entries[n] = entry;

        ptr += dataSize + sizeof(FileImage);
    }

    entries[imageCnt] = NULL;

    return entries;
}


int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: %s <file>\n", argv[0]);
        exit(1);
    }

    // Get all from file
    ImageEntry **entries = readFile(argv[1]);
    
    // Show
    for (int n=0; entries[n] != NULL; n++) {
        printf("FileImage: %i\n", n);
        printf("  idx : %i\n", entries[n]->idx);
        printf("  size: %i\n", entries[n]->size);
        printf("  data: %s\n", entries[n]->data);
    }

    // Free everything again
    for (int n=0; entries[n] != NULL; n++) {
        free(entries[n]->data);
        free(entries[n]);
    }

    return 0;
}