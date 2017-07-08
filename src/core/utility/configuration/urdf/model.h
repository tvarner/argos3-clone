/**
 * @file <argos3/core/utility/configuration/[some path].h>
 *
 * @brief This file provides the class definition for a URDF model
 *
 * @author Thomas Varner - <thomas.g.varner@gmail.com>
 */

#ifndef URDF_H
#define URDF_H

#include "link.h"
#include "joint.h"
#include <argos3/core/utility/math/vector3.h>
#include <argos3/core/utility/datatypes/datatypes.h>
#include <argos3/core/utility/logging/argos_log.h>
#include <argos3/core/utility/configuration/argos_configuration.h>
#include <argos3/core/utility/configuration/argos_exception.h>
#include <vector>

namespace argos {
  class CURDFModel { 
    public:
      
      // URDF contructor
      CURDFModel();

      // return link given link name
      CURDFLink& GetLink(std::string link_name);

      // return root link
      CURDFLink& GetRoot();

      // return joint given joint name
      CURDFJoint& GetJoint(std::string joint_name);

      std::string m_strName;

      std::vector<CURDFLink> m_vecLinks;

      std::vector<CURDFJoint> m_vecJoints;
  };
}

#endif