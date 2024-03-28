using ScriptAPI;
using System;

public class InventoryIntScript : Script 
{
	public GameObject receipt;
	public GameObject ToFather;
	public GameObject ToAntonio;
	public GameObject player;
	public GameObject playerCamera;
    public GameBlackboard gameBlackboard;
	private bool cameraDunMove;
	private Vector2 offset;
	private float PI = 3.14159f;
	private float PI_2 = 1.5708f;
	private bool doOnce = false;
	private Vector3 cameraRot = new Vector3(0,0,0);
    public override void Awake()
	{

	}
	public override void Update()
	{
		//if (Input.GetKeyDown(Keycode.NUM1))
		//{
		//	bool status = receipt.GetActive();
		//	receipt.SetActive(!status);
		//	receipt.GetComponent<TransformComponent>().SetPosition(player.GetComponent<TransformComponent>().GetPosition());
		//}
		if (doOnce)
		{
			cameraRot = playerCamera.GetComponent<TransformComponent>().GetRotation();
            player.GetComponent<FPS_Controller_Script>().playerCanMove = false;
            player.GetComponent<FPS_Controller_Script>().cameraCanMove = false;
            doOnce = false;
		}
        if (cameraDunMove)
		{
			// use WASD to move the object
			if (Input.GetKey(Keycode.W))
			{
				offset.Y += 0.1f;
			}
			if (Input.GetKey(Keycode.S))
			{
                offset.Y -= 0.1f;
            }
			if (Input.GetKey(Keycode.A))
			{
                offset.X -= 0.1f;
            }
			if (Input.GetKey(Keycode.D))
			{
				offset.X += 0.1f;
			}
            //playerCamera.GetComponent<TransformComponent>().SetRotation(new Vector3(0.0f, 0.0f, 0.0f));

            //ToFather.GetComponent<TransformComponent>().SetPosition(player.GetComponent<TransformComponent>().GetPosition() - new Vector3(offset.X, offset.Y, 1.0f));

        }
        if (Input.GetKeyDown(Keycode.ESC))
		{
            GraphicsManagerWrapper.ToggleViewFrom2D(false);
			gameBlackboard.gameState = GameBlackboard.GameState.InGame;
			ToFather.SetActive(false);

			// reset
            player.GetComponent<FPS_Controller_Script>().playerCanMove = true;
            player.GetComponent<FPS_Controller_Script>().cameraCanMove = true;
            cameraDunMove = false;
			offset = new Vector2(0.0f, 0.0f);
			//cameraRot = new Vector3(0.0f, 0.0f, 0.0f);

        }
		if (Input.GetKeyDown(Keycode.G) )
		{
			GraphicsManagerWrapper.ToggleViewFrom2D(true);
			gameBlackboard.gameState = GameBlackboard.GameState.InventoryInteract;
            bool status = ToFather.GetActive();
            ToFather.SetActive(true);
			float offsetAngle = player.GetComponent<TransformComponent>().GetRotation().Y - 180;
			float offsetAngleRadian = offsetAngle * PI / 180.0f;
			ToFather.GetComponent<TransformComponent>().SetRotation(new Vector3(PI_2, offsetAngleRadian, 0));

            ToFather.GetComponent<TransformComponent>().SetPosition(
				player.GetComponent<TransformComponent>().GetPosition() +
				player.GetComponent<FPS_Controller_Script>().playerCamera.getForwardVector());

			ToFather.GetComponent<TransformComponent>().SetPosition(
				new Vector3(
					player.GetComponent<TransformComponent>().GetPosition().X,
					player.GetComponent<TransformComponent>().GetPosition().Y + player.GetComponent<FPS_Controller_Script>().playerCamera.getForwardVector().Y,
					player.GetComponent<TransformComponent>().GetPosition().Z -1 )
				);
			//ToFather.GetComponent<TransformComponent>().SetRotationX(PI_2);

			//Vector3 direction = ToFather.GetComponent<TransformComponent>().GetPosition() - player.GetComponent<TransformComponent>().GetPosition();
			//Vector3 up = new Vector3(0, 1, 0);
			//Quaternion quatRotation = Quaternion.LookRotation(direction, up);
			//Vector3 eulerRotation = Quaternion.EulerAngle(quatRotation);
			//ToFather.GetComponent<TransformComponent>().SetRotation(new Vector3(PI_2, eulerRotation.Y, 0));
			

            cameraDunMove = true;
			doOnce = true;
		}
        if (Input.GetMouseButton(Keycode.M1))
        {
            float rotationAngleRadian = ToFather.GetComponent<TransformComponent>().GetRotation().Y;
            float rotationAngleDegree = rotationAngleRadian * 180.0f / 3.14159f;
            rotationAngleDegree += Input.GetMouseDeltaX();
            rotationAngleRadian = rotationAngleDegree * 3.14159f / 180.0f;
			ToFather.GetComponent<TransformComponent>().SetRotationY(rotationAngleRadian);
        }

    }


 }