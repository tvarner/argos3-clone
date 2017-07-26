/**
 * @file <argos3/plugins/robots/prototype/simulator/entities/link_equipped_entity.cpp>
 *
 * @author Michael Allwright - <allsey87@gmail.com>
 * @author Thomas Varner - <thomas.g.varner@gmail.com>
 */

#include "link_equipped_entity.h"

namespace argos {

   /****************************************/
   /****************************************/

   CLinkEquippedEntity::CLinkEquippedEntity(CComposableEntity* pc_parent) :
      CComposableEntity(pc_parent) {}

   /****************************************/
   /****************************************/

   CLinkEquippedEntity::CLinkEquippedEntity(CComposableEntity* pc_parent,
                                          const std::string& str_id) :
      CComposableEntity(pc_parent, str_id) {}

   /****************************************/
   /****************************************/

    CLinkEquippedEntity::CLinkEquippedEntity(CComposableEntity* pc_parent,
                                          const std::string& str_id,
                                          CURDFModel& urdf) : 
      CComposableEntity(pc_parent, str_id) {

      /*
      * Init links and add them to this component
      */
      for (UInt32 i = 0; i < urdf.m_vecLinks.size(); i++) { 
        CLinkEntity* pcLinkEntity = new CLinkEntity(this, 
                                      urdf.m_vecLinks[i].m_strName);
        AddComponent(pcLinkEntity);
        pcLinkEntity->Init(urdf.m_vecLinks[i], urdf);
        m_tLinks.push_back(pcLinkEntity);
      }
    }


   /****************************************/
   /****************************************/

   void CLinkEquippedEntity::Init(TConfigurationNode& t_tree) {
      try {
         /* Init parent */
         CComposableEntity::Init(t_tree);

         TConfigurationNodeIterator itLink("link");
         for(itLink = itLink.begin(&t_tree);
             itLink != itLink.end();
             ++itLink) {
            
            CLinkEntity* pcLinkEntity = new CLinkEntity(this);
            pcLinkEntity->Init(*itLink);
            AddComponent(*pcLinkEntity);
            m_tLinks.push_back(pcLinkEntity);
         }
      }
      catch(CARGoSException& ex) {
         THROW_ARGOSEXCEPTION_NESTED("Failed to initialize link equipped entity \"" << GetId() << "\".", ex);
      }
   }

   /****************************************/
   /****************************************/

   void CLinkEquippedEntity::Reset() {
      for(CLinkEntity::TList::iterator it = m_tLinks.begin();
          it != m_tLinks.end();
          ++it) {
         (*it)->Reset();
      }
   }

   /****************************************/
   /****************************************/

   /*
   void CLinkEquippedEntity::AddLink(const CVector3& c_offset_position,
                                     const CQuaternion& c_offset_orientation,
                                     const CVector3& c_size,
                                     Real f_mass) {
      CLinkEntity* pcLink =
         new CLinkEntity(
            this,
            "link_" + ToString(m_tLinks.size()),
            c_offset_position,
            c_offset_orientation,
            c_size,
            f_mass);
      m_tLinks.push_back(pcLink);
      fprintf(stderr, "adding link %s\n", pcLink->GetId().c_str());
      AddComponent(*pcLink);
   }
   */

   /****************************************/
   /****************************************/

   CLinkEntity& CLinkEquippedEntity::GetLink(UInt32 un_index) {
      ARGOS_ASSERT(un_index < m_tLinks.size(),
                   "CLinkEquippedEntity::GetLink(), id=\"" <<
                   GetId() <<
                   "\": index out of bounds: un_index = " <<
                   un_index <<
                   ", m_tLinks.size() = " <<
                   m_tLinks.size());
      return *m_tLinks[un_index];
   }

   /****************************************/
   /****************************************/

   void CLinkEquippedEntity::UpdateComponents() {}

   /****************************************/
   /****************************************/

   REGISTER_STANDARD_SPACE_OPERATIONS_ON_COMPOSABLE(CLinkEquippedEntity);

   /****************************************/
   /****************************************/

}