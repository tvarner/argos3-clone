/**
 * @file <argos3/plugins/robots/prototype/simulator/entities/prototype_entity.cpp>
 *
 * @author Michael Allwright - <allsey87@gmail.com>
 */

#include "prototype_entity.h"

#include <argos3/plugins/robots/prototype/simulator/entities/link_equipped_entity.h>
#include <argos3/plugins/robots/prototype/simulator/entities/joint_equipped_entity.h>

#include <argos3/plugins/robots/prototype/simulator/entities/prototype_proximity_sensor_equipped_entity.h>
#include <argos3/plugins/robots/prototype/simulator/entities/prototype_led_equipped_entity.h>
#include <argos3/plugins/robots/prototype/simulator/entities/camera_equipped_entity.h>
#include <argos3/plugins/robots/prototype/simulator/entities/electromagnet_equipped_entity.h>
#include <argos3/plugins/robots/prototype/simulator/entities/tag_equipped_entity.h>
#include <argos3/plugins/robots/prototype/simulator/entities/radio_equipped_entity.h>

#include <argos3/plugins/robots/prototype/simulator/media/tag_medium.h>
#include <argos3/plugins/simulator/media/led_medium.h>

#include <argos3/core/simulator/space/space.h>
//#include <argos3/core/simulator/entity/controllable_entity.h>
#include <argos3/core/simulator/entity/embodied_entity.h>
#include <argos3/core/simulator/simulator.h>

namespace argos {

   /****************************************/
   /****************************************/

   CPrototypeEntity::CPrototypeEntity() :
      CComposableEntity(NULL),
      m_pcControllableEntity(NULL),
      m_pcEmbodiedEntity(NULL),
      m_pcLinkEquippedEntity(NULL),
      m_pcJointEquippedEntity(NULL) {}

   /****************************************/
   /****************************************/

   void CPrototypeEntity::Init(TConfigurationNode& t_tree) {
      try {
         /*
          * Init parent
          */
         CComposableEntity::Init(t_tree);

         // get value of t_tree
         // if value === 'robot', parse URDF, otherwise continue normal implemenation
         if (t_tree->Value() == "robot") { 
          InitURDF(t_tree);
         } else { 
         /*
          * Init parent
          */
         CComposableEntity::Init(t_tree);

         /*
          * Create and init components
          */
         /* Embodied entity */
         m_pcEmbodiedEntity = new CEmbodiedEntity(this);
         AddComponent(*m_pcEmbodiedEntity);
         m_pcEmbodiedEntity->Init(GetNode(t_tree, "body"));

         m_pcLinkEquippedEntity = new CLinkEquippedEntity(this);
         AddComponent(*m_pcLinkEquippedEntity);
         if(NodeExists(t_tree, "links")) {
            m_pcLinkEquippedEntity->Init(GetNode(t_tree, "links"));
         }
/*
         m_pcJointEquippedEntity = new CJointEquippedEntity(this);
         AddComponent(*m_pcJointEquippedEntity);
         if(NodeExists(t_tree, "joints")) {
            m_pcJointEquippedEntity->Init(GetNode(t_tree, "joints"));
         }
*/
         if(NodeExists(t_tree, "devices")) {
            TConfigurationNodeIterator itDevice;
            for(itDevice = itDevice.begin(&GetNode(t_tree, "devices"));
                itDevice != itDevice.end();
                ++itDevice) {

               if(itDevice->Value() == "rangefinders") {
                  CProximitySensorEquippedEntity* m_pcEquippedEntity =
                     new CProximitySensorEquippedEntity(this);
                  m_pcEquippedEntity->Init(*itDevice);
                  AddComponent(*m_pcEquippedEntity);
               }
               else if(itDevice->Value() == "leds" ) {
                  CLEDEquippedEntity* m_pcEquippedEntity =
                     new CLEDEquippedEntity(this);
                  m_pcEquippedEntity->Init(*itDevice);
                  /* Add the LEDs to the specified medium */
                  std::string strMedium;
                  GetNodeAttribute(*itDevice, "medium", strMedium);
                  m_pcEquippedEntity->AddToMedium(CSimulator::GetInstance().GetMedium<CLEDMedium>(strMedium));
                  AddComponent(*m_pcEquippedEntity);
               }
/*
               else if(itDevice->Value() == "cameras" ) {
                  CCameraEquippedEntity* m_pcEquippedEntity =
                     new CCameraEquippedEntity(this);
                  m_pcEquippedEntity->Init(*itDevice);
                  AddComponent(*m_pcEquippedEntity);
               }
               else if(itDevice->Value() == "electromagnets" ) {
                  CElectromagnetEquippedEntity* m_pcEquippedEntity =
                     new CElectromagnetEquippedEntity(this);
                  m_pcEquippedEntity->Init(*itDevice);
                  AddComponent(*m_pcEquippedEntity);
               }
               else if(itDevice->Value() == "tags" ) {
                  CTagEquippedEntity* m_pcEquippedEntity =
                     new CTagEquippedEntity(this);
                  m_pcEquippedEntity->Init(*itDevice);
                  std::string strMedium;
                  GetNodeAttribute(*itDevice, "medium", strMedium);
                  m_pcEquippedEntity->AddToMedium(CSimulator::GetInstance().GetMedium<CTagMedium>(strMedium));
                  AddComponent(*m_pcEquippedEntity);
               }
               else if(itDevice->Value() == "radios" ) {
                  CRadioEquippedEntity* m_pcEquippedEntity =
                     new CRadioEquippedEntity(this);
                  m_pcEquippedEntity->Init(*itDevice);
                  AddComponent(*m_pcEquippedEntity);
               }
*/
               else {
THROW_ARGOSEXCEPTION("Attempt to add unimplemented device type \"" << itDevice->Value() << "\".");
               }
            }
         }

         /* Controllable entity
            It must be the last one, for actuators/sensors to link to composing entities correctly */
         if(NodeExists(t_tree, "controller")) {
            m_pcControllableEntity = new CControllableEntity(this);
            AddComponent(*m_pcControllableEntity);
            m_pcControllableEntity->Init(GetNode(t_tree, "controller"));
         }
         /* Update components */
         UpdateComponents();
         }
      }
      catch(CARGoSException& ex) {
         THROW_ARGOSEXCEPTION_NESTED("Failed to initialize entity \"" << GetId() << "\".", ex);
      }
   }

   void CPrototypeEntity::InitURDF(CURDFModel& urdf) {
    try {
      CURDFParser urdf_parser;
      CURDFModel urdf = urdf_parser.ParseURDF(t_tree);

      // init embodied entity
      m_pcEmbodiedEntity = new CEmbodiedEntity(this,
                                urdf.m_strName,
                                &urdf.getRootLink().m_cPosition, // CVector3
                                &urdf.getRootLink().m_cOrientation, // Quaternion
                                true);

      // init link equipped entity
        // no need to call m_pcLinkEquippedEntity->Init(t_tree)
      m_pcLinkEquippedEntity = new CLinkEquippedEntity(this, 
                                urdf.m_strName + "_links", 
                                urdf);
      AddComponent(*m_pcLinkEquippedEntity);

      // init joint equipped entity
        // no need to call m_pcJointEquippedEntity->Init(t_tree)
      m_pcJointEquippedEntity = new CJointEquippedEntity(this, 
                                urdf.m_strName + "_joints", 
                                urdf,
                                m_pcLinkEquippedEntity);
      AddComponent(*m_pcJointEquippedEntity);

      // @todo: initialize devices

      // @todo: initialize controller entity

      // update components
      UpdateComponents();
    }
    catch(CARGoSException& ex) {
      THROW_ARGOSEXCEPTION_NESTED("Failed to initialize entity \"" << GetId() << "\".", ex);
    }
   }

   /****************************************/
   /****************************************/

   void CPrototypeEntity::Reset() {
      /* Reset all components */
      CComposableEntity::Reset();
      /* Update components */
      UpdateComponents();
   }

   /****************************************/
   /****************************************/

   void CPrototypeEntity::Destroy() {
      CComposableEntity::Destroy();
   }

   /****************************************/
   /****************************************/

   void CPrototypeEntity::UpdateComponents() {
      CComposableEntity::UpdateComponents();
   }

   TConfigurationNode& CPrototypeEntity::GetRoot(TConfigurationNode& t_tree) {

   }

   /****************************************/
   /****************************************/

   REGISTER_ENTITY(CPrototypeEntity,
                   "prototype",
                   "1.0",
                   "Michael Allwright [allsey87@gmail.com]",
                   "A generic physics engine driven, configurable implementation of a prototype",
                   "[long description]",
                   "Under development"
   );

   /****************************************/
   /****************************************/

   REGISTER_STANDARD_SPACE_OPERATIONS_ON_COMPOSABLE(CPrototypeEntity);

   /****************************************/
   /****************************************/
}