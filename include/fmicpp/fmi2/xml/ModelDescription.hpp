/*
 * The MIT License
 *
 * Copyright 2017-2018 Norwegian University of Technology
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING  FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef FMICPP_MODELDESCRIPTION_HPP
#define FMICPP_MODELDESCRIPTION_HPP

#include <memory>
#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include "DefaultExperiment.hpp"
#include "SourceFiles.hpp"
#include "ModelVariables.hpp"

using std::string;
using std::unique_ptr;
using boost::property_tree::ptree;

namespace fmicpp::fmi2::xml {

    struct FmuData {

        string modelIdentifier;

        bool canGetAndSetFMUstate;
        bool canSerializeFMUstate;
        bool needsExecutionTool;
        bool canNotUseMemoryManagementFunctions;
        bool canBeInstantiatedOnlyOncePerProcess;
        bool providesDirectionalDerivative;

        unique_ptr<SourceFiles> sourceFiles = nullptr;

        virtual void load(ptree &node);

    };

    struct CoSimulation: FmuData {

        int maxOutputDerivativeOrder;

        bool canInterpolateInputs;
        bool canRunAsynchronuously;
        bool canHandleVariableCommunicationStepSize;

        void load(ptree &node);

    };

    struct ModelExchange: FmuData {

        int numberOfEventIndicators;
        bool completedIntegratorStepNotNeeded;

        void load(ptree &node);

    };

    struct ModelDescription {

        string guid;
        string fmiVersion;
        string modelName;
        string description;
        string version;
        string author;
        string license;
        string copyright;
        string generationTool;
        string generationDateAndTime;

        int numberOfEventIndicators;

        unique_ptr<CoSimulation> coSimulation = nullptr;
        unique_ptr<ModelExchange> modelExchange = nullptr;
        unique_ptr<DefaultExperiment> defaultExperiment = nullptr;
        unique_ptr<ModelVariables> modelVariables = nullptr;

        void load(string fileName);

    };

}

#endif //FMICPP_MODELDESCRIPTION_HPP