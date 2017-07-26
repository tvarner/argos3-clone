/**
 * @file <argos3/core/utility/configuration/command_line_arg_parser.cpp>
 *
 * @author Thomas Varner- <thomas.g.varner@gmail.com>
 */

#include "model.h"

namespace argos {

  /****************************************/
  /****************************************/

  CURDFModel::CURDFModel() : {

    // SetRootLink();
  }

  CURDFLink& CURDFModel::GetLink(std::string link_name) { 
    for (int i = 0; i < m_vecLinks.size(); i++) {
      if (m_vecLinks[i].m_strName == link_name) {
        return m_vecLinks[i];
      }
    };
    
    // either throw error or log a not found warning
    THROW_ARGOSEXCEPTION("Link not found ");
  }

  CURDFJoint& CURDFModel::GetJoint(std::string joint_name) { 
    for (int i = 0; i < m_vecJoints.size(); i++) {
      if (m_vecJoints[i].m_strName == joint_name) {
        return m_vecJoints[i];
      }
    };

    // either throw error or log a not found warning
    THROW_ARGOSEXCEPTION("Joint not found ");
  }

  // @todo:
  void InitRoot() {
    // iterate through joints
    for (int i = 0; i < m_vecJoints.size(); i++) {

      CURDFLink& parent_link = GetLink(m_vecJoints[i].m_strParent);
      
    }
  };

  CURDFLink& getRootLink() {

  };
}
