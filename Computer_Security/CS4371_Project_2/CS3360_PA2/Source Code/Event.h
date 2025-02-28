
enum class EventType { ARRIVAL, DEPARTURE };

struct Event 
{
	EventType type;
	double time;

	Event(EventType type, double time) : type(type), time(time) {}

	// Ensure that greater time has lower priority
	bool operator<(const Event& other) const
	{
		return time > other.time;
	}

};