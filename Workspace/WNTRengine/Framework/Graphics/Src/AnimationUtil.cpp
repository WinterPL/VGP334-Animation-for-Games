#include "Precompiled.h"
#include "AnimationUtil.h"
#include "Colors.h"
#include "SimpleDraw.h"

using namespace WNTRengine;
using namespace WNTRengine::Graphics;
using namespace WNTRengine::Graphics::AnimationUtil;

namespace
{
	void ComputeBoneTransformRecursive(const Bone* bone, BoneTransforms& boneTransforms)
	{
		if (bone != nullptr)
		{
			boneTransforms[bone->index] = bone->toParentTransform;
			if (bone->parent != nullptr)
			{
				boneTransforms[bone->index] = bone->toParentTransform * boneTransforms[bone->parentIndex];
			}
			for (auto child : bone->children)
			{
				ComputeBoneTransformRecursive(child, boneTransforms);
			}
		}
	}
}

void AnimationUtil::ComputeBoneTransform(ModelId modelId, BoneTransforms& boneTransforms)
{
	auto model = ModelManager::Get()->GetModel(modelId);
	if (model->skeleton != nullptr)
	{
		boneTransforms.resize(model->skeleton->bones.size(), WNTRmath::Matrix4::Identity);
		ComputeBoneTransformRecursive(model->skeleton->root, boneTransforms);
	}
}
void AnimationUtil::ApplyBoneOffsets(ModelId modelId, BoneTransforms& boneTransforms)
{
	auto model = ModelManager::Get()->GetModel(modelId);
	if (model->skeleton != nullptr)
	{
		for (auto& bone : model->skeleton->bones)
		{
			boneTransforms[bone->index] = bone->offsetTransform * boneTransforms[bone->index];
		}

	}
}
void AnimationUtil::DrawSkeleton(ModelId modelId, const BoneTransforms& boneTransforms)
{
	auto model = ModelManager::Get()->GetModel(modelId);
	if (model->skeleton != nullptr)
	{
		for (auto& bone : model->skeleton->bones)
		{
			if (bone->parent != nullptr)
			{
				const auto posA = WNTRmath::GetTranslation(boneTransforms[bone->index]);
				const auto posB = WNTRmath::GetTranslation(boneTransforms[bone->parentIndex]);
				SimpleDraw::AddLine(posA, posB, Colors::HotPink);
				SimpleDraw::AddSphere(10,10,0.01f,posA,Colors::Green);

			}
		}
	}
}