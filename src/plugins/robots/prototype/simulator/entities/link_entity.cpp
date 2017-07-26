/**
 * @file <argos3/plugins/robots/prototype/simulator/entities/body_entity.cpp>
 *
 * @author Michael Allwright - <allsey87@gmail.com>
 */

#include "link_entity.h"

#include <argos3/plugins/robots/prototype/utility/box_geometry3.h>
#include <argos3/plugins/robots/prototype/utility/cylinder_geometry3.h>
#include <argos3/plugins/robots/prototype/utility/sphere_geometry3.h>
#include <argos3/core/utility/math/angles.h>

namespace argos {

   /****************************************/
   /****************************************/

   CLinkEntity::CLinkEntity(CComposableEntity* pc_parent) :
      CComposableEntity(pc_parent),
      m_pcPositionalEntity(NULL),
      m_pcOffsetPositionalEntity(NULL),
      m_pcGeometry(NULL),
      m_fMass(0.0f) {}

   CLinkEntity::CLinkEntity(CComposableEntity* pc_parent,
                           const std::string strId) :
      CComposableEntity(pc_parent, strId),
      m_pcPositionalEntity(NULL),
      m_pcOffsetPositionalEntity(NULL),
      m_pcGeometry(NULL),
      m_fMass(0.0f) {}

   /****************************************/
   /****************************************/

   // Assumes that CLinkEntity::CLinkEntity(CComposableEntity* pc_parent,const std::string strId)
   // is called, so there is no need to initialize composable entity in this method 
   void CLinkEntity::Init(CURDFLink& link, urdf) {
      // @todo implement Init(TConfigurationNode& t_tree) method from link
      try { 
         // init positional
         CQuaternion cOrientation = new CQuaternion(link.m_sVisual.m_sOrigin.m_cRPY.GetX()
                                          link.m_sVisual.m_sOrigin.m_cRPY.GetY(),
                                          link.m_sVisual.m_sOrigin.m_cRPY.GetZ());
         m_pcPositionalEntity = CPositionalEntity(this,
                        link.m_strName + "_origin",
                        link.m_sVisual.m_sOrigin.m_cXYZ,
                        cOrientation);

         // init geometry
         m_pcGeometry = link.m_pcGeometry;

         // init mass
         m_fMass = link.m_sInertial.m_fMass;

         // init offset position and orientation
         CVector3 cOffsetPosition;
         CQuaternion cOffsetOrientation;
         if (link.m_strParentJoint != "") {
            cOffsetPosition = urdf.GetJoint(link.m_strParentJoint).m_sOrigin.m_cXYZ;
            cOffsetOrientation.SetX(urdf.GetJoint(link.m_strParentJoint).m_sOrigin.m_cRPY.GetX());
            cOffsetOrientation.SetY(urdf.GetJoint(link.m_strParentJoint).m_sOrigin.m_cRPY.GetY());
            cOffsetOrientation.SetZ(urdf.GetJoint(link.m_strParentJoint).m_sOrigin.m_cRPY.GetZ());
         }
         m_pcOffsetPositionalEntity = CPositionalEntity(this,
                        link.m_strName + "_offset_origin",
                        cOffsetPosition,
                        cOffsetOrientation);
      }
      catch(CARGoSException& ex) {
         THROW_ARGOSEXCEPTION_NESTED("Error while initializing Link entity", ex);
      }
   }

   /****************************************/
   /****************************************/

   //@todo Is this method to be provided? remove/implement
   void CLinkEntity::Init(TConfigurationNode& t_tree) {
      try {
         /* Init parent */
         CComposableEntity::Init(t_tree);

         /* just use the default initialisation method for the positional entity
          * as the position will be driven directly from a physics engine */
         m_pcPositionalEntity = new CPositionalEntity(this);
         AddComponent(*m_pcPositionalEntity);
         if(NodeExists(t_tree, "coordinates")) {
            m_pcPositionalEntity->Init(GetNode(t_tree, "coordinates"));
         }

         /* Parse Link attributes */ 
         std::string strLinkGeometry;
         GetNodeAttribute(t_tree, "geometry", strLinkGeometry);
         if(strLinkGeometry == "box") {
            /* requested geometry is a box*/
            CVector3 cSize;
            GetNodeAttribute(t_tree, "size", cSize);
            m_pcGeometry = new CBoxGeometry3(cSize);
         } else if(strLinkGeometry == "cylinder") {
            /* requested geometry is a cylinder */
            Real fHeight, fRadius;
            GetNodeAttribute(t_tree, "height", fHeight);
            GetNodeAttribute(t_tree, "radius", fRadius);
            m_pcGeometry = new CCylinderGeometry3(fRadius, fHeight);
         } else if(strLinkGeometry == "sphere") {
            /* requested geometry is a sphere */
            Real fRadius;
            GetNodeAttribute(t_tree, "radius", fRadius);
            m_pcGeometry = new CSphereGeometry3(fRadius);
         } else {
            /* requested geometry is unknown */
            THROW_ARGOSEXCEPTION("Unknown geometry type " << strLinkGeometry << " provided");
         }

         GetNodeAttribute(t_tree, "mass", m_fMass);
         m_pcOffsetPositionalEntity = new CPositionalEntity(this);
         AddComponent(*m_pcOffsetPositionalEntity);
         if(NodeExists(t_tree, "offset")) {
            m_pcOffsetPositionalEntity->Init(GetNode(t_tree, "offset"));
         }
      }
      catch(CARGoSException& ex) {
         THROW_ARGOSEXCEPTION_NESTED("Error while initializing Link entity", ex);
      }
   }

   /****************************************/
   /****************************************/

   void CLinkEntity::Reset() {
      CComposableEntity::Reset();
   }

   /****************************************/
   /****************************************/

   void CLinkEntity::Destroy() {
      CComposableEntity::Destroy();
      delete m_pcGeometry;
   }

   /****************************************/
   /****************************************/

   void CLinkEntity::UpdateComponents() {}

   /****************************************/
   /****************************************/

   REGISTER_STANDARD_SPACE_OPERATIONS_ON_COMPOSABLE(CLinkEntity);

   /****************************************/
   /****************************************/

}