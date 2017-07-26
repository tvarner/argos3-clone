/**
 * @file <argos3/plugins/robots/prototype/simulator/sphere_geometry3.h>
 *
 * @author Michael Allwright - <allsey87@gmail.com>
 */

#ifndef MESH_GEOMETRY3_H
#define MESH_GEOMETRY3_H

#include <argos3/plugins/robots/prototype/utility/geometry3.h>

namespace argos {

   class CGeometryMeshGeometry3 : public CGeometry3 {
      public:
         CGeometryMeshGeometry3(std::string str_filename, Real f_scale) :
            m_strFilename(str_filename),
            m_fScale(f_scale) {}

         EGeometry3Tag GetTag() const {
            return MESH;
         }
      
         CVector3 GetFilename() const {
            return m_strFilename;
         }

         Real GetScale() const {
            return m_fScale;
         }

      private:

         std::string m_strFilename;

         Real m_fScale;
   };
}

#endif