#include "ECSEngineLib/Components/FuelComponent.hpp"
#include "ECSEngineLib/Components/PositionComponent.hpp"
#include "ECSEngineLib/Components/VelocityComponent.hpp"
#include <ECSEngineLib/World.hpp>
#include <boost/serialization/export.hpp>

BOOST_CLASS_EXPORT_GUID(PositionComponent, "PositionComponent")
BOOST_CLASS_EXPORT_GUID(VelocityComponent, "VelocityComponent")
BOOST_CLASS_EXPORT_GUID(FuelComponent, "FuelComponent")
