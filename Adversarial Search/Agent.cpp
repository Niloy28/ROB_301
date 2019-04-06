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

std::string Agent::search_by_depth() const
{
	const auto path = m_tree.search_by_depth();

	return path;
}

std::string Agent::search_by_breadth() const
{
	const auto path = m_tree.search_by_breadth();

	return path;
}


int Agent::mini_max()
{
	// achieved through alpha-beta pruning
	const auto result = this->value(m_tree.return_root());
	return result;
}

double Agent::expectimax()
{
	const auto result = this->expected_value(m_tree.return_root());
	return result;
}


int Agent::value(Node& state, const bool is_max_turn, int alpha, int beta) const
{
	if (state.branches.empty()) return state.weight;
	std::vector<Node> successors = state.branches;

	if (is_max_turn) {
		int v = std::numeric_limits<int>::min();

		for (auto &successor : successors) {
			v = std::max(v, value(successor, false, alpha, beta));
			if (v >= beta) return v;
			alpha = std::max(alpha, v);
		}
		return v;
	}
	else {
		int v = std::numeric_limits<int>::max();

		for (auto& successor : successors) {
			v = std::min(v, value(successor, true, alpha, beta));
			if (v <= alpha) return v;
			beta = std::min(beta, v);
		}
		return v;
	}
}

double Agent::expected_value(Node& state, const bool is_max_turn) const
{
	if (state.branches.empty()) return state.weight;

	std::vector<Node> successors = state.branches;
	if (is_max_turn) {
		double v = std::numeric_limits<double>::min();

		for (auto& i : successors) {
			v = std::max(v, expected_value(i, false));
		}
		return v;
	}
	else {
		double v = 0.0;
		const double probability = state.return_probability();
		for (auto& i : successors)
			v += probability * expected_value(i, true);

		return v;
	}
}
