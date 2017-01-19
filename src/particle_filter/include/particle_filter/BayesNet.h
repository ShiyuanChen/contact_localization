#ifndef BAYESNET_H
#define BAYESNET_H
#include <vector>
#include <array>
#include <cstring>
#include <unordered_set>
#include "definitions.h"
#include "Node.h"

using namespace std;

class BayesNet {
public:
  static const int cdim = 6;
  static const int fulldim = FULLDIM;
  int numParticles; // number of particles
  int maxNumParticles;

  // vector<Node *> node;
  FullJoint fullJoint;
  FullJoint fullJointPrev;
  Particles holeParticles;


  Eigen::MatrixXd cov_mat;
  int numFullJoint;
  int numNode;
  BayesNet();
  void addRoot(int numParticles, cspace b_init[2]);
  void createFullJoint(cspace b_Xprior[2]);
  bool updateFullJoint(double cur_M[2][3], double Xstd_ob, double R, int idx);
  void estimateGaussian(cspace &x_mean, cspace &x_est_stat, int idx);
  void estimateHole(cspace &x_mean, cspace &x_est_stat);
  void getAllParticles(Particles &particles_dest, int idx);
  void generateHole(jointCspace &joint, int datum1, int datum2, int plane, double holeOffset1, double holeOffset2, cspace &hole);
  // vector<cspace> priorSample();
};


#endif // BAYESNET_H