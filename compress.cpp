#include "compress.hpp"
#include <vector>

binary_data compress(binary_data buffer, int width, int height, TJPF pixelFormat) {
    const int JPEG_QUALITY = 85;
    const int COLOR_COMPONENTS = 3;
    long unsigned int jpegSize = 0;
    unsigned char* compressedImage = 0;

    tjhandle _jpegCompressor = tjInitCompress();
    tjCompress2(
        _jpegCompressor, 
        buffer.data(), 
        width, 0, height, pixelFormat,
        &compressedImage, &jpegSize, 
        TJSAMP_444, JPEG_QUALITY, TJFLAG_FASTDCT
    );
    tjDestroy(_jpegCompressor);
    binary_data image_compressed(compressedImage,compressedImage+jpegSize);
    tjFree(compressedImage);
    return image_compressed;
}
