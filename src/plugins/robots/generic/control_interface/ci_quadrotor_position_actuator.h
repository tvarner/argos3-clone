/**
 * @file <argos3/plugins/robots/generic/control_interface/ci_quadrotor_position_actuator.h>
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#ifndef CI_QUADROTOR_POSITION_ACTUATOR_H
#define CI_QUADROTOR_POSITION_ACTUATOR_H

/* To avoid dependency problems when including */
namespace argos {
   class CCI_QuadRotorPositionActuator;
}

#include <argos3/core/control_interface/ci_actuator.h>
#include <argos3/core/utility/math/vector3.h>
#include <argos3/core/utility/math/quaternion.h>

namespace argos {

   class CCI_QuadRotorPositionActuator : public CCI_Actuator {

   public:

      virtual ~CCI_QuadRotorPositionActuator() {}

      /**
       * Sets the absolute position of the robot in the environment.
       * @param c_pos The desired position.
       */
      virtual void SetPosition(const CVector3& c_pos) = 0;

      /**
       * Sets the absolute yaw of the robot in the world.
       * @param c_orient The desired yaw.
       */
      virtual void SetYaw(const CRadians& c_yaw) = 0;

#ifdef ARGOS_WITH_LUA
      virtual void CreateLuaState(lua_State* pt_lua_state);
#endif

   };

}

#endif