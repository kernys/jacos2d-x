/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2011      Zynga Inc.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/


#ifndef __CCDRAWING_PRIMITIVES__
#define __CCDRAWING_PRIMITIVES__
    
/**
 @file
 Drawing OpenGL ES primitives.
 - ccDrawPoint
 - ccDrawLine
 - ccDrawPoly
 - ccDrawCircle
 - ccDrawQuadBezier
 - ccDrawCubicBezier
 
 You can change the color, width and other property by calling the
 glColor4ub(), glLineWidth(), glPointSize().
 
 @warning These functions draws the Line, Point, Polygon, immediately. They aren't batched. If you are going to make a game that depends on these primitives, I suggest creating a batch.
 */
#include "ccTypes.h"
#include "ccMacros.h"
#include "cocoa/CCGeometry.h"    // for CCPoint
#include <vector>
NS_CC_BEGIN

/**
 * @addtogroup global
 * @{
 */
class CCPointsList : public JacosBaseObject
{
public:
	CCPointsList() {}
	CCPointsList(const CCPoint* points, unsigned int numberOfPoints)
	{		
		if (numberOfPoints > 0) {			
			for (unsigned int i = 0; i < numberOfPoints; i++)
				mPoints.push_back(points[i]);
		}
	}

	CCPoint* getPointAt(unsigned int index) {
		if (index >= 0 && index < mPoints.size())
			return &mPoints[index];
		return NULL;
	}

	void addPoint(CCPoint* point) {
		mPoints.push_back(*point);
	}
	void removePointAt(unsigned int index) {
		if (index >= 0 && index <= mPoints.size())
			mPoints.erase(mPoints.begin() + index);
	}
	void insertPointAt(CCPoint* point, unsigned int index) {
		if (index >= 0 && index <= mPoints.size())
			mPoints.insert(mPoints.begin() + index, *point);
	}
	CCPointsList* reverse() {
		CCPointsList *list = new CCPointsList();
		for (unsigned int i = 0; i < mPoints.size(); i++)
			list->mPoints.push_back(mPoints[i]);
		return list;
	}
	const CCPoint* getPointsList() {return &mPoints[0];}
	unsigned int getNumberOfPoints() {return mPoints.size();};
private:
	std::vector<CCPoint> mPoints;
};

class CCPointArray;

/** initialize context */
void CC_DLL ccDrawInit();

/** draws a point given x and y coordinate measured in points */
void CC_DLL ccDrawPoint( const CCPoint& point );

/** draws an array of points.
 @since v0.7.2
 */
void CC_DLL ccDrawPoints( const CCPoint *points, unsigned int numberOfPoints );
void CC_DLL ccDrawPoints(CCPointsList *points);

/** draws a line given the origin and destination point measured in points */
void CC_DLL ccDrawLine( const CCPoint& origin, const CCPoint& destination );

/** draws a rectangle given the origin and destination point measured in points. */
void CC_DLL ccDrawRect( CCPoint origin, CCPoint destination );

/** draws a solid rectangle given the origin and destination point measured in points.
    @since 1.1
 */
void CC_DLL ccDrawSolidRect( CCPoint origin, CCPoint destination, ccColor4F color );

/** draws a polygon given a pointer to CCPoint coordinates and the number of vertices measured in points.
The polygon can be closed or open
*/
void CC_DLL ccDrawPoly( const CCPoint *vertices, unsigned int numOfVertices, bool closePolygon );
void CC_DLL ccDrawPoly( CCPointsList *vertices, bool closePolygon );

/** draws a solid polygon given a pointer to CGPoint coordinates, the number of vertices measured in points, and a color.
 */
void CC_DLL ccDrawSolidPoly( const CCPoint *poli, unsigned int numberOfPoints, ccColor4F color );
void CC_DLL ccDrawSolidPoly( CCPointsList *poli, ccColor4F color );

/** draws a circle given the center, radius and number of segments. */
void CC_DLL ccDrawCircle( const CCPoint& center, float radius, float angle, unsigned int segments, bool drawLineToCenter, float scaleX, float scaleY);
void CC_DLL ccDrawCircle( const CCPoint& center, float radius, float angle, unsigned int segments, bool drawLineToCenter);

/** draws a quad bezier path
 @warning This function could be pretty slow. Use it only for debugging purposes.
 @since v0.8
 */
void CC_DLL ccDrawQuadBezier(const CCPoint& origin, const CCPoint& control, const CCPoint& destination, unsigned int segments);

/** draws a cubic bezier path
 @warning This function could be pretty slow. Use it only for debugging purposes.
 @since v0.8
 */
void CC_DLL ccDrawCubicBezier(const CCPoint& origin, const CCPoint& control1, const CCPoint& control2, const CCPoint& destination, unsigned int segments);

/** draws a Catmull Rom path.
 @warning This function could be pretty slow. Use it only for debugging purposes.
 @since v2.0
 */
void CC_DLL ccDrawCatmullRom( CCPointArray *arrayOfControlPoints, unsigned int segments );

/** draws a Cardinal Spline path.
 @warning This function could be pretty slow. Use it only for debugging purposes.
 @since v2.0
 */
void CC_DLL ccDrawCardinalSpline( CCPointArray *config, float tension,  unsigned int segments );

/** set the drawing color with 4 unsigned bytes
 @since v2.0
 */
void CC_DLL ccDrawColor4B( GLubyte r, GLubyte g, GLubyte b, GLubyte a );

/** set the drawing color with 4 floats
 @since v2.0
 */
void CC_DLL ccDrawColor4F( GLfloat r, GLfloat g, GLfloat b, GLfloat a );

/** set the point size in points. Default 1.
 @since v2.0
 */
void CC_DLL ccPointSize( GLfloat pointSize );

/**
	set line with
 */
void CC_DLL ccLineWidth(GLfloat width);
// end of global group
/// @}

NS_CC_END

#endif // __CCDRAWING_PRIMITIVES__
