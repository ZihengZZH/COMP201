// Robust pose estimation of rigid objects


#include <Eigen/Core>
#include <iostream>
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
#include <pcl/pcl_macros.h>
#include <pcl/common/common.h>
#include <pcl/common/time.h>
#include <pcl/console/print.h>
#include <pcl/features/normal_3d_omp.h>
#include <pcl/features/fpfh_omp.h>
#include <pcl/filters/filter.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/io/io.h>
#include <pcl/io/pcd_io.h>
#include <pcl/io/vtk_lib_io.h>
#include <pcl/registration/icp.h>
#include <pcl/registration/sample_consensus_prerejective.h>
#include <pcl/segmentation/sac_segmentation.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/point_types.h>
#include <vtkPolyDataMapper.h>
#include <pcl/PolygonMesh.h>

// Types
typedef pcl::PointNormal PointNT;
typedef pcl::PointCloud<PointNT> PointCloudT;
typedef pcl::FPFHSignature33 FeatureT;
typedef pcl::FPFHEstimationOMP<PointNT, PointNT, FeatureT> FeatureEstimationT;
typedef pcl::PointCloud<FeatureT> FeatureCloudT;
typedef pcl::visualization::PointCloudColorHandlerCustom<PointNT> ColorHandlerT;

int user_data;


void viewerPsycho(pcl::visualization::PCLVisualizer& viewer) {
	static unsigned count = 0;
	std::stringstream ss;
	ss << "Once per viewer loop: " << count++;
	viewer.removeShape("text", 0);
	viewer.addText(ss.str(), 200, 300, "text", 0);

	user_data++;
}

void displayPointCloud(std::string filename) {
	pcl::PointCloud<pcl::PointXYZRGBA>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZRGBA>);
	pcl::io::loadPCDFile(filename, *cloud);

	pcl::visualization::CloudViewer viewer("Cloud Viewer");

	//blocks until the cloud is actually rendered
	viewer.showCloud(cloud);

	//This will get called once per visualization iteration
	viewer.runOnVisualizationThread(viewerPsycho);
	while (!viewer.wasStopped())
	{
		user_data++;
	}
}


// Align a rigid object to a scene with clutter and occlusions
int main() {
	// Point clouds
	PointCloudT::Ptr object(new PointCloudT);
	PointCloudT::Ptr object_aligned(new PointCloudT);
	PointCloudT::Ptr scene(new PointCloudT);
	FeatureCloudT::Ptr object_features(new FeatureCloudT);
	FeatureCloudT::Ptr scene_features(new FeatureCloudT);


	// displayPointCloud("object.pcd");
	// displayPointCloud("scene.pcd");

	
	// Load object and scene
	pcl::console::print_highlight("Loading point clouds...\n");
	if (pcl::io::loadPCDFile<PointNT>("object.pcd", *object) < 0 ||
		pcl::io::loadPCDFile<PointNT>("scene.pcd", *scene) < 0)
	{
		pcl::console::print_error("Error loading object/scene file!\n");
		return (1);
	}

	// Downsample
	pcl::console::print_highlight("Downsampling...\n");
	pcl::VoxelGrid<PointNT> grid;
	const float leaf = 0.01f; // 5mm
	grid.setLeafSize(leaf, leaf, leaf);
	grid.setInputCloud(object);
	grid.filter(*object);
	grid.setInputCloud(scene);
	grid.filter(*scene);

	// Estimate normals for scene
	pcl::console::print_highlight("Estimating scene normals...\n");
	pcl::NormalEstimationOMP<PointNT, PointNT> nest;
	nest.setNumberOfThreads(2);
	nest.setRadiusSearch(0.01);
	nest.setInputCloud(scene);
	nest.compute(*scene);

	// Estimate features
	pcl::console::print_highlight("Estimating features...\n");
	FeatureEstimationT fest;
	fest.setNumberOfThreads(2);
	fest.setRadiusSearch(0.025);
	fest.setInputCloud(object);
	fest.setInputNormals(object);
	fest.compute(*object_features);
	fest.setInputCloud(scene);
	fest.setInputNormals(scene);
	fest.compute(*scene_features);

	// Perform alignment
	pcl::console::print_highlight("Starting alignment...\n");
	pcl::SampleConsensusPrerejective<PointNT, PointNT, FeatureT> align;
	align.setInputSource(object);
	align.setSourceFeatures(object_features);
	align.setInputTarget(scene);
	align.setTargetFeatures(scene_features);
	align.setMaximumIterations(50000); // Number of RANSAC iterations
	align.setNumberOfSamples(3); // Number of points to sample for generating/prerejecting a pose
	align.setCorrespondenceRandomness(5); // Number of nearest features to use
	align.setSimilarityThreshold(0.9f); // Polygonal edge length similarity threshold
	align.setMaxCorrespondenceDistance(2.5f * leaf); // Inlier threshold
	align.setInlierFraction(0.4f); // Required inlier fraction for accepting a pose hypothesis
	{
		pcl::ScopeTime t("Alignment");
		align.align(*object_aligned);
	}

	if (align.hasConverged())
	{
		// Print results
		printf("\n");
		
		Eigen::Matrix4f transformation = align.getFinalTransformation();
		pcl::console::print_info("    | %6.3f %6.3f %6.3f | \n", transformation(0, 0), transformation(0, 1), transformation(0, 2));
		pcl::console::print_info("R = | %6.3f %6.3f %6.3f | \n", transformation(1, 0), transformation(1, 1), transformation(1, 2));
		pcl::console::print_info("    | %6.3f %6.3f %6.3f | \n", transformation(2, 0), transformation(2, 1), transformation(2, 2));
		pcl::console::print_info("\n");
		pcl::console::print_info("t = < %0.3f, %0.3f, %0.3f >\n", transformation(0, 3), transformation(1, 3), transformation(2, 3));
		pcl::console::print_info("\n");
		pcl::console::print_info("Inliers: %i/%i\n", align.getInliers().size(), object->size());

		Eigen::Affine3f rotation;
		rotation.matrix() = transformation;
		float roll = 0.0f, pitch = 0.0f, yaw = 0.0f;

		pcl::getEulerAngles(rotation, roll, pitch, yaw);
		pcl::console::print_info("\nRoll angle   %6.3f ", roll);
		pcl::console::print_info("\tPitch angle  %6.3f ", pitch);
		pcl::console::print_info("\tYaw angle    %6.3f ", yaw);

		// Show alignment
		pcl::visualization::PCLVisualizer visu("Alignment");
		visu.addPointCloud(scene, ColorHandlerT(scene, 0.0, 255.0, 0.0), "scene");
		visu.addPointCloud(object_aligned, ColorHandlerT(object_aligned, 0.0, 0.0, 255.0), "object_aligned");
		visu.spin();
	}
	else
	{
		pcl::console::print_error("Alignment failed!\n");
		system("pause");
		return (1);
	}

	return (0);
}





/*
		TEST CASE (scan)
----------------------------------
0.05f	

	| -0.225  -0.968  -0.109 |
R = | 0.968	  -0.209  -0.138 |
	| 0.111   -0.136   0.984 |

t = < 0.141, -0.153, -0.075 >

inliners: 617/1915

----------------------------------
0.5f

	| -0.793  -0.968  -0.109 |
R = |  0.598   0.234   0.766 |
	|  0.112   0.923  -0.369 |

t = < -4.692, -6.392, 7.103 >

inliners: 23/66

----------------------------------





		TEST CASE (milk)
----------------------------------
0.05f	

	| -0.642  -0.765  -0.042 |
R = |  0.760  -0.643  -0.093 |
	| -0.098   0.027   0.995 |

t = < -0.159, 0.065, -0.168 >

inliners: 1043/2573

----------------------------------




		TEST CASE (object)
----------------------------------
0.05f	

	| -0.634  -0.410   0.656 |
R = | -0.763   0.469  -0.445 |
	| -0.125  -0.783  -0.610 |

t = < 0.462, -0.242, 0.260 >

inliners: 1167/3432

----------------------------------


		TEST CASE (object)
			GREAT
----------------------------------
0.05f	

	|  0.040  -0.945  -0.323 |
R = | -0.999  -0.033  -0.029 |
	| -0.016   0.324  -0.946 |

t = < -0.260, 0.035, 0.109 >

inliners: 695/1196

----------------------------------


2.5 = 2.5 meters

*/