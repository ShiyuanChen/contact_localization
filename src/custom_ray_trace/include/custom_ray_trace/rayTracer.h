#ifndef RAY_TRACER_H
#define RAY_TRACER_H

#include "rayTrace.h"
#include "ros/ros.h"
#include <tf/tf.h>
#include <tf/transform_listener.h>
#include <geometry_msgs/PoseArray.h>
#include <utility>
#include "calcEntropy.h"

typedef std::vector<std::pair<tf::Transform, tf::Transform>> ParticlePair;
class Ray
{
 public:
  Ray(tf::Point start_, tf::Point end_);

  tf::Point start;
  tf::Point end;

  tf::Vector3 getDirection() const;
  Ray transform(tf::Transform trans);
  Ray getTransformed(tf::Transform trans) const;
};

class ParticleHandler
{
 private:
  ros::NodeHandle rosnode;
  ros::Subscriber particleSub;
  ros::Publisher requestParticlesPub;
  bool particlesInitialized;

 public:
  ParticleHandler();
  ParticleHandler(std::string datumNames);
  tf::TransformListener tf_listener_;
  tf::StampedTransform trans_;
  std::vector<tf::Transform> particles;
  std::vector<tf::Transform> subsetParticles;
  bool newParticles;
  std::string datumName;


  tf::StampedTransform getTransformToPartFrame();  
  void setParticles(geometry_msgs::PoseArray p);
  std::vector<tf::Transform> getParticles();
  std::vector<tf::Transform> getParticleSubset();
  int getNumParticles();
  int getNumSubsetParticles();
  bool theseAreNewParticles();

};




class RayTracer
{
 private:
  ros::NodeHandle n_;
  stl::Mesh mesh;
  stl::Mesh surroundingBox;
  stl::Mesh surroundingBoxAllParticles;

  
 public:
  RayTracer(std::string filename);
  RayTracer();
  bool loadMesh();
  bool loadMesh(std::string filename);
  bool tracePartFrameRay(const Ray &ray, double &distToPart);
  bool traceRay(Ray ray, double &distToPart);
  bool traceRay(const stl::Mesh &mesh, const Ray &ray, double &distToPart);
  bool traceAllParticles(Ray ray, std::vector<double> &distToPart);
  bool traceAllParticles(Ray ray, std::vector<double> &distToPart, ParticlePair &particlePair);


  double getFullStateIG(Ray ray, double radialErr, double distErr, ParticlePair &particlePair);
  double getIG(Ray ray, double radialErr, double distErr);
  double getIG(Ray ray, vector<CalcEntropy::ConfigDist> &distsToParticles, double radialErr, double distErr);
  double getIG(std::vector<Ray> rays, double radialErr, double distErr);
  bool traceCylinderAllParticles(Ray ray, double radius, vector<CalcEntropy::ConfigDist> &dists);
  bool traceCylinderAllParticles(Ray ray, double radius, vector<CalcEntropy::ConfigDist> &distsToPart, ParticlePair &particlePair);
  std::vector<tf::Vector3> getOrthogonalBasis(tf::Vector3 dir);

  stl::Mesh getBoxAroundAllParticles(stl::Mesh mesh);

  void transformRayToPartFrame(Ray &ray);
  ParticleHandler particleHandler;
};


#endif
