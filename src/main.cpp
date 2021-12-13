// Conway's Game of Life
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <thread>
#include <vector>

template <typename T, size_t size>
std::ostream& operator<<(std::ostream& stream, const std::array<T, size>& listType) {
	stream << "{ ";
	for(auto it = listType.begin(); it != listType.end(); it++)
		stream << *it << (std::next(it) != listType.end() ? ", " : " }");
	return stream;
}
template <typename T>
std::ostream& operator<<(std::ostream& stream, const std::vector<T>& listType) {
	stream << "{ ";
	for(auto it = listType.begin(); it != listType.end(); it++)
		stream << *it << (std::next(it) != listType.end() ? ", " : " }");
	return stream;
}

std::vector<std::vector<bool>> loadFile(const char* filename) {
	std::ifstream                  file(filename);
	std::vector<std::vector<bool>> grid;

	if(!file.is_open()) {
		std::cerr << "Could not open file: " << filename << std::endl;
		exit(EXIT_FAILURE);
	}

	std::string line;
	while(std::getline(file, line)) {
		std::vector<bool> row;
		row.reserve(line.size());

		for(const char& c: line) {
			row.emplace_back(
			    c == '1' || c == 'o' || c == 'O' || c == '*' || c == '@' ||
			    c == '#' || c == 'X' || c == 'x' || c == '+' || c == '%' ||
			    c == '$' || c == '&' || c == '~' || c == '^' || c == ';' ||
			    c == ':' || c == '.');
		}

		grid.push_back(row);
	}

	std::cout << "Grid: " << grid << std::endl;
	return grid;
}

void help() {
	std::cout << "Usage: ./gameOfLife [OPTIONS]\n"
		  << "Options:\n"
		  << "  -h, --help\n"
		  << "  -r, --rows <uint16_t> 30\n"
		  << "  -c, --cols <uint16_t> 30\n"
		  << "  -t, --ticksPerSecond <uint8_t> 30\n"
		  << "  -f, --file <filepath>\n";
}

std::vector<std::vector<bool>> stepGrid(const std::vector<std::vector<bool>>& grid) {
	std::vector<std::vector<bool>> newGrid = grid;
	for(size_t i = 0; i < grid.size(); i++) {
		for(size_t j = 0; j < grid[i].size(); j++) {
			int neighbors = 0;
			for(size_t k = std::max(i - 1, (size_t) 0);
			    k <= std::min(i + 1, grid.size() - 1);
			    k++) {
				for(size_t l = std::max(j - 1, (size_t) 0);
				    l <= std::min(j + 1, grid[k].size() - 1);
				    l++) {
					if(k != i || l != j) { neighbors += grid[k][l]; }
				}
			}
			if(grid[i][j]) {
				if(neighbors < 2 || neighbors > 3) {
					newGrid[i][j] = false;
				}
			} else {
				if(neighbors == 3) { newGrid[i][j] = true; }
			}
		}
	}

	return newGrid;
};

bool equalGrid(
    std::vector<std::vector<bool>>& grid1,
    std::vector<std::vector<bool>>& grid2) {
	if(grid1.size() != grid2.size()) { return false; }
	for(size_t i = 0; i < grid1.size(); i++) {
		if(grid1[i].size() != grid2[i].size()) { return false; }
		for(size_t j = 0; j < grid1[i].size(); j++) {
			if(grid1[i][j] != grid2[i][j]) { return false; }
		}
	}
	return true;
}

int main(int argc, const char* argv[]) {
	uint16_t rows = 0, cols = 0;
	uint8_t  ticksPerSecond = 0;
	bool     isFile         = false;

	std::vector<std::vector<bool>> grid;

	if(argc % 2 == 0) {
		help();
		return EXIT_FAILURE;
	} else {
		for(int i = 1; i < argc; i += 2) {
			if(strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
				help();
				return EXIT_FAILURE;
			} else if(
			    strcmp(argv[i], "-r") == 0 ||
			    strcmp(argv[i], "--rows") == 0) {
				rows = atoi(argv[i + 1]);
			} else if(
			    strcmp(argv[i], "-c") == 0 ||
			    strcmp(argv[i], "--cols") == 0) {
				cols = atoi(argv[i + 1]);
			} else if(
			    strcmp(argv[i], "-t") == 0 ||
			    strcmp(argv[i], "--ticksPerSecond") == 0) {
				ticksPerSecond = atoi(argv[i + 1]);
			} else if(
			    strcmp(argv[i], "-f") == 0 ||
			    strcmp(argv[i], "--file") == 0) {
				isFile = true;
				grid   = loadFile(argv[i + 1]);
				rows   = grid.size();
				cols   = grid[0].size();
			}
		}
	}

	if(!ticksPerSecond) ticksPerSecond = 10;

	if(!isFile) {
		if(!rows) rows = 10;
		if(!cols) cols = 10;
		grid.reserve(rows);
		for(uint16_t i = 0; i < rows; i++) {
			grid.emplace_back(std::vector(cols, false));
		}
	}

	int delay = 1000 / ticksPerSecond;

	while(1) {
		std::cout << "\033[2J\033[1;1H";
		for(int i = 0; i < rows; i++) {
			for(int j = 0; j < cols; j++) {
				if(grid[i][j]) {
					std::cout << "\033[47m  \033[0m";
				} else
					std::cout << "\033[40m  \033[0m";
			}
			std::cout << "\n";
		}

		auto newGrid = stepGrid(grid);
		if(equalGrid(grid, newGrid)) {
			break;
		} else {
			grid = newGrid;
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(delay));
	}

	return EXIT_SUCCESS;
}
