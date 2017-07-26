/**
 * @file <argos3/core/utility/configuration/[some path].h>
 *
 * @brief This file provides the class definition for a URDF link
 *
 * @author Thomas Varner - <thomas.g.varner@gmail.com>
 */

#ifndef JOINT_H
#define JOINT_H

#include <argos3/core/utility/math/vector3.h>
#include <string>

namespace argos {
  class CURDFJoint { 
    public:
      // Joint contstructor 
      CURDFJoint();

      struct SOrigin {
        CVector3 m_cXYZ;
        CVector3 m_Origin;
      }

      struct SAxis { 
        CVector3 m_cXYZ;
        CVector3 m_cRPY;
      };

      struct SCalibration {
        Real m_fRising;
        Real m_fFalling;
      };

      struct SDynamics {
        Real m_fDamping;
        Real m_fFriction;
      };

      struct SLimit {
        Real m_fEffort;
        Real m_fVelocity;
        Real m_fLower;
        Real m_fUpper;
      };

      struct SMimic {
        std::string m_strJoint;
        Real m_fMultiplier;
        Real m_fOffset;
      };

      struct SSafetyController {
        Real m_fSoftLowerLimit;
        Real m_fSoftUpperLimit;
        Real m_fKPosition;
        Real m_fKVelocity;
      }; 

      std::string m_strName;

      std::string m_strType;

      std::string m_strParent;

      std::string m_strChild;

      SAxis m_sAxis;

      SCalibration m_sCalibration;

      SDynamics m_sDynamics;

      SLimit m_sLimit;

      SMimic m_sMimic;

      SSafetyController m_sSafetyController;
  };
}

#endif
