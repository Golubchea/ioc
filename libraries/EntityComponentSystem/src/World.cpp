
#include <ECSEngineLib/World.hpp>
#include <boost/archive/basic_archive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

#include <fstream>

World::World()
    : next_entity_id_(1)
{}

Entity World::CreateEntity() {
    return next_entity_id_++;
}

void World::DestroyEntity(Entity entity) {
    for (auto& [type, map] : components_) {
        map.erase(entity);
    }
}

void World::Save(const std::string &filename) {
  std::ofstream ofs(filename, std::ios::binary);
  boost::archive::binary_oarchive oa(ofs);
  oa << *this;
}

void World::Load(const std::string &filename) {
  std::ifstream ifs(filename, std::ios::binary);
  boost::archive::binary_iarchive ia(ifs);
  ia >> *this;
}
