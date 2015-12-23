/*
 * Copyright (C) 2015 Marcus Soll
 * This file is part of fooling_dnn.
 *
 * fooling_dnn is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * fooling_dnn is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with fooling_dnn. If not, see <http://www.gnu.org/licenses/>.
 */

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
