module;

#include "uuid.h"

export module dsm.uuid;

export class dsmUUID {
public:
  ~dsmUUID() = default;
  static uuids::uuid gen();
  static std::string string();
};

uuids::uuid dsmUUID::gen() {
  std::random_device rd;
  auto seed_data = std::array<int, std::mt19937::state_size>{};
  std::generate(std::begin(seed_data), std::end(seed_data), std::ref(rd));
  std::seed_seq seq(std::begin(seed_data), std::end(seed_data));
  std::mt19937 generator(seq);
  uuids::uuid_random_generator gen{generator};
  return gen();
}

std::string dsmUUID::string() { return uuids::to_string(dsmUUID::gen()); }

