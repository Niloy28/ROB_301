#pragma once

#include <vector>
#include <tuple>
#include <utility>

enum actions {slow = 0, fast = 1};
enum car_states {cool = 0, warm = 1, overheated = 2};

class RacingAgent
{
public:
	void read_file(const std::string& file_name);
	std::vector<double> value_iteration() const;

private:
	static std::vector<std::vector<actions>> m_available_actions;
	static std::vector<std::vector<std::vector<std::tuple<car_states, double, int>>>> m_outcomes;

	// utility functions
	double return_q_value(std::vector<std::tuple<car_states, double, int>>& outcomes, std::vector<double>& prev_value) const;
};

bool has_converged(std::vector<double>& lhs, std::vector<double>& rhs, double epsilon = 0.01);

