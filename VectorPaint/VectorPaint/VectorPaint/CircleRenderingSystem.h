#include <gtc/type_ptr.hpp>
#include "ECS.h"
#include "Manager.h"
#include "TransformComponent.h"
#include "CircleComponent.h"

class CircleRendererSystem : public ECS::System
{
public:
	CircleComponent* mCircleComponent;
	TransformComponent* transformComponent;
	Renderer* renderer;
	Model* model;
	~CircleRendererSystem() override {}
	void Initialize() override
	{
		if (entity->hasComponent<CircleComponent>())
		{
			mCircleComponent = entity->getComponent<CircleComponent>();
		}
		if (entity->hasComponent<TransformComponent>())
		{
			transformComponent = entity->getComponent<TransformComponent>();
		}
		renderer = Manager::GetInstance()->GetRenderer();
		model = mCircleComponent->GetModel();
	}
	void Update() override
	{
		model->SetPosition(glm::vec2(transformComponent->Position.x, transformComponent->Position.y));
		model->SetScale(glm::vec2(transformComponent->Scale.x, transformComponent->Scale.y));
	}
	void Render() override
	{
		Rect viewPortRect = renderer->GetViewportRect();
		glm::vec2 viewPort = glm::vec2(viewPortRect.w, viewPortRect.h);
		renderer->shaders[(int)(ShaderType::CircleShader)]->SetVec2f(glm::vec2(mCircleComponent->mLineStart.x, mCircleComponent->mLineStart.y), "circle.start");
		renderer->shaders[(int)(ShaderType::CircleShader)]->SetVec2f(glm::vec2(mCircleComponent->mLineEnd.x, mCircleComponent->mLineEnd.y), "circle.end");
		renderer->shaders[(int)(ShaderType::CircleShader)]->SetVec2f(glm::vec2(transformComponent->Scale.x, transformComponent->Scale.y), "circle.scale");
		model->render(renderer->shaders[(int)(ShaderType::CircleShader)]);
	}
};