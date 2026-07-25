
//#include "Fragmentation.h"

//Fragmentation::Fragmentation(std::vector<uint8_t> data) : data_(data) {};

// vector -> v|e|c|t|o|r
//std::priority_queue<std::vector<uint8_t>> Fragmentation::fragmentation_vector(std::vector<uint8_t>& data_) {
//	std::vector<uint8_t> sector_byte;
//	std::vector<uint8_t>* ptr_vectro_byte = &data_;
//	size_t size_sector = 0;
//	sector_byte.reserve(size_sector);
//	for (const auto& byte : *ptr_vectro_byte) {
//		if (sector_byte.size() != STEP_FRAGMENTATION) {
//			sector_byte.push_back(byte);
//		}
//		else {
//			fragment_data.push(std::move(sector_byte));
//			sector_byte.clear();
//		}
//	}
//	if (!sector_byte.empty()) {
//		fragment_data.push(std::move(sector_byte));
//	}
//	return fragment_data;
//}

// if vector == priority_queue
//bool Fragmentation::integrity_check() {
//	std::priority_queue<std::vector<uint8_t>> copy_fragment_queue = fragment_data;
//	auto current = data_.begin();
//	while (!copy_fragment_queue.empty()) {
//		const std::vector<uint8_t> sector = fragment_data.top();
//		if (!std::equal(sector.begin(), sector.end(), current)) {
//			return false;
//		}
//		std::advance(current, sector.size());
//	}
//	return true;
//}
// + function clear priority_queue
