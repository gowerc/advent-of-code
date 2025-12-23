

.PHONY: all test

all:
	@printf "\n\n----- Configuring -----\n\n"
	@cmake -S . -B build
	@printf "\n\n----- Building -----\n\n"
	@cmake --build build
	@printf "\n\n----- Running -----\n\n"
	@time ./build/day02
	@printf "\n\n----- Done - ----\n\n"

test:
	@printf "\n\n----- Configuring -----\n\n"
	@cmake -S . -B build
	@printf "\n\n----- Building -----\n\n"
	@cmake --build build
	@printf "\n\n----- Testing -----\n\n"
	@ctest --test-dir build