#include "Camera.hpp"

#include "glm/gtx/transform.hpp"
#include "glm/gtx/rotate_vector.hpp"

#include <iostream>


Camera& Camera::Instance(){
    static Camera* instance = new Camera();
    return *instance;
}

void Camera::MouseLook(SDL_Window* m_window, int mouseX, int mouseY){
    // TODO: Which vector are you modifying?
    // *hint* not the eye...

    float xDistanceFromWindowCenter = mouseX - ((float)1280 / 2);
    float yDistanceFromWindowCenter = ((float)720 / 2) -mouseY;
    float cameraRotationSpeed = 0.25;
    float yaw = xDistanceFromWindowCenter * cameraRotationSpeed;
    float pitch = yDistanceFromWindowCenter * cameraRotationSpeed;

    SDL_WarpMouseInWindow(m_window, 1280 / 2, 720 / 2); 

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    m_viewDirection = glm::normalize(direction);

}


// void Camera::MouseLook(int mouseX, int mouseY){
//     // TODO: Which vector are you modifying?
//     // *hint* not the eye...
//     float lastX = 400;
//     float lastY = 300;
//     float yaw = -90.0f;
//     float pitch = 0.0f;

//     float xoffset = mouseX - lastX;
//     float yoffset = lastY - mouseY; // reversed since y-coordinates range from bottom to top
//     lastX = mouseX;
//     lastY = mouseY;

//     const float sensitivity = 0.1f;
//     xoffset *= sensitivity;
//     yoffset *= sensitivity;
//     yaw   += xoffset;
//     pitch += yoffset;
//     if(pitch > 89.0f){
//       pitch =  89.0f;
//     }
//     if(pitch < -89.0f){
//       pitch = -89.0f;    
//     }

//     glm::vec3 direction;
//     direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
//     direction.y = sin(glm::radians(pitch));
//     direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
//     m_viewDirection = glm::normalize(direction);

// }

// void Camera::MouseLook(int mouseX, int mouseY){
//     // Record our new position as a vector
//     glm::vec2 newMousePosition(mouseX, mouseY);
//     static bool firstLook = true;
//     // Note: we need to handle the 'first' mouse event
//     // Note: We should also 'center' the mouse in our
//     //       program when we execute it.
//     if(true == firstLook){
//         firstLook=false;
//         m_oldMousePosition = newMousePosition;
//     }
//     // if (mouseX == 640 && mouseY == 360){
//     //     m_oldMousePosition = newMousePosition;
//     // }
//     // Detect how much the mouse has moved since
//     // the last time
//     glm::vec2 mouseDelta = m_oldMousePosition - newMousePosition; 
//     mouseDelta.x *= 0.2f; // mouse sensitivity.
//     // Update the view direction
//     m_viewDirection = glm::rotate(m_viewDirection,glm::radians(mouseDelta.x),m_upVector);

//     std::cout << "m_viewDirection.x: " << m_viewDirection.x << std::endl;
//     std::cout << "m_viewDirection.y: " << m_viewDirection.y << std::endl;
//     std::cout << "m_viewDirection.z: " << m_viewDirection.z << std::endl;

//     // Update our old position after we have made changes 
//     m_oldMousePosition = newMousePosition;
// }


void Camera::MoveForward(float speed){
    // m_eyePosition.z -= speed;
    // m_eyePosition.z += speed * m_viewDirection.z;
    // m_eyePosition.x += speed * m_viewDirection.x;
    m_eyePosition += speed * m_viewDirection;
}

void Camera::MoveBackward(float speed){
    // m_eyePosition.z += speed;
    m_eyePosition.z -= speed * m_viewDirection.z;
    m_eyePosition.x -= speed * m_viewDirection.x;
    // m_eyePosition -= speed * m_viewDirection;
}

void Camera::MoveLeft(float speed){
    // m_eyePosition.x -= speed;
    // m_eyePosition.x -= glm::normalize(glm::cross(m_viewDirection.x, m_upVector)) * speed;
    m_eyePosition -= glm::normalize(glm::cross(m_viewDirection, m_upVector)) * speed;
}

void Camera::MoveRight(float speed){
    // m_eyePosition.x += speed;
    // m_eyePosition.x += glm::normalize(glm::cross(m_viewDirection.x, m_upVector)) * speed;
    m_eyePosition += glm::normalize(glm::cross(m_viewDirection, m_upVector)) * speed;
}

void Camera::MoveUp(float speed){
    m_eyePosition += speed * m_upVector;
}

void Camera::MoveDown(float speed){
    m_eyePosition -= speed * m_upVector;
}

// Set the position for the camera
void Camera::SetCameraEyePosition(float x, float y, float z){
    m_eyePosition.x = x;
    m_eyePosition.y = y;
    m_eyePosition.z = z;
}

float Camera::GetEyeXPosition(){
    return m_eyePosition.x;
}

float Camera::GetEyeYPosition(){
    return m_eyePosition.y;
}

float Camera::GetEyeZPosition(){
    return m_eyePosition.z;
}

float Camera::GetViewXDirection(){
    return m_viewDirection.x;
}

float Camera::GetViewYDirection(){
    return m_viewDirection.y;
}

float Camera::GetViewZDirection(){
    return m_viewDirection.z;
}

void Camera::SetCameraViewPosition(float x, float y, float z){
    m_viewDirection.x = x;
    m_viewDirection.y = y;
    m_viewDirection.z = z;
}


Camera::Camera(){
    std::cout << "(Constructor) Created a Camera!\n";
	// Position us at the origin.
    m_eyePosition = glm::vec3(0.0f,0.0f, 0.0f);
	// Looking down along the z-axis initially.
	// Remember, this is negative because we are looking 'into' the scene.
    m_viewDirection = glm::vec3(0.0f,0.0f, -1.0f);
	// For now--our upVector always points up along the y-axis
    m_upVector = glm::vec3(0.0f, 1.0f, 0.0f);
}

glm::mat4 Camera::GetWorldToViewmatrix() const{
    // Think about the second argument and why that is
    // setup as it is.
    return glm::lookAt( m_eyePosition,
                        m_eyePosition + m_viewDirection,
                        m_upVector);
}
