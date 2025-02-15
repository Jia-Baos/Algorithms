/*
 * In this example we show how to estimate the angle of a pendulum attached to
 * a frame moving in vertical direction. The length of the pendulum is "d", the
 * mass (concentrated at pendulum end point) of the frame is "m", the gravity
 * acceleration is "g" and there is a friction coefficient "b" at the bearing.
 *
 * The state of the system is q = (phi, omega) (angle and angular velocity):
 * n = 2
 * The input of the system is u = (a) (linear acceleration pointing up): l = 1
 * The output of the system is y = (a, b) (position of the pendulum end-point in
 * a local coordinate frame.
 */

#include <iostream>
#include <random>
#include <vector>

#include "../extended_kalman_filter.h"

// namespace plt = matplotlibcpp;

using namespace arma;
using namespace std;
using namespace kf;

// Time and samples
const double system_dt = 0.01;
const double measurement_dt = 0.05;
const double simulation_time = 10.0;

int N = static_cast<int>(simulation_time / system_dt);
int M = static_cast<int>(measurement_dt / system_dt);

// Process constants
const double m = 1.0; // Mass in kg
const double g = 9.8; // Gravitational accel.
const double d = 1.0; // Length in m
const double b = 0.5; // Friction coef. in 1/s

// Process function as standard function
vec processFunction(const vec &q, const vec &u) {
  vec q_pred = vec(2).zeros();

  q_pred(0) = q(0) + q(1) * system_dt;
  q_pred(1) = q(1) + (m * (u(0) - g) * d * sin(q(0)) - b * q(1)) * system_dt /
                         (m * d * d);

  return q_pred;
}

// Output function as lambda
auto outputFunction = [](const vec &q) -> vec {
  return {d * sin(q(0)), d * cos(q(0))};
};

// Process Jacobian as member function
struct ProcessJacobian {
  mat processJacobian(const vec &q, const vec &u) {
    double a11 = 1.0;
    double a12 = system_dt;
    double a21 = (u(0) - g) * cos(q(0)) * system_dt / d;
    double a22 = 1.0 - b * system_dt / (m * d * d);

    return {{a11, a12}, {a21, a22}};
  }
};

// Output Jacobian as function object
struct outputJacobian {
  mat operator()(const vec &q) const {
    return {{d * cos(q(0)), 0.0}, {-d * sin(q(0)), 0.0}};
  }
};

int main() {
  // Buffers for plots
  vector<double> time(N);

  vector<double> true_ang(N);
  vector<double> true_vel(N);
  vector<double> true_acc(N);

  vector<vec> measured_xy(N);
  vector<double> measured_ang(N);
  vector<double> estimated_ang(N);
  vector<double> believed_acc(N);

  // Pseudo random numbers generator
  double measurement_mu = 0.0;    // Mean
  double measurement_sigma = 0.1; // Standard deviation

  double process_mu = 0.0;
  double process_sigma = 0.05;

  default_random_engine generator;
  normal_distribution<double> measurement_noise(measurement_mu,
                                                measurement_sigma);
  normal_distribution<double> process_noise(process_mu, process_sigma);

  // Preparing EKF
  ExtendedKalmanFilter ekf(1, 2, 2);

  // Use standard function
  ekf.setProcessFunction(processFunction);

  // Use predefined lambda
  ekf.setOutputFunction(outputFunction);

  // Use member function
  ProcessJacobian s;
  using std::placeholders::_1;
  using std::placeholders::_2;
  ekf.setProcessJacobian(
      std::bind(&ProcessJacobian::processJacobian, &s, _1, _2));

  // Use function object
  ekf.setOutputJacobian(outputJacobian());

  mat Q = {{0.001, 0.0}, {0.0, 0.001}};
  mat R = {{1.0, 0.0}, {0.0, 1.0}};

  ekf.setProcessCovariance(Q);
  ekf.setOutputCovariance(R);

  // Initial values (unknown by EKF)
  time[0] = 0.0;

  true_ang[0] = 1.5;
  true_vel[0] = 0.0;
  true_acc[0] = 0.0;

  measured_xy[0] = {0.0, 0.0};
  measured_ang[0] = 0.0;
  estimated_ang[0] = 0.0;
  believed_acc[0] = 0.0;

  // Simulation
  for (int i = 1; i < N; ++i) {
    time[i] = i * system_dt;

    // We belive that acceleration was this
    believed_acc[i] = sin(time[i] * 2.0 * M_PI / simulation_time);

    // In fact there was some noise on input
    true_acc[i] = believed_acc[i] + process_noise(generator);

    // We use the process function to simulate the system
    vec q =
        processFunction({true_ang[i - 1], true_vel[i - 1]}, {true_acc[i - 1]});
    true_vel[i] = q(1);
    true_ang[i] = q(0);

    // New measurement comes once every M samples of the system
    if (i % M == 1) {
      measured_xy[i] = outputFunction({true_ang[i]});
      measured_xy[i](0) += measurement_noise(generator);
      measured_xy[i](1) += measurement_noise(generator);
      measured_ang[i] = atan2(measured_xy[i](0), measured_xy[i](1));
    } else {
      measured_xy[i] = measured_xy[i - 1];
      measured_ang[i] = measured_ang[i - 1];
    }

    // Here we do the magic
    ekf.updateState({believed_acc[i]}, measured_xy[i]);

    estimated_ang[i] = ekf.getEstimate()(0);

    std::cout << "timestamp: " << i << ", true ang: " << true_ang[i]
              << ", estimated_ang, " << estimated_ang[i] << std::endl;
  }

  return 0;
}
