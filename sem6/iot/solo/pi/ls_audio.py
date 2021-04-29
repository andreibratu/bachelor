import pyaudio

p = pyaudio.PyAudio()
device_count = p.get_device_count()
for i in range(0, device_count):
    print("Name: " + p.get_device_info_by_index(i)["name"])
    print("Index: " + str(p.get_device_info_by_index(i)["index"]))
    print("\n")