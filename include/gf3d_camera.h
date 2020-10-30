#ifndef __GF3D_CAMERA_H__
#define __GF3D_CAMERA_H__

#include "gfc_matrix.h"
#include "gf3d_vgraphics.h"
/**
 * @brief get the current camera view
 * @param view output, the matrix provided will be populated with the current camera information
 */
void gf3d_camera_get_view(Matrix4 view);

/**
 * @brief set the current camera based on the matrix provided
 */
void gf3d_camera_set_view(Matrix4 view);

/**
 * @brief set the camera properties based on position and direction that the camera should be looking
 * @param position the location for the camera
 * @param target the point the camera should be looking at
 * @param up the direction considered to be "up"
 */
void gf3d_camera_look_at(
    Vector3D position,
    Vector3D target,
    Vector3D up
);

/*
	@brief initialize the camera matrix to the ubo origin
*/
void gf3d_camera_set(Matrix4 start);

/**
 * @brief explicitely set the camera positon, holding all other parameters the same
 * @param position the new position for the camera
 */
void gf3d_camera_set_position(Vector3D position);

/*
	@brief returns the current position of the camera
*/
Vector3D gf3d_camera_get_pos();

/*
	@brief calls both the move and rotate functions to keep the camera tied to the player
	@param two vector3Ds for player position and input rotation
*/
void gf3d_camera_update(Vector3D pos, Vector3D rotation);

#endif
