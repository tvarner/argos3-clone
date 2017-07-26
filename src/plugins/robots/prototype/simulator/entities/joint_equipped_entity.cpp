/**
 * @file <argos3/plugins/robots/prototype/simulator/entities/joint_equipped_entity.cpp>
 *
 * @author Michael Allwright - <allsey87@gmail.com>
 */

#include "joint_equipped_entity.h"

namespace argos {

   /****************************************/
   /****************************************/

    CJointEquippedEntity::CJointEquippedEntity(CComposableEntity* pc_parent) :
      CComposableEntity(pc_parent) {}

    /****************************************/
    /****************************************/

    CJointEquippedEntity::CJointEquippedEntity(CComposableEntity* pc_parent,
                                          const std::string& str_id) :
      CComposableEntity(pc_parent, str_id) {}

    CJointEquippedEntity::CJointEquippedEntity(CComposableEntity* pc_parent,
                                          const std::string& str_id,
                                          CURDFModel urdf,
                                          CLinkEquippedEntity* linkEquippedEntity) :
      CComposableEntity(pc_parent, str_id) {

      /*
      * Init joints and add them to this component
      */
      for (UInt32 i = 0; i < urdf.m_vecJoints.size(); i++) {
        CJointEntity* pcJointEntity = new CJointEntity(this, 
                                                    &urdf.m_vecJoints[i].m_strName, 
                                                    false);
        pcJointEntity->Init(&urdf.m_vecJoints[i], linkEquippedEntity);
        AddComponent(pcJointEntity);
        m_tJoints.push_back(pcJointEntity);
      }
    }

   /****************************************/
   /****************************************/

   void CJointEquippedEntity::Init(TConfigurationNode& t_tree) {
      try {
         /* Init parent */
         CComposableEntity::Init(t_tree);

         /* Get a reference to the body equipped entity */
         //CBodyEquippedEntity& cBodyEquippedEntity = GetParent().GetComponent<CBodyEquippedEntity>("bodies");

         /* Go through the joints */
         TConfigurationNodeIterator itJoint("joint");
         for(itJoint = itJoint.begin(&t_tree);
             itJoint != itJoint.end();
             ++itJoint) {
           
            CJointEntity* pcJointEntity = new CJointEntity(this);
            pcJointEntity->Init(*itJoint);
            AddComponent(*pcJointEntity);
            m_tJoints.push_back(pcJointEntity);
         }
      }
      catch(CARGoSException& ex) {
         THROW_ARGOSEXCEPTION_NESTED("Failed to initialize joint equipped entity \"" << GetId() << "\".", ex);
      }
   }

   /****************************************/
   /****************************************/

   void CJointEquippedEntity::Reset() {
      for(CJointEntity::TList::iterator it = m_tJoints.begin();
          it != m_tJoints.end();
          ++it) {
         (*it)->Reset();
      }
   }

   /****************************************/
   /****************************************/
   /*
   void CJointEquippedEntity::AddJoint(CFrameEntity::TList tFrames,
                                       bool b_disable_collisions) {

      CJointEntity* pcJoint =
         new CJointEntity(
            this,
            GetId() + ".joint[" + ToString(m_tJoints.size()) + "]");
      m_tJoints.push_back(pcJoint);
      fprintf(stderr, "adding joint %s\n", pcJoint->GetId().c_str());
      AddComponent(*pcJoint);
     
   }
   */
   /****************************************/
   /****************************************/

   CJointEntity& CJointEquippedEntity::GetJoint(UInt32 un_index) {
      ARGOS_ASSERT(un_index < m_tJoints.size(),
                   "CJointEquippedEntity::GetJoint(), id=\"" <<
                   GetId() <<
                   "\": index out of bounds: un_index = " <<
                   un_index <<
                   ", m_tJoints.size() = " <<
                   m_tJoints.size());
      return *m_tJoints[un_index];
   }

   /****************************************/
   /****************************************/

   void CJointEquippedEntity::UpdateComponents() {}

   /****************************************/
   /****************************************/

   void CJointEquippedEntity::SetJointPosition(UInt32 un_index,
                           const CVector3& c_position);

    void CJointEquippedEntity::SetJointOrientation(UInt32 un_index,
                              const CQuaternion& c_orientation);   

   /****************************************/
   /****************************************/

   REGISTER_STANDARD_SPACE_OPERATIONS_ON_COMPOSABLE(CJointEquippedEntity);

   /****************************************/
   /****************************************/

}