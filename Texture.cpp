// Texture.cpp: implementation of the Texture class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Texture.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Texture::Texture()
{


}

Texture::~Texture()
{

}

/* glmReadPPM: read a PPM raw (type P6) file.  The PPM file has a header
 * that should look something like:
 *
 *    P6
 *    # comment
 *    width height max_value
 *    rgbrgbrgb...
 *
 * where "P6" is the magic cookie which identifies the file type and
 * should be the only characters on the first line followed by a
 * carriage return.  Any line starting with a # mark will be treated
 * as a comment and discarded.   After the magic cookie, three integer
 * values are expected: width, height of the image and the maximum
 * value for a pixel (max_value must be < 256 for PPM raw files).  The
 * data section consists of width*height rgb triplets (one byte each)
 * in binary format (i.e., such as that written with fwrite() or
 * equivalent).
 *
 * The rgb data is returned as an array of unsigned chars (packed
 * rgb).  The malloc()'d memory should be free()'d by the caller.  If
 * an error occurs, an error message is sent to stderr and NULL is
 * returned.
 *
 * filename   - name of the .ppm file.
 * width      - will contain the width of the image on return.
 * height     - will contain the height of the image on return.
 *
 */
 GLubyte* Texture::glmReadPPM(char* filename, int* width, int* height)
{
    FILE* fp;
    int i, w, h, d;
    unsigned char* image;
    char head[70];          /* max line <= 70 in PPM (per spec). */
    
    fp = fopen(filename, "rb");
    if (!fp) {
        perror(filename);
        return NULL;
    }
    
    /* grab first two chars of the file and make sure that it has the
       correct magic cookie for a raw PPM file. */
    fgets(head, 70, fp);
    if (strncmp(head, "P6", 2)) {
        fprintf(stderr, "%s: Not a raw PPM file\n", filename);
        return NULL;
    }
    
    /* grab the three elements in the header (width, height, maxval). */
    i = 0;
    while(i < 3) {
        fgets(head, 70, fp);
        if (head[0] == '#')     /* skip comments. */
            continue;
        if (i == 0)
            i += sscanf(head, "%d %d %d", &w, &h, &d);
        else if (i == 1)
            i += sscanf(head, "%d %d", &h, &d);
        else if (i == 2)
            i += sscanf(head, "%d", &d);
    }
    
    /* grab all the image data in one fell swoop. */
    image = (unsigned char*)malloc(sizeof(unsigned char)*w*h*3);
    fread(image, sizeof(unsigned char), w*h*3, fp);
    fclose(fp);
    
    *width = w;
    *height = h;
    return image;
}

void Texture::ReadPPM(LPSTR filename)
{
	ppmtexData=glmReadPPM(filename,&ppmWidth,&ppmHeight);

	glGenTextures(1, texName);
	// Typical Texture Generation Using Data From The Bitmap
	glBindTexture(GL_TEXTURE_2D, texName[0]);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP); // Set Up Sphere Mapping
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP); // Set Up Sphere Mapping
	
	// Generate The Texture
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, ppmWidth, ppmHeight, GL_RGB, GL_UNSIGNED_BYTE, ppmtexData);

	free(ppmtexData);

}

void Texture::ReadImage(LPSTR filename)
{
	BuildTexture(filename,texName[0]);
}

/*void Texture::ReadBMP(LPSTR filename)
{
	dib = FreeImage_LoadBMP(filename,BMP_DEFAULT);
	FIBITMAP *cc = FreeImage_ConvertTo24Bits(dib); 
	dibtexData=FreeImage_GetBits(cc); 
	glGenTextures(1, texName);
	glBindTexture(GL_TEXTURE_2D, texName[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	// Generate The Texture
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, FreeImage_GetWidth(cc), FreeImage_GetHeight(cc), GL_RGB, GL_UNSIGNED_BYTE, dibtexData);

	free(dibtexData);

}*/
void Texture::ApplyTexture(void)
{
	glEnable(GL_TEXTURE_GEN_S); // Enable Sphere Mapping
	glEnable(GL_TEXTURE_GEN_T); // Enable Sphere Mapping
		glBindTexture(GL_TEXTURE_2D, texName[0]);
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
}





/****************************************************************************
*                                     *                                     *
*  Jeff Molofee's IPicture Basecode   *    Huge Thanks To: Dave Richards    *
*       http://nehe.gamedev.net       *                    Bobby Ward &     *
*                2002                 *                    The MSDN         *
*                                     *                                     *
*****************************************************************************
*                                                                           *
*   Loads  : BMP, EMF, GIF, ICO, JPG, WMF                                   *
*   Source : Reads From Disk Or The Internet                                *
*   Extras : Images Can Be Any Width Or Height                              *
*                                                                           *
*****************************************************************************
*                                                                           *
*   ReshapeGL  : Set Your Aspect Ratio, How You Want                        *
*   WindowProc : Add Custom WM_ Events (Mouse, Etc)                         *
*   WinMain    : Set The Window Title                                       *
*                Set Resolution & Color Depth                               *
*                Remove 4 Lines Of Code To Force Fullscreen (Commented)     *
*                                                                           *
*****************************************************************************
*                                                                           *
*   Free To Use In Projects Of Your Own.  All I Ask For Is A Simple Greet   *
*   Or Mention Of The Site In Your Readme Or The Project Itself :)          *
*                                                                           *
****************************************************************************/
int Texture::BuildTexture(char *szPathName, GLuint &texid)						// Load Image And Convert To A Texture
{
	HDC			hdcTemp;												// The DC To Hold Our Bitmap
	HBITMAP		hbmpTemp;												// Holds The Bitmap Temporarily
	IPicture	*pPicture;												// IPicture Interface
	OLECHAR		wszPath[MAX_PATH+1];									// Full Path To Picture (WCHAR)
	char		szPath[MAX_PATH+1];										// Full Path To Picture
	long		lWidth;													// Width In Logical Units
	long		lHeight;												// Height In Logical Units
	long		lWidthPixels;											// Width In Pixels
	long		lHeightPixels;											// Height In Pixels
	GLint		glMaxTexDim ;											// Holds Maximum Texture Size

	if (strstr(szPathName, "http://"))									// If PathName Contains http:// Then...
	{
		strcpy(szPath, szPathName);										// Append The PathName To szPath
	}
	else																// Otherwise... We Are Loading From A File
	{
		GetCurrentDirectory(MAX_PATH, szPath);							// Get Our Working Directory
		strcat(szPath, "\\");											// Append "\" After The Working Directory
		strcat(szPath, szPathName);										// Append The PathName
	}

	MultiByteToWideChar(CP_ACP, 0, szPath, -1, wszPath, MAX_PATH);		// Convert From ASCII To Unicode
	HRESULT hr = OleLoadPicturePath(wszPath, 0, 0, 0, IID_IPicture, (void**)&pPicture);

	if(FAILED(hr))														// If Loading Failed
		return FALSE;													// Return False

	hdcTemp = CreateCompatibleDC(GetDC(0));								// Create The Windows Compatible Device Context
	if(!hdcTemp)														// Did Creation Fail?
	{
		pPicture->Release();											// Decrements IPicture Reference Count
		return FALSE;													// Return False (Failure)
	}

	glGetIntegerv(GL_MAX_TEXTURE_SIZE, &glMaxTexDim);					// Get Maximum Texture Size Supported
	
	pPicture->get_Width(&lWidth);										// Get IPicture Width (Convert To Pixels)
	lWidthPixels	= MulDiv(lWidth, GetDeviceCaps(hdcTemp, LOGPIXELSX), 2540);
	pPicture->get_Height(&lHeight);										// Get IPicture Height (Convert To Pixels)
	lHeightPixels	= MulDiv(lHeight, GetDeviceCaps(hdcTemp, LOGPIXELSY), 2540);

	// Resize Image To Closest Power Of Two
	if (lWidthPixels <= glMaxTexDim) // Is Image Width Less Than Or Equal To Cards Limit
		lWidthPixels = 1 << (int)floor((log((double)lWidthPixels)/log(2.0f)) + 0.5f); 
	else  // Otherwise  Set Width To "Max Power Of Two" That The Card Can Handle
		lWidthPixels = glMaxTexDim;
 
	if (lHeightPixels <= glMaxTexDim) // Is Image Height Greater Than Cards Limit
		lHeightPixels = 1 << (int)floor((log((double)lHeightPixels)/log(2.0f)) + 0.5f);
	else  // Otherwise  Set Height To "Max Power Of Two" That The Card Can Handle
		lHeightPixels = glMaxTexDim;
	
	//	Create A Temporary Bitmap
	BITMAPINFO	bi = {0};												// The Type Of Bitmap We Request
	DWORD		*pBits = 0;												// Pointer To The Bitmap Bits

	bi.bmiHeader.biSize			= sizeof(BITMAPINFOHEADER);				// Set Structure Size
	bi.bmiHeader.biBitCount		= 32;									// 32 Bit
	bi.bmiHeader.biWidth		= lWidthPixels;							// Power Of Two Width
	bi.bmiHeader.biHeight		= lHeightPixels;						// Make Image Top Up (Positive Y-Axis)
	bi.bmiHeader.biCompression	= BI_RGB;								// RGB Encoding
	bi.bmiHeader.biPlanes		= 1;									// 1 Bitplane

	//	Creating A Bitmap This Way Allows Us To Specify Color Depth And Gives Us Imediate Access To The Bits
	hbmpTemp = CreateDIBSection(hdcTemp, &bi, DIB_RGB_COLORS, (void**)&pBits, 0, 0);
	
	if(!hbmpTemp)														// Did Creation Fail?
	{
		DeleteDC(hdcTemp);												// Delete The Device Context
		pPicture->Release();											// Decrements IPicture Reference Count
		return FALSE;													// Return False (Failure)
	}

	SelectObject(hdcTemp, hbmpTemp);									// Select Handle To Our Temp DC And Our Temp Bitmap Object

	// Render The IPicture On To The Bitmap
	pPicture->Render(hdcTemp, 0, 0, lWidthPixels, lHeightPixels, 0, lHeight, lWidth, -lHeight, 0);

	// Convert From BGR To RGB Format And Add An Alpha Value Of 255
	for(long i = 0; i < lWidthPixels * lHeightPixels; i++)				// Loop Through All Of The Pixels
	{
		BYTE* pPixel	= (BYTE*)(&pBits[i]);							// Grab The Current Pixel
		BYTE  temp		= pPixel[0];									// Store 1st Color In Temp Variable (Blue)
		pPixel[0]		= pPixel[2];									// Move Red Value To Correct Position (1st)
		pPixel[2]		= temp;											// Move Temp Value To Correct Blue Position (3rd)

		// This Will Make Any Black Pixels, Completely Transparent		(You Can Hardcode The Value If You Wish)
		//if ((pPixel[0]==0) && (pPixel[1]==0) && (pPixel[2]==0))			// Is Pixel Completely Black
		//	pPixel[3]	=   0;											// Set The Alpha Value To 0
		//else															// Otherwise
			pPixel[3]	= 255;											// Set The Alpha Value To 255
	}

	glGenTextures(1, &texid);											// Create The Texture

	// Typical Texture Generation Using Data From The Bitmap
	glBindTexture(GL_TEXTURE_2D, texid);								// Bind To The Texture ID
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);		// (Modify This For The Type Of Filtering You Want)
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);     // (Modify This For The Type Of Filtering You Want)
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, lWidthPixels, lHeightPixels, 0, GL_RGBA, GL_UNSIGNED_BYTE, pBits);	// (Modify This If You Want Mipmaps)

	DeleteObject(hbmpTemp);												// Delete The Object
	DeleteDC(hdcTemp);													// Delete The Device Context

	pPicture->Release();												// Decrements IPicture Reference Count

	return TRUE;														// Return True (All Good)
}

