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
	
	// Fills the stages array with how many fish are at each stage, i.e at the start there are 2 fish at stage 3 so stages[3] = 2
	generate(stages.begin(), stages.end(), [&]() { return count(input.begin(), input.end(), i++); });
	for (int d = 0; d < 80; ++d)
    {
		// Since stages is a 7 element array, stages[0] will always hold how many new fish are to be spawned (i.e, have an internal counter of 0)
		uint64_t new_fish = stages[0];

		// Rotating the stages becomes important then, because all the fish at stages[1] have to move to stages[0].
		// Since the newly spawned fish begin with an internal counter of 6, it makes sense that they are rotated to stages[6].
		rotate(stages.begin(), stages.begin() + 1, stages.end());
        rotate(pre_stages.begin(), pre_stages.begin() + 1, pre_stages.end());

		// The pre-stages are necessary because according to the puzzle definition new fish begin with an internal timer of 8
		// and do not start counting down until the next day. The prior rotation occurs because pre_stages[0] is holding fish
		// with an internal timer of 8. When they get rotated and end up at pre_stages[1] they are ready to be added to stages[6] and
		// begin their countdown.
        stages[6] += pre_stages[1];
        pre_stages[1] = new_fish;
    }
    
	// Finally, add up the total fish in any stage of it's spawn cycle with any fish just spawned or in the waiting period before counting down.
	uint64_t sum = accumulate(stages.begin(), stages.end(), 0UL) + accumulate(pre_stages.begin(), pre_stages.end(), 0UL);

    cout << "Total fish: " << sum << endl;

	return 0;
}
