#include <iostream>
#include <vector>
#include <pcl/io/ply_io.h>
#include <pcl/point_types.h>
#include <pcl/common/common.h>

// 定义点类型
typedef pcl::PointXYZ PointT;
typedef pcl::PointCloud<PointT> PointCloudT;

// 函数声明
std::vector<PointCloudT::Ptr> splitPointCloudByY(const PointCloudT::Ptr& inputCloud, int numFrames);
void savePointClouds(const std::vector<PointCloudT::Ptr>& clouds, const std::string& baseFilename);

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input_pcd_file>" << std::endl;
        return -1;
    }

    // 加载输入点云
    PointCloudT::Ptr inputCloud(new PointCloudT);
    if (pcl::io::loadPLYFile<PointT>(argv[1], *inputCloud) == -1) {
        std::cerr << "Error loading file " << argv[1] << std::endl;
        return -1;
    }

    std::cout << "Loaded point cloud with " << inputCloud->size() << " points." << std::endl;

    // 分割点云为10帧
    const int numFrames = 10;
    std::vector<PointCloudT::Ptr> separatedClouds = splitPointCloudByY(inputCloud, numFrames);

    // 保存分割后的点云
    savePointClouds(separatedClouds, "frame_");

    return 0;
}

std::vector<PointCloudT::Ptr> splitPointCloudByY(const PointCloudT::Ptr& inputCloud, int numFrames) {
    std::vector<PointCloudT::Ptr> result(numFrames);

    // 初始化输出点云
    for (int i = 0; i < numFrames; ++i) {
        result[i] = PointCloudT::Ptr(new PointCloudT);
        result[i]->header = inputCloud->header;
    }

    // 找到Y坐标的最小值和最大值
    PointT minPt, maxPt;
    pcl::getMinMax3D(*inputCloud, minPt, maxPt);
    float yRange = maxPt.y - minPt.y;
    float frameHeight = yRange / numFrames;

    std::cout << "Y coordinate range: [" << minPt.y << ", " << maxPt.y << "]" << std::endl;
    std::cout << "Frame height: " << frameHeight << std::endl;

    // 分割点云
    for (const PointT& point : *inputCloud) {
        // 计算点属于哪一帧
        int frameIndex = static_cast<int>((point.y - minPt.y) / frameHeight);
        
        // 确保索引在有效范围内
        frameIndex = std::max(0, std::min(numFrames - 1, frameIndex));
        
        result[frameIndex]->push_back(point);
    }

    // 输出各帧点数
    for (int i = 0; i < numFrames; ++i) {
        std::cout << "Frame " << i << " contains " << result[i]->size() << " points." << std::endl;
    }

    return result;
}

void savePointClouds(const std::vector<PointCloudT::Ptr>& clouds, const std::string& baseFilename) {
    for (size_t i = 0; i < clouds.size(); ++i) {
        std::string filename = baseFilename + std::to_string(i) + ".ply";
        if (pcl::io::savePLYFileASCII(filename, *clouds[i]) == -1) {
            std::cerr << "Error saving file " << filename << std::endl;
        } else {
            std::cout << "Saved " << filename << " with " << clouds[i]->size() << " points." << std::endl;
        }
    }
}