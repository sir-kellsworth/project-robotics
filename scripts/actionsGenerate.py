#!/usr/bin/python3

import csv
import os
import sys

actionHeaderTemplate = "../ActionMessage/Action.h.template"
actionSourceTemplate = "../ActionMessage/Action.cpp.template"
actionDecoderHeaderTemplate = "../ActionMessage/ActionDecoder.h.template"
actionDecoderSourceTemplate = "../ActionMessage/ActionDecoder.cpp.template"
classNameTemplate = "${CLASS_NAME}"
paramListTemplate = "${PARAM_LIST}"
gettersTemplate = "${GETTERS}"
settersTemplate = "${SETTERS}"
typeIdTemplate = "${TYPE_ID}"
packetSizeTemplate = "${PACKET_SIZE}"
memberTemplate = "${MEMBER_VARIABLES}"
sizeParamsTemplate = "${SIZE_PARAMS}"
methodSeparater = "//*****************************************************************************"


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
def memberVariablesGenerate(params):
    paramsList = ""
    if len(params) > 0:
        for param in params:
            paramsList = paramsList + "\t" + param['type'] + " m_" + param['name'] + ";\n"

    return paramsList


#******************************************************************************
def memberVariablesSourceGenerate(params):
    memberInits = ""
    if len(params) > 0:
        memberInits = ":"
        for param in params:
            memberInits = memberInits + "m_" + param['name'] + "(" + param['name'] + "),\n"

    memberInits = memberInits[:-2]
    return memberInits


#******************************************************************************
def packetSizeGet(params):
    #needs to be at least 1
    packetSize = "1"
    for param in params:
        packetSize += " + sizeof(" + param['type'] + ")"

    return packetSize


#******************************************************************************
def sizeParamsHeaderGet(params):
    paramsSize = ""
    index = 0
    if len(params) > 0:
        for param in params:
            paramsSize = paramsSize + "\tstatic const uint8_t SIZE_PARAM_" + str(index) + ";\n"
            index += 1

    return paramsSize


#******************************************************************************
def sizeParamsSourceGet(params, namespace):
    paramsSize = ""
    index = 0
    if len(params) > 0:
        for param in params:
            paramsSize = paramsSize + "const uint8_t " + namespace + "::SIZE_PARAM_" + str(index) \
                + " = sizeof(" + param['type'] + ");\n"
            index += 1

    return paramsSize


#******************************************************************************
def gettersSourceGenerate(params, namespace):
    getters = ""
    if len(params) > 0:
        for param in params:
            getters = getters + methodSeparater + \
                "\n" + param['type'] + " " + namespace + "::" + param['name'] + "Get()" + \
                "\n{" + \
                "\n\treturn m_" + param['name'] + ";" + \
                "\n}\n\n"

    return getters


#******************************************************************************
def settersSourceGenerate(params, namespace):
    setters = ""
    if len(params) > 0:
        for param in params:
            setters = setters + methodSeparater + \
                "\nvoid " + namespace + "::" + param['name'] + "Set" + \
                "\n(\n" + \
                "\n\tconst " + param['type'] + "& " + param['name'] + \
                "\n)" + \
                "\n{" + \
                "\n\tm_" + param['name'] + " = " + param['name'] + ";" + \
                "\n}\n\n"

    return setters


#******************************************************************************
def gettersProtoGenerate(params):
    getters = ""
    if len(params) > 0:
        for param in params:
            getters = getters + \
                "\n" + param['type'] + " " + param['name'] + "Get();" + \
                "\n"

    return getters


#******************************************************************************
def settersProtoGenerate(params):
    setters = ""
    if len(params) > 0:
        for param in params:
            setters = setters + \
                "\nvoid " + param['name'] + "Set(" + \
                "\n\tconst " + param['type'] + "& " + param['name'] + ");" + \
                "\n"

    return setters


#******************************************************************************
def headerGenerate(classInfo):
    templateString = ""
    with open(actionHeaderTemplate, 'r') as file:
        templateString = file.read()
        templateString = templateString.replace(classNameTemplate, classInfo['className'])
        params = paramsGenerate(classInfo['params'])
        templateString = templateString.replace(paramListTemplate, params)
        memberVariables = memberVariablesGenerate(classInfo['params'])
        templateString = templateString.replace(memberTemplate, memberVariables)
        getters = gettersProtoGenerate(classInfo['params'])
        templateString = templateString.replace(gettersTemplate, getters)
        setters = settersProtoGenerate(classInfo['params'])
        templateString = templateString.replace(settersTemplate, setters)
        paramsSize = sizeParamsHeaderGet(classInfo['params'])
        templateString = templateString.replace(sizeParamsTemplate, paramsSize)

    return templateString


#******************************************************************************
def sourceGenerate(classInfo):
    templateString = ""
    with open(actionSourceTemplate, 'r') as file:
        templateString = file.read()
        templateString = templateString.replace(classNameTemplate, classInfo['className'])
        templateString = templateString.replace(typeIdTemplate, classInfo['typeIdIndex'])
        packetSize = packetSizeGet(classInfo['params'])
        templateString = templateString.replace(packetSizeTemplate, packetSize)
        namespace = classInfo['namespace']
        paramsSize = sizeParamsSourceGet(classInfo['params'], namespace)
        templateString = templateString.replace(sizeParamsTemplate, paramsSize)
        params = paramsGenerate(classInfo['params'])
        templateString = templateString.replace(paramListTemplate, params)
        memberInit = memberVariablesSourceGenerate(classInfo['params'])
        templateString = templateString.replace(memberTemplate, memberInit)
        getters = gettersSourceGenerate(classInfo['params'], namespace)
        templateString = templateString.replace(gettersTemplate, getters)
        setters = settersSourceGenerate(classInfo['params'], namespace)
        templateString = templateString.replace(settersTemplate, setters)

    return templateString


#******************************************************************************
def classGenerate(dir, classInfo):
    header = headerGenerate(classInfo)
    source = sourceGenerate(classInfo)
    className = os.path.join(dir, classInfo['className'])
    with open(className + ".h", 'w') as headerFile:
        headerFile.write(header)
    with open(className + ".cpp", 'w') as sourceFile:
        sourceFile.write(source)


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
