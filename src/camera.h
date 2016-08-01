#ifndef _CAMERA_H
#define _CAMERA_H

typedef struct {
  float x;
  float z;
  float a;
  float y;
  float v;
} Camera;

void Camera_init( Camera* );
void Camera_moveleft( Camera* );
void Camera_moveright( Camera* );
void Camera_moveforward( Camera* );
void Camera_moveback( Camera* );
void Camera_rotateleft( Camera* );
void Camera_rotateright( Camera* );
void Camera_moveup( Camera* );
void Camera_movedown( Camera* );
void Camera_tiltup( Camera* );
void Camera_tiltdown( Camera* );

#endif
