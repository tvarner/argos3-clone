#!/bin/sh

export ARGOS_PLUGIN_PATH=/Users/tvarner/Documents/argos3/core:/Users/tvarner/Documents/argos3/testing:/Users/tvarner/Documents/argos3/plugins/robots/e-puck:/Users/tvarner/Documents/argos3/plugins/robots/eye-bot:/Users/tvarner/Documents/argos3/plugins/robots/foot-bot:/Users/tvarner/Documents/argos3/plugins/robots/generic:/Users/tvarner/Documents/argos3/plugins/robots/spiri:/Users/tvarner/Documents/argos3/plugins/simulator/visualizations/qt-opengl:/Users/tvarner/Documents/argos3/plugins/simulator/entities:/Users/tvarner/Documents/argos3/plugins/simulator/physics_engines/dynamics2d:/Users/tvarner/Documents/argos3/plugins/simulator/physics_engines/physx:/Users/tvarner/Documents/argos3/plugins/simulator/physics_engines/pointmass3d:/Users/tvarner/Documents/argos3/plugins/simulator/media

export DYLD_LIBRARY_PATH=${DYLD_LIBRARY_PATH}:${ARGOS_PLUGIN_PATH}
