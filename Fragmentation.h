//#pragma once
//#include <vector>
//#include <queue>
//#include <memory>
//class Fragmentation : public std::enable_shared_from_this<Fragmentation> {
//public:
//	explicit Fragmentation(std::vector<uint8_t> data);
//
//	std::priority_queue<std::vector<uint8_t>> fragmentation_vector(std::vector<uint8_t>& data_);
//
//	bool integrity_check();
//
//	void stress_of_old_fragments(std::priority_queue<std::vector<uint8_t>>& fragment_data);
//private:
//	const std::vector<uint8_t> data_;
//	static const int STEP_FRAGMENTATION = 16;
//	static std::priority_queue<std::vector<uint8_t>> fragment_data;
//};