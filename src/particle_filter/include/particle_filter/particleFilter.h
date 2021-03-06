#ifndef PARTICLE_FILTER_H
#define PARTICLE_FILTER_H
#include <vector>
#include <array>
#include <cstring>
#include <unordered_set>
#include <Eigen/Dense>
#include "definitions.h"
#include "fullStatePFilter.h"
#include "distanceTransformNew.h"
using namespace std;

// class Node;
class particleFilter
{
 public:
  static const int cdim;
  int numParticles; // number of particles
  int maxNumParticles;

  particleFilter (int n_particles, jointCspace b_init[2], 
				double Xstd_ob=0.0001, double R=0.01);

  void addObservation (double obs[2][3], vector<vec4x3> &mesh, distanceTransform *dist_transform, bool miss, int datum);
  //void addObservation (double obs[3], double cube[3], int idx_obs);
  void estimateGaussian(cspace &x_mean, cspace &x_est_stat);
  void getAllParticles(Particles &particles_dest);
  void getAllParticles(Particles &particles_dest, int idx);
  void getHoleParticles(Particles &particles_dest);
  int getNumParticles();
  void computeHoleError(Particles &holeConfigs, cspace &trueConfig, double circle_radius = 0.001, double hole_depth = 0.035,
                                      double fit_ratio = 0.8, int num_poly_iterations = 20);

 protected:
  // Parameters of filter
  
  double Xstd_ob; // observation measurement error

  double R; // probe radius
  // Node *root;
  fullStatePFilter fullStateFilter;
  // internal variables
  jointCspace b_Xprior[2]; // Initial distribution (mean and variance)
  //cspace b_Xpre[2];   // Previous (estimated) distribution (mean and variance)
  // Particles particles;  // Current set of particles
  // Particles particlesPrev; // Previous set of particles
  // Particles particles_1; // Previous previous set of particles
  // std::vector<Particles> particlesSet;

  // Eigen::MatrixXd cov_mat;

  // Local functions
  // void createParticles(Particles &particles, cspace b_Xprior[2], int n_particles);
  // bool updateParticles(double cur_M[2][3], vector<vec4x3> &mesh, distanceTransform *dist_transform, bool miss);
  // Node* addDatum(std::vector<Node*> node, std::vector<double[3]> offset, std::vector<double[3]> tol);
  // Node* addInitialDatum();
};
// void Transform(double measure[3], cspace src, double dest[3]);
void Transform(double measure[2][3], cspace src, double dest[2][3]);
void inverseTransform(double measure[3], cspace src, double dest[3]);
void inverseTransform(double measure[2][3], cspace src, double dest[2][3]);

void Transform(Eigen::Vector3d &src, cspace config, Eigen::Vector3d &dest);
void inverseTransform(Eigen::Vector3d &src, cspace config, Eigen::Vector3d &dest);

// void getDisplacement(particleFilter::)
int checkInObject(vector<vec4x3> &mesh, double voxel_center[3]);
int getIntersectionSeg(vector<vec4x3> &mesh, double pstart[3], double pend[3]);
int getIntersection(vector<vec4x3> &mesh, double pstart[3], double dir[3], double intersection[3]);
double testResult(vector<vec4x3> &mesh, cspace config, double touch[2][3], double R);
int checkObstacles(vector<vec4x3> &mesh, cspace config, double touch[2][3], double dist);
int checkObstacles(vector<vec4x3> &mesh, cspace config, double start[2][3], double check_length, double dist);
int checkIntersections(vector<vec4x3> &mesh, double voxel_center[3], double dir[3], double check_length, double &dist);
int checkEmptyBin(std::unordered_set<string> *set, cspace config);
void calcDistance(vector<vec4x3> &mesh, cspace trueConfig, cspace meanConfig, double euclDist[2]);
#endif // PARTICLE_FILTER_H

