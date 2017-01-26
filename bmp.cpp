//
// Author: Matthias Gude <abraxas@informatik.uni-freiburg.de>
//
// Modified by Volker Blanz, 25.4.2001
//

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include "LA.h"
#include "Namen.h"
#include "bmp.h"

// from ioutil:

WORDX readWord(FILE *f) {
  BYTEX buf[2];
  fread((void*)buf, 1, 2, f);
  return (((WORDX)buf[1])<<8) | buf[0];
}

DWORDX readDWord(FILE *f) {
  BYTEX buf[4];
  fread((void*)buf, 1, 4, f);
  return (((WORDX)buf[3])<<24) | 
        (((WORDX)buf[2])<<16) |
        (((WORDX)buf[1])<<8) |
        buf[0];
}

void writeWord(WORDX w, FILE *f) {
  BYTEX buf[2];
  buf[0]=(BYTEX)(w&0x00FF);
  buf[1]=(BYTEX)(w&0xFF00)>>8;
  fwrite(buf, 1, 2, f);
}

void writeDWord(DWORDX w, FILE *f) {
  BYTEX buf[4];
  buf[0]=(BYTEX)(w&0x000000FF);
  buf[1]=(BYTEX)((w&0x0000FF00)>>8);    
  buf[2]=(BYTEX)((w&0x00FF0000)>>16);
  buf[3]=(BYTEX)((w&0xFF000000)>>24);
fwrite(buf, 1, 4, f);
}

/**********************************************************************/


bool checkMagicKey(FILE *f) {
    char magic[2];
    fread(magic, 2, 1, f);
    return (strncmp(magic, MAGICKEY, 2)==0);
}

void readFileHeader(FILE *f, BITMAPFILEHEADERX *h) {
    h->bfSize=readDWord(f);
    h->bfReserved1=readWord(f);
    h->bfReserved2=readWord(f);
    h->bfOffBits=readDWord(f);
}

void readInfoHeader(FILE *f, BITMAPINFOHEADERX *h) {
    h->biSize=readDWord(f);
    h->biWidth=readDWord(f);
    h->biHeight=readDWord(f);
    h->biPlanes=readWord(f);
    h->biBitCount=readWord(f);
    h->biCompression=readDWord(f);
    h->biSizeImage=readDWord(f);
    h->biXPelsPerMeter=readDWord(f);
    h->biYPelsPerMeter=readDWord(f);
    h->biClrUsed=readDWord(f);
    h->biClrImportant=readDWord(f);
}

void readData(FMatrix &r, FMatrix &g, FMatrix &b, FILE *f, BITMAPINFOHEADERX bi) {
  int i, j;
  int rest;
  int w = bi.biWidth;	 
  int h = bi.biHeight;  
  int nbits = bi.biBitCount;
  int comp = bi.biCompression;
  int ncols = bi.biClrUsed;
  RGBQUADX *colormap;
  DWORDX *buffer;
  double factor = 1.0 / 255.0;

    if (!(nbits==1 || nbits==4 || nbits==8 || nbits==24) || bi.biPlanes!=1 || 
	comp>BI_RLE4 ) {
	return;					// weird BMP image
    }
	
    if (!(comp==BI_RGB || (nbits==4 && comp==BI_RLE4) || 
	  (nbits==8 && comp==BI_RLE8))) {
	return;				// weird compression type
    }
	
    /* read image data */
    buffer =  new DWORDX[w*h*3];
    switch(nbits) {
    case 1: {
      //std::cerr <<  "Sorry, 1 bit Images not supported yet!" << std::endl;
	return;
    }
    case 4: {
	BYTEX tmp;
	BYTEX idx[2];
	int k;
		
	if(comp==BI_RLE4) {
	  //std::cerr << "Sorry, compressed Images not supported yet!\n" << std::endl;
	    return;
	}
	/* read colormap */
	colormap = new RGBQUADX[ncols];
	fread(colormap, sizeof(RGBQUADX), ncols, f);	
	rest = ((int)(w/2.+0.5))%4;
	for(i=0; i<h; ++i) {
	    /* read scanline */
	    for(j=0; j<=w; j+=2) {
	      tmp = fgetc(f);
	      idx[0] = (tmp & 0xF0)>>4;
	      idx[1] = (tmp & 0x0F);
	      for(k=0; k<2 && j+k<w; ++k)
		buffer[i*w+j+k] = (((DWORDX)colormap[idx[k]].rgbRed)<<16) |
		  (((DWORDX)colormap[idx[k]].rgbGreen)<<8) | 
		  colormap[idx[k]].rgbBlue;	
	    }
	    /* throw fillbytes */
	    for(j=0; j<rest; ++j)
	      fgetc(f);
	}
	delete [] colormap;
	break;
    } /* case4 */
	
    case 8: {
	BYTEX idx;
	if(comp==BI_RLE8) {
	  //std::cerr << "Sorry, compressed Images not supported yet!\n" << std::endl;
	    return;
	}
	/* read colormap */
	colormap = new RGBQUADX[ncols];
	fread(colormap, sizeof(RGBQUADX), ncols, f);
		
	rest = (w*3)%4;
	for(i=0; i<h; ++i) {
	    /* read scanline */
	    for(j=0; j<w; ++j) {
		idx = fgetc(f);
		buffer[i*w+j] = (((DWORDX)colormap[idx].rgbRed)<<16) |
		    (((DWORDX)colormap[idx].rgbGreen)<<8) | 
		    colormap[idx].rgbBlue;
	    }
	    /* throw fillbytes */
	    for(j=0; j<rest; ++j)
		fgetc(f);
	}
	delete [] colormap;
	break;
    } /* case 8 */
	
    case 24: {
	rest = (w)%4;
	for(i=0; i<h; ++i) {
	    /* read scanline */
	    for(j=0; j<w; ++j) {
		buffer[i*w+j] = (BYTEX)fgetc(f) |
		    (((DWORDX)fgetc(f))<<8) | (((DWORDX)fgetc(f))<<16);
	    }
	    /* throw fillbytes */
	    for(j=0; j<rest; ++j)
		fgetc(f);
	}
	break;
    } /* case 24 */ 
			 
    default: {
      //std::cerr << "There occured an failure while reading the Imagedata" << std::endl;
    }
    } /* switch(nbits) */	 
			 
    for(int y=r.nrl; y<=r.nrh; ++y) {
      for(int x=r.ncl; x<=r.nch; ++x) {
#ifndef _WIN32
	r.m[y][x] = (float) factor * ((buffer[w*y+x] & 0x00FF0000)>>16);
	g.m[y][x] = (float) factor * ((buffer[w*y+x] & 0x0000FF00)>>8);	
	b.m[y][x] = (float) factor *  (buffer[w*y+x] & 0x000000FF);
#endif
#ifdef _WIN32
	b.m[y][x] = (float) factor * ((buffer[w*y+x] & 0x00FF0000)>>16);
	g.m[y][x] = (float) factor * ((buffer[w*y+x] & 0x0000FF00)>>8);	
	r.m[y][x] = (float) factor *  (buffer[w*y+x] & 0x000000FF);
#endif

      }
    }
    delete [] buffer;
}

void printFileHeader(BITMAPFILEHEADERX h) {
  h=h;
  /*
    cout << "BitmapFileHeader" << std::endl;
    cout << "\tSize.............." <<  h.bfSize << std::endl;
    cout << "\tReserved1........." << h.bfReserved1 << std::endl;
    cout << "\tReserved2........." << h.bfReserved2 << std::endl;
    cout << "\tOffsetBits........" << h.bfOffBits << std::endl;
  */
}

void printInfoHeader(BITMAPINFOHEADERX h) {
  h=h;
  /*
    cout << "BitmapInfoHeader\n";
    cout << "\tSize.............." << h.biSize << std::endl;
    cout << "\tWidth............." << h.biWidth << std::endl;
    cout << "\tHeight............" << h.biHeight << std::endl;
    cout << "\tPlanes............" << h.biPlanes << std::endl;
    cout << "\tBitCount.........." << h.biBitCount << std::endl;
    cout << "\tCompression......." << h.biCompression << std::endl;
    cout << "\tSizeImage........." << h.biSizeImage << std::endl;
    cout << "\tXPelsPerMeter....." << h.biXPelsPerMeter << std::endl;
    cout << "\tYPelsPerMeter....." << h.biYPelsPerMeter << std::endl;
    cout << "\tColorsUsed........" << h.biClrUsed << std::endl;
    cout << "\tColorsImportant..." << h.biClrImportant << std::endl;
  */
}


bool loadBMP(FMatrix& r, FMatrix& g, FMatrix& b, const char* fname) {
  FILE *f;
  BITMAPFILEHEADERX fheader;
  BITMAPINFOHEADERX iheader;

  char ffname[60];
  sprintf(ffname,"%s%s",PFAD,fname);
  //printf("%s%s\n",PFAD,fname);
  f = fopen(ffname, "rb");
  
  if(!f) {
    std::cerr << "unable to open " << ffname << "!" << std::endl;
    return false;
  }

   
  if(!checkMagicKey(f)) { 
    std::cerr << ffname << " is not a bitmap-file." << std::endl; 
    return false; 
  }   
  
  readFileHeader(f, &fheader);
  
  //printFileHeader(fheader);
  
  readInfoHeader(f, &iheader);
    
  /* 0 means all colors are used */
  if ( iheader.biClrUsed == 0 ) {
    iheader.biClrUsed = 1 << iheader.biBitCount;
  }
  if ( iheader.biClrImportant == 0 ) {
    iheader.biClrImportant = iheader.biClrUsed;
    }
  
  //printInfoHeader(iheader);

  /* ckeck and set size if necessary */
  if(r.width() != (int)iheader.biWidth || r.height() != (int)iheader.biHeight) {
    if (r.allocated())
      r.free_FMatrix();
    r.alloc_FMatrix(0,iheader.biHeight -1, 0,iheader.biWidth -1);
  }
  if(g.width() != (int)iheader.biWidth || g.height() != (int)iheader.biHeight) {
    if (g.allocated())
      g.free_FMatrix();
    g.alloc_FMatrix(0,iheader.biHeight -1, 0,iheader.biWidth -1);
  }
  if(b.width() != (int)iheader.biWidth || b.height() != (int)iheader.biHeight) {
    if (b.allocated())
      b.free_FMatrix();
    b.alloc_FMatrix(0,iheader.biHeight -1, 0,iheader.biWidth -1);  
  }

  readData(r, g, b, f, iheader);	
	
  fclose(f);

  return true;
}

bool saveBMP(FMatrix& r, FMatrix& g, FMatrix& b, const char* fname) {
  FILE *f = fopen(fname, "wb");
  BITMAPFILEHEADERX fheader;
  BITMAPINFOHEADERX iheader;
  int x, y;
  int w = r.width();
  int h = r.height();
  int rest = w%4;
  float factor = 255.0;

  if(w != g.width() || w != b.width() ||
     h != g.height() || h != b.height()) {
    //std::cerr << "Failure in saveBMP(): ";
    //std::cerr << "all three images must have the same size!" << std::endl;
  }
 

   /* fill Fileheader */
  fheader.bfSize = 2 + /* magickey */
    sizeof(BITMAPFILEHEADERX) +
    sizeof(BITMAPINFOHEADERX) + 
    h * (3*w + rest);
  fheader.bfReserved1 = fheader.bfReserved2 = 0;
  fheader.bfOffBits = 54;
	

  /* fill infoheader */
  iheader.biSize = 40;
  iheader.biWidth = w;
  iheader.biHeight = h;
  iheader.biPlanes = 1;
  iheader.biBitCount = 24;
  iheader.biCompression = BI_RGB;
  iheader.biSizeImage = (3*w+rest)*h;
  iheader.biXPelsPerMeter = 2952;
  iheader.biYPelsPerMeter = 2952;
  iheader.biClrUsed = 0;
  iheader.biClrImportant = 0;
	
  /* write magickey */
  fwrite((void*)MAGICKEY, 2, 1, f);
    
  /* write fileheader */
  writeDWord(fheader.bfSize, f);
  writeWord(fheader.bfReserved1, f);
  writeWord(fheader.bfReserved2, f);
  writeDWord(fheader.bfOffBits, f);
    
  /* write infoheader */
  writeDWord(iheader.biSize, f);
  writeDWord(iheader.biWidth, f);
  writeDWord(iheader.biHeight, f);
  writeWord(iheader.biPlanes, f);
  writeWord(iheader.biBitCount, f);
  writeDWord(iheader.biCompression, f);
  writeDWord(iheader.biSizeImage, f);
  writeDWord(iheader.biXPelsPerMeter, f);
  writeDWord(iheader.biYPelsPerMeter, f);
  writeDWord(iheader.biClrUsed, f);
  writeDWord(iheader.biClrImportant, f);

  /* write imagedata */
  for(y=r.nrl; y<=r.nrh; ++y) {
    for(x=r.ncl; x<=r.nch; ++x) {
      fputc((BYTEX)(factor * b.m[y][x]), f);
      fputc((BYTEX)(factor * g.m[y][x]), f);
      fputc((BYTEX)(factor * r.m[y][x]), f);
    }
    for(x=0; x<rest; ++x)
      fputc(0, f);
  }
  fclose(f);
  
  return true;
}
