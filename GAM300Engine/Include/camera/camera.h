#ifndef TDS_CAMERA
#define TDS_CAMERA

#include "TDSMath.h"
#include "Input.h"

namespace TDS
{
	class TDSCamera
	{
	public:

		Mat4 viewMatrix;
		Mat4 projectionMatrix;




	private:

		float fov{};
		float znear{};
		float zfar{};

		Vec3 position{};
		void updateViewMatrix()
		{

		}
	};




}//namespace TDS


#endif // !TDS_CAMERA
