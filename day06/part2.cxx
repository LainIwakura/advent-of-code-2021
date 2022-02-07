#include <iostream> 
#include <algorithm>
#include <numeric>
#include <array>

using namespace std;

constexpr array input = {
	1,1,1,1,3,1,4,1,4,1,1,2,5,2,5,1,1,1,4,3,1,4,1,1,1,1,1,1,1,2,1,2,4,1,1,1,1,1,1,1,3,1,1,5,1,1,2,1,5,1,1,1,1,1,1,1,1,4,3,1,1,1,2,1,1,5,2,1,1,1,1,4,5,1,1,2,4,1,1,1,5,1,1,1,1,
	5,1,3,1,1,4,2,1,5,1,2,1,1,1,1,1,3,3,1,5,1,1,1,1,3,1,1,1,4,1,1,1,4,1,4,3,1,1,1,4,1,2,1,1,1,2,1,1,1,1,5,1,1,3,5,1,1,5,2,1,1,1,1,1,4,4,1,1,2,1,1,1,4,1,1,1,1,5,3,1,1,1,5,1,1,
	1,4,1,4,1,1,1,5,1,1,3,2,2,1,1,1,4,1,3,1,1,1,2,1,3,1,1,1,1,4,1,1,1,1,2,1,4,1,1,1,1,1,4,1,1,2,4,2,1,2,3,1,3,1,1,2,1,1,1,3,1,1,3,1,1,4,1,3,1,1,2,1,1,1,4,1,1,3,1,1,5,1,1,3,1,
	1,1,1,5,1,1,1,1,1,2,3,4,1,1,1,1,1,2,1,1,1,1,1,1,1,3,2,2,1,3,5,1,1,4,4,1,3,4,1,2,4,1,1,3,1
};

int main()
{
	array<uint64_t, 7> stages;
	array<uint64_t, 2> pre_stages;

	std::fill(pre_stages.begin(), pre_stages.end(), 0UL);

	int i = 0;
	generate(stages.begin(), stages.end(), [&]() { return count(input.begin(), input.end(), i++); });

	// Literally just have to change the stop number
	for (int d = 0; d < 256; ++d)
    {
		uint64_t new_fish = stages[0];
		rotate(stages.begin(), stages.begin() + 1, stages.end());
        rotate(pre_stages.begin(), pre_stages.begin() + 1, pre_stages.end());
        stages[6] += pre_stages[1];
        pre_stages[1] = new_fish;
    }
    
	// Answer can fit in this range, no need for bigint libs
	uint64_t sum = accumulate(stages.begin(), stages.end(), 0UL) + accumulate(pre_stages.begin(), pre_stages.end(), 0UL);

    cout << "Total fish: " << sum << endl;

	return 0;
}
