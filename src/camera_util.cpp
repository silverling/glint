#include "camera_util.h"

#include <opencv2/imgproc.hpp>

namespace App {

CameraUtil::CameraUtil(CameraInitType type, const std::string &source, Engine::Engine &engine) : engine(engine) {
    // Connect camera
    source_ = {.type = type, .source = source};
    switch (type) {
    case CameraInitType::FromSerial: {
        this->camera = Metavision::Camera::from_serial(source);
        break;
    }
    case CameraInitType::FromFile: {
        this->camera = Metavision::Camera::from_file(source);
        break;
    }
    default:
        throw std::runtime_error("Unknown camera initialization type");
    }

    // Init image
    this->width = this->camera.geometry().get_width();
    this->height = this->camera.geometry().get_height();
    this->image = cv::Mat(this->width, this->height, CV_8UC4, cv::Scalar(255, 255, 255, 255));

    // Init texture
    this->texture = this->engine.createTexture(this->width, this->height);
    this->engine.updateTexture(this->texture, this->image);

    // Create frame generator
    this->frameGenerator = new Metavision::CDFrameGenerator(this->width, this->height);
    this->frameGenerator->set_display_accumulation_time_us(10000);

    // Set up frame generator callback
    this->camera.cd().add_callback([&](const Metavision::EventCD *begin, const Metavision::EventCD *end) {
        std::unique_lock<std::mutex> lock(frameGeneratorMutex);
        frameGenerator->add_events(begin, end);
    });

    // Set up output callback for frame generator
    this->frameGenerator->start(30, [&](const Metavision::timestamp &, const cv::Mat &frame) {
        if (paused_)
            return;
        std::unique_lock<std::mutex> lock(this->imageMutex, std::try_to_lock);
        if (lock.owns_lock()) {
            cv::cvtColor(frame, this->image, cv::COLOR_BGR2RGBA);
        }
    });
}

std::unique_ptr<CameraUtil> CameraUtil::from_serial(const std::string &serial, Engine::Engine &engine) {
    return std::unique_ptr<CameraUtil>(new CameraUtil(CameraInitType::FromSerial, serial, engine));
}

std::unique_ptr<CameraUtil> CameraUtil::from_file(const std::string &file_path, Engine::Engine &engine) {
    return std::unique_ptr<CameraUtil>(new CameraUtil(CameraInitType::FromFile, file_path, engine));
}

CameraUtil::~CameraUtil() {
    if (this->frameGenerator) {
        this->frameGenerator->stop();
        delete this->frameGenerator;
        this->frameGenerator = nullptr;
    }

    this->camera.stop_recording(); // Stop all ongoing recordings
    if (this->camera.is_running()) {
        this->camera.stop();
    }

    this->engine.destroyTexture(this->texture);
}

bool CameraUtil::startRecording(const std::filesystem::path &file_path) {
    if (source_.type == CameraInitType::FromFile) {
        return false;
    }
    return this->camera.start_recording(file_path);
}

bool CameraUtil::stopRecording(const std::filesystem::path &file_path) {
    if (source_.type == CameraInitType::FromFile) {
        return false;
    }
    return this->camera.stop_recording(file_path);
}

void CameraUtil::update() {
    std::unique_lock<std::mutex> lock(this->imageMutex);
    this->engine.updateTexture(this->texture, this->image);
}

} // namespace App