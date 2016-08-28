****************************************************************************************************

ADSP-BF561 EZ-KIT 

Video input oput project
____________________________________________________________________________________________________

This streams input from a video source to a output screen.
A video source is aquired frame-by-frame into SDRAM from the VideoDecoder. 
The frames are then output with a one-frame delay to the Encoder.

____________________________________________________________________________________________________



CONTENTS

I.	FUNCTIONAL DESCRIPTION
II.     PROJECT STRUCTURE


I.    FUNCTIONAL DESCRIPTION

	Core A sets up Clock frequencies, SDRAM controller, the Video Encoder and Decoder, and PPI0 to 
	perform the video acquisiton in ITU-656	mode. Frames are stroed in SDRAM (in a circular fashion,
	4 frames at a time).
	
	Core B sets up PPI1 to perform video output. It then waits for the first valid frame in memory
	from Core A, and starts the transfers. GP output mode is used.
	
		
II. PROJECT STRUCTURE

	This is a dual core project. It consists of a main project - containing only system defines and linker settings-
			".\video_inout.dpj",
	four sub-projects 		- containing the source code -
			".\coreA\coreA.dpj"					( code exclusive to core A, in L1 memory )
			".\coreB\coreB.dpj"					( code exclusive to core B, in L1 memory )
			".\Shared Memory L2\L2_SRAM.dpj"	( code that is shared between the cores, in on-chip L2 memory )
			".\Shared Memory L3\L3_SDRAM.dpj"	( code that is shared between the cores, in off-chip L3 memory, SDRAM ),
	and the project group that ties everything together:
			".\video_in_out.dpg".


