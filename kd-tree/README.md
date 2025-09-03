#### Review:
- Use of raw pointers for left and right could be replaced with smart (unique) pointers for easier memory management.
- Line 218 of cpp file has the min max distance checks inverted. Should be: `if( dist >= minDist && dist <= maxDist )`.
- Costly use of sqrt could be avoided when comparisons are all that is needed. E.g.: `if( dx*dx + dy*dy <= radius*radius )`.
- Even with knowledge of a kd tree, it's still difficult to follow low level algorithm details. Comments explaining each step would be very helpful for someone new to this.
- In the split function: Modern C++ alternatives to memcopy could be used for better safety and readability - e.g. std::vector::assign.
