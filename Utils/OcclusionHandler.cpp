//
// Created by Ars Poyezzhayev on 21.11.16.
//

#include "OcclusionHandler.h"

bool OcclusionHandler::isMerge(cv::Rect blob1, cv::Rect blob2, cv::Rect potentialMerge) {
    return (blob1 & potentialMerge).area() > threshold && (blob2 & potentialMerge).area() > threshold;
}

std::vector<cv::Rect> OcclusionHandler::findAllMerges(std::vector<cv::Rect> blobs) {
    std::vector<cv::Rect> merges;
    //Checks the collisions by pairs of the rectangles
    if (buffer.size() != 0 && blobs.size() != 0){
        for (int i = 0; i < buffer.size()-1; ++i) {
            for (int j = i+1; j < buffer.size(); ++j) {
                for (int k = 0; k < blobs.size(); ++k) {
                    if (isMerge(buffer[i], buffer[j], blobs[k])){
                        merges.push_back(blobs[k]);
                    };
                }
            }
        }
    }
    return merges;
}

void OcclusionHandler::fillBuffer(std::vector<cv::Rect> buffer) {
    this->buffer = buffer;
}

std::vector<cv::Rect> OcclusionHandler::findAllSplits(std::vector<cv::Rect> blobs) {
    std::vector<cv::Rect> splits;
    if (buffer.size() != 0 && blobs.size() != 0){
        for (int i = 0; i < blobs.size()-1; ++i) {
            for (int j = i+1; j < blobs.size(); ++j) {
                for (int k = 0; k < buffer.size(); ++k) {
                    if (isMerge(blobs[i], blobs[j], buffer[k])){
                        splits.push_back(buffer[k]);
                    };
                }
            }
        }
    }
    return splits;
}

// ==========================Incomplete=================================
int calculateIntersection(cv::Rect blob1, cv::Rect blob2){
    return (blob1 & blob2).area();
}

void findMerges(std::vector<Track> tracks, std::vector<cv::Rect> detections){
    int intersections[tracks.size()][detections.size()];
    //form the intersections matrix
    for (int i = 0; i < tracks.size(); ++i) {
        for (int j = 0; j < detections.size(); ++j) {
            intersections[i][j] = (tracks[i].getLastRect() & detections[j]).area();
        }
    }

    //find merges
    for (int k = 0; k < tracks.size(); ++k) {
        for (int i = 0; i < detections.size(); ++i) {

        }
    }


}