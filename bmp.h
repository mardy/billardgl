/*
 * Author: Matthias Gude <abraxas@informatik.uni-freiburg.de>
 *
 * Modified by Volker Blanz, 25.4.2001
 */

#ifndef BMP_H
#define BMP_H

#include "LA.h"

#ifndef TYPEDEFS_H
#define TYPEDEFS_H

typedef unsigned char BYTEX;     /* must be 1 byte */
typedef unsigned short WORDX;    /* must be 2 byte */
typedef unsigned int DWORDX;     /* must be 4 byte */

typedef BYTEX Color;

#endif /* TYPEDEFS_H */



/* constants for the biCompression field */
#define BI_RGB        0L
#define BI_RLE8       1L
#define BI_RLE4       2L
#define BI_BITFIELDS  3L

const char MAGICKEY[2] = {'B', 'M'};

/*===========================================================================
 * RGBQUAD (3.0)
 * 
 * The RGBQUAD structure describes a color consisting of relative intensities 
 * of red, green, and blue. The bmiColors member of the BITMAPINFO structure
 * consists of an array of RGBQUAD structures.
 * 
 * Member          Description
 * 
 * rgbBlue         Specifies the intensity of blue in the color. 
 * rgbGreen        Specifies the intensity of green in the color. 
 * rgbRed          Specifies the intensity of red in the color. 
 * rgbReserved     Not used; must be set to zero. 
 * 
 *==========================================================================*/
typedef struct {
  BYTEX    rgbBlue;
  BYTEX    rgbGreen;
  BYTEX    rgbRed;
  BYTEX    rgbReserved;
} RGBQUADX;
/*===========================================================================
 * BITMAPFILEHEADER (3.0)
 * 
 * The BITMAPFILEHEADER structure contains information about the 
 * type, size, and layout of a device-independent bitmap (DIB) file.
 *
 * Member          Description
 *  
 * bfSize          Specifies the size of the file, in bytes. 
 * bfReserved1     Reserved; must be set to zero. 
 * bfReserved2     Reserved; must be set to zero. 
 * bfOffBits       Specifies the byte offset from the BITMAPFILEHEADER 
 *                 structure to the actual bitmap data in the file.
 *
 * Comments
 * A BITMAPINFO or BITMAPCOREINFO structure immediately follows the
 * BITMAPFILEHEADER structure in the DIB file.
 * 
 *==========================================================================*/
typedef struct {
  DWORDX   bfSize;
  WORDX    bfReserved1;
  WORDX    bfReserved2;
  DWORDX   bfOffBits;
} BITMAPFILEHEADERX;
/*===========================================================================
 * BITMAPINFOHEADER (3.0)
 *
 * The BITMAPINFOHEADER structure contains information about the dimensions and
 * color format of a Windows 3.0 or later device-independent bitmap (DIB).
 * 
 * Member          Description
 * 
 * biSize          Specifies the number of bytes required by the
 *                 BITMAPINFOHEADER structure.
 * 
 * biWidth         Specifies the width of the bitmap, in pixels. 
 * biHeight        Specifies the height of the bitmap, in pixels. 
 * 
 * biPlanes        Specifies the number of planes for the target device. This
 *                 member must be set to 1.
 * 
 * biBitCount      Specifies the number of bits per pixel. This value must be 
 *                 1, 4, 8, or 24.
 * 
 * biCompression   Specifies the type of compression for a compressed bitmap. 
 *                 It can be one of the following values:
 * 
 *   Value           Meaning
 * 
 *   BI_RGB          Specifies that the bitmap is not compressed. 
 * 
 *   BI_RLE8         Specifies a run-length encoded format for bitmaps with 
 *                   8 bits per pixel. The compression format is a 2-byte 
 *                   format consisting of a count byte followed by a byte 
 *                   containing a color index.  For more information, see the 
 *                   following Comments section.
 *
 *   BI_RLE4         Specifies a run-length encoded format for bitmaps with 
 *                   4 bits per pixel. The compression format is a 2-byte 
 *                   format consisting of a count byte followed by two 
 *                   word-length  color indexes.  For more information, see 
 *                   the following Comments section.
 * 
 * biSizeImage     Specifies the size, in bytes, of the image. It is valid to
 *                 set this member to zero if the bitmap is in the BI_RGB
 *                 format.
 * 
 * biXPelsPerMeter Specifies the horizontal resolution, in pixels per meter, of
 *                 the target device for the bitmap. An application can use 
 *                 this value to select a bitmap from a resource group that 
 *                 best matches the characteristics of the current device.
 * 
 * biYPelsPerMeter Specifies the vertical resolution, in pixels per meter, of
 *                 the target device for the bitmap.
 * 
 * biClrUsed       Specifies the number of color indexes in the color table
 *                 actually used by the bitmap. If this value is zero, the 
 *                 bitmap uses the maximum number of colors corresponding to 
 *                 the value of the biBitCount member. For more information on
 *                 the maximum sizes of the color table, see the description 
 *                 of the BITMAPINFO structure later in this topic.
 * 
 *                 If the biClrUsed member is nonzero, it specifies the actual 
 *                 number of colors that the graphics engine or device driver will 
 *                 access if the biBitCount member is less than 24. If biBitCount 
 *                 is set to 24, biClrUsed specifies the size of the reference color
 *                 table used to optimize performance of Windows color palettes.  
 *                 If the bitmap is a packed bitmap (that is, a bitmap in  which the
 *                 bitmap array immediately follows the BITMAPINFO header and which 
 *                 is referenced by a single pointer), the biClrUsed member must be
 *                 set to zero or to the actual size of the color table.
 * 
 * biClrImportant  Specifies the number of color indexes that are considered
 *                 important for displaying the bitmap. If this value is zero, 
 *                 all colors are important.
 * 
 * Comments
 * 
 * The BITMAPINFO structure combines the BITMAPINFOHEADER structure and a color
 * table to provide a complete definition of the dimensions and colors of a
 * Windows 3.0 or later DIB. For more information about specifying a Windows 
 * 3.0 DIB, see the description of the BITMAPINFO structure.
 * 
 * An application should use the information stored in the biSize member to
 * locate the color table in a BITMAPINFO structure as follows:
 * 
 * pColor = ((LPSTR) pBitmapInfo + (WORD) (pBitmapInfo->bmiHeader.biSize))
 * 
 * Windows supports formats for compressing bitmaps that define their colors
 * with 8 bits per pixel and with 4 bits per pixel. Compression reduces the 
 * disk and memory storage required for the bitmap. The following paragraphs 
 * describe these formats.
 * 
 * BI_RLE8
 * 
 * When the biCompression member is set to BI_RLE8, the bitmap is compressed
 * using a run-length encoding format for an 8-bit bitmap. This format may be
 * compressed in either of two modes: encoded and absolute. Both modes can 
 * occur anywhere throughout a single bitmap.
 * 
 * Encoded mode consists of two bytes: the first byte specifies the number of
 * consecutive pixels to be drawn using the color index contained in the second
 * byte. In addition, the first byte of the pair can be set to zero to indicate
 * an escape that denotes an end of line, end of bitmap, or a delta. The
 * interpretation of the escape depends on the value of the second byte of the
 * pair. The following list shows the meaning of the second byte:
 * 
 * Value   Meaning
 * 
 * 0       End of line. 
 * 1       End of bitmap. 
 * 2       Delta. The two bytes following the escape contain unsigned values
 * indicating the horizontal and vertical offset of the next pixel from the
 * current position.
 * 
 * Absolute mode is signaled by the first byte set to zero and the second byte
 * set to a value between 0x03 and 0xFF. In absolute mode, the second byte
 * represents the number of bytes that follow, each of which contains the color
 * index of a single pixel. When the second byte is set to 2 or less, the 
 * escape has the same meaning as in encoded mode. In absolute mode, each run 
 * must be aligned on a word boundary.  The following example shows the 
 * hexadecimal values of an 8-bit compressed bitmap:
 * 
 * 
 * 
 * 03 04 05 06 00 03 45 56 67 00 02 78 00 02 05 01
 * 02 78 00 00 09 1E 00 01
 * 
 * This bitmap would expand as follows (two-digit values represent a color 
 * index for a single pixel):
 * 
 * 04 04 04
 * 06 06 06 06 06
 * 45 56 67
 * 78 78
 * move current position 5 right and 1 down
 * 78 78
 * end of line
 * 1E 1E 1E 1E 1E 1E 1E 1E 1E
 * end of RLE bitmap
 * 
 * BI_RLE4
 * 
 * When the biCompression member is set to BI_RLE4, the bitmap is compressed
 * using a run-length encoding (RLE) format for a 4-bit bitmap, which also uses
 * encoded and absolute modes. In encoded mode, the first byte of the pair
 * contains the number of pixels to be drawn using the color indexes in the
 * second byte. The second byte contains two color indexes, one in its
 * high-order nibble (that is, its low-order four bits) and one in its 
 * low-order nibble. The first of the pixels is drawn using the color 
 * specified by the high-order nibble, the second is drawn using the color in 
 * the low-order nibble, the third is drawn with the color in the high-order 
 * nibble, and so on, until all the pixels specified by the first byte have 
 * been drawn.  In absolute mode, the first byte contains zero, the second 
 * byte contains the number of color indexes that follow, and subsequent bytes
 *  contain color indexes in their high- and low-order nibbles, one color 
 * index for each pixel. In absolute mode, each run must be aligned on a word 
 * boundary. The end-of-line, end-of-bitmap, and delta escapes also apply to 
 * BI_RLE4.
 * 
 * The following example shows the hexadecimal values of a 4-bit compressed
 * bitmap:
 * 
 * 03 04 05 06 00 06 45 56 67 00 04 78 00 02 05 01
 * 04 78 00 00 09 1E 00 01
 * 
 * This bitmap would expand as follows (single-digit values represent a color
 * index for a single pixel):
 * 
 * 
 * 
 * 0 4 0
 * 0 6 0 6 0
 * 4 5 5 6 6 7
 * 7 8 7 8
 * move current position 5 right and 1 down
 * 7 8 7 8
 * end of line
 * 1 E 1 E 1 E 1 E 1
 * end of RLE bitmap
 * 
 *==========================================================================*/
typedef struct {
  DWORDX   biSize;
  DWORDX   biWidth;
  DWORDX   biHeight;
  WORDX    biPlanes;
  WORDX    biBitCount;
  DWORDX   biCompression;
  DWORDX   biSizeImage;
  DWORDX   biXPelsPerMeter;
  DWORDX   biYPelsPerMeter;
  DWORDX   biClrUsed;
  DWORDX   biClrImportant;
} BITMAPINFOHEADERX;

/*===========================================================================
 * BITMAPINFO (3.0) 
 *
 * The BITMAPINFO structure fully defines the dimensions and color 
 * information for a Windows 3.0 or later device-independent bitmap 
 * (DIB).
 *
 * Member          Description
 * 
 * bmiHeader       Specifies a BITMAPINFOHEADER structure that contains
 * information about the dimensions and color format of a DIB.
 * 
 * bmiColors       Specifies an array of RGBQUAD structures that define the
 *                 colors in the bitmap.
 * 
 * Comments
 * 
 * A Windows 3.0 or later DIB consists of two distinct parts: a BITMAPINFO
 * structure, which describes the dimensions and colors of the bitmap, and an
 * array of bytes defining the pixels of the bitmap. The bits in the array are
 * packed together, but each scan line must be zero-padded to end on a LONG
 * boundary. Segment boundaries, however, can appear anywhere in the bitmap. 
 * The origin of the bitmap is the lower-left corner.
 * 
 * The biBitCount member of the BITMAPINFOHEADER structure determines the 
 * number of bits which define each pixel and the maximum number of colors in 
 * the bitmap. This member may be set to any of the following values:
 *  
 * Value   Meaning
 * 
 * 1       The bitmap is monochrome, and the bmciColors member must contain two
 * entries. Each bit in the bitmap array represents a pixel. If the bit is
 * clear, the pixel is displayed with the color of the first entry in the
 * bmciColors table. If the bit is set, the pixel has the color of the second
 * entry in the table.
 * 
 * 4       The bitmap has a maximum of 16 colors, and the bmciColors member
 * contains 16 entries. Each pixel in the bitmap is represented by a four-bit
 * index into the color table.
 * 
 * For example, if the first byte in the bitmap is 0x1F, the byte represents 
 * two pixels. The first pixel contains the color in the second table entry, 
 * and the second pixel contains the color in the sixteenth table entry.
 * 
 * 8       The bitmap has a maximum of 256 colors, and the bmciColors member
 * contains 256 entries. In this case, each byte in the array represents a
 * single pixel.
 * 
 * 24      The bitmap has a maximum of 2^24 colors. The bmciColors member is
 * NULL, and each 3-byte sequence in the bitmap array represents the relative
 * intensities of red, green, and blue, respectively, of a pixel.
 * 
 * The biClrUsed member of the BITMAPINFOHEADER structure specifies the number
 * of color indexes in the color table actually used by the bitmap. If the
 * biClrUsed member is set to zero, the bitmap uses the maximum number of 
 * colors corresponding to the value of the biBitCount member.
 * 
 * The colors in the bmiColors table should appear in order of importance.
 * Alternatively, for functions that use DIBs, the bmiColors member can be an
 * array of 16-bit unsigned integers that specify an index into the currently
 * realized logical palette instead of explicit RGB values. In this case, an
 * application using the bitmap must call DIB functions with the wUsage
 * parameter set to DIB_PAL_COLORS.
 * 
 * Note:   The bmiColors member should not contain palette indexes if the 
 * bitmap is to be stored in a file or transferred to another application. 
 * Unless the application uses the bitmap exclusively and under its complete 
 * control, the bitmap color table should contain explicit RGB values.
 *  
 *==========================================================================*/
typedef struct tagBITMAPINFOX {  /* bmi */
    BITMAPINFOHEADERX    bmiHeader;
    RGBQUADX             bmiColors[1];
} BITMAPINFOX;


// NOTE: Origin m[0][0] is in lower left corner.
//       Float values of red, green, and blue component 
//       are in [0,1].
bool loadBMP(FMatrix& r, FMatrix& g, FMatrix& b, const char* fname);
bool saveBMP(FMatrix& r, FMatrix& g, FMatrix& b, const char* fname);


#endif /* BMP_H */
