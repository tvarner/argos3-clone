/**
 * @file <argos3/core/utility/configuration/[some path].h>
 *
 * @brief This file provides the class definition for a URDF link
 *
 * @author Thomas Varner - <thomas.g.varner@gmail.com>
 */

#ifndef LINK_H
#define LINK_H

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

      struct SBox {
        CVector3 m_cSize;
      };

      struct SCylinder {
        Real m_fRadius;
        Real m_fLength;
      };

      struct SSphere {
        Real m_fRadius;
      };

      struct SMesh {
        std::string m_strFilename;
        Real m_fScale;
      };

      struct SGeometry {
        SBox m_sBox;
        SCylinder m_sCylinder;
        SSphere m_sSphere;
        SMesh m_sMesh;
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
        SGeometry m_sGeometry;
        SMaterial m_sMaterial;
      };

      struct SCollision { 
        std::string m_strName;
        SOrigin m_sOrigin;
        SGeometry m_sGeometry;
      }; 

      std::string m_strName;

      SInertial m_sInertial;

      SVisual m_sVisual;

      SCollision m_sCollision;
  };
}

#endif