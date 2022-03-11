#!/usr/bin/python3

import csv
import os
import sys

actionEncoderHeaderTemplate = "../ActionMessage/ActionEncoder.h.template"
actionEncoderSourceTemplate = "../ActionMessage/ActionEncoder.cpp.template"
classNameTemplate = "${CLASS_NAME}"
definitionNameTemplate = "${DEFINITION_NAME}"
encoderSetTemplate = "${MEMCPY_STATEMENTS}"
memberTemplate = "${MEMBER_VARIABLES}"
indexParamsTemplate = "${INDEX_PARAMS}"


#******************************************************************************
def paramsIndexSourceGenerate(params, namespace):
    paramsIndex = ""
    if len(params) > 0:
        startIndex = 2
        index = 0
        for param in params:
            nextIndex = "\tconst uint16_t INDEX_PARAM_" + str(index) \
                + "("
            if index == 0:
                nextIndex = nextIndex + str(startIndex)
            else:
                nextIndex = nextIndex + "INDEX_PARAM_" + str(index-1) + " + "
                nextIndex = nextIndex + namespace + "::SIZE_PARAM_" + str(index)

            nextIndex = nextIndex + ");\n"
            paramsIndex = paramsIndex + nextIndex
            index += 1

    return paramsIndex


#******************************************************************************
def encoderSourceGenerate(params, namespace):
    encoder = ""
    if len(params) > 0:
        index = 0
        for param in params:
            encoder = encoder + "\t" + param['type'] + " " + param['name'] \
                + " = m_action->" + param['name'] + "Get();\n"
        for param in params:
            encoder = encoder + "\tmemcpy(&data[INDEX_PARAM_" + str(index) + "], &" \
                + param['name'] + ", sizeof(" + param['type'] + "));\n"
            index += 1

    return encoder


#******************************************************************************
def headerGenerate(classInfo):
    templateString = ""
    EncoderName = classInfo['className'] + "Encoder"
    with open(actionEncoderHeaderTemplate, 'r') as file:
        templateString = file.read()
        templateString = templateString.replace(classNameTemplate, EncoderName)
        templateString = templateString.replace(definitionNameTemplate, classInfo['className'])

    return templateString


#******************************************************************************
def sourceGenerate(classInfo):
    templateString = ""
    EncoderName = classInfo['className'] + "Encoder"
    definitionNamespace = "ActionMessage::" + classInfo['className']
    with open(actionEncoderSourceTemplate, 'r') as file:
        templateString = file.read()
        templateString = templateString.replace(classNameTemplate, EncoderName)
        templateString = templateString.replace(definitionNameTemplate, definitionNamespace)
        paramsIndex = paramsIndexSourceGenerate(classInfo['params'], classInfo['namespace'])
        templateString = templateString.replace(indexParamsTemplate, paramsIndex)
        encoderSetString = encoderSourceGenerate(classInfo['params'], classInfo['namespace'])
        templateString = templateString.replace(encoderSetTemplate, encoderSetString)

    return templateString


#******************************************************************************
def classGenerate(dir, classInfo):
    header = headerGenerate(classInfo)
    source = sourceGenerate(classInfo)
    className = os.path.join(dir, classInfo['className'] + "Encoder")
    with open(className + ".h", 'w') as headerFile:
        headerFile.write(header)
    with open(className + ".cpp", 'w') as sourceFile:
        sourceFile.write(source)


#******************************************************************************
def paramsGenerate(params):
    paramsList = ""
    if len(params) > 0:
        paramsList = "\n"
        for param in params:
            paramsList = paramsList + "\t" + param['type'] + " " + param['name'] + ",\n"

        paramsList = paramsList[:-2]

    return paramsList


#******************************************************************************
def configCsvParse(file):
    classes = []
    with open(file, 'r')as file:
      csvFile = csv.reader(file)
      next(csvFile, None)
      typeIdIndex = 0
      for line in csvFile:
        nextClass = {}
        nextClass['className'] = line[0].strip()
        numParams = int(line[1])
        nextClass['numParams'] = numParams
        nextClass['namespace'] = "ActionMessage::" + nextClass['className']
        nextClass['typeIdIndex'] = str(typeIdIndex)
        typeIdIndex += 1
        params = []
        for i in range(numParams):
            index = i * 2
            params.append({
                'type' : line[2 + index].strip(),
                'name' : line[2 + index + 1].strip()})

        nextClass['params'] = params
        classes.append(nextClass)

    return classes


file = sys.argv[1]
dir = os.path.dirname(sys.argv[0]) + "/../ActionMessage/"
classes = configCsvParse(file)
for nextClass in classes:
    classGenerate(dir, nextClass)
