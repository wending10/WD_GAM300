#include "GraphicsMgrWrapper.hxx"

namespace ScriptAPI
{
	 void GraphicsManagerWrapper::ToggleViewFrom2D(bool condition)
	{
		 TDS::GraphicsManagerWrapperCalls::ToggleViewFrom2D(condition);
	}

	 bool GraphicsManagerWrapper::IsViewingFrom2D()
	{
		 return TDS::GraphicsManagerWrapperCalls::IsViewingFrom2D();
	}

	 void GraphicsManagerWrapper::SetLayerToRender(int ID)
	 {
		 TDS::GraphicsManagerWrapperCalls::SetLayerToRender(ID);
	 }
	 int GraphicsManagerWrapper::CurrentRenderedLayer()
	 {
		 return TDS::GraphicsManagerWrapperCalls::CurrentRenderedLayer();
	 }
	 unsigned int GraphicsManagerWrapper::GetPickedObject()
	 {
		 return TDS::GraphicsManagerWrapperCalls::GetPickedObject();
	 }
}