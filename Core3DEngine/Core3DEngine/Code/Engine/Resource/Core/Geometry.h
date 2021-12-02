/*****************************************************************//**
 * \file   Geometry.h
 * \brief  ÉWÉIÉÅÉgÉä
 * 
 * \author USAMI KOSHI
 * \date   2021/10/06
 *********************************************************************/
#ifndef _GEOMETRY_
#define _GEOMETRY_

#include "Mesh.h"

class Geometry
{
public:
	static void Quad(Core::CoreMesh& out);
	static void Plane(Core::CoreMesh& out, int split = 10, float size = 1.0f, float texSize = 0.1f);
	static void Cube(Core::CoreMesh& out);
	static void Sphere(Core::CoreMesh& out, int nSplit, float fSize, float fTexSize);
	static void SkyDome(Core::CoreMesh& out, int nSegment, float fTexSplit);
};

#endif // !_GEOMETRY_
