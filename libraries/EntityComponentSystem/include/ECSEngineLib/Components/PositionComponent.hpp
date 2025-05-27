#pragma once

#include "../Component.hpp"
#include <array>
#include <boost/serialization/array.hpp>
#include <boost/serialization/serialization.hpp>

struct PositionComponent : public Component {
public:
  PositionComponent() = default;
  explicit PositionComponent(const std::array<double, 2> &pos)
      : position(pos) {}

  template <class Archive>
  void serialize(Archive &ar, const unsigned int version) {
    ar &boost::serialization::base_object<Component>(*this);
    ar & position;
  }

  std::array<double, 2> getPosition() const;
  void setPosition(const std::array<double, 2> &newPosition);

private:
  friend class boost::serialization::access;
  std::array<double, 2> position;
};

inline std::array<double, 2> PositionComponent::getPosition() const {
  return position;
}

inline void
PositionComponent::setPosition(const std::array<double, 2> &newPosition) {
  position = newPosition;
}
// #include <boost/serialization/export.hpp>
// BOOST_CLASS_EXPORT_GUID(PositionComponent, "PositionComponent")
