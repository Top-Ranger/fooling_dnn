#ifndef ALEXNETSIMULATION_H
#define ALEXNETSIMULATION_H

#include <simulation/genericsimulation.h>

#include <caffe/caffe.hpp>
#include <caffe/util/io.hpp>
#include <caffe/blob.hpp>
#include <string>
#include <QMutex>

class AlexNetSimulation : public GenericSimulation
{
public:
    struct config {
        std::string image_path;
        std::string proto_path;
        std::string caffemodel_path;

        config() :
            image_path("./image.png"),
            proto_path("./deploy.prototxt"),
            caffemodel_path("./bvlc_alexnet.caffemodel")
        {
        }
    };

    AlexNetSimulation(config config = config());
    ~AlexNetSimulation();

    qint32 needInputLength();
    qint32 needOutputLength();
    GenericSimulation *createConfigCopy();

    qint32 getClass();

protected:
    void _initialise();
    double _getScore();

private:
    config _config;
    qint32 _class;

    // Use only one instance for memory reasons
    static caffe::Net<float> *_alexnet;
    static QMutex *_mutex;

};

#endif // ALEXNETSIMULATION_H
