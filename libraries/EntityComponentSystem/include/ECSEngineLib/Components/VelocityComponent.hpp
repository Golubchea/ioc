#pragma once

#include "../Component.hpp"
#include <array>
#include <boost/serialization/array.hpp>
#include <boost/serialization/serialization.hpp>
class VelocityComponent : public Component {

public:
  VelocityComponent() = default;
  explicit VelocityComponent(const std::array<double, 2> &vel)
      : velocity(vel) {}

  template <class Archive>
  void serialize(Archive &ar, const unsigned int version) {
    ar &boost::serialization::base_object<Component>(*this);
    ar & velocity;
  }

  std::array<double, 2> getVelocity() const;
  void setVelocity(const std::array<double, 2> &newVelocity);

private:
  std::array<double, 2> velocity;
  friend class boost::serialization::access;
};

inline std::array<double, 2> VelocityComponent::getVelocity() const {
  return velocity;
}

inline void
VelocityComponent::setVelocity(const std::array<double, 2> &newVelocity) {
  velocity = newVelocity;
}
// #include <boost/serialization/export.hpp>
// BOOST_CLASS_EXPORT_GUID(VelocityComponent, "VelocityComponent")
