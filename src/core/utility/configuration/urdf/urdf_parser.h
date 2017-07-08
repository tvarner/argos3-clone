/**
 * @file <argos3/core/utility/configuration/[some path].h>
 *
 * @brief This file provides the class definition for a URDF link
 *
 * @author Thomas Varner - <thomas.g.varner@gmail.com>
 */

#ifndef URDF_PARSER_H
#define URDF_PARSER_H

#include <argos3/core/utility/logging/argos_log.h>
#include <argos3/core/utility/configuration/argos_configuration.h>
#include <argos3/core/utility/configuration/urdf/model.h>
#include <argos3/core/utility/string_utilities.h>
#include <argos3/core/utility/datatypes/datatypes.h>
#include <argos3/core/utility/configuration/argos_exception.h>
#include <string>

namespace argos {
  class CURDFParser { 

  public: 
    CURDFParser();

    CURDFModel ParseURDF(TConfigurationNode& c_robot_node);

    void ParseLinks(CURDFModel& c_robot_model, TConfigurationNode& c_robot_node);

    void ParseJoints(CURDFModel& c_robot_model, TConfigurationNode& c_robot_node);

    CURDFLink ParseLink(TConfigurationNode& c_link_node);

    void ParseLinkInertial(CURDFLink& c_link, TConfigurationNode& c_link_node);

    void ParseLinkVisual(CURDFLink& c_link, TConfigurationNode& c_link_node);

    void ParseLinkCollision(CURDFLink& c_link, TConfigurationNode& c_link_node);

    void ParseLinkVisualGeometry(CURDFLink& c_link, TConfigurationNode& geometry_node);

    void ParseLinkCollisionGeometry(CURDFLink& c_link, TConfigurationNode& geometry_node);

    CURDFJoint ParseJoint(TConfigurationNode& joint_node);
  };
}

#endif