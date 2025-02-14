/* Author: Constantinos Chamzas */

#include <robowflex_library/robot.h>
#include <robowflex_library/scene.h>
#include <robowflex_library/trajectory.h>

#include <moveit/ompl_interface/parameterization/model_based_state_space.h>
#include <robowflex_ompl/ompl_trajectory.h>

using namespace robowflex;

OMPL::OMPLTrajectory::OMPLTrajectory(const RobotConstPtr &robot, const std::string &group)
  : Trajectory(robot, group)
{
}

OMPL::OMPLTrajectory::OMPLTrajectory(robot_trajectory::RobotTrajectory &trajectory) : Trajectory(trajectory)
{
}

ompl::geometric::PathGeometric OMPL::OMPLTrajectory::toOMPLPath(const ompl::geometric::SimpleSetupPtr &ss)
{
    auto path = ompl::geometric::PathGeometric(ss->getSpaceInformation());
    auto tstate = ss->getSpaceInformation()->allocState();
    auto traj_msg = getMessage();

    // transform to Path geometric
    for (const auto &state_vec : traj_msg.joint_trajectory.points)
        for (unsigned int j = 0; j < state_vec.positions.size(); j++)
            tstate->as<ompl_interface::ModelBasedStateSpace::StateType>()->values[j] = state_vec.positions[j];

    path.append(tstate);

    return path;
}
