import urllib.request
import json
import hashlib

url = "https://vulkan.lunarg.com/sdk/files.json"
sha256 = hashlib.sha256()

try:
    with urllib.request.urlopen(url) as response:
        json_content = response.read().decode('utf-8')

    json_data = json.loads(json_content)["linux"]
    latest = []
    for version in json_data.keys():
        splitted = str(version).split('.')
        if len(latest) == 0:
            latest = splitted
            continue
        for i in range(0, 4):
            if latest[i] < splitted[i]:
                latest = splitted
                break
    latest = '.'.join(latest)
    file_name = json_data[latest].files[0].file_name
    sha = json_data[latest].files[0].sha
    tar_url = "https://sdk.lunarg.com/sdk/download/{v}/linux/vulkansdk-linux-x86_64-{v}.tar.gz".format(v=latest)

    with urllib.request.urlopen(tar_url) as response:
        print("Downloading latest Vulkan SDK (" + str(int(json_data[latest].files[0].size/1024/1024)) + "MB) version " + latest)
        tarball = response.read()

    sha256.update(tarball)
    checksum = sha256.hexdigest()
    if sha != checksum:
        user_response = input("Downloaded SDK failed to match checksum. Do you want to install anyways? y/(N): ")
        if user_response != "y" or user_response != "Y":
            exit(0)
    with open('vulkansdk.tar.gz', 'wb') as file:
        file.write(tarball)
except urllib.error.URLError as e:
    exit(1)
except json.JSONDecodeError as e:
    exit(1)