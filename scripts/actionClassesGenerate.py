import os
from actionsGenerate import *
from actionDecoderGenerate import *

file = sys.argv[1]
dir = os.path.dirname(sys.argv[0]) + "/../ActionMessage/"
classes = configCsvParse(file)
for nextClass in classes:
    classGenerate(dir, nextClass)
