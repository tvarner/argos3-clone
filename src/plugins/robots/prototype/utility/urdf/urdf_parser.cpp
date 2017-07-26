/**
 * @file <argos3/core/utility/configuration/command_line_arg_parser.cpp>
 *
 * @author Thomas Varner- <thomas.g.varner@gmail.com>
 */

#include "urdf_parser.h"

namespace argos {

	/****************************************/
	/****************************************/

	CURDFParser::CURDFParser() {}

	CURDFModel CURDFParser::ParseURDF(TConfigurationNode& c_robot_node) {
		CURDFModel cRobotModel;

		if (NodeAttributeExists(c_robot_node, "name")) { 
			GetNodeAttribute(c_robot_node, "name", cRobotModel.m_strName); // parse link named
		} else { 
			THROW_ARGOSEXCEPTION("Robot name attribute is required ");
		}

		ParseLinks(cRobotModel, c_robot_node);
		ParseJoints(cRobotModel, c_robot_node);
		cRobotModel.InitRoot();
		return cRobotModel;
	}

	void CURDFParser::ParseLinks(CURDFModel& c_robot_model, TConfigurationNode& c_robot_node) {
		std::vector<CURDFLink> vecLinks;
c
		for ( itLinkNode = itLinkNode.begin( &c_robot_node ); itLinkNode != itLinkNode.end(); itLinkNode++ ) {

			// create link
			CURDFLink cLink = ParseLink(*itLinkNode);

			// add link to vector
			vecLinks.push_back(cLink);
		}
		c_robot_model.m_vecLinks = vecLinks;
	}

	void CURDFParser::ParseJoints(CURDFModel& c_robot_model, TConfigurationNode& c_robot_node) {
		std::vector<CURDFJoint> vecJoints;
		TConfigurationNodeIterator itJointNode("joint");
		for ( itJointNode = itJointNode.begin( &c_robot_node ); itJointNode != itJointNode.end(); itJointNode++ ) {
			// create joint
			CURDFJoint cJoint = ParseJoint(*itJointNode);
			
			// add joint to vector
			vecJoints.push_back(cJoint);
		}
		c_robot_model.m_vecJoints = vecJoints;
	}

	void CURDFParser::SetRootLink(CURDFModel& c_robot_model) { 

	}

	CURDFLink CURDFParser::ParseLink(TConfigurationNode& c_link_node) {
		// create link
		CURDFLink cLink;

		if (NodeAttributeExists(c_link_node, "name")) { 
			GetNodeAttribute(c_link_node, "name", cLink.m_strName); // parse link named
		} else { 
			THROW_ARGOSEXCEPTION("Link name attribute is required ");
		}

		ParseLinkInertial(cLink, c_link_node); // parse inertial node
		ParseLinkVisual(cLink, c_link_node); // parse visual node
		ParseLinkCollision(cLink, c_link_node);// parse collision node
		return cLink;
	}

	void CURDFParser::ParseLinkInertial(CURDFLink& c_link, TConfigurationNode& c_link_node) {
		// parse inertial
		if (NodeExists(c_link_node, "inertial")) {
			TConfigurationNode& cInertialNode = GetNode(c_link_node, "inertial");

			// parse origin
			if (NodeExists(c_link_node, "origin")) {
				TConfigurationNode& cOriginNode = GetNode(cInertialNode, "origin");

				if (NodeAttributeExists(cOriginNode, "xyz")) {
					std::string strOriginXYZ;
					GetNodeAttribute(cOriginNode, "xyz", strOriginXYZ);
					std::vector<std::string> vexXYZ;
					Tokenize(strOriginXYZ, vexXYZ);
					Real fOriginX = FromString<Real>(vexXYZ[0]);
					Real fOriginY = FromString<Real>(vexXYZ[1]);
					Real fOriginZ = FromString<Real>(vexXYZ[2]);
					c_link.m_sInertial.m_sOrigin.m_cXYZ = CVector3( fOriginX, fOriginY, fOriginZ );
				} else { 
					c_link.m_sInertial.m_sOrigin.m_cXYZ = CVector3( 0 , 0 , 0 );
				}

				if (NodeAttributeExists(cOriginNode, "rpy")) { 
					std::string strOriginRPY;
					GetNodeAttribute(cOriginNode, "rpy", strOriginRPY);
					std::vector<std::string> vecRPY;
					Tokenize(strOriginRPY, vecRPY);
					Real fOriginR = FromString<Real>(vecRPY[0]);
					Real fOriginP = FromString<Real>(vecRPY[1]);
					Real fOriginY = FromString<Real>(vecRPY[2]);
					c_link.m_sInertial.m_sOrigin.m_cRPY = CVector3( fOriginR, fOriginP, fOriginY );
				} else { 
					c_link.m_sInertial.m_sOrigin.m_cRPY = CVector3( 0 , 0 , 0 );
				}
			}

			// parse mass
			if (NodeExists(cInertialNode, "mass")) {
				TConfigurationNode& cMassNode = GetNode(cInertialNode, "mass");

				std::string strMass;
				GetNodeAttribute(cMassNode, "value", strMass);
				c_link.m_sInertial.m_fMass = FromString<Real>(strMass);
			}

			// parse inertia
			if (NodeExists(cInertialNode, "inertia")) {
				TConfigurationNode& cInertiaNode = GetNode(cInertialNode, "inertia");

				std::string strIXX;
				std::string strIXY;
				std::string strIXZ;
				std::string strIYY;
				std::string strIYZ;
				std::string strIZZ;			
				GetNodeAttribute(cInertiaNode, "ixx", strIXX);
				GetNodeAttribute(cInertiaNode, "ixy", strIXY);
				GetNodeAttribute(cInertiaNode, "ixz", strIXZ);
				GetNodeAttribute(cInertiaNode, "iyy", strIYY);
				GetNodeAttribute(cInertiaNode, "iyz", strIYZ);
				GetNodeAttribute(cInertiaNode, "izz", strIZZ);
				c_link.m_sInertial.m_sInertia.m_fIXX = FromString<Real>(strIXX);
				c_link.m_sInertial.m_sInertia.m_fIXY = FromString<Real>(strIXY);
				c_link.m_sInertial.m_sInertia.m_fIXZ = FromString<Real>(strIXZ);
				c_link.m_sInertial.m_sInertia.m_fIYY = FromString<Real>(strIYY);
				c_link.m_sInertial.m_sInertia.m_fIYZ = FromString<Real>(strIYZ);
				c_link.m_sInertial.m_sInertia.m_fIZZ = FromString<Real>(strIZZ);
			}
		}
	}

	void CURDFParser::ParseLinkVisual(CURDFLink& c_link, TConfigurationNode& c_link_node) {
		// parse visual
		if (NodeExists(c_link_node, "visual")) {
			TConfigurationNode& cVisualNode = GetNode(c_link_node, "visual");

			if (NodeExists(cVisualNode, "origin")) {
				TConfigurationNode& cOriginNode = GetNode(cVisualNode, "origin");

				if (NodeAttributeExists(cOriginNode, "xyz")) { 
					std::string strOriginXYZ;
					GetNodeAttribute(cOriginNode, "xyz", strOriginXYZ);
					std::vector<std::string> vexXYZ;
					Tokenize(strOriginXYZ, vexXYZ);
					Real fOriginX = FromString<Real>(vexXYZ[0]);
					Real fOriginY = FromString<Real>(vexXYZ[1]);
					Real fOriginZ = FromString<Real>(vexXYZ[2]);
					c_link.m_sVisual.m_sOrigin.m_cXYZ = CVector3( fOriginX, fOriginY, fOriginZ );		
				} else { 
					c_link.m_sVisual.m_sOrigin.m_cXYZ = CVector3( 0 , 0 , 0 );
				}

				if (NodeAttributeExists(cOriginNode, "rpy")) { 
					std::string strOriginRPY;
					GetNodeAttribute(cOriginNode, "rpy", strOriginRPY);
					std::vector<std::string> vecRPY;
					Tokenize(strOriginRPY, vecRPY);
					Real fOriginR = FromString<Real>(vecRPY[0]);
					Real fOriginP = FromString<Real>(vecRPY[1]);
					Real fOriginY = FromString<Real>(vecRPY[2]);
					c_link.m_sVisual.m_sOrigin.m_cRPY = CVector3( fOriginR, fOriginP, fOriginY );
				} else { 
					c_link.m_sVisual.m_sOrigin.m_cRPY = CVector3( 0 , 0 , 0 );
				}
			}

			if (NodeExists(cVisualNode, "geometry")) { 
				TConfigurationNode& cGeometryNode = GetNode(cVisualNode, "geometry");
				ParseGeometry(c_link, cGeometryNode, "visual");			
			} else { 
				THROW_ARGOSEXCEPTION("Link visual geometry is required");
			}

			if (NodeExists(cVisualNode, "material")) {
				TConfigurationNode& cMaterialNode = GetNode(cVisualNode, "material");

				// parse visual material name
				if (NodeAttributeExists(cVisualNode, "name")) { 
					GetNodeAttribute(cMaterialNode, "name", c_link.m_sVisual.m_sMaterial.m_strName);
				}

				// parse visual material color
				if (NodeExists(cVisualNode, "color")) { 
					TConfigurationNode& cColorNode = GetNode(cMaterialNode, "color");
					std::string strColor;

					if (NodeAttributeExists(cColorNode, "color")) { 
						GetNodeAttribute(cColorNode, "color", strColor);
						std::vector<std::string> vecColor;
						Tokenize(strColor, vecColor);
						c_link.m_sVisual.m_sMaterial.m_sColor.m_fR = FromString<Real>(vecColor[0]);
						c_link.m_sVisual.m_sMaterial.m_sColor.m_fG = FromString<Real>(vecColor[1]);
						c_link.m_sVisual.m_sMaterial.m_sColor.m_fB = FromString<Real>(vecColor[2]);
						c_link.m_sVisual.m_sMaterial.m_sColor.m_fA = FromString<Real>(vecColor[3]);
					}
				}

				// parse visual material texture
				if (NodeExists(cVisualNode, "texture")) { 
					TConfigurationNode& cTextureNode = GetNode(cMaterialNode, "texture");

					if (NodeAttributeExists(cTextureNode, "filename")) { 
						GetNodeAttribute(cTextureNode, "filename", c_link.m_sVisual.m_sMaterial.m_strTexture);
					}
				}
			}
		}
	}

	void CURDFParser::ParseLinkCollision(CURDFLink& c_link, TConfigurationNode& c_link_node) {
		if (NodeExists(c_link_node, "collision")) { 
			// parse collision
			TConfigurationNode& cCollisionNode = GetNode(c_link_node, "collision");

			// parse collision name
			if (NodeAttributeExists(cCollisionNode, "name")) { 
				GetNodeAttribute(c_link_node, "name", c_link.m_sCollision.m_strName);
			}

			// parse collisision origin
			if (NodeExists(cCollisionNode, "origin")) { 
				TConfigurationNode& cOriginNode = GetNode(cCollisionNode, "origin");

				if (NodeAttributeExists(cOriginNode, "xyz")) { 
					std::string strOriginXYZ;
					GetNodeAttribute(cOriginNode, "xyz", strOriginXYZ);
					std::vector<std::string> vexXYZ;
					Tokenize(strOriginXYZ, vexXYZ);
					Real fOriginX = FromString<Real>(vexXYZ[0]);
					Real fOriginY = FromString<Real>(vexXYZ[1]);
					Real fOriginZ = FromString<Real>(vexXYZ[2]);
					c_link.m_sCollision.m_sOrigin.m_cXYZ = CVector3( fOriginX, fOriginY, fOriginZ );			
				} else { 
					c_link.m_sCollision.m_sOrigin.m_cXYZ = CVector3( 0 , 0 , 0 );
				}

				if (NodeAttributeExists(cOriginNode, "rpy")) { 
					std::string strOriginRPY;
					GetNodeAttribute(cOriginNode, "rpy", strOriginRPY);
					std::vector<std::string> vecRPY;
					Tokenize(strOriginRPY, vecRPY);
					Real fOriginR = FromString<Real>(vecRPY[0]);
					Real fOriginP = FromString<Real>(vecRPY[1]);
					Real fOriginY = FromString<Real>(vecRPY[2]);
					c_link.m_sCollision.m_sOrigin.m_cRPY = CVector3( fOriginR, fOriginP, fOriginY );
				} else { 
					c_link.m_sCollision.m_sOrigin.m_cRPY = CVector3( 0 , 0 , 0 );
				}
			} else { 
				c_link.m_sCollision.m_sOrigin.m_cXYZ = CVector3( 0 , 0 , 0 );
				c_link.m_sCollision.m_sOrigin.m_cRPY = CVector3( 0 , 0 , 0 );
			}

			// parse collision geometry
			if (NodeExists(cCollisionNode, "geometry")) { 
				TConfigurationNode& cGeometryNode = GetNode(cCollisionNode, "geometry");
				ParseGeometry(c_link, cGeometryNode, "collision");	
			}
		}
	}

	void CURDFParser::ParseGeometry(CURDFLink& c_link, TConfigurationNode& c_geometry_node, std::string strType) { 
		
		// parse geometry box
		if (NodeExists(c_geometry_node, "box")) { 
			TConfigurationNode& cBoxNode = GetNode(c_geometry_node, "box");
			
			if (NodeAttributeExists(cBoxNode, "size")) { 
				std::string strBoxSize;
				GetNodeAttribute(cBoxNode, "size", strBoxSize);
				std::vector<std::string> vecSize;
				Tokenize(strBoxSize, vecSize);
				Real fSizeX = FromString<Real>(vecSize[0]);
				Real fSizeY = FromString<Real>(vecSize[1]);
				Real fSizeZ = FromString<Real>(vecSize[2]);
				CVector3 cSize = new CVector3( fSizeX, fSizeY, fSizeZ );

				if (strType == "visual") { 
					link.m_sVisual.m_cGeometry = new CBoxGeometry3(cSize);
				} else if (strType == "collision") { 
					link.m_sCollision.m_cGeometry = new CBoxGeometry3(cSize);
				} else { 
					THROW_ARGOSEXCEPTION("Invalid geometry type. Options are: 'visual' or 'collision'.")
				}
			}
		}

		// parse geometry cylinder
		if (NodeExists(c_geometry_node, "cylinder")) { 
			TConfigurationNode& cCylinderNode = GetNode(c_geometry_node, "cylinder");
			
			Real fRadius;
			Real fHeight;
			if (NodeAttributeExists(cCylinderNode, "radius")) {
				std::string strCylinderRadius;
				GetNodeAttribute(cCylinderNode, "radius", strCylinderRadius);
				fRadius = FromString<Real>(strCylinderRadius);
			}

			if (NodeAttributeExists(cCylinderNode, "length")) {
				std::string strCylinderLength;
				GetNodeAttribute(cCylinderNode, "length", strCylinderLength);
				fHeight = FromString<Real>(strCylinderLength);
			}

			if (strType == "visual") { 
				link.m_sVisual.m_cGeometry = new CCylinderGeometry3(fRadius, fHeight);
			} else if (strType == "collision") { 
				link.m_sCollision.m_cGeometry = new CCylinderGeometry3(fRadius, fHeight);
			} else { 
				THROW_ARGOSEXCEPTION("Invalid geometry type. Options are: 'visual' or 'collision'.")
			}
		}

		// parse geometry sphere
		if (NodeExists(c_geometry_node, "sphere")) { 
			TConfigurationNode& cSphereNode = GetNode(c_geometry_node, "sphere");

			Real fRadius;
			if (NodeAttributeExists(cSphereNode, "radius")) {
				std::string strSphereRadius;
				GetNodeAttribute(cSphereNode, "radius", strSphereRadius);
				fRadius = FromString<Real>(strSphereRadius);
			}

			if (strType == "visual") { 
				link.m_sVisual.m_cGeometry = new CSphereGeometry3(fRadius);
			} else if (strType == "collision") { 
				link.m_sCollision.m_cGeometry = new CSphereGeometry3(fRadius);
			} else { 
				THROW_ARGOSEXCEPTION("Invalid geometry type. Options are: 'visual' or 'collision'.")
			}
		}

		// parse geometry mesh
		if (NodeExists(c_geometry_node, "mesh")) { 
			TConfigurationNode& cMeshNode = GetNode(c_geometry_node, "mesh");

			std::string strFilename;
			Real fScale;

			if (NodeAttributeExists(cMeshNode, "filename")) { 
				GetNodeAttribute(cMeshNode, "filename", strFilename);
			}

			if (NodeAttributeExists(cMeshNode, "scale")) {
				std::string strScale;
				GetNodeAttribute(cMeshNode, "scale", strScale);
				fScale = FromString<Real>(strScale);
			}

			if (strType == "visual") { 
				link.m_sVisual.m_cGeometry = new CGeometryMeshGeometry3(strFilename, fScale);
			} else if (strType == "collision") { 
				link.m_sCollision.m_cGeometry = new CGeometryMeshGeometry3(strFilename, fScale);
			} else { 
				THROW_ARGOSEXCEPTION("Invalid geometry type. Options are: 'visual' or 'collision'.")
			}
		}
	}

	CURDFJoint CURDFParser::ParseJoint(TConfigurationNode& c_joint_node) { 
		// create joint
		CURDFJoint cJoint;

		// parse name
		if (NodeAttributeExists(c_joint_node, "name")) { 
			GetNodeAttribute(c_joint_node, "name", cJoint.m_strName);
		} else { 
			THROW_ARGOSEXCEPTION("Joint name is required");
		}

		// parse type
		if (NodeAttributeExists(c_joint_node, "type")) { 
			GetNodeAttribute(c_joint_node, "type", cJoint.m_strType);
		} else { 
			THROW_ARGOSEXCEPTION("Joint type is required");
		}

		// parse parent
		if (NodeExists(c_joint_node, "parent")) { 
			TConfigurationNode& cParentNode = GetNode(c_joint_node, "parent");

			if (NodeAttributeExists(cParentNode, "link")) { 
				GetNodeAttribute(cParentNode, "link", cJoint.m_strParent);
			}
		} else { 
			THROW_ARGOSEXCEPTION("Joint parent is required");
		}

		// parse children
		if (NodeExists(c_joint_node, "child")) { 
			TConfigurationNode& cChildNode = GetNode(c_joint_node, "child");

			if (NodeAttributeExists(cChildNode, "link")) { 
				GetNodeAttribute(cChildNode, "link", cJoint.m_strChild);
			}
		} else { 
			THROW_ARGOSEXCEPTION("Joint child is required");
		}

		// set children links on parent link, and parent link on children links
		// set parent joint on each link
		CURFLink& parentLink = urdf.GetLink(cJoint.m_strParent);
		parentLink.m_vecChildrenLinks = cJoint.m_vecChildren;
		for (int i = 0, i < parentLink.m_vecChildrenLinks.size(), i++) { 
			urdf.GetLink(parentLink.m_vecChildrenLinks[i]).m_strParentLink = parentLink.m_strName;
			urdf.GetLink(parentLink.m_vecChildrenLinks[i]).m_strParentJoint = cJoint.m_strName;
		}

		// parse joint origin
		if (NodeExists(c_joint_node, "origin")) {
			TConfigurationNode& cOriginNode = GetNode(cInertialNode, "origin");

			if (NodeAttributeExists(cOriginNode, "xyz")) {
				std::string strOriginXYZ;
				GetNodeAttribute(cOriginNode, "xyz", strOriginXYZ);
				std::vector<std::string> vexXYZ;
				Tokenize(strOriginXYZ, vexXYZ);
				Real fOriginX = FromString<Real>(vexXYZ[0]);
				Real fOriginY = FromString<Real>(vexXYZ[1]);
				Real fOriginZ = FromString<Real>(vexXYZ[2]);
				cJoint.m_sOrigin.m_cXYZ = CVector3( fOriginX, fOriginY, fOriginZ );
			} else { 
				cJoint.m_sOrigin.m_cXYZ = CVector3( 0 , 0 , 0 );
			}

			if (NodeAttributeExists(cOriginNode, "rpy")) { 
				std::string strOriginRPY;
				GetNodeAttribute(cOriginNode, "rpy", strOriginRPY);
				std::vector<std::string> vecRPY;
				Tokenize(strOriginRPY, vecRPY);
				Real fOriginR = FromString<Real>(vecRPY[0]);
				Real fOriginP = FromString<Real>(vecRPY[1]);
				Real fOriginY = FromString<Real>(vecRPY[2]);
				cJoint.m_sOrigin.m_cRPY = CVector3( fOriginR, fOriginP, fOriginY );
			} else { 
				cJoint.m_sOrigin.m_cRPY = CVector3( 0 , 0 , 0 );
			}
		}		

		// parse axis node
		if (NodeExists(c_joint_node, "axis")) { 
			TConfigurationNode& cAxisNode = GetNode(c_joint_node, "axis");

			if (NodeAttributeExists(cAxisNode, "xyz")) { 
				std::string strAxisXYZ;
				GetNodeAttribute(cAxisNode, "xyz", strAxisXYZ);

				std::vector<std::string> vexXYZ;
				Tokenize(strAxisXYZ, vexXYZ);
				Real fOriginX = FromString<Real>(vexXYZ[0]);
				Real fOriginY = FromString<Real>(vexXYZ[1]);
				Real fOriginZ = FromString<Real>(vexXYZ[2]);
				cJoint.m_sAxis.m_cXYZ = CVector3( fOriginX, fOriginY, fOriginZ );
			} else { 
				THROW_ARGOSEXCEPTION("Joint axis xyz is required");
			}
		}

		// parse calibration node
		if (NodeExists(c_joint_node, "calibration")) {
			TConfigurationNode& cCalibrationNode = GetNode(c_joint_node, "calibration");


			if (NodeAttributeExists(cCalibrationNode, "rising")) { 
				std::string strCalibrationRising;
				GetNodeAttribute(cCalibrationNode, "rising", strCalibrationRising);
				cJoint.m_sCalibration.m_fRising = FromString<Real>(strCalibrationRising);
			}

			if (NodeAttributeExists(cCalibrationNode, "falling")) { 
				std::string strCalibrationFalling;
				GetNodeAttribute(cCalibrationNode, "falling", strCalibrationFalling);
				cJoint.m_sCalibration.m_fFalling = FromString<Real>(strCalibrationFalling);
			}
		}

		// parse dynamics node
		if (NodeExists(c_joint_node, "dynamics")) {
			TConfigurationNode& cDynamicsNode = GetNode(c_joint_node, "dynamics");

			if (NodeAttributeExists(cDynamicsNode, "damping")) { 
				std::string strDynamicsDamping;
				GetNodeAttribute(cDynamicsNode, "damping", strDynamicsDamping);
				cJoint.m_sDynamics.m_fDamping = FromString<Real>(strDynamicsDamping);
			}

			if (NodeAttributeExists(cDynamicsNode, "friction")) { 
				std::string strDynamicsFriction;
				GetNodeAttribute(cDynamicsNode, "friction", strDynamicsFriction);
				cJoint.m_sDynamics.m_fFriction = FromString<Real>(strDynamicsFriction);
			}
		}

		// parse limit node
		if (NodeExists(c_joint_node, "limit")) { 
			TConfigurationNode& cLimitNode = GetNode(c_joint_node, "limit");

			if (NodeAttributeExists(cLimitNode, "effort")) { 
				std::string strDynamicsEffort;
				GetNodeAttribute(cLimitNode, "effort", strDynamicsEffort);
				cJoint.m_sLimit.m_fEffort = FromString<Real>(strDynamicsEffort);
			} else { 
				THROW_ARGOSEXCEPTION("Effort is required for joint limit");
			}

			if (NodeAttributeExists(cLimitNode, "velocity")) { 
				std::string strDynamicsVelocity;
				GetNodeAttribute(cLimitNode, "velocity", strDynamicsVelocity);
				cJoint.m_sLimit.m_fVelocity = FromString<Real>(strDynamicsVelocity);
			} else { 
				THROW_ARGOSEXCEPTION("Velocity is required for joint limit");
			}

			if (NodeAttributeExists(cLimitNode, "lower")) { 
				std::string strDynamicsLower;
				GetNodeAttribute(cLimitNode, "lower", strDynamicsLower);
				cJoint.m_sLimit.m_fLower = FromString<Real>(strDynamicsLower);
			}

			if (NodeAttributeExists(cLimitNode, "upper")) { 
				std::string strDynamicsUpper;
				GetNodeAttribute(cLimitNode, "upper", strDynamicsUpper);
				cJoint.m_sLimit.m_fUpper = FromString<Real>(strDynamicsUpper);
			}
		} else if (cJoint.m_strType == "prismatic" || cJoint.m_strType == "revolute") { 
			THROW_ARGOSEXCEPTION("Limit is required for prismatic and revolute joints");
		}

		// parse mimic node
		if (NodeExists(c_joint_node, "mimic")) { 
			TConfigurationNode& cMimicNode = GetNode(c_joint_node, "mimic");

			if (NodeAttributeExists(cMimicNode, "joint")) { 
				GetNodeAttribute(cMimicNode, "joint", cJoint.m_sMimic.m_strJoint);
			} else { 
				THROW_ARGOSEXCEPTION("Joint name is required for joint mimic");
			}

			if (NodeAttributeExists(cMimicNode, "multiplier")) { 
				std::string strMultiplier;
				GetNodeAttribute(cMimicNode, "multiplier", strMultiplier);
				cJoint.m_sMimic.m_fMultiplier = FromString<Real>(strMultiplier);
			}

			if (NodeAttributeExists(cMimicNode, "offset")) { 
				std::string strOffset;
				GetNodeAttribute(cMimicNode, "offset", strOffset);
				cJoint.m_sMimic.m_fOffset = FromString<Real>(strOffset);
			}
		}

		// parse safety controller node
		if (NodeExists(c_joint_node, "safety_controller")) { 
			TConfigurationNode& cSafetyController = GetNode(c_joint_node, "safety_controller");

			if (NodeAttributeExists(cSafetyController, "k_velocity")) { 
				std::string strKVelocity;
				GetNodeAttribute(cSafetyController, "k_velocity", strKVelocity);
				cJoint.m_sSafetyController.m_fKVelocity = FromString<Real>(strKVelocity);
			} else { 
				THROW_ARGOSEXCEPTION("K velocity is required for joint safety controller");
			}

			if (NodeAttributeExists(cSafetyController, "soft_lower_limit")) {
				std::string strSoftLowerLimit;
				GetNodeAttribute(cSafetyController, "soft_lower_limit", strSoftLowerLimit);
				cJoint.m_sSafetyController.m_fSoftLowerLimit = FromString<Real>(strSoftLowerLimit);
			}

			if (NodeAttributeExists(cSafetyController, "soft_upper_limit")) {
				std::string strSoftUpperLimit;
				GetNodeAttribute(cSafetyController, "soft_upper_limit", strSoftUpperLimit);
				cJoint.m_sSafetyController.m_fSoftUpperLimit = FromString<Real>(strSoftUpperLimit);
			}

			if (NodeAttributeExists(cSafetyController, "k_position")) {
				std::string strKPosition;
				GetNodeAttribute(cSafetyController, "k_position", strKPosition);
				cJoint.m_sSafetyController.m_fKPosition = FromString<Real>(strKPosition);
			}
		}

		return cJoint;
	}
}