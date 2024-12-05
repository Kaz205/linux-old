// receiver_manager.hpp

#pragma once

#include <shared_mutex>
#include <map>

#include "command.hpp"
#include "receiver_base.hpp"

namespace px4 {

class ReceiverManager final {
public:
	ReceiverManager() {};
	~ReceiverManager() {};

	// cannot copy
	ReceiverManager(const ReceiverManager &) = delete;
	ReceiverManager& operator=(const ReceiverManager &) = delete;

	// cannot move
	ReceiverManager(ReceiverManager &&) = delete;
	ReceiverManager& operator=(ReceiverManager &&) = delete;

	bool Register(px4::command::ReceiverInfo &info, px4::ReceiverBase *receiver);
	bool Unregister(px4::ReceiverBase *receiver);
	px4::ReceiverBase* SearchAndOpen(px4::command::ReceiverInfo &key, px4::command::ReceiverInfo &info, std::uint32_t &data_id);
	px4::ReceiverBase* SearchByDataId(std::uint32_t data_id);
	void ClearDataId(px4::ReceiverBase *receiver);

private:
	struct ReceiverData {
		px4::command::ReceiverInfo info;
		bool valid_data_id;
	};

	bool GenerateDataId(px4::ReceiverBase *receiver, std::uint32_t &data_id);

	std::shared_mutex mtx_;
	std::map<px4::ReceiverBase*, ReceiverData> data_;
};

} // namespace px4
