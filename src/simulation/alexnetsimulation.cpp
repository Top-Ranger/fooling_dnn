#include "alexnetsimulation.h"

#include <QtCore/qmath.h>

caffe::Net<float> *AlexNetSimulation::_alexnet = NULL;
QMutex *AlexNetSimulation::_mutex = new QMutex();

using namespace caffe;

namespace {

}

AlexNetSimulation::AlexNetSimulation(config config) :
    _config(config),
    _class(-1)
{
}

AlexNetSimulation::~AlexNetSimulation()
{
}

qint32 AlexNetSimulation::needInputLength()
{
    return 0;
}

qint32 AlexNetSimulation::needOutputLength()
{
    return 0;
}

GenericSimulation *AlexNetSimulation::createConfigCopy()
{
    return new AlexNetSimulation(_config);
}

qint32 AlexNetSimulation::getClass()
{
    return _class;
}

void AlexNetSimulation::_initialise()
{
    _network->initialise(_gene);

    Caffe::set_mode(Caffe::CPU);
    Caffe::set_phase(Caffe::TEST);

    _mutex->lock();
    if(_alexnet == NULL)
    {
        _alexnet = new Net<float>(_config.proto_path.c_str());
        _alexnet->CopyTrainedLayersFrom(_config.caffemodel_path.c_str());
    }
    _mutex->unlock();
}

double AlexNetSimulation::_getScore()
{
    // Read image
    _network->processInput(QList<double>());

    Datum datum;
    if(!ReadImageToDatum(_config.image_path.c_str(), 1, 227, 227, true, &datum))
    {
        QNN_CRITICAL_MSG("Can not read image" << QString::fromStdString(_config.image_path));
        return -1;
    }

    Blob<float>* blob = new Blob<float>(1, datum.channels(), datum.height(), datum.width());
    BlobProto blob_proto;
    blob_proto.set_num(1);
    blob_proto.set_channels(datum.channels());
    blob_proto.set_height(datum.height());
    blob_proto.set_width(datum.width());
    qint32 size = qMax((int) datum.data().size(), datum.float_data_size());
    for (qint32 i = 0; i < size; ++i)
    {
        blob_proto.add_data(0.0);
    }
    const std::string& data = datum.data();
    if (data.size() != 0)
    {
        for (qint32 i = 0; i < size; ++i)
        {
            blob_proto.set_data(i, blob_proto.data(i) + (uint8_t)data[i]);
        }
    }

    blob->FromProto(blob_proto);

    std::vector<Blob<float>*> v;
    v.push_back(blob);

    _mutex->lock();
    // Calculate result
    float f = 0.0;
    const vector<Blob<float>*>& result = _alexnet->Forward(v, &f);
    _mutex->unlock();

    // Find maximum
    float max = -1;
    _class = -1;

    for(quint32 i = 0; i < result.size(); ++i)
    {
        if(result[0]->cpu_data()[i] > max)
        {
            max = result[0]->cpu_data()[i];
            _class = i;
        }
    }

    // Clean up
    v.clear();
    delete blob;

    // Score = confidence = maximum output
    return max;
}


