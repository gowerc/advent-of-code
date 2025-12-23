

.PHONY: all

all:
	@printf "\n\n----- Configuring -----\n\n"
	@cmake -S . -B build
	@printf "\n\n----- Building -----\n\n"
	@cmake --build build
	@printf "\n\n----- Running -----\n\n"
	@./build/day03
	@printf "\n\n----- Done -----\n\n"

test:
	@printf "\n\n----- Configuring -----\n\n"
	@cmake -S . -B build
	@printf "\n\n----- Building -----\n\n"
	@cmake --build build
	@printf "\n\n----- Testing -----\n\n"
	@ctest --test-dir build