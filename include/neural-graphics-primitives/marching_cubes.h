/*
 * Copyright (c) 2020-2022, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */

/** @file   marching_cubes.h
 *  @author Thomas Müller & Alex Evans, NVIDIA
 */

#pragma once

NGP_NAMESPACE_BEGIN

void marching_cubes_gpu(BoundingBox aabb, Eigen::Vector3i res_3d, float thresh, const tcnn::GPUMemory<float> &density, tcnn::GPUMemory<Eigen::Vector3f> &vert_out, tcnn::GPUMemory<uint32_t> &indices_out);

// computes the average of the 1ring of all verts, as homogenous coordinates
void compute_mesh_1ring(const tcnn::GPUMemory<Eigen::Vector3f> &verts, const tcnn::GPUMemory<uint32_t> &indices, tcnn::GPUMemory<Eigen::Vector4f> &output_pos, tcnn::GPUMemory<Eigen::Vector3f> &output_normals);

void compute_mesh_opt_gradients(float thresh,
	const tcnn::GPUMemory<Eigen::Vector3f> &verts, const tcnn::GPUMemory<Eigen::Vector3f> &vert_normals,
	const tcnn::GPUMemory<Eigen::Vector4f> &verts_smoothed,
	uint32_t padded_output_width, const __half *densities,
	uint32_t input_gradient_width, 	const float *input_gradients,
	tcnn::GPUMemory<Eigen::Vector3f> &verts_gradient_out,
	float k_smooth_amount,	float k_density_amount,	float k_inflate_amount
);

void save_mesh(tcnn::GPUMemory<Eigen::Vector3f> &verts,
	tcnn::GPUMemory<Eigen::Vector3f> &normals,
	tcnn::GPUMemory<uint32_t> &indices,
	const char *optional_outputname,
	bool unwrap_it,
	float nerf_scale,
	Eigen::Vector3f nerf_offset
);

#ifdef NGP_GUI
void draw_mesh_gl(
	const tcnn::GPUMemory<Eigen::Vector3f> &verts,
	const tcnn::GPUMemory<Eigen::Vector3f> &normals,
	const tcnn::GPUMemory<Eigen::Vector3f> &cols,
	const tcnn::GPUMemory<uint32_t> &indices,
	Eigen::Vector2i resolution,	Eigen::Vector2f focal_length,
	Eigen::Matrix<float, 3, 4> camera_matrix,
	Eigen::Vector2f screen_center,
	int mesh_render_mode
);
#endif

void save_density_grid_to_png(const tcnn::GPUMemory<float> &density, const char *filename, Eigen::Vector3i res3d, float thresh, bool swap_y_z=true);

NGP_NAMESPACE_END

