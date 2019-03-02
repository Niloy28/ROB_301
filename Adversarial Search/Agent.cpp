#include <fstream>
#include <limits>
#include <algorithm>

#include "Agent.h"

int Agent::m_max = std::numeric_limits<int>::max();
int Agent::m_min = std::numeric_limits<int>::min();

void Agent::read_file(std::string& file_name)
{
	std::fstream fs;
	fs.open(file_name, std::ios::in);

	m_tree.read_file(fs);
}


int Agent::mini_max()
{
	const auto result = this->value(m_tree.return_root());
	return result;
}

int Agent::value(Node& state, const bool is_max_turn, int alpha, int beta) const
{
	if (state.branches.empty()) return state.weight;
	std::vector<Node> successors = state.branches;

	if (is_max_turn) {
		int v = std::numeric_limits<int>::min();

		for (auto &i : successors) {
			v = std::max(v, value(i, false, alpha, beta));
			if (v > beta) return v;
			alpha = std::max(alpha, v);
		}
		return v;
	}
	else {
		int v = std::numeric_limits<int>::max();

		for (auto& i : successors) {
			v = std::min(v, value(i, true, alpha, beta));
			if (v < alpha) return v;
			beta = std::min(beta, v);
		}
		return v;
	}
}

