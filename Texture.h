// Texture.h: interface for the Texture class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TEXTURE_H__4919E609_776C_4CBA_B1EB_203D0A325262__INCLUDED_)
#define AFX_TEXTURE_H__4919E609_776C_4CBA_B1EB_203D0A325262__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "EasyGL.h"
//#include "FreeImage.h"
#include <olectl.h>														// Header File For The OLE Controls Library	(Used In BuildTexture)
#include <math.h>														// Header File For The Math Library			(Used In BuildTexture)


class Texture  
{
	friend class BaseModel;
	friend class SimpleModel;
	friend class ObjectModel;
	friend class CustomModel;
	friend class GeometricModel;
	friend class FontModel;
	friend class EasyGL;
public:
	Texture();
	virtual ~Texture();

private:
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
	GLubyte* glmReadPPM(char* filename, int* width, int* height);



/// End of the Reading Section
//////////////////////////////////////////////////////////////////
	
	
	GLuint texName[1];
	GLubyte* ppmtexData;
	int ppmWidth;
	int ppmHeight;

	GLubyte* dibtexData;
	//FIBITMAP* dib;

public:
	void ApplyTexture(void);
	void ReadPPM(LPSTR filename);
	//void ReadBMP(LPSTR filename);
	void Draw(float,float); // Draw the texture at specific position

private:
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
	int BuildTexture(char *szPathName, GLuint &texid);

public:
	void ReadImage(LPSTR filename);
};

#endif // !defined(AFX_TEXTURE_H__4919E609_776C_4CBA_B1EB_203D0A325262__INCLUDED_)
