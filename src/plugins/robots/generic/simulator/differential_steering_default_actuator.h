/**
 * @file <argos3/plugins/simulator/actuators/differential_steering_default_actuator.h>
 *
 * @author Carlo Pinciroli - <ilpincy@gmail.com>
 */

#ifndef DIFFERENTIAL_STEERING_ACTUATOR_DEFAULT_H
#define DIFFERENTIAL_STEERING_ACTUATOR_DEFAULT_H

#include <string>
#include <map>

namespace argos {
   class CDifferentialSteeringDefaultActuator;
}

#include <argos3/plugins/robots/generic/control_interface/ci_differential_steering_actuator.h>
#include <argos3/core/simulator/actuator.h>
#include <argos3/plugins/simulator/entities/wheeled_entity.h>
#include <argos3/core/simulator/entity/composable_entity.h>
#include <argos3/core/utility/math/rng.h>

namespace argos {

   class CDifferentialSteeringDefaultActuator : public CSimulatedActuator,
                                                public CCI_DifferentialSteeringActuator {

   public:

      enum DIFFERENTIAL_STEERING {
         LEFT_WHEEL = 0,
         RIGHT_WHEEL = 1
      };

   public:

      /**
       * @brief Constructor.
       */
      CDifferentialSteeringDefaultActuator();

      /**
       * @brief Destructor.
       */
      virtual ~CDifferentialSteeringDefaultActuator() {}

      virtual void SetRobot(CComposableEntity& c_entity);

      virtual void Init(TConfigurationNode& t_tree);

      /**
       * @brief Sets the linear velocity of the two steering.
       * Velocities are expressed in cm per second.
       *
       * @param f_left_velocity desired left wheel velocity.
       * @param f_right_velocity desired right wheel velocity.
       */
      virtual void SetLinearVelocity(Real f_left_velocity,
                                     Real f_right_velocity);

      virtual void Update();

      virtual void Reset();

   protected:

      /** Adds noise to the steering velocity */
      virtual void AddGaussianNoise();

   protected:

      CWheeledEntity* m_pcWheeledEntity;
      
      /** Random number generator */
      CRandom::CRNG* m_pcRNG;
      
      /** Noise parameters, at the moment noise is Gaussian */
      Real m_fNoiseStdDeviation;

   };

}

#endif
