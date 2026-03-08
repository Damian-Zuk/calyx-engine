#pragma once

namespace Calyx {

	class UUID
	{
	public:
		UUID();
		UUID(uint64_t uuid);
		UUID(const UUID&) = default;

		operator uint64_t() const { return m_UUID; }
		operator json() const { return (uint64_t)m_UUID; }
		UUID operator=(const json& j) { m_UUID = (uint64_t)j; return m_UUID; }
	private:
		uint64_t m_UUID;
	};

}

namespace std {

	template <typename T> struct hash;

	template<>
	struct hash<Calyx::UUID>
	{
		std::size_t operator()(const Calyx::UUID& uuid) const
		{
			return (uint64_t)uuid;
		}
	};

}
