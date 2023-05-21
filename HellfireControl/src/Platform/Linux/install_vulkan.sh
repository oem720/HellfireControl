#!/usr/bin/env bash

mkdir /opt
pushd /opt

python3 "$1"

if [ $? -ne 0 ]; then
  echo "An error occurred while trying to download the Vulkan SDK"
else
  tar -xzf vulkansdk.tar.gz -C ./vulkan
  rm vulkansdk.tar.gz

  pushd vulkan
  for file in "$PWD"/include/vulkan/*; do
    sudo ln -s "$file" /usr/local/include/"$(basename "$file")"
  done
  for file in "$PWD"/lib/libvulkan.so*; do
    sudo ln -s "$file" /usr/local/lib/"$(basename "$file")"
  done
  for file in "$PWD"/lib/libVkLayer_*.so; do
    sudo ln -s "$file" /usr/local/lib/"$(basename "$file")"
  done
  sudo mkdir -p /usr/local/share/vulkan/explicit_layer.d
  for file in "$PWD"/etc/vulkan/explicit_layer.d/VkLayer_*.json; do
    sudo ln -s "$file" /usr/local/share/vulkan//explicit_layer.d/"$(basename "$file")"
  done
  sudo ldconfig
  echo "Vulkan installed successfully"
fi

popd
popd