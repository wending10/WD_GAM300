#include "GraphicComponent.hxx"
#include "components/GraphicsComponent.h"

namespace ScriptAPI {
	GraphicComponent::GraphicComponent(TDS::EntityID ID) : entityID(ID) {}
	
	float GraphicComponent::getColourAlpha() {
		return TDS::GetGraphicsComponent(entityID)->GetColor().w;
	}

	void GraphicComponent::SetColourAlpha(float value) {
		float r = Color.X;
		float g = Color.Y;
		float b = Color.Z;
		Color = Vector4(r, g, b, value);
	}

	TDS::EntityID GraphicComponent::GetEntityID() {
		return entityID;
	}

	void GraphicComponent::SetEntityID(TDS::EntityID ID) {
		entityID = ID;
	}

	Vector4 GraphicComponent::Color::get() {
		return Vector4(TDS::GetGraphicsComponent(entityID)->GetColor());
	}

	void GraphicComponent::Color::set(Vector4 value) {
		TDS::GetGraphicsComponent(entityID)->SetColor(value.X, value.Y, value.Z, value.W);
	}
	
}