#!/usr/bin/env bash

pushd $HOME/Downloads

python3 "$1"

if [ $? -ne 0 ]; then
  echo "An error occurred while trying to download the Vulkan SDK"
else
  hdiutil attach -quiet vulkansdk.dmg
  open /Volumes/VulkanSDK/InstallVulkan.app
fi

popd