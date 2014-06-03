#!/bin/sh

set -ex 

#
# Section 1
#
./req 020704		# Reset
./req 020801		# Section?
./req 02030200000800f0	# Color
./req 020801		# Section?
./req 0204		# Loop
./req 020801		# Section?
./req 02030300000400f0	# Color
./req 020801		# Section?
./req 0204		# Loop
./req 020801		# Section?
./req 02030400000200f0	# Color
./req 020801		# Section?
./req 0204		# Loop
./req 020801		# Section?
./req 02030500000100f0	# Color
./req 020801		# Section?
./req 0204		# Loop
./req 020801		# Section?
./req 02030600006000f0	# Color
./req 020801		# Section?
./req 0204		# Loop
./req 020801		# Section?
./req 02030700010000f0	# Color
./req 020801		# Section?
./req 0204		# Loop
./req 020801		# Section?
./req 02030800020000f0	# Color
./req 020801		# Section?
./req 0204		# Loop
./req 020801		# Section?
./req 02030900480000f0	# Color
./req 020801		# Section?
./req 0204		# Loop
./req 020801		# Section?
./req 02030a00008000f0	# Color
./req 020801		# Section?
./req 0204		# Loop
./req 0209		# Save
#
# Section 2
#
#./req 020704		# Reset
./req 020802		# Section?
./req 02010100200000f000 # Morph
./req 020802		# Section?
./req 02010100200000000f # Morph
./req 020802		# Section?
./req 0204		# Loop
./req 020802		# Section?
./req 0203020fdfff	# Color
./req 020802		# Section?
./req 0204		# Loop
./req 0209		# Save
#
# Section 5
#
#./req 020704		# Reset
./req 020805		# Section?
./req 02030100200000f0	# Color
./req 020805		# Section?
./req 0204		# Loop
./req 0209		# Save
#
# Section 6
#
#./req 020704		# Reset
./req 020806		# Section?
./req 02010100200000ff90 # Morph
./req 020806		# Section?
./req 020101002000f9000f # Morph
./req 020806		# Section?
./req 0204		# Loop
./req 0209		# Save
#
# Section 7
#
#./req 020704		# Reset
./req 020807		# Section?
./req 020101002000f9 # Morph
./req 020807		# Section?
./req 020101002000000f90 # Morph
./req 020807		# Section?
./req 0204		# Loop
./req 020807		# Section?
./req 0203020fdfff	# Color
./req 020807		# Section?
./req 0204		# Loop
./req 0209		# Save
#
# Section 8
#
#./req 020704		# Reset
./req 020808		# Section?
./req 020301002000f9	# Color
./req 020808		# Section?
./req 0204		# Loop
./req 0209		# Save
#
# Section 9
#
#./req 020704		# Reset
./req 020809		# Section?
./req 020201002000f9	# Pulse
./req 020809		# Section?
./req 0204		# Loop
./req 0209		# Save
#
# Unknown
#
#./req 020704		# Reset
./req 021d03
./req 020e00c8		# Speed
./req 02030200000800f0	# Color
./req 0204		# Loop
./req 02030300000400f0	# Color
./req 0204		# Loop
./req 02030400000200f0	# Color
./req 0204		# Loop
./req 02030500000100f0	# Color
./req 0204		# Loop
./req 02030600006000f0	# Color
./req 0204		# Loop
./req 02030700010000f0	# Color
./req 0204		# Loop
./req 02030800020000f0	# Color
./req 0204		# Loop
./req 02030900480000f0	# Color
./req 0204		# Loop
./req 02030a00008000f0	# Color
./req 0204		# Loop
./req 02030b0f9410	# Color
./req 0204		# Loop
#
# Execute
#
./req 0205		# Apply
