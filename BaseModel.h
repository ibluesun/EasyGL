#include <vector>
using namespace std;
// Basemodel.h: interface for the BaseModel class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BASEMODEL_H__F307A88A_7309_4F57_890A_1695898F8275__INCLUDED_)
#define AFX_BASEMODEL_H__F307A88A_7309_4F57_890A_1695898F8275__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class Texture;
class CameraModel;
class Material;
#include "EasyGL.h"
class PickFunctionClass
{
	public:
		virtual void RunPickFunction(void)=0;
};
class BaseModel
{
	friend class EasyGL;
public:
	BaseModel();
	virtual ~BaseModel();
protected:
	virtual void Render(void)=0;
	Texture *modelTexture;
	Material *modelMaterial;
	GLdouble Opacity;  // for transparency
	
	// Address of function which will be called
	void* PickCallBackFunction; 
	PickFunctionClass* PickCallBackObject;
	virtual void RunPickFunction(void);

public:
	GLuint pkname;
	BOOL picking;
	void PickFunction(void*);
	void PickFunction(PickFunctionClass*);

	void AttachTexture(Texture* tex);
	void AttachMaterial(Material* mat);
	void ReleaseTexture(void);
	virtual void ChangeOpacity(GLdouble cc);

//// members that will be virtually inheretince
public:
	virtual void Unitize(void)=0;
	virtual void Scale(GLfloat sc)=0;
	virtual void ReverseWinding(void)=0;
	virtual void get_postion(GLfloat*,GLfloat*,GLfloat*)=0;
};

////////////////////////////////////////////////
///////////////////////////
// Simlpe Model Class


class SimpleModel : public BaseModel  
{
	friend class EasyGL;
public:
	SimpleModel();
	virtual ~SimpleModel();

///////////////////////////////////////////////////////////////////
// The next funcions will behave exactly like its preceding opengl
// functions.
//
// note:
//     these funcions will not trace the current location of the model
// they just move it
// if you feed the function with false
// transformation begin from the first
//
// if you feed it with true 
// the new transformation multiplied to the old matrix
// Enjoy
//
// Ahmed Sadek ModificationS

////////////////////////////////////////////////////


protected:
	GLfloat effectmatrix[16];//store the matrix of movement which will be 
							  //called when Render is Called
public:
	void Translate(GLfloat,GLfloat,GLfloat,BOOL);
	void Rotate(GLfloat,GLfloat,GLfloat,GLfloat,BOOL);
	void Scale(GLfloat,GLfloat,GLfloat,BOOL);


///////////////////////////////////////////////////////////
/// Now with some fantasy with standard template library
/// I want to make an array of points express some kind
//  of path which model can go through it
//
protected:
	friend class translateelement;
	friend class rotateelement;
	friend class TRelement;

	struct translateelement
	{
		GLfloat x;
		GLfloat y;
		GLfloat z;
		virtual void Run(GLfloat tempmatrix[16]);
	}*poi;

	struct rotateelement:public translateelement
	{
		GLfloat deg;
		void Run(GLfloat tempmatrix[16]);
	}*roi;
	
	struct TRelement:public translateelement
	{
		GLfloat vx;
		GLfloat vy;
		GLfloat vz;
		GLfloat deg;
		void Run(GLfloat tempmatrix[16]);
	}*proi;

	vector <translateelement*> Ppoints;
	vector <translateelement*>::iterator Pp;


public:
	void addTpoint(GLfloat,GLfloat,GLfloat);
	void addRpoint(GLfloat,GLfloat,GLfloat,GLfloat);
	void addTRpoint(GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat);

	void removelastpoint(void);
	void clearthepath(void);
protected:
	BOOL usepath;
public:
	void EnablePathTrace(void);
	void DisablePathTrace(void);
protected:
	void GetNextPoint(void);

/////////////////////////////////////////////////////////////
// Camera Attachment implemnteation
protected:
	CameraModel* camerame;         /// for camera center
	CameraModel* cameraEye;        /// for camera it self or its eye
public:
	void AttachCamera(CameraModel* cm);
	void AttachCameraEye(CameraModel* cm);
	void ReleaseCamera(void);

////////////////////////////////////////////////////////////
// position manipulation
	void Unitize(void);
	void Scale(GLfloat sc);
	void ReverseWinding(void);
	void get_postion(GLfloat* x,GLfloat* y,GLfloat* z);
};

///////////////////////////////////////////////////////////////////
///////////////////
/////////
/////
class ObjectModel: public SimpleModel
{
public:
	ObjectModel();
	virtual ~ObjectModel();
	////////////////////////////////////////////////////////
	/// The next section is for Wave Front Object Files
	////////////////////
	#ifndef M_PI
	#define M_PI 3.14159265f
	#endif

	#define GLM_NONE     (0)            /* render with only vertices */
	#define GLM_FLAT     (1 << 0)       /* render with facet normals */
	#define GLM_SMOOTH   (1 << 1)       /* render with vertex normals */
	#define GLM_TEXTURE  (1 << 2)       /* render with texture coords */
	#define GLM_COLOR    (1 << 3)       /* render with colors */
	#define GLM_MATERIAL (1 << 4)       /* render with materials */
	#define T(x) (model->triangles[(x)])

	class Glm
	{
		friend struct GLMnode;
		friend struct GLMmaterial;
		friend struct GLMtriangle;
		friend struct GLMgroup;
		friend struct GLMmodel;

		/* _GLMnode: general purpose node */
		struct GLMnode {
		friend class Glm;
			GLuint         index;
			GLboolean      averaged;
			struct GLMnode* next;
		};
		
		/* GLMmaterial: Structure that defines a material in a model.*/
		struct GLMmaterial
		{
		friend class Glm;
		  char* name;                   /* name of material */
		  GLfloat diffuse[4];           /* diffuse component */
		  GLfloat ambient[4];           /* ambient component */
		  GLfloat specular[4];          /* specular component */
		  GLfloat emmissive[4];         /* emmissive component */
		  GLfloat shininess;            /* specular exponent */
		};

		/* GLMtriangle: Structure that defines a triangle in a model.
		 */
		struct GLMtriangle {
		friend class Glm;
		  GLuint vindices[3];           /* array of triangle vertex indices */
		  GLuint nindices[3];           /* array of triangle normal indices */
		  GLuint tindices[3];           /* array of triangle texcoord indices*/
		  GLuint findex;                /* index of triangle facet normal */
		};

		/* GLMgroup: Structure that defines a group in a model.
		 */
		struct GLMgroup {
		friend class Glm;
		  char*             name;           /* name of this group */
		  GLuint            numtriangles;   /* number of triangles in this group */
		  GLuint*           triangles;      /* array of triangle indices */
		  GLuint            material;       /* index to material for group */
		  struct GLMgroup* next;           /* pointer to next group in model */
		};

		/* GLMmodel: Structure that defines a model.
		 */
		struct GLMmodel {
		friend class Glm;
		  char*    pathname;            /* path to this model */
		  char*    mtllibname;          /* name of the material library */

		  GLuint   numvertices;         /* number of vertices in model */
		  GLfloat* vertices;            /* array of vertices  */

		  GLuint   numnormals;          /* number of normals in model */
		  GLfloat* normals;             /* array of normals */

		  GLuint   numtexcoords;        /* number of texcoords in model */
		  GLfloat* texcoords;           /* array of texture coordinates */

		  GLuint   numfacetnorms;       /* number of facetnorms in model */
		  GLfloat* facetnorms;          /* array of facetnorms */

		  GLuint       numtriangles;    /* number of triangles in model */
		  GLMtriangle* triangles;       /* array of triangles */

		  GLuint       nummaterials;    /* number of materials in model */
		  GLMmaterial* materials;       /* array of materials */

		  GLuint       numgroups;       /* number of groups in model */
		  GLMgroup*    groups;          /* linked list of groups */

		  GLfloat position[3];          /* position of the model */

		};

		
	public:
		Glm();
		~Glm();


		/* glmUnitize: "unitize" a model by translating it to the origin and
		 * scaling it to fit in a unit cube around the origin.  Returns the
		 * scalefactor used.
		 *
		 * model - properly initialized GLMmodel structure 
		 */
		GLfloat glmUnitize();

		/* glmDimensions: Calculates the dimensions (width, height, depth) of
		 * a model.
		 *
		 * model      - initialized GLMmodel structure
		 * dimensions - array of 3 GLfloats (GLfloat dimensions[3])
		 */
		GLvoid glmDimensions(GLfloat* dimensions);

		/* glmScale: Scales a model by a given amount.
		 * 
		 * model - properly initialized GLMmodel structure
		 * scale - scalefactor (0.5 = half as large, 2.0 = twice as large)
		 */
		GLvoid glmScale(GLfloat scale);

		/* glmReverseWinding: Reverse the polygon winding for all polygons in
		 * this model.  Default winding is counter-clockwise.  Also changes
		 * the direction of the normals.
		 * 
		 * model - properly initialized GLMmodel structure 
		 */
		GLvoid glmReverseWinding();

		/* glmFacetNormals: Generates facet normals for a model (by taking the
		 * cross product of the two vectors derived from the sides of each
		 * triangle).  Assumes a counter-clockwise winding.
		 *
		 * model - initialized GLMmodel structure
		 */
		GLvoid glmFacetNormals();

		/* glmVertexNormals: Generates smooth vertex normals for a model.
		 * First builds a list of all the triangles each vertex is in.  Then
		 * loops through each vertex in the the list averaging all the facet
		 * normals of the triangles each vertex is in.  Finally, sets the
		 * normal index in the triangle for the vertex to the generated smooth
		 * normal.  If the dot product of a facet normal and the facet normal
		 * associated with the first triangle in the list of triangles the
		 * current vertex is in is greater than the cosine of the angle
		 * parameter to the function, that facet normal is not added into the
		 * average normal calculation and the corresponding vertex is given
		 * the facet normal.  This tends to preserve hard edges.  The angle to
		 * use depends on the model, but 90 degrees is usually a good start.
		 *
		 * model - initialized GLMmodel structure
		 * angle - maximum angle (in degrees) to smooth across
		 */
		GLvoid glmVertexNormals(GLfloat angle);

		/* glmLinearTexture: Generates texture coordinates according to a
		 * linear projection of the texture map.  It generates these by
		 * linearly mapping the vertices onto a square.
		 *
		 * model - pointer to initialized GLMmodel structure
		 */
		GLvoid glmLinearTexture();

		/* glmSpheremapTexture: Generates texture coordinates according to a
		 * spherical projection of the texture map.  Sometimes referred to as
		 * spheremap, or reflection map texture coordinates.  It generates
		 * these by using the normal to calculate where that vertex would map
		 * onto a sphere.  Since it is impossible to map something flat
		 * perfectly onto something spherical, there is distortion at the
		 * poles.  This particular implementation causes the poles along the X
		 * axis to be distorted.
		 *
		 * model - pointer to initialized GLMmodel structure
		 */
		GLvoid glmSpheremapTexture();

		/* glmDelete: Deletes a GLMmodel structure.
		 *
		 * model - initialized GLMmodel structure
		 */
		GLvoid glmDelete();

		/* glmReadOBJ: Reads a model description from a Wavefront .OBJ file.
		 * Returns a pointer to the created object which should be free'd with
		 * glmDelete().
		 *
		 * filename - name of the file containing the Wavefront .OBJ format data.  
		 */
		void glmReadOBJ(char* filename);

		/* glmWriteOBJ: Writes a model description in Wavefront .OBJ format to
		 * a file.
		 *
		 * model    - initialized GLMmodel structure
		 * filename - name of the file to write the Wavefront .OBJ format data to
		 * mode     - a bitwise or of values describing what is written to the file
		 *            GLM_NONE    -  write only vertices
		 *            GLM_FLAT    -  write facet normals
		 *            GLM_SMOOTH  -  write vertex normals
		 *            GLM_TEXTURE -  write texture coords
		 *            GLM_FLAT and GLM_SMOOTH should not both be specified.
		 */
		GLvoid glmWriteOBJ(char* filename, GLuint mode);

		/* glmDraw: Renders the model to the current OpenGL context using the
		 * mode specified.
		 *
		 * model    - initialized GLMmodel structure
		 * mode     - a bitwise OR of values describing what is to be rendered.
		 *            GLM_NONE    -  render with only vertices
		 *            GLM_FLAT    -  render with facet normals
		 *            GLM_SMOOTH  -  render with vertex normals
		 *            GLM_TEXTURE -  render with texture coords
		 *            GLM_FLAT and GLM_SMOOTH should not both be specified.
		 */
		GLvoid glmDraw(GLuint mode);

		/* glmList: Generates and returns a display list for the model using
		 * the mode specified.
		 *
		 * model    - initialized GLMmodel structure
		 * mode     - a bitwise OR of values describing what is to be rendered.
		 *            GLM_NONE    -  render with only vertices
		 *            GLM_FLAT    -  render with facet normals
		 *            GLM_SMOOTH  -  render with vertex normals
		 *            GLM_TEXTURE -  render with texture coords
		 *            GLM_FLAT and GLM_SMOOTH should not both be specified.  
		 */
		GLuint glmList(GLuint mode);

		/* glmWeld: eliminate (weld) vectors that are within an epsilon of
		 * each other.
		 *
		 * model      - initialized GLMmodel structure
		 * epsilon    - maximum difference between vertices
		 *              ( 0.00001 is a good start for a unitized model)
		 *
		 */
		GLvoid glmWeld(GLfloat epsilon);

	private:

		GLMmodel *model;
		GLMgroup *group;

		/* glmMax: returns the maximum of two floats */
		GLfloat glmMax(GLfloat a, GLfloat b);

		/* glmAbs: returns the absolute value of a float */
		GLfloat glmAbs(GLfloat f);

		/* glmDot: compute the dot product of two vectors
		 *
		 * u - array of 3 GLfloats (GLfloat u[3])
		 * v - array of 3 GLfloats (GLfloat v[3])
		 */
		GLfloat glmDot(GLfloat* u, GLfloat* v);

		/* glmCross: compute the cross product of two vectors
		 *
		 * u - array of 3 GLfloats (GLfloat u[3])
		 * v - array of 3 GLfloats (GLfloat v[3])
		 * n - array of 3 GLfloats (GLfloat n[3]) to return the cross product in
		 */
		GLvoid glmCross(GLfloat* u, GLfloat* v, GLfloat* n);

		/* glmNormalize: normalize a vector
		 *
		 * v - array of 3 GLfloats (GLfloat v[3]) to be normalized
		 */
		GLvoid glmNormalize(GLfloat* v);

		/* glmEqual: compares two vectors and returns GL_TRUE if they are
		 * equal (within a certain threshold) or GL_FALSE if not. An epsilon
		 * that works fairly well is 0.000001.
		 *
		 * u - array of 3 GLfloats (GLfloat u[3])
		 * v - array of 3 GLfloats (GLfloat v[3]) 
		 */
		GLboolean glmEqual(GLfloat* u, GLfloat* v, GLfloat epsilon);

		/* glmWeldVectors: eliminate (weld) vectors that are within an
		 * epsilon of each other.
		 *
		 * vectors     - array of GLfloat[3]'s to be welded
		 * numvectors - number of GLfloat[3]'s in vectors
		 * epsilon     - maximum difference between vectors 
		 *
		 */
		GLfloat* glmWeldVectors(GLfloat* vectors, GLuint* numvectors, GLfloat epsilon);

		/* glmFindGroup: Find a group in the model */
		void glmFindGroup(char* name);

		/* glmAddGroup: Add a group to the model */
		void glmAddGroup(char* name);

		/* glmFindGroup: Find a material in the model */
		GLuint glmFindMaterial(char* name);

		/* glmDirName: return the directory given a path
		 *
		 * path - filesystem path
		 *
		 * NOTE: the return value should be free'd.
		 */
		char* glmDirName(char* path);

		/* glmReadMTL: read a wavefront material library file
		 *
		 * model - properly initialized GLMmodel structure
		 * name  - name of the material library
		 */
		GLvoid glmReadMTL(char* name);

		/* glmWriteMTL: write a wavefront material library file
		 *
		 * model   - properly initialized GLMmodel structure
		 * modelpath  - pathname of the model being written
		 * mtllibname - name of the material library to be written
		 */
		GLvoid glmWriteMTL(char* modelpath, char* mtllibname);

		/* glmFirstPass: first pass at a Wavefront OBJ file that gets all the
		 * statistics of the model (such as #vertices, #normals, etc)
		 *
		 * model - properly initialized GLMmodel structure
		 * file  - (fopen'd) file descriptor 
		 */
		GLvoid glmFirstPass(FILE* file);

		/* glmSecondPass: second pass at a Wavefront OBJ file that gets all
		 * the data.
		 *
		 * model - properly initialized GLMmodel structure
		 * file  - (fopen'd) file descriptor 
		 */
		GLvoid glmSecondPass(FILE* file);

	public:
		GLdouble opac;

	};

protected:
	Glm glmMesh;

protected:
	void Render(void);

public:
	void LoadGLMFile(LPSTR filename);
	void ChangeOpacity(GLdouble cc);	
public:
	void Unitize(void);
	void Scale(GLfloat sc);
	void ReverseWinding(void);
};

///////////////////////////////////////////////////////
////////////////
//// Custom Model

class CustomModel : public SimpleModel
{
private:
// Address of function which will be called
	void* RenderAddr; 

public:
// Specifiy the callback function which draw the model
	void RenderAddress(void*);
	CustomModel();
protected:
	void Render(void);

};

////////////////////////////////////////////////////////
//////////////////////
//// Geometric Model
///  just for cube and sphere etc.

class GeometricModel : public SimpleModel
{
private:
		GLUquadricObj* quad;
		int selector;             // 1-cube 2-sphere 

		//sphere
		GLdouble Radius;          // for sphere

		//Cube
		GLdouble unit;

		//Disk
		GLdouble innerRadius;
		GLdouble outerRadius;

		//Cylinder
		GLdouble baseRadius;
		GLdouble topRadius;
		GLdouble cheight;

		//partial disk
		GLdouble startAngle;
		GLdouble sweepAngle;


public:
		GeometricModel();
		virtual ~GeometricModel();
		void ItIsSphere(GLdouble Rad);
		void ItIsCube(GLdouble uni);
		void ItIsDisk(GLdouble inRad,GLdouble outRad);
		void ItIsPartialDisk(GLdouble inRad,GLdouble outRad,GLdouble startAng,GLdouble sweepAng);
		void ItIsCylinder(GLdouble baseRad,GLdouble topRad,GLdouble hi);

protected:
	void Render(void);
};

////////////////////////////////////////////////////
////////////////////
////  Font Model
//

class FontModel:public SimpleModel
{

private:	
    void KillFont(void);
	GLuint fbase;				// Base Display List For The Font Set
	GLYPHMETRICSFLOAT gmf[256]; // Storage For Information About Our Font
	HDC EGLDC;
	const char *fmt;
public:
	virtual ~FontModel();
	void BuildFont(EasyGL* cc,int,const char *ft, ...);
	LPCSTR FontName;
	int FontWeight;
protected:
	void Render(void);

};

class DynamicModel:public SimpleModel
{

};

#endif // !defined(AFX_BASEMODEL_H__F307A88A_7309_4F57_890A_1695898F8275__INCLUDED_)
