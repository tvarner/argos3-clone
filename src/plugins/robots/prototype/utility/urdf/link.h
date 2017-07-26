/**
 * @file <argos3/core/utility/configuration/[some path].h>
 *
 * @brief This file provides the class definition for a URDF link
 *
 * @author Thomas Varner - <thomas.g.varner@gmail.com>
 */

#ifndef LINK_H
#define LINK_H

#include <argos3/plugins/robots/prototype/simulator/box_geometry3.h>
#include <argos3/plugins/robots/prototype/simulator/cylinder_geometry3.h>
#include <argos3/plugins/robots/prototype/simulator/sphere_geometry3.h>
#include <argos3/plugins/robots/prototype/simulator/mesh.h>
#include <argos3/core/utility/math/vector3.h>
#include <string>

namespace argos {
  class CURDFLink { 
    public:
      
      // link contstructor 
      CURDFLink();

      struct SInertia {
        Real m_fIXX;
        Real m_fIXY;
        Real m_fIXZ;
        Real m_fIYY;
        Real m_fIYZ;
        Real m_fIZZ;
      };
 
      struct SOrigin {
        CVector3 m_cXYZ;
        CVector3 m_cRPY;
      };

      struct SInertial {
        Real m_fMass;
        SOrigin m_sOrigin;
        SInertia m_sInertia;
      };

      struct SColor {
        Real m_fR;
        Real m_fG;
        Real m_fB;
        Real m_fA;
      };

      struct SMaterial {
        std::string m_strName;
        std::string m_strTexture;
        SColor m_sColor;
      };

      struct SVisual {
        std::string m_strName;
        SOrigin m_sOrigin;
        CGeometry m_cGeometry;
        SMaterial m_sMaterial;
      };

      struct SCollision { 
        std::string m_strName;
        SOrigin m_sOrigin;
        CGeometry m_cGeometry;
      }; 

      std::string m_strName;

      std::string m_strParentLink;

      std::string m_strParentJoint;

      std::vector<std::string> m_vecChildrenLinks;

      SInertial m_sInertial;

      SVisual m_sVisual;

      SCollision m_sCollision;
  };
}

#endif