import wradlib as wrl
import numpy as np
import json

print("Hello from Python file")

def get_vol_data(volPath):
    rbdict = wrl.io.read_rainbow(
        volPath, loaddata=True
    )
    return rbdict["volume"]


class NumpyArrayEncoder(json.JSONEncoder):
    def default(self, obj):
        if isinstance(obj, np.ndarray):
            return obj.tolist()  # Convert NumPy array to a Python list
        return super(NumpyArrayEncoder, self).default(obj)


def get_json_file(volPath):
    data = get_vol_data(volPath)
    json_data = json.dumps(data, cls=NumpyArrayEncoder)
    return json_data

