#pragma once

#include <Platform/Stl.hpp>

struct AnimatedSpriteCycleData {
    std::string name;					// name of the animation
    size_t startFrame;		// the index of the first frame of an animation
    size_t numberOfFrames;	// the total numbers of frames in the animation
    size_t framesPerRow;
    float width;					// the width of each frame
    float height;					// the height of each frame
    float rotationCenterX;		// rotation center x-coordinate
    float rotationCenterY;		// rotation center y-coordinate
    float paddingWidth;			// width of the padding
    float paddingHeight;			// height of the padding
    float borderPaddingWidth;		// width of the border padding
    float borderPaddingHeight;	// height of the border padding
};

using AnimatedSpriteCycleDataVector = std::vector<AnimatedSpriteCycleData>;
