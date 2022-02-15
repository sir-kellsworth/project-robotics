#!/usr/bin/python3

import csv
import os
import sys

actionDecoderHeaderTemplate = "../ActionMessage/ActionDecoder.h.template"
actionDecoderSourceTemplate = "../ActionMessage/ActionDecoder.cpp.template"
classNameTemplate = "${CLASS_NAME}"
definitionNameTemplate = "${DEFINITION_NAME}"
getterTemplate = "${GETTER}"
memberTemplate = "${MEMBER_VARIABLES}"
paramListTemplate = "${PARAM_LIST}"
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
                nextIndex = nextIndex + "sizeof(" + namespace + "::SIZE_PARAM_" + str(index) + ")"

            nextIndex = nextIndex + ");\n"
            paramsIndex = paramsIndex + nextIndex
            index += 1

    return paramsIndex

#******************************************************************************
def getterSourceGenerate(params, namespace):
    getter = ""
    if len(params) > 0:
        index = 0
        for param in params:
            getter = getter + "\t\t*reinterpret_cast<" + param['type'] + "*>(&m_data[" \
                + "INDEX_PARAM_" + str(index) + "]),\n"
            index += 1
        getter = getter[:-2]

    return getter


#******************************************************************************
def headerGenerate(classInfo):
    templateString = ""
    decoderName = classInfo['className'] + "Decoder"
    with open(actionDecoderHeaderTemplate, 'r') as file:
        templateString = file.read()
        templateString = templateString.replace(classNameTemplate, decoderName)
        templateString = templateString.replace(definitionNameTemplate, classInfo['className'])

    return templateString


#******************************************************************************
def sourceGenerate(classInfo):
    templateString = ""
    decoderName = classInfo['className'] + "Decoder"
    definitionNamespace = "ActionMessage::" + classInfo['className']
    with open(actionDecoderSourceTemplate, 'r') as file:
        templateString = file.read()
        templateString = templateString.replace(classNameTemplate, decoderName)
        templateString = templateString.replace(definitionNameTemplate, definitionNamespace)
        paramsIndex = paramsIndexSourceGenerate(classInfo['params'], classInfo['namespace'])
        templateString = templateString.replace(indexParamsTemplate, paramsIndex)
        definitionGetString = getterSourceGenerate(classInfo['params'], classInfo['namespace'])
        templateString = templateString.replace(paramListTemplate, definitionGetString)

    return templateString


#******************************************************************************
def classGenerate(dir, classInfo):
    header = headerGenerate(classInfo)
    source = sourceGenerate(classInfo)
    className = os.path.join(dir, classInfo['className'] + "Decoder")
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
