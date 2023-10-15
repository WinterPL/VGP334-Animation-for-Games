#pragma once

#include "Bone.h"

namespace WNTRengine::Graphics
{
	struct Skeleton
	{
		Bone* roott = nullptr;
		std::vector<std::unique_ptr<Bone>>bones;
	};


}